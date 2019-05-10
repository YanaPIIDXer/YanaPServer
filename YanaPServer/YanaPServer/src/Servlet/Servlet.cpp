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

	std::stringstream ResponseStream;

	if (!Parser.Parse(pData, Request))
	{
		pEvent->OnError(Request, ResponseStream);
		SendResponse(ResponseStream);
		return;
	}

	switch (Request.Method)
	{
		case EHttpMethod::POST:

			pEvent->OnPost(Request, ResponseStream);
			break;

		case EHttpMethod::GET:

			pEvent->OnGet(Request, ResponseStream);
			break;

		default:

			// とりあえずエラーにしておく。
			pEvent->OnError(Request, ResponseStream);
			break;
	}

	SendResponse(ResponseStream);
}


// レスポンス送信.
void CServlet::SendResponse(std::stringstream &Stream)
{
	// @TODO:実際にはレスポンスコードとかを付加する必要がある。
	// @FIXME:出力される文字列がおかしい。
	//		  多分自前のストリームクラスを定義しないと駄目っぽい。
	const char *pData = Stream.str().data();
	unsigned int Size = Stream.str().size();
	Send(pData, Size);
}

}
}
