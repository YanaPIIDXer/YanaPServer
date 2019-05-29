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

// �R���X�g���N�^
CServletPeer::CServletPeer(YanaPServer::Socket::ISocket *pSocket, CServletFinder *pInFinder, IHttpServerEvent *pInHttpServerEvent)
	: CPeerBase(pSocket)
	, pFinder(pInFinder)
	, SendSize(0)
	, pHttpServerEvent(pInHttpServerEvent)
{
}

// �f�X�g���N�^
CServletPeer::~CServletPeer()
{
}

// ��M�����B
void CServletPeer::OnRecv(const char *pData, unsigned int Size)
{
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

			// �Ƃ肠�����G���[�ɂ��Ă����B
			Response.StatusCode = EHttpStatusCode::BadRequest;
			pServlet->OnError(Request, Response);
			break;
	}

	SendResponse(Request, Response);
}

// ���M����
void CServletPeer::OnSend(unsigned int Size)
{
	if (SendSize > Size)
	{
		SendSize -= Size;
		return;
	}

	// ���M���I������ؒf����B
	SendSize = 0;
	Disconnect();
}


// ���X�|���X���M.
void CServletPeer::SendResponse(const SHttpRequest &Request, const SHttpResponse &Response)
{
	CSimpleStream SendData;

	// ���X�|���X�w�b�_
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
		localtime_s(&CurrentTime, &Time);

		tm Expires = { CurrentTime.tm_sec, CurrentTime.tm_min, CurrentTime.tm_hour, CurrentTime.tm_mday + 1, CurrentTime.tm_mon, CurrentTime.tm_year };
		time_t ExpiresTime = mktime(&Expires);
		localtime_s(&Expires, &ExpiresTime);

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

	// �{�f�B���u�`���ށB
	SendData.AppendBinary(Response.ContentStream.Get(), Response.ContentStream.GetLength());

	// �u��������B
	const char *pData = SendData.Get();
	unsigned int Size = SendData.GetLength() + 1;
	SendSize += Size;
	Send(pData, Size);
}

}
}
