#ifndef __SERVLET_H__
#define __SERVLET_H__

#include "../Peer/PeerBase.h"
#include "../Socket/Socket.h"
#include "ServletEvent.h"

namespace YanaPServer
{
namespace Servlet
{

/**
 * @class CServlet
 * @brief HTTP�ڑ�����������N���X�B
 *        Java Servlet�݂����ȃ��m�B
 */
class CServlet : public YanaPServer::Peer::CPeerBase
{

public:

	/**
	 * @brief �R���X�g���N�^
	 * @param[in] pSocket �\�P�b�g
	 * @param[in] IServletEvent �C�x���g�C���^�t�F�[�X
	 */
	CServlet(YanaPServer::Socket::ISocket *pSocket, IServletEvent *pInEvent);

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CServlet();

	/**
	 * @fn virtual void OnRecv(const char *pData, unsigned int Size) override
	 * @brief ��M����
	 * @param[in] pData �f�[�^
	 * @param[in] Size �f�[�^��
	 */
	virtual void OnRecv(const char *pData, unsigned int Size) override;

private:

	// �C�x���g�C���^�t�F�[�X
	IServletEvent *pEvent;

};

}
}

#endif		// #ifndef __SERVLET_H__
