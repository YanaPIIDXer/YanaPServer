#include "Servlet/ServletPeer.h"
#include "Servlet/ServletFinder.h"
#include "Servlet/HttpServerEvent.h"
#include "Servlet/HttpRequestParser.h"
#include "Util/Stream/StringStream.h"
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

	CStringStream ResponseStream;

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
void CServletPeer::SendResponse(const std::string &ProtocolVersion, EStatusCode StatusCode, const CStringStream &Stream)
{
	CStringStream SendData;

	// レスポンスヘッダ
	SendData.Append(ProtocolVersion.c_str());
	SendData.Append(" ");
	switch (StatusCode)
	{
		case EStatusCode::OK:

			SendData.AppendLine("200 OK");
			break;

		case EStatusCode::NotFound:

			SendData.AppendLine("404 Not Found");
			break;

		case EStatusCode::BadRequest:

			SendData.AppendLine("400 Bad Request");
			break;
	}
	SendData.AppendLine("Content-Type: text/html");
	std::ostringstream ContentLength;
	ContentLength << "Content-Length: " << Stream.GetLength();
	SendData.AppendLine(ContentLength.str().c_str());
	SendData.Append("\r\n");
	
	// ボディをブチ込む。
	SendData.Append(Stream.Get());

	// ブン投げる。
	const char *pData = SendData.Get();
	unsigned int Size = SendData.GetLength() + 1;
	SendSize += Size;
	Send(pData, Size);
}

}
}
