#ifndef __PEERBASE_H__
#define __PEERBASE_H__

#include "YanaPServer/Socket/Socket.h"
using namespace YanaPServer::Socket;

namespace YanaPServer
{
namespace Peer
{

/**
 * @class PeerBase
 * @brief �s�A���N���X
 */
class PeerBase
{

public:
	
	/**
	 * @brief �R���X�g���N�^
	 * @param[in] pInSocket �\�P�b�g
	 */
	PeerBase(ISocket *pInSocket);

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~PeerBase() = 0;

	/**
	 * @fn bool IsValid() const
	 * @brief �L�����H
	 * @return �L���Ȃ�true��Ԃ��B
	 */
	bool IsValid() const { return (pSocket != nullptr); }

private:

	// �\�P�b�g
	ISocket *pSocket;
	

	// �\�P�b�g���.
	void ReleaseSocket();

};

}
}

#endif		// #ifndef __PEERBASE_H__
