#include "Servlet/ServletPeer.h"
#include "Servlet/ServletFinder.h"
#include "Servlet/HttpRequestParser.h"
#include "Util/Stream/StringStream.h"
#include <sstream>

#include <iostream>

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
	std::cout << pData << std::endl;

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
	//		 �����Ƃ��ŘM���悤�ɂ���K�v������B
	CStringStream SendData;
	SendData.Append("HTTP/1.1 200 OK\n");
	SendData.Append("Content-Type: text/html\n");
	std::ostringstream ContentLength;
	ContentLength << "Content-Length: " << Stream.GetLength() << "\n";
	SendData.Append(ContentLength.str().c_str());
	SendData.Append("\r\n");
	
	SendData.Append(Stream.Get());

	const char *pData = SendData.Get();
	unsigned int Size = SendData.GetLength() + 1;
	SendSize += Size;
	Send(pData, Size);
}

}
}
