#include "Servlet/ServletPeer.h"
#include "Servlet/HttpRequestParser.h"

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

	std::stringstream ResponseStream;

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
void CServletPeer::SendResponse(std::stringstream &Stream)
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
