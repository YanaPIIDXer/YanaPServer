#include "Servlet/Secure/SSLHandshake.h"
#include "Servlet/ServletPeer.h"
#include "Util/Stream/MemoryStreamReader.h"
#include "Util/RandomString.h"
#include <random>
#include "Util/Stream/MemorySizeCaliculator.h"

#include <iostream>
#include <fstream>

using namespace YanaPServer::Util::Stream;
using namespace YanaPServer::Servlet::Secure::Packet;
using namespace YanaPServer::Util;

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
	, CurrentMessage(ServerHello)
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
			HandshakeRecord.Serialize(&StreamReader);

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
	switch (CurrentMessage)
	{
		case EMessageType::ServerCertificate:

			SendServerCertificate();
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

	CurrentMessage = EMessageType::ServerHello;

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
	ServerHello.CipherSuite = SSL_RSA_WITH_RC4_128_MD5;
	ServerHello.CompressionMethod = 0;

	SendHandshakePacket(EMessageType::ServerHello, &ServerHello);
	CurrentMessage = EMessageType::ServerCertificate;
}

// ServerCertificate�𑗐M.
void CSSLHandshake::SendServerCertificate()
{
	std::ifstream FileStream("Certificate/server.crt", std::ios::in | std::ios::binary);
	if (!FileStream)
	{
		std::cout << "CRT File Load Failed." << std::endl;
		bIsProcessing = false;
		return;
	}

	CSSLServerCertificate ServerCertificate;

	std::vector<char> Certificate;
	while (!FileStream.eof())
	{
		static const unsigned int BufferSize = 1024;
		char Buffer[BufferSize];
		FileStream.read(Buffer, BufferSize);
		auto ReadSize = FileStream.gcount();
		for (unsigned int i = 0; i < ReadSize; i++)
		{
			if (Buffer[i] == '\n') { continue; }
			Certificate.push_back(Buffer[i]);
		}
	}
	ServerCertificate.CertificateList.push_back(Certificate);

	SendHandshakePacket(EMessageType::ServerCertificate, &ServerCertificate);
}

// ServerHelloDone�𑗐M.
void CSSLHandshake::SendServerHelloDone()
{
	CSSLServerHelloDone ServerHelloDone;
	SendHandshakePacket(EMessageType::ServerHelloDone, &ServerHelloDone);
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
	OutRecord.Length = SizeCaliculator.GetSize();
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
