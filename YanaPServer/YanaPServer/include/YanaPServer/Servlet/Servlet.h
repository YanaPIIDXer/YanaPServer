#ifndef __SERVLET_H__
#define __SERVLET_H__

#include "../Peer/PeerBase.h"
#include "../Socket/Socket.h"

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
	 */
	CServlet(YanaPServer::Socket::ISocket *pSocket);

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

};

}
}

#endif		// #ifndef __SERVLET_H__
