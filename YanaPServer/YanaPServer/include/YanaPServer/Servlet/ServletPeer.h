#ifndef __SERVLET_H__
#define __SERVLET_H__

#include "../Peer/PeerBase.h"
#include "../Socket/Socket.h"
#include "Servlet.h"

namespace YanaPServer
{
namespace Servlet
{

/**
 * @class CServletPeer
 * @brief HTTP�ڑ�����������N���X�B
 *        Java Servlet�݂����ȃ��m�B
 *        ���������Peer
 */
class CServletPeer : public YanaPServer::Peer::CPeerBase
{

public:

	/**
	 * @brief �R���X�g���N�^
	 * @param[in] pSocket �\�P�b�g
	 * @param[in] pInServlet Servlet�C���^�t�F�[�X
	 */
	CServletPeer(YanaPServer::Socket::ISocket *pSocket, IServlet *pInServlet);

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CServletPeer();

	/**
	 * @fn virtual void OnRecv(const char *pData, unsigned int Size) override
	 * @brief ��M����
	 * @param[in] pData �f�[�^
	 * @param[in] Size �f�[�^��
	 */
	virtual void OnRecv(const char *pData, unsigned int Size) override;

private:

	// Servlet�C���^�t�F�[�X
	IServlet *pServlet;


	// ���X�|���X���M.
	void SendResponse(const YanaPServer::Util::Stream::CDynamicMemoryStreamWriter &Stream);

};

}
}

#endif		// #ifndef __SERVLET_H__
