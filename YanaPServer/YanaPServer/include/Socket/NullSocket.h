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
	 * @fn virtual void SetReceiveCallback(const std::function<void(const char *, unsigned int)> &Callback) override
	 * @brief ��M�R�[���o�b�N��ݒ�
	 * @param[in] Callback �R�[���o�b�N�֐�
	 */
	virtual void SetReceiveCallback(const std::function<void(const char *, unsigned int)> &Callback) override {}

	/**
	 * @fn virtual void Release() override
	 * @brief ���
	 */
	virtual void Release() override {}

};

}
}

#endif		// #ifndef __NULLSOCKETBEHAVIOUR_H__
