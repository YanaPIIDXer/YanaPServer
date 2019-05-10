#include "Servlet/HttpServer.h"
#include "Servlet/ServletPeer.h"

namespace YanaPServer
{
namespace Servlet
{

using namespace YanaPServer::Peer;
using namespace YanaPServer::Socket;

// コンストラクタ
CHttpServer::CHttpServer(IServlet *pInServlet)
	: CApplicationBase([](PeerPtr pPeer) {})
	, pServlet(pInServlet)
{
}

// デストラクタ
CHttpServer::~CHttpServer()
{
}


// Peer生成.
CPeerBase *CHttpServer::CreatePeer(ISocket *pSocket)
{
	CServletPeer *pPeer = new CServletPeer(pSocket, pServlet);
	return pPeer;
}

}
}