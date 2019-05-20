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

// �R���X�g���N�^
CServletPeer::CServletPeer(YanaPServer::Socket::ISocket *pSocket, CServletFinder *pInFinder)
	: CPeerBase(pSocket)
	, pFinder(pInFinder)
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
		// @TODO:���̃G���[�ǂ�����ׂ��E�E�E�H
		//		 �Ƃ肠�����K���ɕԂ��B
		ResponseStream.Append("Error.");
		SendResponse(ResponseStream);
		return;
	}

	IServlet *pServlet = pFinder->Find(Request.Path.c_str());
	if (pServlet == nullptr)
	{
		// 404
		// @TODO:���B
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

			// �Ƃ肠�����G���[�ɂ��Ă����B
			pServlet->OnError(Request, ResponseStream);
			break;
	}

	SendResponse(ResponseStream);
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
void CServletPeer::SendResponse(const CStringStream &Stream)
{
	// @TODO:���̃��X�|���X�w�b�_
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
