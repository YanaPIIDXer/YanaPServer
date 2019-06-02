#include "Servlet/Secure/SSLHandshake.h"
#include "Servlet/ServletPeer.h"
#include "Util/Stream/MemoryStreamReader.h"
#include "Util/RandomString.h"
#include <random>
#include "Util/Stream/MemorySizeCaliculator.h"
#include "Util/Secure/Base64.h"
#include <fstream>

#include <iostream>

using namespace YanaPServer::Util::Stream;
using namespace YanaPServer::Servlet::Secure::Packet;
using namespace YanaPServer::Util;
using namespace YanaPServer::Util::Secure;

namespace YanaPServer
{
namespace Servlet
{
namespace Secure
{

// コンストラクタ
CSSLHandshake::CSSLHandshake(CServletPeer *pInPeer)
	: pPeer(pInPeer)
	, bIsProcessing(false)
	, Version(0)
	, CurrentState(ESendState::ServerHello)
{
}

// デストラクタ
CSSLHandshake::~CSSLHandshake()
{
}

// 受信した
void CSSLHandshake::OnRecv(const char *pData, unsigned int Size)
{
	CMemoryStreamReader StreamReader(pData, Size);
	OnRecvData(&StreamReader);
}


// データを受信した。
void CSSLHandshake::OnRecvData(IMemoryStream *pStream)
{
	CSSLRecord Record;
	if (!Record.Serialize(pStream))
	{
		bIsProcessing = false;
		pPeer->Disconnect();
		return;
	}

	printf("Type:%02X\n", Record.Type);
	std::cout << "Length:" << Record.Length << std::endl;
	switch (Record.Type)
	{
		case 0x16:
			{
				CSSLHandshakeRecord HandshakeRecord;
				if (!HandshakeRecord.Serialize(pStream))
				{
					bIsProcessing = false;
					pPeer->Disconnect();
					return;
				}

				printf("MessageType:0x%02X\n", HandshakeRecord.MessageType);

				switch (HandshakeRecord.MessageType)
				{
					case EMessageType::ClientHello:

						OnRecvClientHello(pStream);
						SendServerCertificate();
						SendServerHelloDone();
						break;

					case EMessageType::ClientKeyExchange:

						OnRecvClientKeyExchange(pStream);
						OnRecvData(pStream);
						break;
				}
			}
			break;

		case 0x14:

			{
				unsigned char Type = 0;
				if (!pStream->Serialize(&Type))
				{
					bIsProcessing = false;
					pPeer->Disconnect();
					return;
				}

				switch (Type)
				{
					case 0x01:

						// ChangeCipherSpec受信.
						OnRecvEncryptedData(pStream);
						break;
				}
			}
			break;
	}
}

// 暗号化されたデータを受信した。
void CSSLHandshake::OnRecvEncryptedData(IMemoryStream *pStream)
{
	CSSLRecord Record;
	if (!Record.Serialize(pStream))
	{
		bIsProcessing = false;
		pPeer->Disconnect();
		return;
	}

	std::cout << "==== Recv Encrypted Data ====" << std::endl;
	printf("Type:%02X\n", Record.Type);
	std::cout << "Length:" << Record.Length << std::endl;

}

// ClientHelloを受信した。
void CSSLHandshake::OnRecvClientHello(IMemoryStream *pStream)
{
	bIsProcessing = true;

	CSSLClientHello ClientHello;
	if (!ClientHello.Serialize(pStream))
	{
		bIsProcessing = false;
		pPeer->Disconnect();
		return;
	}
	
	Version = ClientHello.ClientVersion;
	printf("Version:0x%04X\n", Version);

	unsigned short UseCipherSuite = ECipherSuite::TLS_RSA_WITH_3DES_EDE_CBC_SHA;
	bool bFound = false;
	for (auto CipherSuite : ClientHello.CipherSuite)
	{
		if (CipherSuite == UseCipherSuite)
		{
			bFound = true;
			break;
		}
	}
	if (!bFound)
	{
		std::cout << "Invalid Cipher Suite." << std::endl;
		bIsProcessing = false;
		pPeer->Disconnect();
		return;
	}

	memcpy(ClientRandom, ClientHello.Random, 28);

	CurrentState = ESendState::ServerHello;

	CRandomString RandomStr;
	RandomStr.Generate(28);

	CSSLServerHello ServerHello;
	ServerHello.Version = ClientHello.ClientVersion;
	ServerHello.Time = ClientHello.Time;
	memcpy(ServerRandom, RandomStr.Get(), 28);
	memcpy(ServerHello.Random, ServerRandom, 28);
	/*
	std::random_device Rnd;
	for (int i = 0; i < 10; i++)
	{
		ServerHello.SessionId.push_back(Rnd() % 255);
	}
	*/
	ServerHello.CipherSuite = UseCipherSuite;
	ServerHello.CompressionMethod = 0;

	SendHandshakePacket(EMessageType::ServerHello, &ServerHello);
	CurrentState = ESendState::ServerCertificate;
}

// ServerCertificateを送信.
void CSSLHandshake::SendServerCertificate()
{
	std::ifstream FileStream("Certificate/server.crt", std::ios::in);
	if (!FileStream)
	{
		std::cout << "CRT File Load Failed." << std::endl;
		bIsProcessing = false;
		pPeer->Disconnect();
		return;
	}

	std::string CrtData = "";

	while (!FileStream.eof())
	{
		static const unsigned int BufferSize = 5096;
		char Buffer[BufferSize];
		memset(Buffer, 0, BufferSize);
		FileStream.getline(Buffer, BufferSize);
		CrtData += Buffer;
	}

	// Base64でエンコードされている箇所のみを取り出す。
	std::string FindText = "-----BEGIN CERTIFICATE-----";
	auto Pos = CrtData.find(FindText);
	if (Pos != std::string::npos)
	{
		CrtData.replace(Pos, FindText.length(), "");
	}
	FindText = "-----END CERTIFICATE-----";
	Pos = CrtData.find(FindText);
	if (Pos != std::string::npos)
	{
		CrtData.replace(Pos, FindText.length(), "");
	}

	// デコードしたデータを投げ付ける。
	std::vector<unsigned char> Decoded;
	if (!CBase64::Decode(CrtData, Decoded))
	{
		std::cout << "Certificate Base64 Decode Failed." << std::endl;
		bIsProcessing = false;
		pPeer->Disconnect();
		return;
	}

	CSSLServerCertificate ServerCertificate;
	ServerCertificate.CertificateList.push_back(Decoded);
	SendHandshakePacket(EMessageType::ServerCertificate, &ServerCertificate);

	// 秘密鍵もここで読み込んでおく。
	LoadPrivateKey();
	
	CurrentState = ESendState::ServerHelloDone;
}

// ServerHelloDoneを送信.
void CSSLHandshake::SendServerHelloDone()
{
	CSSLServerHelloDone ServerHelloDone;
	SendHandshakePacket(EMessageType::ServerHelloDone, &ServerHelloDone);

	CurrentState = ESendState::End;
}

// ClientKeyExchangeを受信した。
void CSSLHandshake::OnRecvClientKeyExchange(IMemoryStream *pStream)
{
	CSSLClientKeyExchange ClientKeyExchange;
	if (!ClientKeyExchange.Serialize(pStream))
	{
		bIsProcessing = false;
		pPeer->Disconnect();
		return;
	}
}

// ハンドシェイクパケットを送信.
void CSSLHandshake::SendHandshakePacket(unsigned char MessageType, YanaPServer::Util::ISerializable *pPacket)
{
	// レコード
	CSSLRecord Record;
	MakeSSLRecordPacket(pPacket, Record);
	pPeer->Send(&Record);

	// ハンドシェイクレコード
	CSSLHandshakeRecord HandshakeRecord;
	MakeSSLHandshakeRecordPacket(MessageType, pPacket, HandshakeRecord);
	pPeer->Send(&HandshakeRecord);
	
	// 本体
	pPeer->Send(pPacket);
}

// SSLRecordパケットを生成.
void CSSLHandshake::MakeSSLRecordPacket(YanaPServer::Util::ISerializable *pPacket, YanaPServer::Servlet::Secure::Packet::CSSLRecord &OutRecord)
{
	CMemorySizeCaliculator SizeCaliculator;
	pPacket->Serialize(&SizeCaliculator);

	OutRecord.Type = 0x16;
	OutRecord.Version = Version;
	OutRecord.Length = SizeCaliculator.GetSize() + 4;
}

// SSLハンドシェイクレコードパケットを生成
void CSSLHandshake::MakeSSLHandshakeRecordPacket(unsigned char MessageType, YanaPServer::Util::ISerializable *pPacket, YanaPServer::Servlet::Secure::Packet::CSSLHandshakeRecord &OutRecord)
{
	CMemorySizeCaliculator SizeCaliculator;
	pPacket->Serialize(&SizeCaliculator);

	OutRecord.MessageType = MessageType;
	OutRecord.BodyLength = SizeCaliculator.GetSize();
}

// 秘密鍵の読み込み
void CSSLHandshake::LoadPrivateKey()
{
	std::ifstream FileStream("Certificate/server.key", std::ios::in);
	if (!FileStream)
	{
		std::cout << "KEY File Load Failed." << std::endl;
		bIsProcessing = false;
		pPeer->Disconnect();
		return;
	}

	std::string KeyData = "";

	while (!FileStream.eof())
	{
		static const unsigned int BufferSize = 5096;
		char Buffer[BufferSize];
		memset(Buffer, 0, BufferSize);
		FileStream.getline(Buffer, BufferSize);
		KeyData += Buffer;
	}

	// Base64でエンコードされている箇所のみを取り出す。
	std::string FindText = "-----BEGIN RSA PRIVATE KEY-----";
	auto Pos = KeyData.find(FindText);
	if (Pos != std::string::npos)
	{
		KeyData.replace(Pos, FindText.length(), "");
	}
	FindText = "-----END RSA PRIVATE KEY-----";
	Pos = KeyData.find(FindText);
	if (Pos != std::string::npos)
	{
		KeyData.replace(Pos, FindText.length(), "");
	}

	if (!CBase64::Decode(KeyData, PrivateKey))
	{
		std::cout << "PrivateKey Base64 Decode Failed." << std::endl;
		bIsProcessing = false;
		pPeer->Disconnect();
		return;
	}
}

}
}
}
