#include "Servlet/Secure/SSLHandshake.h"
#include "Servlet/Secure/Packet/SSLPacket.h"
#include "Util/Stream/MemoryStreamReader.h"

#include <iostream>

using namespace YanaPServer::Util::Stream;
using namespace YanaPServer::Servlet::Secure::Packet;

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

	switch (Record.MessageType)
	{
		case EMessageType::ClientHello:

			OnRecvClientHello(&StreamReader);
			break;
	}
}


// ClientHello����M�����B
void CSSLHandshake::OnRecvClientHello(IMemoryStream *pStream)
{
	CSSLClientHello Packet;
	if (!Packet.Serialize(pStream))
	{
		// @TODO:���s���̏����ǂ�����E�E�E�H
		return;
	}

	std::cout << "Client Hello Serialize Success." << std::endl;
}

}
}
}
