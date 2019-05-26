#include "Servlet/ServletPeer.h"
#include "Servlet/ServletFinder.h"
#include "Servlet/HttpServerEvent.h"
#include "Servlet/HttpRequestParser.h"
#include "Util/Stream/SimpleStream.h"
#include <sstream>

using namespace YanaPServer::Util::Stream;

namespace YanaPServer
{
namespace Servlet
{

// コンストラクタ
CServletPeer::CServletPeer(YanaPServer::Socket::ISocket *pSocket, CServletFinder *pInFinder, IHttpServerEvent *pInHttpServerEvent)
	: CPeerBase(pSocket)
	, pFinder(pInFinder)
	, SendSize(0)
	, pHttpServerEvent(pInHttpServerEvent)
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

	CSimpleStream ResponseStream;

	if (!Parser.Parse(pData, Request))
	{
		pHttpServerEvent->OnError(Request, ResponseStream);
		SendResponse(Request.ProtocolVersion, EStatusCode::BadRequest, ResponseStream);
		return;
	}

	IServlet *pServlet = pFinder->Find(Request.Path.c_str());
	if (pServlet == nullptr)
	{
		// 404
		pHttpServerEvent->OnNotFound(Request, ResponseStream);
		SendResponse(Request.ProtocolVersion, EStatusCode::NotFound, ResponseStream);
		return;
	}

	EStatusCode StatusCode = EStatusCode::OK;
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
			StatusCode = EStatusCode::BadRequest;
			pServlet->OnError(Request, ResponseStream);
			break;
	}

	SendResponse(Request.ProtocolVersion, StatusCode, ResponseStream);
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
void CServletPeer::SendResponse(const std::string &ProtocolVersion, EStatusCode StatusCode, const CSimpleStream &Stream)
{
	CSimpleStream SendData;

	// レスポンスヘッダ
	SendData.AppendString(ProtocolVersion.c_str());
	SendData.AppendString(" ");
	switch (StatusCode)
	{
		case EStatusCode::OK:

			SendData.AppendStringLine("200 OK");
			break;

		case EStatusCode::NotFound:

			SendData.AppendStringLine("404 Not Found");
			break;

		case EStatusCode::BadRequest:

			SendData.AppendStringLine("400 Bad Request");
			break;
	}
	SendData.AppendStringLine("Content-Type: text/html");
	std::ostringstream ContentLength;
	ContentLength << "Content-Length: " << Stream.GetLength();
	SendData.AppendStringLine(ContentLength.str().c_str());
	SendData.AppendString("\r\n");
	
	// ボディをブチ込む。
	SendData.AppendBinary(Stream.Get(), Stream.GetLength());

	// ブン投げる。
	const char *pData = SendData.Get();
	unsigned int Size = SendData.GetLength() + 1;
	SendSize += Size;
	Send(pData, Size);
}

}
}
