#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "WidnowsSocket.h"
#include "YanaPServer/Socket/Windows/WinSockManager.h"

namespace YanaPServer
{
namespace Socket
{

// コンストラクタ
CWindowsSocket::CWindowsSocket(const SOCKET &InSocket)
	: Socket(InSocket)
	, NonBlockingMode(1)
	, State(EState::Connected)
{
	ioctlsocket(Socket, FIONBIO, &NonBlockingMode);
}

// コンストラクタ
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

// デストラクタ
CWindowsSocket::~CWindowsSocket()
{
	Release();
}

// 毎フレーム実行する処理
void CWindowsSocket::Poll()
{
	if (State == EState::Connecting)
	{
		if (connect(Socket, (sockaddr *)&ConnectAddr, sizeof(ConnectAddr)))
		{
			State = EState::Connected;
		}
	}
}

// 解放.
void CWindowsSocket::Release()
{
	if (Socket == INVALID_SOCKET) { return; }

	closesocket(Socket);
	Socket = INVALID_SOCKET;
}

}
}

#endif		// #ifdef _WIN32
