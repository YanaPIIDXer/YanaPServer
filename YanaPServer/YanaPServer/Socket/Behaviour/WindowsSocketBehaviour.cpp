#ifdef _WIN32
#include "WidnowsSocketBehaviour.h"

namespace YanaPServer
{
namespace Socket
{
namespace Behaviour
{

// コンストラクタ
CWindowsSocketBehaviour::CWindowsSocketBehaviour()
	: Socket(INVALID_SOCKET)
{
}

// デストラクタ
CWindowsSocketBehaviour::~CWindowsSocketBehaviour()
{
	Release();
}

// 解放.
void CWindowsSocketBehaviour::Release()
{
	if (Socket == INVALID_SOCKET) { return; }

	closesocket(Socket);
	Socket = INVALID_SOCKET;
}

}
}
}

#endif		// #ifdef _WIN32
