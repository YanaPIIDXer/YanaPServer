#include "Servlet/Servlet.h"

// コンストラクタ
CServlet::CServlet(YanaPServer::Socket::ISocket *pSocket)
	: CPeerBase(pSocket)
{
}

// デストラクタ
CServlet::~CServlet()
{
}
