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

// �R���X�g���N�^
CServletPeer::CServletPeer(YanaPServer::Socket::ISocket *pSocket, CServletFinder *pInFinder, IHttpServerEvent *pInHttpServerEvent)
	: CPeerBase(pSocket)
	, pFinder(pInFinder)
	, pHttpServerEvent(pInHttpServerEvent)
	, SendSize(0)
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

			// �Ƃ肠�����G���[�ɂ��Ă����B
			StatusCode = EStatusCode::BadRequest;
			pServlet->OnError(Request, ResponseStream);
			break;
	}

	SendResponse(Request.ProtocolVersion, StatusCode, ResponseStream);
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
void CServletPeer::SendResponse(const std::string &ProtocolVersion, EStatusCode StatusCode, const CStringStream &Stream)
{
	CStringStream SendData;

	// ���X�|���X�w�b�_
	SendData.Append(ProtocolVersion.c_str());
	SendData.Append(" ");
	switch (StatusCode)
	{
		case EStatusCode::OK:

			SendData.Append("200 OK\n");
			break;

		case EStatusCode::NotFound:

			SendData.Append("404 Not Found\n");
			break;

		case EStatusCode::BadRequest:

			SendData.Append("400 Bad Request\n");
			break;
	}
	SendData.Append("Content-Type: text/html\n");
	std::ostringstream ContentLength;
	ContentLength << "Content-Length: " << Stream.GetLength() << "\n";
	SendData.Append(ContentLength.str().c_str());
	SendData.Append("\r\n");
	
	// �{�f�B���u�`���ށB
	SendData.Append(Stream.Get());

	// �u��������B
	const char *pData = SendData.Get();
	unsigned int Size = SendData.GetLength() + 1;
	SendSize += Size;
	Send(pData, Size);
}

}
}
