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
	 * @fn virtual void Poll()
	 * @brief ���t���[�����s���鏈��
	 */
	virtual void Poll() {}

	/**
	 * @fn virtual bool IsValid() const
	 * @brief �L�����H
	 * @return �L���ɂ͂Ȃ�Ȃ��̂ŏ��false��Ԃ��B
	 */
	virtual bool IsValid() const { return false; }

	/**
	 * @fn virtual bool Send(const char *pData, unsigned int Size)
	 * @brief ���M
	 * @param[in] pData �f�[�^
	 * @param[in] Size ���M�T�C�Y
	 * @return �������Ȃ��̂ŏ��false��Ԃ��B
	 */
	virtual bool Send(const char *pData, unsigned int Size) { return false; }

	/**
	 * @fn virtual void Release()
	 * @brief ���
	 */
	virtual void Release() {}

};

}
}

#endif		// #ifndef __NULLSOCKETBEHAVIOUR_H__
