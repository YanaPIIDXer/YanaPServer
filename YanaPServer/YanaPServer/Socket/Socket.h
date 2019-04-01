#ifndef __SOCKETBEHAVIOUR_H__
#define __SOCKETBEHAVIOUR_H__

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
	 * @fn virtual void Release() = 0
	 * @brief ���
	 */
	virtual void Release() = 0;

};

}
}

#endif		// #ifndef __SOCKETBEHAVIOUR_H__
