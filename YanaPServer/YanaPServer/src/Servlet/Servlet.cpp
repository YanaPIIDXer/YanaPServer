#include "Servlet/Servlet.h"

// �R���X�g���N�^
CServlet::CServlet(YanaPServer::Socket::ISocket *pSocket)
	: CPeerBase(pSocket)
{
}

// �f�X�g���N�^
CServlet::~CServlet()
{
}
