#ifndef __WINDOWSLISTENSOCKET_H__
#define __WINDOWSLISTENSOCKET_H__

#ifdef _WIN32
#include <WinSock2.h>
#include "ListenSocket.h"

namespace YanaPServer
{
namespace Socket
{
class ISocket;

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
	 * @fn virtual void Poll()
	 * @brief ���t���[���Ăяo������
	 */
	virtual void Poll();

	/**
	 * @fn virtual bool Listen(unsigned int Port)
	 * @brief Listen�J�n
	 * @param[in] Port �|�[�g�ԍ�
	 * @param[in] AcceptCallback Accept�������̃R�[���o�b�N�֐�
	 * @return ����ɏ������I��������true��Ԃ��B
	 */
	virtual bool Listen(unsigned int Port, const std::function<void(ISocket *)> &AcceptCallback);

private:

	// �\�P�b�g
	SOCKET Socket;

	// �m���u���b�L���O���[�h
	u_long NonBlockingMode;

	// Accept���̃R�[���o�b�N
	std::function<void(ISocket *)> OnAccept;


	// �\�P�b�g�̏�����.
	bool Init();

	// �o�C���h
	bool Bind(unsigned int Port);

	// ���b�X��
	bool Listen();

	// ���.
	void Release();

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
