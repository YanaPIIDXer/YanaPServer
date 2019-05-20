#ifndef __NULLSOCKETBEHAVIOUR_H__
#define __NULLSOCKETBEHAVIOUR_H__

#include "Socket.h"

namespace YanaPServer
{
namespace Socket
{

/**
 * @class CNullSocket
 * @brief �������Ȃ�Socket
 *		  ����`�̃v���b�g�t�H�[���Ŏg�p�����B
 */
class CNullSocket : public ISocket
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CNullSocket() {}

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CNullSocket() {}

	/**
	 * @fn virtual void Poll() override
	 * @brief ���t���[�����s���鏈��
	 */
	virtual void Poll() override {}

	/**
	 * @fn virtual bool Connect(const char *pHost, unsigned int Port) override
	 * @brief �ڑ�
	 * @param[in] pHost �z�X�g
	 * @param[in] Port �|�[�g
	 * @return �������Ȃ��̂ŏ��false��Ԃ��B
	 */
	virtual bool Connect(const char *pHost, unsigned int Port) override { return false; }

	/**
	 * @fn virtual void SetEventListener() override
	 * @brief �C�x���g���X�i���Z�b�g
	 * @param[in] pListener �C�x���g���X�i
	 */
	virtual void SetEventListener(ISocketEventListener *pListener) override {}

	/**
	 * @fn virtual bool IsValid() const override
	 * @brief �L�����H
	 * @return �L���ɂ͂Ȃ�Ȃ��̂ŏ��false��Ԃ��B
	 */
	virtual bool IsValid() const override { return false; }

	/**
	 * @fn virtual bool Send(const char *pData, unsigned int Size) override
	 * @brief ���M
	 * @param[in] pData �f�[�^
	 * @param[in] Size ���M�T�C�Y
	 * @return �������Ȃ��̂ŏ��false��Ԃ��B
	 */
	virtual bool Send(const char *pData, unsigned int Size) override { return false; }

	/**
	 * @fn virtual void Release(ESocketDisconnectReason Reason) override
	 * @brief ���
	 * @param[in] Reason �ؒf���R
	 */
	virtual void Release(ESocketDisconnectReason Reason) override {}

};

}
}

#endif		// #ifndef __NULLSOCKETBEHAVIOUR_H__
