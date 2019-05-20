#include "Servlet/ServletPeer.h"
#include "Servlet/ServletFinder.h"
#include "Servlet/HttpRequestParser.h"
#include "Util/Stream/StringStream.h"
#include <sstream>

using namespace YanaPServer::Util::Stream;

namespace YanaPServer
{
namespace Servlet
{

// コンストラクタ
CServletPeer::CServletPeer(YanaPServer::Socket::ISocket *pSocket, CServletFinder *pInFinder)
	: CPeerBase(pSocket)
	, pFinder(pInFinder)
	, SendSize(0)
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

// 送信した
void CServletPeer::OnSend(unsigned int Size)
{
	if (SendSize > Size)
	{
		SendSize -= Size;
		return;
	}

	// 送信し終えたら切断する。
	SendSize = 0;
	Disconnect();
}


// レスポンス送信.
void CServletPeer::SendResponse(const CStringStream &Stream)
{
	// @TODO:仮のレスポンスヘッダ
	CStringStream Header;
	Header.Append("HTTP/1.1 200 OK\n");
	Header.Append("Content-Type: text/html; charset=utf8\n");
	std::ostringstream ContentLength;
	ContentLength << "Content-Length: " << Stream.GetLength() << "\n";
	Header.Append(ContentLength.str().c_str());
	Header.Append("\n\n");
	const char *pHeader = Header.Get();
	unsigned int HeaderSize = Header.GetLength() + 1;
	SendSize += HeaderSize;
	Send(pHeader, HeaderSize);

	const char *pData = Stream.Get();
	unsigned int Size = Stream.GetLength() + 1;
	SendSize += Size;
	Send(pData, Size);
}

}
}
