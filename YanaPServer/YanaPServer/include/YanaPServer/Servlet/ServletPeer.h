#ifndef __SERVLET_H__
#define __SERVLET_H__

#include "../Peer/PeerBase.h"
#include "../Socket/Socket.h"
#include "Servlet.h"

namespace YanaPServer
{
namespace Servlet
{

class CServletFinder;

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
	 * @param[in] pInFinder ServletFinder
	 */
	CServletPeer(YanaPServer::Socket::ISocket *pSocket, CServletFinder *pInFinder);

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

	/** 
	 * @fn virtual void OnSend(unsigned int Size) override
	 * @brief ���M����
	 * @param[in] Size ���M�����f�[�^��
	 */
	virtual void OnSend(unsigned int Size) override;

private:

	// ServletFinder
	CServletFinder *pFinder;

	// ���M�T�C�Y
	unsigned int SendSize;


	// ���X�|���X���M.
	void SendResponse(const YanaPServer::Util::Stream::CStringStream &Stream);

};

}
}

#endif		// #ifndef __SERVLET_H__
