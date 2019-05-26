#include "Servlet/ServletPeer.h"
#include "Servlet/ServletFinder.h"
#include "Servlet/HttpServerEvent.h"
#include "Servlet/HttpRequestParser.h"
#include "Util/Stream/SimpleStream.h"
#include <sstream>
#include <time.h>

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
	SHttpResponse Response;

	if (!Parser.Parse(pData, Request))
	{
		pHttpServerEvent->OnError(Request, Response);
		SendResponse(Request, EStatusCode::BadRequest, Response);
		return;
	}

	IServlet *pServlet = pFinder->Find(Request.Path.c_str());
	if (pServlet == nullptr)
	{
		// 404
		pHttpServerEvent->OnNotFound(Request, Response);
		SendResponse(Request, EStatusCode::NotFound, Response);
		return;
	}

	EStatusCode StatusCode = EStatusCode::OK;
	switch (Request.Method)
	{
		case EHttpMethod::POST:

			pServlet->OnPost(Request, Response);
			break;

		case EHttpMethod::GET:

			pServlet->OnGet(Request, Response);
			break;

		default:

			// とりあえずエラーにしておく。
			StatusCode = EStatusCode::BadRequest;
			pServlet->OnError(Request, Response);
			break;
	}

	SendResponse(Request, StatusCode, Response);
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
void CServletPeer::SendResponse(const SHttpRequest &Request, EStatusCode StatusCode, const SHttpResponse &Response)
{
	CSimpleStream SendData;

	// レスポンスヘッダ
	SendData.AppendString(Request.ProtocolVersion.c_str());
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

	// Content-Length
	std::ostringstream ContentLength;
	ContentLength << "Content-Length: " << Response.ContentStream.GetLength();
	SendData.AppendStringLine(ContentLength.str().c_str());
	
	// Set-Cookie
	if (Response.CookieInfo.bIsEnable && Response.CookieInfo.Name != "")
	{
		std::ostringstream SetCookie;
		SetCookie << "Set-Cookie: ";
		SetCookie << Response.CookieInfo.Name + "=" + Response.CookieInfo.Value + "; ";

		time_t Time = time(nullptr);
		tm CurrentTime;
		localtime_s(&CurrentTime, &Time);

		tm Expires = { CurrentTime.tm_sec, CurrentTime.tm_min, CurrentTime.tm_hour, CurrentTime.tm_mday + 1, CurrentTime.tm_mon, CurrentTime.tm_year };
		time_t ExpiresTime = mktime(&Expires);
		localtime_s(&Expires, &ExpiresTime);

		static const int BufferSize = 512;
		char Buffer[BufferSize];
		strftime(Buffer, BufferSize, "expires=%a, %d-%b-%Y %T GMT; ", &Expires);

		SetCookie << Buffer;

		SetCookie << "path=" + Request.Path + "; ";
		SetCookie << "domain=" + Request.Domain;

		SendData.AppendStringLine(SetCookie.str().c_str());
	}
	
	SendData.AppendString("\r\n");

	// ボディをブチ込む。
	SendData.AppendBinary(Response.ContentStream.Get(), Response.ContentStream.GetLength());

	// ブン投げる。
	const char *pData = SendData.Get();
	unsigned int Size = SendData.GetLength() + 1;
	SendSize += Size;
	Send(pData, Size);
}

}
}
