#include "Servlet/Servlet.h"

#include <iostream>

namespace YanaPServer
{
namespace Servlet
{

// コンストラクタ
CServlet::CServlet(YanaPServer::Socket::ISocket *pSocket, IServletEvent *pInEvent)
	: CPeerBase(pSocket)
	, pEvent(pInEvent)
{
}

// デストラクタ
CServlet::~CServlet()
{
}

// 受信した。
void CServlet::OnRecv(const char *pData, unsigned int Size)
{
	std::cout << pData << std::endl;

	char TestData[] = "Test";
	Send(TestData, sizeof(TestData));
}

}
}
