#include "Servlet/Servlet.h"
#include "Servlet/HttpRequestParser.h"

namespace YanaPServer
{
namespace Servlet
{

// �R���X�g���N�^
CServlet::CServlet(YanaPServer::Socket::ISocket *pSocket, IServletEvent *pInEvent)
	: CPeerBase(pSocket)
	, pEvent(pInEvent)
{
}

// �f�X�g���N�^
CServlet::~CServlet()
{
}

// ��M�����B
void CServlet::OnRecv(const char *pData, unsigned int Size)
{
	CHttpRequestParser Parser;
	SHttpRequest Request;

	std::stringstream ResponseStream;

	if (!Parser.Parse(pData, Request))
	{
		pEvent->OnError(Request, ResponseStream);
		SendResponse(ResponseStream);
		return;
	}

	switch (Request.Method)
	{
		case EHttpMethod::POST:

			pEvent->OnPost(Request, ResponseStream);
			break;

		case EHttpMethod::GET:

			pEvent->OnGet(Request, ResponseStream);
			break;

		default:

			// �Ƃ肠�����G���[�ɂ��Ă����B
			pEvent->OnError(Request, ResponseStream);
			break;
	}

	SendResponse(ResponseStream);
}


// ���X�|���X���M.
void CServlet::SendResponse(std::stringstream &Stream)
{
	// @TODO:���ۂɂ̓��X�|���X�R�[�h�Ƃ���t������K�v������B
	// @FIXME:�o�͂���镶���񂪂��������B
	//		  �������O�̃X�g���[���N���X���`���Ȃ��Ƒʖڂ��ۂ��B
	const char *pData = Stream.str().data();
	unsigned int Size = Stream.str().size();
	Send(pData, Size);
}

}
}
