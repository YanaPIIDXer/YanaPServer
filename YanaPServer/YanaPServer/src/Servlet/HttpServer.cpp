#include "Servlet/HttpServer.h"
#include "Servlet/Servlet.h"

namespace YanaPServer
{
namespace Servlet
{

using namespace YanaPServer::Peer;
using namespace YanaPServer::Socket;

// コンストラクタ
CHttpServer::CHttpServer(IServletEvent *pInServletEvent)
	: CApplicationBase([](PeerPtr pPeer) {})
	, pServletEvent(pInServletEvent)
{
}

// デストラクタ
CHttpServer::~CHttpServer()
{
}


// Peer生成.
CPeerBase *CHttpServer::CreatePeer(ISocket *pSocket)
{
	CServlet *pServlet = new CServlet(pSocket, pServletEvent);
	return pServlet;
}

}
}