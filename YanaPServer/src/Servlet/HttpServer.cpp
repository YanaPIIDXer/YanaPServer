#include "Servlet/HttpServer.h"
#include "Servlet/ServletPeer.h"

namespace YanaPServer
{
namespace Servlet
{

using namespace YanaPServer::Peer;
using namespace YanaPServer::Socket;

CHttpDefaultServerEvent CHttpDefaultServerEvent::Instance;

// �R���X�g���N�^
CHttpServer::CHttpServer()
	: CApplicationBase([](PeerPtr pPeer) {})
	, pEvent(&CHttpDefaultServerEvent::GetInstance())
{
}

// �R���X�g���N�^
CHttpServer::CHttpServer(IHttpServerEvent *pInEvent)
	: CApplicationBase([](PeerPtr pPeer) {})
	, pEvent(pInEvent)
{
}

// �f�X�g���N�^
CHttpServer::~CHttpServer()
{
}

// Servlet�ǉ��B
void CHttpServer::AddServlet(IServlet *pServlet)
{
	ServletFinder.Add(pServlet);
}


// Peer����.
CPeerBase *CHttpServer::CreatePeer(ISocket *pSocket)
{
	CServletPeer *pPeer = new CServletPeer(pSocket, &ServletFinder, pEvent);
	return pPeer;
}

}
}