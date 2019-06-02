#include "Servlet/Secure/SSLHandshake.h"
#include "Servlet/ServletPeer.h"
#include "Util/Stream/MemoryStreamReader.h"
#include "Util/RandomString.h"
#include <random>
#include "Util/Stream/MemorySizeCaliculator.h"
#include "Util/Secure/Base64.h"

#include <iostream>
#include <fstream>

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

// �R���X�g���N�^
CSSLHandshake::CSSLHandshake(CServletPeer *pInPeer)
	: pPeer(pInPeer)
	, bIsProcessing(false)
	, Version(0)
	, CurrentState(ESendState::ServerHello)
{
}

// �f�X�g���N�^
CSSLHandshake::~CSSLHandshake()
{
}

// ��M����
void CSSLHandshake::OnRecv(const char *pData, unsigned int Size)
{
	CMemoryStreamReader StreamReader(pData, Size);
	CSSLRecord Record;
	if (!Record.Serialize(&StreamReader))
	{
		bIsProcessing = false;
		pPeer->Disconnect();
		return;
	}

	Version = Record.Version;
	
	std::cout << "Type:" << (int)Record.Type << std::endl;
	std::cout << "Length:" << Record.Length << std::endl;
	printf("Version:0x%04X\n", Version);
	switch (Record.Type)
	{
		case 0x16:
		{
			CSSLHandshakeRecord HandshakeRecord;
			if (!HandshakeRecord.Serialize(&StreamReader))
			{
				bIsProcessing = false;
				pPeer->Disconnect();
				return;
			}

			switch (HandshakeRecord.MessageType)
			{
				case EMessageType::ClientHello:

					OnRecvClientHello(&StreamReader);
					break;
				}
		}
		break;
	}
}

// ���𑗐M.
void CSSLHandshake::SendNext()
{
	switch (CurrentState)
	{
		case ESendState::ServerCertificate:

			SendServerCertificate();
			break;

		case ESendState::ServerHelloDone:

			SendServerHelloDone();
			break;

		default:

			break;
	}
}


// ClientHello����M�����B
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

	CurrentState = ESendState::ServerHello;

	CRandomString RandomStr;
	RandomStr.Generate(28);

	std::random_device Rnd;

	CSSLServerHello ServerHello;
	ServerHello.Version = ClientHello.ClientVersion;
	ServerHello.Time = ClientHello.Time;
	memcpy(ServerHello.Random, RandomStr.Get(), 28);
	/*
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

// ServerCertificate�𑗐M.
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

	// Base64�ŃG���R�[�h����Ă���ӏ��݂̂����o���B
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

	// �f�R�[�h�����f�[�^�𓊂��t����B
	std::vector<unsigned char> Decoded;
	if (!CBase64::Decode(CrtData, Decoded))
	{
		std::cout << "Base64 Decode Failed." << std::endl;
		bIsProcessing = false;
		pPeer->Disconnect();
		return;
	}

	CSSLServerCertificate ServerCertificate;
	ServerCertificate.CertificateList.push_back(Decoded);
	SendHandshakePacket(EMessageType::ServerCertificate, &ServerCertificate);

	CurrentState = ESendState::ServerHelloDone;
}

// ServerHelloDone�𑗐M.
void CSSLHandshake::SendServerHelloDone()
{
	CSSLServerHelloDone ServerHelloDone;
	SendHandshakePacket(EMessageType::ServerHelloDone, &ServerHelloDone);

	CurrentState = ESendState::End;
}

// �n���h�V�F�C�N�p�P�b�g�𑗐M.
void CSSLHandshake::SendHandshakePacket(unsigned char MessageType, YanaPServer::Util::ISerializable *pPacket)
{
	// ���R�[�h
	CSSLRecord Record;
	MakeSSLRecordPacket(pPacket, Record);
	pPeer->Send(&Record);

	// �n���h�V�F�C�N���R�[�h
	CSSLHandshakeRecord HandshakeRecord;
	MakeSSLHandshakeRecordPacket(MessageType, pPacket, HandshakeRecord);
	pPeer->Send(&HandshakeRecord);
	
	// �{��
	pPeer->Send(pPacket);
}

// SSLRecord�p�P�b�g�𐶐�.
void CSSLHandshake::MakeSSLRecordPacket(YanaPServer::Util::ISerializable *pPacket, YanaPServer::Servlet::Secure::Packet::CSSLRecord &OutRecord)
{
	CMemorySizeCaliculator SizeCaliculator;
	pPacket->Serialize(&SizeCaliculator);

	OutRecord.Type = 0x16;
	OutRecord.Version = Version;
	OutRecord.Length = SizeCaliculator.GetSize() + 4;
}

// SSL�n���h�V�F�C�N���R�[�h�p�P�b�g�𐶐�
void CSSLHandshake::MakeSSLHandshakeRecordPacket(unsigned char MessageType, YanaPServer::Util::ISerializable *pPacket, YanaPServer::Servlet::Secure::Packet::CSSLHandshakeRecord &OutRecord)
{
	CMemorySizeCaliculator SizeCaliculator;
	pPacket->Serialize(&SizeCaliculator);

	OutRecord.MessageType = MessageType;
	OutRecord.BodyLength = SizeCaliculator.GetSize();
}

}
}
}
