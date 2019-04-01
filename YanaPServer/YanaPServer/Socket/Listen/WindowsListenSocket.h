#ifndef __WINDOWSLISTENSOCKET_H__
#define __WINDOWSLISTENSOCKET_H__

#ifdef _WIN32
#include <WinSock2.h>
#include "ListenSocket.h"

namespace YanaPServer
{
namespace Socket
{
namespace Listen
{

/**
 * @class CWindowsListenSocket
 * @brief Windows��Listen�p�\�P�b�g�N���X
 * @detail �V���O���g���N���X
 */
class CWindowsListenSocket : public IListenSocket
{

public:

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CWindowsListenSocket();

	/**
	 * @fn virtual bool Listen(unsigned int Port)
	 * @brief Listen�J�n
	 * @param[in] Port �|�[�g�ԍ�
	 * @return ����ɏ������I��������true��Ԃ��B
	 */
	virtual bool Listen(unsigned int Port);

private:

	// �\�P�b�g
	SOCKET Socket;

	// ======== Singleton =============
public:

	/**
		* @fn static CWindowsListenSocket &GetInstance()
		* @brief �V���O���g���C���X�^���X�擾
		* @return �V���O���g���C���X�^���X
		*/
	static CWindowsListenSocket &GetInstance() { return Instance; }

private:

	CWindowsListenSocket();
	static CWindowsListenSocket Instance;

};

}
}
}

#endif		// #ifdef _WIN32


#endif			// #ifndef __WINDOWSLISTENSOCKET_H__
