#include "Servlet/Secure/SSLHandshake.h"
#include "Servlet/ServletPeer.h"
#include "Util/Stream/MemoryStreamReader.h"
#include "Util/RandomString.h"
#include <random>
#include "Util/Stream/MemorySizeCaliculator.h"
#include "Util/Secure/Base64.h"
#include <fstream>
#include "boost/uuid/name_generator_md5.hpp"
#include "boost/uuid/name_generator_sha1.hpp"

#include <iostream>

using namespace YanaPServer::Util::Stream;
using namespace YanaPServer::Servlet::Secure::Packet;
using namespace YanaPServer::Util;
using namespace YanaPServer::Util::Secure;
using namespace boost::multiprecision;
using namespace boost::uuids::detail;

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
		SendAlert(EAlertLevel::Fatal, EAlertDescription::HandshakeFailuer);
		return;
	}

	if (Record.Type == 0x80)
	{
		SendAlert(EAlertLevel::Fatal, EAlertDescription::CloseNotify);
		return;
	}

	printf("Type:%02X\n", Record.Type);
	std::cout << "Length:" << Record.Length << std::endl;
	switch (Record.Type)
	{
		case ERecordType::Handshake:
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

		case ERecordType::ChangeCipherSpec:

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
		SendAlert(EAlertLevel::Fatal, EAlertDescription::HandshakeFailuer);
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
		SendAlert(EAlertLevel::Fatal, EAlertDescription::HandshakeFailuer);
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
		SendAlert(EAlertLevel::Fatal, EAlertDescription::UnsupportedCertificate);
		return;
	}

	memcpy(ClientRandom, &ClientHello.Time, 4);
	memcpy(ClientRandom + 4, ClientHello.Random, 28);

	CRandomString RandomStr;
	RandomStr.Generate(28, true);

	CSSLServerHello ServerHello;
	ServerHello.Version = ClientHello.ClientVersion;
	ServerHello.Time = ClientHello.Time;
	memcpy(ServerHello.Random, RandomStr.Get(), 28);
	memcpy(ServerRandom, &ServerHello.Time, 4);
	memcpy(ServerRandom + 4, RandomStr.Get(), 28);
	std::random_device Rnd;
	for (int i = 0; i < 10; i++)
	{
		ServerHello.SessionId.push_back(Rnd() % 255);
	}
	ServerHello.CipherSuite = UseCipherSuite;
	ServerHello.CompressionMethod = 0;

	SendHandshakePacket(EMessageType::ServerHello, &ServerHello);
}

// ServerCertificateを送信.
void CSSLHandshake::SendServerCertificate()
{
	std::ifstream FileStream("Certificate/server.crt", std::ios::in);
	if (!FileStream)
	{
		std::cout << "CRT File Load Failed." << std::endl;
		SendAlert(EAlertLevel::Fatal, EAlertDescription::CertificateUnknown);
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
		SendAlert(EAlertLevel::Fatal, EAlertDescription::CertificateUnknown);
		return;
	}

	CSSLServerCertificate ServerCertificate;
	ServerCertificate.CertificateList.push_back(Decoded);
	SendHandshakePacket(EMessageType::ServerCertificate, &ServerCertificate);
}

// ServerHelloDoneを送信.
void CSSLHandshake::SendServerHelloDone()
{
	CSSLServerHelloDone ServerHelloDone;
	SendHandshakePacket(EMessageType::ServerHelloDone, &ServerHelloDone);
}

// ClientKeyExchangeを受信した。
void CSSLHandshake::OnRecvClientKeyExchange(IMemoryStream *pStream)
{
	CSSLClientKeyExchange ClientKeyExchange;
	if (!ClientKeyExchange.Serialize(pStream))
	{
		SendAlert(EAlertLevel::Fatal, EAlertDescription::HandshakeFailuer);
		return;
	}

	// 秘密鍵を読み込む。
	LoadPrivateKey();

	// プリマスタシークレットの復号化.
	cpp_int PreMasterSecret(ClientKeyExchange.PreMasterSecret);
	cpp_int Prime1(PrivateKey.BERs[0]->Children[4]->Content);
	cpp_int Prime2(PrivateKey.BERs[0]->Children[5]->Content);
	PreMasterSecret = DecriptPreMasterSecret(PreMasterSecret, Prime1, Prime2);

	// マスタシークレット計算.
	MasterSecret = CalcMasterSecret(PreMasterSecret);
	std::cout << "Master Secret:" << MasterSecret << std::endl;
}

// ハンドシェイクパケットを送信.
void CSSLHandshake::SendHandshakePacket(unsigned char MessageType, YanaPServer::Util::ISerializable *pPacket)
{
	// レコード
	CSSLRecord Record;
	MakeSSLRecordPacket(ERecordType::Handshake, pPacket, Record);
	pPeer->Send(&Record);

	// ハンドシェイクレコード
	CSSLHandshakeRecord HandshakeRecord;
	MakeSSLHandshakeRecordPacket(MessageType, pPacket, HandshakeRecord);
	pPeer->Send(&HandshakeRecord);
	
	// 本体
	pPeer->Send(pPacket);
}

// SSLRecordパケットを生成.
void CSSLHandshake::MakeSSLRecordPacket(ERecordType Type, YanaPServer::Util::ISerializable *pPacket, YanaPServer::Servlet::Secure::Packet::CSSLRecord &OutRecord)
{
	CMemorySizeCaliculator SizeCaliculator;
	pPacket->Serialize(&SizeCaliculator);

	OutRecord.Type = Type;
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
		SendAlert(EAlertLevel::Fatal, EAlertDescription::CertificateUnknown);
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

	std::vector<unsigned char> Data;
	if (!CBase64::Decode(KeyData, Data))
	{
		std::cout << "PrivateKey Base64 Decode Failed." << std::endl;
		SendAlert(EAlertLevel::Fatal, EAlertDescription::CertificateUnknown);
		return;
	}

	CMemoryStreamReader StreamReader((char *)&Data[0], Data.size());
	if (!PrivateKey.Serialize(&StreamReader))
	{
		std::cout << "PrivateKey Serialize Failed." << std::endl;
		SendAlert(EAlertLevel::Fatal, EAlertDescription::CertificateUnknown);
		return;
	}
}

// Alertを送信.
void CSSLHandshake::SendAlert(EAlertLevel Level, EAlertDescription Description)
{
	CSSLAlert Alert;
	Alert.Level = Level;
	Alert.Description = Description;

	CSSLRecord Record;
	MakeSSLRecordPacket(ERecordType::Alert, &Alert, Record);

	pPeer->Send(&Record);
	pPeer->Send(&Alert);

	bIsProcessing = false;
}

// PRF計算.
void CSSLHandshake::CalcPRF(const std::string &Secret, const std::string &Label, const std::string &Seed, std::vector<unsigned char> &OutBytes)
{
	OutBytes.clear();

	std::string LabelAndSeed = Label + Seed;
	
	// MD5
	std::string MD5Str = Secret.substr(0, Secret.length() / 2) + LabelAndSeed;
	md5 MD5;
	MD5.process_bytes(MD5Str.c_str(), MD5Str.length());
	md5::digest_type MD5ResultTmp;
	MD5.get_digest(MD5ResultTmp);
	unsigned int MD5Result[5];
	for (int i = 0; i < 4; i++)
	{
		MD5Result[i] = MD5ResultTmp[i];
	}
	MD5Result[4] = 0;

	// SHA1
	std::string SHA1Str = Secret.substr(Secret.length() / 2) + LabelAndSeed;
	sha1 SHA1;
	SHA1.process_bytes(SHA1Str.c_str(), SHA1Str.length());
	sha1::digest_type SHA1Result;
	SHA1.get_digest(SHA1Result);

	// 排他的論理和を取り、配列にブチ込む。
	for (int i = 0; i < 5; i++)
	{
		int XOR = MD5Result[i] ^ SHA1Result[i];
		unsigned char Bytes[4];
		memcpy(Bytes, &XOR, 4);
		for(unsigned char Byte : Bytes)
		{
			OutBytes.push_back(Byte);
		}
	}
}

// プリマスタシークレットを復号化.
cpp_int CSSLHandshake::DecriptPreMasterSecret(const cpp_int &PreMasterSecret, const cpp_int &Prime1, const cpp_int &Prime2)
{
	if (Prime1 == 0) { return 1; }

	if ((Prime1 % 2) == 0)
	{
		cpp_int t = DecriptPreMasterSecret(PreMasterSecret, Prime1 / 2, Prime2);
		return t * t % Prime2;
	}

	return PreMasterSecret * DecriptPreMasterSecret(PreMasterSecret, Prime1 - 1, Prime2);
}

// マスタシークレットを計算.
cpp_int CSSLHandshake::CalcMasterSecret(const cpp_int &PreMasterSecret)
{
	std::vector<unsigned char> Bytes;

	std::string Seed = "master secret";
	Seed += ClientRandom;
	Seed += ServerRandom;

	P_Hash(Seed, PreMasterSecret.str(), 48, Bytes);

	cpp_int Result(Bytes);
	return Result;
}

// P_Hash
void CSSLHandshake::P_Hash(const std::string &Seed, const std::string &Secret, int NeedBytes, std::vector<unsigned char> &OutBytes)
{
	int Count = NeedBytes / 16;
	std::string MD5Seed = Seed + Secret;
	for (int i = 0; i < Count; i++)
	{
		md5 MD5;
		MD5.process_bytes(Seed.c_str(), Seed.length());
		md5::digest_type Result;
		MD5.get_digest(Result);

		char Bytes[16];
		memcpy(Bytes, Result, 16);
		for (auto Byte : Bytes)
		{
			OutBytes.push_back((unsigned char) Byte);
		}

		MD5Seed = Bytes;
		MD5Seed += Secret;
	}
}

}
}
}
