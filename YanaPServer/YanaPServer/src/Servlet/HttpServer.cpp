#include "Servlet/HttpServer.h"
#include "Servlet/Servlet.h"

namespace YanaPServer
{
namespace Servlet
{

using namespace YanaPServer::Peer;
using namespace YanaPServer::Socket;

// �R���X�g���N�^
CHttpServer::CHttpServer(IServletEvent *pInServletEvent)
	: CApplicationBase([](PeerPtr pPeer) {})
	, pServletEvent(pInServletEvent)
{
}

// �f�X�g���N�^
CHttpServer::~CHttpServer()
{
}


// Peer����.
CPeerBase *CHttpServer::CreatePeer(ISocket *pSocket)
{
	CServlet *pServlet = new CServlet(pSocket, pServletEvent);
	return pServlet;
}

}
}