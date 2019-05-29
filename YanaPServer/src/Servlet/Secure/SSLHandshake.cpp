#include "Servlet/Secure/SSLHandshake.h"
#include "Servlet/ServletPeer.h"
#include "Servlet/Secure/Packet/SSLPacket.h"
#include "Util/Stream/MemoryStreamReader.h"
#include "Util/RandomString.h"
#include <random>
#include "Util/Stream/MemorySizeCaliculator.h"

#include <iostream>

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
		// @TODO:���s���̏����ǂ�����E�E�E�H
		return;
	}

	std::cout << "Type:" << (int)Record.Type << std::endl;
	std::cout << "MessageType:" << (int)Record.MessageType << std::endl;
	switch (Record.MessageType)
	{
		case EMessageType::ClientHello:

			OnRecvClientHello(Record.Version, &StreamReader);
			break;
	}
}


// ClientHello����M�����B
void CSSLHandshake::OnRecvClientHello(unsigned short Version, IMemoryStream *pStream)
{
	CSSLClientHello ClientHello;
	if (!ClientHello.Serialize(pStream))
	{
		// @TODO:���s���̏����ǂ�����E�E�E�H
		return;
	}

	CRandomString RandomStr;
	RandomStr.Generate(28);

	std::random_device Rnd;

	CSSLServerHello ServerHello;
	ServerHello.Version = ClientHello.ClientVersion;
	ServerHello.Time = ClientHello.Time;
	memcpy(ServerHello.Random, RandomStr.Get(), 28);
	for (int i = 0; i < 64; i++)
	{
		ServerHello.SessionId.push_back(Rnd());
	}
	ServerHello.CipherSuite = 0x0005;
	ServerHello.CompressionMethod = 0;

	CMemorySizeCaliculator SizeCaliculator;
	ServerHello.Serialize(&SizeCaliculator);

	CSSLRecord Record;

	Record.Type = 0x16;
	Record.Version = Version;
	Record.MessageType = 0x02;
	Record.BodyLength = SizeCaliculator.GetSize();
	Record.Length = 8 + Record.BodyLength;

	// ���R�[�h���M.
	pPeer->Send(&Record);

	// ServerHello���M.
	pPeer->Send(&ServerHello);
}

}
}
}
