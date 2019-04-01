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
	 * @fn virtual void Release()
	 * @brief ���
	 */
	virtual void Release() {}

};

}
}

#endif		// #ifndef __NULLSOCKETBEHAVIOUR_H__
