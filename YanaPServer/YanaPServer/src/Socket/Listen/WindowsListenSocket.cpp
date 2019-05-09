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

// コンストラクタ
CWindowsListenSocket::CWindowsListenSocket()
	: Socket(INVALID_SOCKET)
	, NonBlockingMode(1)
{
}

// デストラクタ
CWindowsListenSocket::~CWindowsListenSocket()
{
	Release();
}

// 毎フレーム呼び出す処理
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

// Listen開始.
bool CWindowsListenSocket::Listen(unsigned int Port, const std::function<void(ISocket *)> &AcceptCallback)
{
	if (Socket != INVALID_SOCKET) { return true; }		// 初期化済み。

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


// バインド
bool CWindowsListenSocket::Bind(unsigned int Port)
{
	sockaddr_in Addr;

	Addr.sin_family = AF_INET;
	Addr.sin_port = htons(Port);
	Addr.sin_addr.S_un.S_addr = INADDR_ANY;

	return (bind(Socket, (sockaddr *)(&Addr), sizeof(Addr)) != SOCKET_ERROR);
}

// 解放.
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
