#include "Servlet/HttpServer.h"
#include "Servlet/ServletPeer.h"

namespace YanaPServer
{
namespace Servlet
{

using namespace YanaPServer::Peer;
using namespace YanaPServer::Socket;

// �R���X�g���N�^
CHttpServer::CHttpServer()
	: CApplicationBase([](PeerPtr pPeer) {})
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
	CServletPeer *pPeer = new CServletPeer(pSocket, &ServletFinder);
	return pPeer;
}

}
}