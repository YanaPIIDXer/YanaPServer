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

// 初期化.
bool CWindowsSocketBehaviour::Initialize()
{
	if (Socket != INVALID_SOCKET)
	{
		// 一旦解放.
		Release();
	}

	WSADATA WsaData;
	int Result = WSAStartup(MAKEWORD(2, 0), &WsaData);
	if (Result != 0) { return false; }

	Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (Socket == INVALID_SOCKET)
	{
		WSACleanup();
		return false;
	}

	return true;
}

// 解放.
void CWindowsSocketBehaviour::Release()
{
	if (Socket == INVALID_SOCKET) { return; }

	WSACleanup();

	Socket = INVALID_SOCKET;
}

}
}
}
