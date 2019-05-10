#include "Servlet/Servlet.h"
#include "Servlet/HttpRequestParser.h"

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
	CHttpRequestParser Parser;
	SHttpRequest Request;
	if (!Parser.Parse(pData, Request))
	{
		pEvent->OnError(Request);
		return;
	}

	switch (Request.Method)
	{
		case EHttpMethod::POST:

			pEvent->OnPost(Request);
			break;

		case EHttpMethod::GET:

			pEvent->OnGet(Request);
			break;

		default:

			// とりあえずエラーにしておく。
			pEvent->OnError(Request);
			break;
	}
}

}
}
