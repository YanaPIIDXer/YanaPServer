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

// コンストラクタ
CSSLHandshake::CSSLHandshake(CServletPeer *pInPeer)
	: pPeer(pInPeer)
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
	CSSLRecord Record;
	if (!Record.Serialize(&StreamReader))
	{
		// @TODO:失敗時の処理どうする・・・？
		return;
	}

	switch (Record.MessageType)
	{
		case EMessageType::ClientHello:

			OnRecvClientHello(&StreamReader);
			break;
	}
}


// ClientHelloを受信した。
void CSSLHandshake::OnRecvClientHello(IMemoryStream *pStream)
{
	CSSLClientHello Packet;
	if (!Packet.Serialize(pStream))
	{
		// @TODO:失敗時の処理どうする・・・？
		return;
	}

	std::cout << "Client Hello Serialize Success." << std::endl;
}

}
}
}
