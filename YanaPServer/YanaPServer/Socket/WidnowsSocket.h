#ifndef __WINDOWSSOCKETBEHAVIOUR_H__
#define __WINDOWSSOCKETBEHAVIOUR_H__

#ifdef _WIN32

#include "Socket.h"
#include <WinSock2.h>

namespace YanaPServer
{
namespace Socket
{

/**
 * @class CWindowsSocket
 * @brief Windows�ł̃\�P�b�g�̋�������������N���X
 */
class CWindowsSocket : public ISocket
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CWindowsSocket(const SOCKET &InSocket);

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CWindowsSocket();

	/**
	 * @fn virtual void Release()
	 * @brief �������
	 */
	virtual void Release();

private:

	// �\�P�b�g
	SOCKET Socket;

};

}
}

#endif		// #ifdef _WIN32

#endif		// #ifndef __WINDOWSSOCKETBEHAVIOUR_H__
