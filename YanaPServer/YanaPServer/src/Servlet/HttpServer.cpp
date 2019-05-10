#include "Servlet/HttpServer.h"
#include "Servlet/Servlet.h"

namespace YanaPServer
{
namespace Servlet
{

using namespace YanaPServer::Peer;
using namespace YanaPServer::Socket;

// コンストラクタ
CHttpServer::CHttpServer()
	: CApplicationBase([](PeerPtr pPeer) {})
{
}

// デストラクタ
CHttpServer::~CHttpServer()
{
}


// Peer生成.
CPeerBase *CHttpServer::CreatePeer(ISocket *pSocket)
{
	CServlet *pServlet = new CServlet(pSocket);
	return pServlet;
}

}
}