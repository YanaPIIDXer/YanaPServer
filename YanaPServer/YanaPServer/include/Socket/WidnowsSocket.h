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
	 * @fn virtual void Poll() override
	 * @brief ���t���[�����s���鏈��
	 */
	virtual void Poll() override;

	/**
	 * @fn virtual bool IsValid() const override
	 * @brief �L�����H
	 * @return �L���Ȃ�true��Ԃ��B
	 */
	virtual bool IsValid() const override { return (Socket != INVALID_SOCKET); }

	/**
	 * @fn virtual bool Send(const char *pData, unsigned int Size) override
	 * @brief ���M
	 * @param[in] pData �f�[�^
	 * @param[in] Size ���M�T�C�Y
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Send(const char *pData, unsigned int Size) override;

	/**
	 * @fn virtual void SetReceiveCallback(const std::function<void(const char *, unsigned int)> &Callback) override
	 * @brief ��M�R�[���o�b�N��ݒ�
	 * @param[in] Callback �R�[���o�b�N�֐�
	 */
	virtual void SetReceiveCallback(const std::function<void(const char *, unsigned int)> &Callback) override { ReceiveCallback = Callback; }

	/**
	 * @fn virtual void Release() override
	 * @brief �������
	 */
	virtual void Release() override;

	/**
	 * @fn virtual void SetReleaseCallback(const std::function<void()> &Callback) override
	 * @brief ����R�[���o�b�N��ݒ�
	 * @param[in] Callback ����R�[���o�b�N
	 */
	virtual void SetReleaseCallback(const std::function<void()> &Callback) override { ReleaseCallback = Callback; }

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

	// ��M�R�[���o�b�N
	std::function<void(const char *, unsigned int)> ReceiveCallback;

	// ����R�[���o�b�N
	std::function<void()> ReleaseCallback;


	// ���M����.
	void SendProc();

	// ��M����.
	void RecvProc();

};

}
}

#endif		// #ifdef _WIN32

#endif		// #ifndef __WINDOWSSOCKETBEHAVIOUR_H__
