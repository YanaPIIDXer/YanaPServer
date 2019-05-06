#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Socket/WidnowsSocket.h"
#include "Socket/Windows/WinSockManager.h"

namespace YanaPServer
{
namespace Socket
{

// �R���X�g���N�^
CWindowsSocket::CWindowsSocket(const SOCKET &InSocket)
	: Socket(InSocket)
	, NonBlockingMode(1)
	, State(EState::Connected)
{
	ioctlsocket(Socket, FIONBIO, &NonBlockingMode);
}

// �R���X�g���N�^
CWindowsSocket::CWindowsSocket(const std::string &Host, unsigned int Port)
	: Socket(INVALID_SOCKET)
	, NonBlockingMode(1)
	, State(EState::Connecting)
{
	if (!Windows::CWinSockManager::GetInstance().Initialize()) { return; }

	Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (Socket == INVALID_SOCKET) { return; }

	ConnectAddr.sin_family = AF_INET;
	ConnectAddr.sin_port = htons(Port);
	ConnectAddr.sin_addr.S_un.S_addr = inet_addr(Host.c_str());

	ioctlsocket(Socket, FIONBIO, &NonBlockingMode);
}

// �f�X�g���N�^
CWindowsSocket::~CWindowsSocket()
{
	Release();
}

// ���t���[�����s���鏈��
void CWindowsSocket::Poll()
{
	if (!IsValid()) { return; }

	switch (State)
	{
		case EState::Connecting:

			if (connect(Socket, (sockaddr *)&ConnectAddr, sizeof(ConnectAddr)))
			{
				State = EState::Connected;
			}
			break;

		case EState::Connected:

			SendProc();
			RecvProc();
			break;
	}
}

// ���M.
bool CWindowsSocket::Send(const char *pData, unsigned int Size)
{
	if (!IsValid()) { return false; }

	for (unsigned int i = 0; i < Size; i++)
	{
		DataQueue.push(pData[i]);
	}
	return true;
}

// ���.
void CWindowsSocket::Release()
{
	if (Socket == INVALID_SOCKET) { return; }

	closesocket(Socket);
	Socket = INVALID_SOCKET;
}


// ���M����.
void CWindowsSocket::SendProc()
{
	if (DataQueue.size() == 0) { return; }

	int SendSize = send(Socket, &DataQueue.front(), DataQueue.size(), 0);
	if (SendSize == SOCKET_ERROR) { return; }

	for (int i = 0; i < SendSize; i++)
	{
		DataQueue.pop();
	}
}

// ��M����.
void CWindowsSocket::RecvProc()
{
	// �R�[���o�b�N���ݒ肳��Ă��Ȃ��ꍇ�͉������Ȃ��B
	if (!ReceiveCallback) { return; }

	static const int BufferSize = 2048;
	char Buffer[BufferSize];
	memset(Buffer, 0, BufferSize);

	int RecvSize = recv(Socket, Buffer, BufferSize, 0);
	if (RecvSize == SOCKET_ERROR) { return; }

	ReceiveCallback(Buffer, RecvSize);
}

}
}

#endif		// #ifdef _WIN32