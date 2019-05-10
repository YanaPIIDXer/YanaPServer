#include "Servlet/HttpServer.h"
#include "Servlet/ServletPeer.h"

namespace YanaPServer
{
namespace Servlet
{

using namespace YanaPServer::Peer;
using namespace YanaPServer::Socket;

// �R���X�g���N�^
CHttpServer::CHttpServer(IServlet *pInServlet)
	: CApplicationBase([](PeerPtr pPeer) {})
	, pServlet(pInServlet)
{
}

// �f�X�g���N�^
CHttpServer::~CHttpServer()
{
}


// Peer����.
CPeerBase *CHttpServer::CreatePeer(ISocket *pSocket)
{
	CServletPeer *pPeer = new CServletPeer(pSocket, pServlet);
	return pPeer;
}

}
}