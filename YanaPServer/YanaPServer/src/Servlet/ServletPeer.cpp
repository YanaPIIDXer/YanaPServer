#include "Servlet/ServletPeer.h"
#include "Servlet/HttpRequestParser.h"
#include "Util/Stream/DynamicMemoryStreamWriter.h"

using namespace YanaPServer::Util::Stream;

namespace YanaPServer
{
namespace Servlet
{

// コンストラクタ
CServletPeer::CServletPeer(YanaPServer::Socket::ISocket *pSocket, IServlet *pInServlet)
	: CPeerBase(pSocket)
	, pServlet(pInServlet)
{
}

// デストラクタ
CServletPeer::~CServletPeer()
{
}

// 受信した。
void CServletPeer::OnRecv(const char *pData, unsigned int Size)
{
	CHttpRequestParser Parser;
	SHttpRequest Request;

	CDynamicMemoryStreamWriter ResponseStream;

	if (!Parser.Parse(pData, Request))
	{
		pServlet->OnError(Request, ResponseStream);
		SendResponse(ResponseStream);
		return;
	}

	switch (Request.Method)
	{
		case EHttpMethod::POST:

			pServlet->OnPost(Request, ResponseStream);
			break;

		case EHttpMethod::GET:

			pServlet->OnGet(Request, ResponseStream);
			break;

		default:

			// とりあえずエラーにしておく。
			pServlet->OnError(Request, ResponseStream);
			break;
	}

	SendResponse(ResponseStream);
}


// レスポンス送信.
void CServletPeer::SendResponse(const CDynamicMemoryStreamWriter &Stream)
{
	// @TODO:実際にはレスポンスコードとかを付加する必要がある。
	const char *pData = Stream.GetBuffer();
	unsigned int Size = Stream.GetSize();
	Send(pData, Size);
}

}
}
