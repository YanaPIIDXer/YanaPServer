#include "Servlet/HttpServer.h"
#include "Servlet/ServletPeer.h"

namespace YanaPServer
{
namespace Servlet
{

using namespace YanaPServer::Peer;
using namespace YanaPServer::Socket;

CHttpDefaultServetEvent CHttpDefaultServetEvent::Instance;

// コンストラクタ
CHttpServer::CHttpServer()
	: CApplicationBase([](PeerPtr pPeer) {})
	, pEvent(&CHttpDefaultServetEvent::GetInstance())
{
}

// コンストラクタ
CHttpServer::CHttpServer(IHttpServerEvent *pInEvent)
	: CApplicationBase([](PeerPtr pPeer) {})
	, pEvent(pInEvent)
{
}

// デストラクタ
CHttpServer::~CHttpServer()
{
}

// Servlet追加。
void CHttpServer::AddServlet(IServlet *pServlet)
{
	ServletFinder.Add(pServlet);
}


// Peer生成.
CPeerBase *CHttpServer::CreatePeer(ISocket *pSocket)
{
	CServletPeer *pPeer = new CServletPeer(pSocket, &ServletFinder, pEvent);
	return pPeer;
}

}
}