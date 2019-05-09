#include "Socket/Listen/WindowsListenSocket.h"
#include "Socket/WidnowsSocket.h"
#include "Socket/Windows/WinSockManager.h"
#ifdef _WIN32

namespace YanaPServer
{
namespace Socket
{
namespace Listen
{

CWindowsListenSocket CWindowsListenSocket::Instance;

// �R���X�g���N�^
CWindowsListenSocket::CWindowsListenSocket()
	: Socket(INVALID_SOCKET)
	, NonBlockingMode(1)
{
}

// �f�X�g���N�^
CWindowsListenSocket::~CWindowsListenSocket()
{
	Release();
}

// ���t���[���Ăяo������
void CWindowsListenSocket::Poll()
{
	if (Socket == INVALID_SOCKET) { return; }

	sockaddr_in Addr;
	int Len = sizeof(Addr);
	SOCKET AcceptSocket = accept(Socket, (sockaddr *)&Addr, &Len);
	if (AcceptSocket == INVALID_SOCKET) { return; }

	CWindowsSocket *pNewSocket = new CWindowsSocket(AcceptSocket);
	OnAccept(pNewSocket);
}

// Listen�J�n.
bool CWindowsListenSocket::Listen(unsigned int Port, const std::function<void(ISocket *)> &AcceptCallback)
{
	if (Socket != INVALID_SOCKET) { return true; }		// �������ς݁B

	if (!Socket::Windows::CWinSockManager::GetInstance().Initialize()) { return false; }

	Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (Socket == INVALID_SOCKET) { return false; }

	if (!Bind(Port))
	{
		Release();
		return false;
	}

	if (listen(Socket, 1) == SOCKET_ERROR)
	{
		Release();
		return false;
	}

	ioctlsocket(Socket, FIONBIO, &NonBlockingMode);

	OnAccept = AcceptCallback;
	return true;
}


// �o�C���h
bool CWindowsListenSocket::Bind(unsigned int Port)
{
	sockaddr_in Addr;

	Addr.sin_family = AF_INET;
	Addr.sin_port = htons(Port);
	Addr.sin_addr.S_un.S_addr = INADDR_ANY;

	return (bind(Socket, (sockaddr *)(&Addr), sizeof(Addr)) != SOCKET_ERROR);
}

// ���.
void CWindowsListenSocket::Release()
{
	if (Socket == INVALID_SOCKET) { return; }

	closesocket(Socket);
	Socket = INVALID_SOCKET;
}

}
}
}

#endif		// #ifdef _WIN32
