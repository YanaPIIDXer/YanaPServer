#ifndef __WINDOWSSOCKETBEHAVIOUR_H__
#define __WINDOWSSOCKETBEHAVIOUR_H__

#ifdef _WIN32

#include "Socket.h"
#include <WinSock2.h>
#include <string>
#include <queue>

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
	 * @param[in] InSocket �\�P�b�g
	 */
	CWindowsSocket(const SOCKET &InSocket);

	/**
	 * @brief �R���X�g���N�^
	 * @param[in] Host �z�X�g
	 * @param[in] Port �|�[�g�ԍ�
	 */
	CWindowsSocket(const std::string &Host, unsigned int Port);

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CWindowsSocket();

	/**
	 * @fn virtual void Poll()
	 * @brief ���t���[�����s���鏈��
	 */
	virtual void Poll();

	/**
	 * @fn virtual bool IsValid() const
	 * @brief �L�����H
	 * @return �L���Ȃ�true��Ԃ��B
	 */
	virtual bool IsValid() const { return (Socket != INVALID_SOCKET); }

	/**
	 * @fn virtual bool Send(const char *pData, unsigned int Size)
	 * @brief ���M
	 * @param[in] pData �f�[�^
	 * @param[in] Size ���M�T�C�Y
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Send(const char *pData, unsigned int Size);

	/**
	 * @fn virtual void Release()
	 * @brief �������
	 */
	virtual void Release();

private:

	// State
	class EState
	{
	public:
		enum
		{
			Connecting,
			Connected,
		};
	};

	// �\�P�b�g
	SOCKET Socket;

	// �m���u���b�L���O���[�h
	u_long NonBlockingMode;

	// �X�e�[�g
	unsigned char State;

	// �ڑ���A�h���X
	sockaddr_in ConnectAddr;

	// �f�[�^�L���[
	std::queue<char> DataQueue;


	// ���M����.
	void SendProc();

};

}
}

#endif		// #ifdef _WIN32

#endif		// #ifndef __WINDOWSSOCKETBEHAVIOUR_H__
