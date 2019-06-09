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

// �R���X�g���N�^
CSSLHandshake::CSSLHandshake(CServletPeer *pInPeer)
	: pPeer(pInPeer)
	, bIsProcessing(false)
	, Version(0)
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
	OnRecvData(&StreamReader);
}


// �f�[�^����M�����B
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

						// ChangeCipherSpec��M.
						OnRecvEncryptedData(pStream);
						break;
				}
			}
			break;
	}
}

// �Í������ꂽ�f�[�^����M�����B
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

	// ��U�f�[�^��S�����o���B
	std::vector<char> Data;
	Data.resize(Record.Length);
	pStream->Serialize(&Data[0], Record.Length);
}

// ClientHello����M�����B
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

// ServerCertificate�𑗐M.
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
		std::cout << "Certificate Base64 Decode Failed." << std::endl;
		SendAlert(EAlertLevel::Fatal, EAlertDescription::CertificateUnknown);
		return;
	}

	CSSLServerCertificate ServerCertificate;
	ServerCertificate.CertificateList.push_back(Decoded);
	SendHandshakePacket(EMessageType::ServerCertificate, &ServerCertificate);
}

// ServerHelloDone�𑗐M.
void CSSLHandshake::SendServerHelloDone()
{
	CSSLServerHelloDone ServerHelloDone;
	SendHandshakePacket(EMessageType::ServerHelloDone, &ServerHelloDone);
}

// ClientKeyExchange����M�����B
void CSSLHandshake::OnRecvClientKeyExchange(IMemoryStream *pStream)
{
	CSSLClientKeyExchange ClientKeyExchange;
	if (!ClientKeyExchange.Serialize(pStream))
	{
		SendAlert(EAlertLevel::Fatal, EAlertDescription::HandshakeFailuer);
		return;
	}

	// �閧����ǂݍ��ށB
	LoadPrivateKey();

	// �v���}�X�^�V�[�N���b�g�̕�����.
	cpp_int PreMasterSecret(ClientKeyExchange.PreMasterSecret);
	cpp_int Prime1(PrivateKey.BERs[0]->Children[4]->Content);
	cpp_int Prime2(PrivateKey.BERs[0]->Children[5]->Content);
	PreMasterSecret = Decript(PreMasterSecret, Prime1, Prime2);

	// �}�X�^�V�[�N���b�g�v�Z.
	MasterSecret = CalcMasterSecret(PreMasterSecret);
	std::cout << "Master Secret:" << MasterSecret << std::endl;

	// �L�[�u���b�N�v�Z.
	std::string  Seed = ServerRandom;
	Seed += ClientRandom;
	std::vector<unsigned char> KeyBlock;
	CalcPRF(MasterSecret.str(), "key expension", Seed, 104, KeyBlock);
	
	// �L�[�u���b�N��؂�o���B
	memcpy(ClientWriteMAC, &KeyBlock[0], 20);
	memcpy(ServerWriteMAC, &KeyBlock[20], 20);
	memcpy(ClientSecretKey, &KeyBlock[40], 24);
	memcpy(ServerSecretKey, &KeyBlock[64], 24);
	memcpy(PrevClientCipherBlock, &KeyBlock[88], 8);
	memcpy(PrevServerCipherBlock, &KeyBlock[96], 8);
}

// �n���h�V�F�C�N�p�P�b�g�𑗐M.
void CSSLHandshake::SendHandshakePacket(unsigned char MessageType, YanaPServer::Util::ISerializable *pPacket)
{
	// ���R�[�h
	CSSLRecord Record;
	MakeSSLRecordPacket(ERecordType::Handshake, pPacket, Record);
	pPeer->Send(&Record);

	// �n���h�V�F�C�N���R�[�h
	CSSLHandshakeRecord HandshakeRecord;
	MakeSSLHandshakeRecordPacket(MessageType, pPacket, HandshakeRecord);
	pPeer->Send(&HandshakeRecord);
	
	// �{��
	pPeer->Send(pPacket);
}

// SSLRecord�p�P�b�g�𐶐�.
void CSSLHandshake::MakeSSLRecordPacket(ERecordType Type, YanaPServer::Util::ISerializable *pPacket, YanaPServer::Servlet::Secure::Packet::CSSLRecord &OutRecord)
{
	CMemorySizeCaliculator SizeCaliculator;
	pPacket->Serialize(&SizeCaliculator);

	OutRecord.Type = Type;
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

// �閧���̓ǂݍ���
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

	// Base64�ŃG���R�[�h����Ă���ӏ��݂̂����o���B
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

// Alert�𑗐M.
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

// ������.
cpp_int CSSLHandshake::Decript(const cpp_int &Encrypted, const cpp_int &Prime1, const cpp_int &Prime2)
{
	if (Prime1 == 0) { return 1; }

	if ((Prime1 % 2) == 0)
	{
		cpp_int t = Decript(Encrypted, Prime1 / 2, Prime2);
		return t * t % Prime2;
	}

	return Encrypted * Decript(Encrypted, Prime1 - 1, Prime2);
}

// �}�X�^�V�[�N���b�g���v�Z.
cpp_int CSSLHandshake::CalcMasterSecret(const cpp_int &PreMasterSecret)
{
	std::vector<unsigned char> Bytes;

	std::string Seed = ClientRandom;
	Seed += ServerRandom;

	CalcPRF(PreMasterSecret.str(), "master secret", Seed, 48, Bytes);

	cpp_int Result(Bytes);
	return Result;
}

// PRF�v�Z.
void CSSLHandshake::CalcPRF(const std::string &Secret, const std::string &Label, const std::string &Seed, unsigned int NeedBytes, std::vector<unsigned char> &OutBytes)
{
	// MD5
	std::string HashSecret = Secret.substr(0, Secret.length() / 2);
	std::vector<unsigned char> MD5Result;
	P_Hash(EHashType::MD5, Label + Seed, HashSecret, NeedBytes, MD5Result);

	// SHA1
	HashSecret = Secret.substr(HashSecret.length());
	std::vector<unsigned char> SHA1Result;
	P_Hash(EHashType::SHA1, Label + Seed, HashSecret, NeedBytes, SHA1Result);

	// XOR������Ă����B
	OutBytes.clear();
	for (unsigned int i = 0; i < NeedBytes; i++)
	{
		OutBytes.push_back(MD5Result[i] ^ SHA1Result[i]);
	}
}

// P_Hash
void CSSLHandshake::P_Hash(EHashType Type, const std::string &Seed, const std::string &Secret, unsigned int NeedBytes, std::vector<unsigned char> &OutBytes)
{
	unsigned int HashBytes = (Type == EHashType::MD5 ? 16 : 20);
	unsigned int Count = NeedBytes / HashBytes;
	if ((NeedBytes % HashBytes) > 0)
	{
		Count++;
	}
	std::string HashSeed = Seed + Secret;
	std::vector<unsigned char> ResultBytes;
	for (unsigned int i = 0; i < Count * HashBytes; i++)
	{
		ResultBytes.push_back(0);
	}

	for (unsigned int i = 0; i < Count; i++)
	{
		switch (Type)
		{
			case EHashType::MD5:

				{
					md5 MD5;
					MD5.process_bytes(HashSeed.c_str(), HashSeed.length());
					md5::digest_type Result;
					MD5.get_digest(Result);
					char Bytes[16];
					memcpy(Bytes, Result, 16);
					for (int j =0; j < 16; j++)
					{
						ResultBytes[i * 16 + j] = (unsigned char) Bytes[i];
					}
					HashSeed = Bytes;
				}
				break;

			case EHashType::SHA1:

				{
					sha1 SHA;
					SHA.process_bytes(HashSeed.c_str(), HashSeed.length());
					sha1::digest_type Result;
					SHA.get_digest(Result);
					char Bytes[20];
					memcpy(Bytes, Result, 20);
					for (int j = 0; j < 20; j++)
					{
						ResultBytes[i * 20 + j] = (unsigned char) Bytes[i];
					}
					HashSeed = Bytes;
				}
				break;
		}
		HashSeed += Secret;
	}

	OutBytes.clear();
	for (unsigned int i = 0; i < NeedBytes; i++)
	{
		OutBytes.push_back(ResultBytes[i]);
	}
}

}
}
}
