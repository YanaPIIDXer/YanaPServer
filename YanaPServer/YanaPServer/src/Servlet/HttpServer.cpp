#include "Servlet/HttpServer.h"
#include "Servlet/Servlet.h"

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


// Peer����.
CPeerBase *CHttpServer::CreatePeer(ISocket *pSocket)
{
	CServlet *pServlet = new CServlet(pSocket);
	return pServlet;
}

}
}