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
		pHttpServerEvent->OnError(Request, Response);
		SendResponse(Request.ProtocolVersion, EStatusCode::BadRequest, Response);
		return;
	}

	IServlet *pServlet = pFinder->Find(Request.Path.c_str());
	if (pServlet == nullptr)
	{
		// 404
		pHttpServerEvent->OnNotFound(Request, Response);
		SendResponse(Request.ProtocolVersion, EStatusCode::NotFound, Response);
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

			// �Ƃ肠�����G���[�ɂ��Ă����B
			StatusCode = EStatusCode::BadRequest;
			pServlet->OnError(Request, Response);
			break;
	}

	SendResponse(Request.ProtocolVersion, StatusCode, Response);
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
void CServletPeer::SendResponse(const std::string &ProtocolVersion, EStatusCode StatusCode, const SHttpResponse &Response)
{
	CSimpleStream SendData;

	// ���X�|���X�w�b�_
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
	ContentLength << "Content-Length: " << Response.ContentStream.GetLength();
	SendData.AppendStringLine(ContentLength.str().c_str());
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
