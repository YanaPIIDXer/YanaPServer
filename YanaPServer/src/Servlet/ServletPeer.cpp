#include "Servlet/ServletPeer.h"
#include "Servlet/ServletFinder.h"
#include "Servlet/HttpServerEvent.h"
#include "Servlet/HttpRequestParser.h"
#include "Util/Stream/MemoryStreamReader.h"
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
	, SSLHandshake(this)
{
}

// デストラクタ
CServletPeer::~CServletPeer()
{
}

// 受信した。
void CServletPeer::OnRecv(const char *pData, unsigned int Size)
{
	CMemoryStreamReader StreamReader(pData, Size);
	unsigned char CheckType = 0;
	StreamReader.Serialize(&CheckType);
	switch (CheckType)
	{
		case 0x16:
		case 0x14:
		case 0x15:
		case 0x17:
		case 0x80:

			// 先頭１バイトが上記のものだったらSSL通信。
			SSLHandshake.OnRecv(pData, Size);
			return;
	}

	CHttpRequestParser Parser;
	SHttpRequest Request;
	SHttpResponse Response;

	if (!Parser.Parse(pData, Request))
	{
		Response.StatusCode = EHttpStatusCode::BadRequest;
		pHttpServerEvent->OnError(Request, Response);
		SendResponse(Request, Response);
		return;
	}

	IServlet *pServlet = pFinder->Find(Request.Path.c_str());
	if (pServlet == nullptr)
	{
		// 404
		Response.StatusCode = EHttpStatusCode::NotFound;
		pHttpServerEvent->OnNotFound(Request, Response);
		SendResponse(Request, Response);
		return;
	}

	Response.StatusCode = EHttpStatusCode::OK;
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
			Response.StatusCode = EHttpStatusCode::BadRequest;
			pServlet->OnError(Request, Response);
			break;
	}

	SendResponse(Request, Response);
}

// 送信した
void CServletPeer::OnSend(unsigned int Size)
{
	if (SSLHandshake.IsProcessing()) { return; }

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
void CServletPeer::SendResponse(const SHttpRequest &Request, const SHttpResponse &Response)
{
	CSimpleStream SendData;

	// レスポンスヘッダ
	SendData.AppendString(Request.ProtocolVersion.c_str());
	SendData.AppendString(" ");
	switch (Response.StatusCode)
	{
		case EHttpStatusCode::OK:

			SendData.AppendStringLine("200 OK");
			break;

		case EHttpStatusCode::NotFound:

			SendData.AppendStringLine("404 Not Found");
			break;

		case EHttpStatusCode::BadRequest:

			SendData.AppendStringLine("400 Bad Request");
			break;
	}

	// Content-Type
	std::string ContentType = "Content-Type: " + Response.ContentType;
	SendData.AppendStringLine(ContentType.c_str());
	
	// Content-Length
	std::ostringstream ContentLength;
	ContentLength << "Content-Length: " << Response.ContentStream.GetLength();
	SendData.AppendStringLine(ContentLength.str().c_str());
	
	// Set-Cookie
	if (!Response.CookieMap.empty())
	{
		time_t Time = time(nullptr);
		tm CurrentTime;
#if _WIN32
		localtime_s(&CurrentTime, &Time);
#else
		localtime_r(&Time, &CurrentTime);
#endif

		tm Expires = { CurrentTime.tm_sec, CurrentTime.tm_min, CurrentTime.tm_hour, CurrentTime.tm_mday + 1, CurrentTime.tm_mon, CurrentTime.tm_year };
		time_t ExpiresTime = mktime(&Expires);
#if _WIN32
		localtime_s(&Expires, &ExpiresTime);
#else
		localtime_r(&ExpiresTime, &Expires);
#endif

		static const int TimeBufferSize = 512;
		char TimeBuffer[TimeBufferSize];
		strftime(TimeBuffer, TimeBufferSize, "expires=%a, %d-%b-%Y %T GMT; ", &Expires);

		for (const auto &It : Response.CookieMap)
		{
			std::ostringstream SetCookie;
			SetCookie << "Set-Cookie: ";
			SetCookie << It.first + "=" + It.second + "; ";

			SetCookie << TimeBuffer;

			SetCookie << "path=" + Request.Path + "; ";
			SetCookie << "domain=" + Request.Domain;

			SendData.AppendStringLine(SetCookie.str().c_str());
		}
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
