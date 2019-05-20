#include "Servlet/ServletPeer.h"
#include "Servlet/ServletFinder.h"
#include "Servlet/HttpRequestParser.h"
#include "Util/Stream/StringStream.h"

using namespace YanaPServer::Util::Stream;

namespace YanaPServer
{
namespace Servlet
{

// �R���X�g���N�^
CServletPeer::CServletPeer(YanaPServer::Socket::ISocket *pSocket, CServletFinder *pInFinder)
	: CPeerBase(pSocket)
	, pFinder(pInFinder)
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


// ���X�|���X���M.
void CServletPeer::SendResponse(const CStringStream &Stream)
{
	// @TODO:���ۂɂ̓��X�|���X�R�[�h�Ƃ���t������K�v������B
	const char *pData = Stream.Get();
	unsigned int Size = Stream.GetLength() + 1;
	Send(pData, Size);
}

}
}
