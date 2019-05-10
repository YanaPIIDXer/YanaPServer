#include "Servlet/ServletPeer.h"
#include "Servlet/ServletFinder.h"
#include "Servlet/HttpRequestParser.h"
#include "Util/Stream/StringStream.h"

using namespace YanaPServer::Util::Stream;

namespace YanaPServer
{
namespace Servlet
{

// コンストラクタ
CServletPeer::CServletPeer(YanaPServer::Socket::ISocket *pSocket, CServletFinder *pInFinder)
	: CPeerBase(pSocket)
	, pFinder(pInFinder)
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

	CStringStream ResponseStream;

	if (!Parser.Parse(pData, Request))
	{
		// @TODO:このエラーどうするべき・・・？
		//		 とりあえず適当に返す。
		ResponseStream.Append("Error.");
		SendResponse(ResponseStream);
		return;
	}

	IServlet *pServlet = pFinder->Find(Request.Path.c_str());
	if (pServlet == nullptr)
	{
		// 404
		// @TODO:仮。
		ResponseStream.Append("404 Not Found.");
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
void CServletPeer::SendResponse(const CStringStream &Stream)
{
	// @TODO:実際にはレスポンスコードとかを付加する必要がある。
	const char *pData = Stream.Get();
	unsigned int Size = Stream.GetLength() + 1;
	Send(pData, Size);
}

}
}
