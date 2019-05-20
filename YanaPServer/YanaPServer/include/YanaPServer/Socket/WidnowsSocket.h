#ifndef __WINDOWSSOCKETBEHAVIOUR_H__
#define __WINDOWSSOCKETBEHAVIOUR_H__

#ifdef _WIN32

#include "Socket.h"
#include <WinSock2.h>
#include <string>
#include <vector>

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
	CWindowsSocket();

	/**
	 * @brief �R���X�g���N�^
	 * @param[in] InSocket �\�P�b�g
	 */
	CWindowsSocket(const SOCKET &InSocket);

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
	 * @fn virtual bool Connect(const char *pHost, unsigned int Port) override
	 * @brief �ڑ�
	 * @param[in] pHost �z�X�g
	 * @param[in] Port �|�[�g
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Connect(const char *pHost, unsigned int Port) override;

	/**
	 * @fn virtual void SetEventListener() override
	 * @brief �C�x���g���X�i���Z�b�g
	 * @param[in] pListener �C�x���g���X�i
	 */
	virtual void SetEventListener(ISocketEventListener *pListener) override { pEventListener = pListener; }

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
	 * @fn virtual void Release(ESocketDisconnectReason Reason) override
	 * @brief �������
	 * @param[in] Reason �ؒf���R
	 */
	virtual void Release(ESocketDisconnectReason Reason) override;

private:

	// State
	class EState
	{
	public:
		enum
		{
			// �������Ă��Ȃ�
			None,

			// �ڑ���.
			Connecting,

			// �ڑ�����
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
	std::vector<char> DataQueue;

	// �C�x���g���X�i
	ISocketEventListener *pEventListener;


	// ���M����.
	void SendProc();

	// ��M����.
	void RecvProc();

};

}
}

#endif		// #ifdef _WIN32

#endif		// #ifndef __WINDOWSSOCKETBEHAVIOUR_H__
