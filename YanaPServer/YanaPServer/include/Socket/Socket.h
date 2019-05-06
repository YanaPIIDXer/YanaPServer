#ifndef __SOCKETBEHAVIOUR_H__
#define __SOCKETBEHAVIOUR_H__

#include <functional>

namespace YanaPServer
{
namespace Socket
{

/**
 * @class ISocket
 * @brief �\�P�b�g�̋������������邽�߂̃C���^�t�F�[�X
 */
class ISocket
{

public:

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~ISocket() {}

	/**
	 * @fn virtual void Poll() = 0
	 * @brief ���t���[�����s���鏈��
	 */
	virtual void Poll() = 0;

	/**
	 * @fn virtual bool IsValid()
	 * @brief �L�����H
	 * @return �L���Ȃ�true��Ԃ��B
	 */
	virtual bool IsValid() const = 0;

	/**
	 * @fn virtual bool Send(const char *pData, unsigned int Size) = 0
	 * @brief ���M
	 * @param[in] pData �f�[�^
	 * @param[in] Size ���M�T�C�Y
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Send(const char *pData, unsigned int Size) = 0;

	/**
	 * @fn virtual void SetReceiveCallback(const std::function<void(const char *, unsigned int)> &Callback) = 0
	 * @brief ��M�R�[���o�b�N��ݒ�
	 * @param[in] Callback �R�[���o�b�N�֐�
	 */
	virtual void SetReceiveCallback(const std::function<void(const char *, unsigned int)> &Callback) = 0;

	/**
	 * @fn virtual void Release() = 0
	 * @brief ���
	 */
	virtual void Release() = 0;

};

}
}

#endif		// #ifndef __SOCKETBEHAVIOUR_H__