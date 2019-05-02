#ifndef __APPLICATIONBASE_H__
#define __APPLICATIONBASE_H__
#include "YanaPServer/Socket/Socket.h"
using namespace YanaPServer::Socket;
#include "YanaPServer/Peer/PeerBase.h"
using namespace YanaPServer::Peer;
#include <vector>
#include <memory>
#include <functional>

typedef std::weak_ptr<CPeerBase> PeerPtr;

namespace YanaPServer
{
namespace Application
{

/**
 * @class CApplicationBase
 * @brief �A�v���P�[�V�������C�����N���X
 */
class CApplicationBase
{

private:		// �ʖ���`.

	typedef std::shared_ptr<CPeerBase> PeerSharedPtr;
	typedef std::vector<PeerSharedPtr> PeerList;

public:

	/**
	 * @brief �R���X�g���N�^
	 * @param[in] ListenPort �ҋ@�|�[�g
	 */
	CApplicationBase(unsigned int ListenPort, const std::function<void(PeerPtr)> &OnConnectFunction);

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CApplicationBase();

	/**
	 * @fn void Poll()
	 * @brief ���t���[���̏���
	 * @detail ���C���t���[���ŌĂяo�����B
	 */
	void Poll();

protected:

	/**
	 * @fn virtual CPeerBase *CreatePeer(ISocket *pSocket) = 0
	 * @brief Peer����
	 * @param[in] pSocket �\�P�b�g
	 * @return CPeerBase��h�������I�u�W�F�N�g�𐶐����ĕԂ��B
	 */
	virtual CPeerBase *CreatePeer(ISocket *pSocket) = 0;

private:

	// Peer���X�g
	PeerList Peers;

	// �ڑ����R�[���o�b�N
	std::function<void(PeerPtr)> OnConnect;


	// Listen�����B
	void OnListen(ISocket *pSocket);

};

}
}

#endif		// #ifndef __APPLICATIONBASE_H__
