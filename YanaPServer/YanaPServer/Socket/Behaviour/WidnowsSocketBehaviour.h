#ifndef __WINDOWSSOCKETBEHAVIOUR_H__
#define __WINDOWSSOCKETBEHAVIOUR_H__

#include "SocketBehaviour.h"
#include <WinSock2.h>

namespace YanaPServer
{
namespace Socket
{
namespace Behaviour
{

/**
 * @class CWindowsSocketBehaviour
 * @brief Windows�ł̃\�P�b�g�̋�������������N���X
 */
class CWindowsSocketBehaviour : public ISocketBehaviour
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CWindowsSocketBehaviour();

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CWindowsSocketBehaviour();

	/**
	 * @fn virtual bool Initialize()
	 * @brief ������
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Initialize();

	/**
	 * @fn virtual void Release()
	 * @brief �������
	 */
	virtual void Release();

private:

	// ����������Ă��邩�H
	bool bInitialized;

};

}
}
}

#endif		// #ifndef __WINDOWSSOCKETBEHAVIOUR_H__
