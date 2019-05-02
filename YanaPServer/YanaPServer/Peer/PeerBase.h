#ifndef __PEERBASE_H__
#define __PEERBASE_H__

#include "YanaPServer/Socket/Socket.h"
using namespace YanaPServer::Socket;

namespace YanaPServer
{
namespace Peer
{

/**
 * @class CPeerBase
 * @brief �s�A���N���X
 */
class CPeerBase
{

public:
	
	/**
	 * @brief �R���X�g���N�^
	 * @param[in] pInSocket �\�P�b�g
	 */
	CPeerBase(ISocket *pInSocket);

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CPeerBase();

	/**
	 * @fn bool IsValid() const
	 * @brief �L�����H
	 * @return �L���Ȃ�true��Ԃ��B
	 */
	bool IsValid() const { return (pSocket != nullptr && pSocket->IsValid()); }

	/**
	 * @fn void Send(const char *pData, unsigned int Size)
	 * @brief ���M
	 * @param[in] pData �f�[�^
	 * @param[in] Size �f�[�^��
	 */
	void Send(const char *pData, unsigned int Size);

protected:

	/**
	 * @fn virtual void OnRecv(const char *pData, unsigned int Size) = 0
	 * @brief ��M�������̏���
	 * @param[in] pData �f�[�^
	 * @param[in] Size �f�[�^��
	 */
	virtual void OnRecv(const char *pData, unsigned int Size) = 0;

private:

	// �\�P�b�g
	ISocket *pSocket;
	

	// �\�P�b�g���.
	void ReleaseSocket();

};

}
}

#endif		// #ifndef __PEERBASE_H__
