#ifdef _WIN32
#include "WidnowsSocket.h"

namespace YanaPServer
{
namespace Socket
{

// コンストラクタ
CWindowsSocket::CWindowsSocket(const SOCKET &InSocket)
	: Socket(InSocket)
{
}

// デストラクタ
CWindowsSocket::~CWindowsSocket()
{
	Release();
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
