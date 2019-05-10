#ifndef __PEERBASE_H__
#define __PEERBASE_H__

#include "Socket/Socket.h"
#include "Socket/SocketEventListener.h"

namespace YanaPServer
{
namespace Peer
{

/**
 * @class CPeerBase
 * @brief �s�A���N���X
 * @detail ��{�I�ɂ̓R�C�c��h�������N���X��weak_ptr�𗘗p�ґ��ŊǗ�����B
 *	       �ؒf���ɂ͏���ɏ�������i�e�ɂȂ�shared_ptr��������j�̂ŁA
 *	       �R�C�c���g���ĉ�����鎞��expired()�`�F�b�N���Ȃ��Ǝ��Ȃ܂���B
 */
class CPeerBase : public YanaPServer::Socket::ISocketEventListener
{

public:
	
	/**
	 * @brief �R���X�g���N�^
	 * @param[in] pInSocket �\�P�b�g
	 */
	CPeerBase(YanaPServer::Socket::ISocket *pInSocket);

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CPeerBase() = 0;

	/**
	 * @fn void Poll()
	 * @brief ���t���[���̏���
	 */
	void Poll();

	/**
	 * @fn void SetOverrideEventListener(ISocketEventListener *pListener)
	 * @brief �\�P�b�g�C�x���g���I�[�o�[���C�h����C�x���g���X�i���Z�b�g
	 * @detail �C�x���g���X�i�̃������Ǘ��idelete���j�͍s��Ȃ��̂Œ��ӁB
	 * @param[in] pListener �C�x���g���X�i
	 */
	void SetOverrideEventListener(ISocketEventListener *pListener);

	/**
	 * @fn void RemoveOverrideEventListener()
	 * @brief �\�P�b�g�C�x���g���I�[�o�[���C�h����C�x���g���X�i�������B
	 */
	void RemoveOverrideEventListener() { SetOverrideEventListener(this); }

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

	/**
	 * @fn virtual void OnDisconnect() override
	 * @brief �ؒf���ꂽ
	 */
	virtual void OnDisconnect() override {}

private:

	// �\�P�b�g
	YanaPServer::Socket::ISocket *pSocket;


	// �\�P�b�g���.
	void ReleaseSocket();

};

}
}

#endif		// #ifndef __PEERBASE_H__