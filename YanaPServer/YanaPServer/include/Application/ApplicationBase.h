#ifndef __APPLICATIONBASE_H__
#define __APPLICATIONBASE_H__
#include "Socket/Socket.h"
using namespace YanaPServer::Socket;
#include "Peer/PeerBase.h"
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
	 * @param[in] OnConnectFunction �ڑ����R�[���o�b�N
	 */
	CApplicationBase(const std::function<void(PeerPtr)> &OnConnectFunction);

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CApplicationBase();

	/**
	 * @fn bool StartListen(unsigned int Port)
	 * @brief Listen�J�n
	 * @param[in] Port �ҋ@�|�[�g
	 * @return ����������true��Ԃ��B
	 */
	bool StartListen(unsigned int Port);

	/**
	 * @fn bool Service()
	 * @brief ���t���[���̏���
	 * @detail ���C���t���[���ŌĂяo�����B
	 * @return ���C�����[�v���I�����鎞��false��Ԃ��B
	 */
	bool Service();

protected:

	/**
	 * @fn virtual CPeerBase *CreatePeer(ISocket *pSocket) = 0
	 * @brief Peer����
	 * @param[in] pSocket �\�P�b�g
	 * @return CPeerBase��h�������I�u�W�F�N�g�𐶐����ĕԂ��B
	 */
	virtual CPeerBase *CreatePeer(ISocket *pSocket) = 0;

	/**
	 * @fn virtual bool Update()
	 * @brief �X�V����
	 * @return ���炩�̗v���Ń��C�����[�v�𔲂���ꍇ��false��Ԃ�
	 */
	virtual bool Update() { return true; }

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
