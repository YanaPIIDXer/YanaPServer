#include "Servlet/ServletPeer.h"
#include "Servlet/HttpRequestParser.h"

namespace YanaPServer
{
namespace Servlet
{

// �R���X�g���N�^
CServletPeer::CServletPeer(YanaPServer::Socket::ISocket *pSocket, IServlet *pInServlet)
	: CPeerBase(pSocket)
	, pServlet(pInServlet)
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

	std::stringstream ResponseStream;

	if (!Parser.Parse(pData, Request))
	{
		pServlet->OnError(Request, ResponseStream);
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
void CServletPeer::SendResponse(std::stringstream &Stream)
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
