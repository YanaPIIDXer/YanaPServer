#include "WidnowsSocketBehaviour.h"

namespace YanaPServer
{
namespace Socket
{
namespace Behaviour
{

// コンストラクタ
CWindowsSocketBehaviour::CWindowsSocketBehaviour()
	: bInitialized(false)
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
	WSADATA WsaData;
	WSAStartup(MAKEWORD(2, 0), &WsaData);

	bInitialized = true;
	return true;
}

// 解放.
void CWindowsSocketBehaviour::Release()
{
	if (!bInitialized) { return; }

	WSACleanup();

	bInitialized = false;
}

}
}
}
