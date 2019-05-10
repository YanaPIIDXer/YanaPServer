#include "Servlet/Servlet.h"

#include <iostream>

namespace YanaPServer
{
namespace Servlet
{

// �R���X�g���N�^
CServlet::CServlet(YanaPServer::Socket::ISocket *pSocket)
	: CPeerBase(pSocket)
{
}

// �f�X�g���N�^
CServlet::~CServlet()
{
}

// ��M�����B
void CServlet::OnRecv(const char *pData, unsigned int Size)
{
	std::cout << pData << std::endl;

	char TestData[] = "Test";
	Send(TestData, sizeof(TestData));
}

}
}
