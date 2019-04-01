#ifndef __NULLSOCKETBEHAVIOUR_H__
#define __NULLSOCKETBEHAVIOUR_H__

#include "SocketBehaviour.h"

namespace YanaPServer
{
namespace Socket
{
namespace Behaviour
{

/**
 * @class CNullSocketBehaviour
 * @brief �������Ȃ�SocketBehaviour
 *		  ����`�̃v���b�g�t�H�[���Ŏg�p�����B
 */
class CNullSocketBehaviour : public ISocketBehaviour
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CNullSocketBehaviour() {}

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CNullSocketBehaviour() {}

	/**
	 * @fn virtual void Release()
	 * @brief ���
	 */
	virtual void Release() {}

};

}
}
}

#endif		// #ifndef __NULLSOCKETBEHAVIOUR_H__
