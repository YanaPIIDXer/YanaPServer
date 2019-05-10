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
	if (!Parser.Parse(pData, Request))
	{
		pEvent->OnError(Request);
		return;
	}

	switch (Request.Method)
	{
		case EHttpMethod::POST:

			pEvent->OnPost(Request);
			break;

		case EHttpMethod::GET:

			pEvent->OnGet(Request);
			break;

		default:

			// �Ƃ肠�����G���[�ɂ��Ă����B
			pEvent->OnError(Request);
			break;
	}
}

}
}
