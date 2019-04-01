#include "Socket.h"
#include "Behaviour/SocketBehaviour.h"
#include "Behaviour/WidnowsSocketBehaviour.h"
#include "Behaviour/NullSocketBehaviour.h"

using namespace YanaPServer::Socket::Behaviour;

namespace YanaPServer
{
namespace Socket
{

// コンストラクタ
CSocket::CSocket()
	: pBehaviour(NULL)
{
}

// デストラクタ
CSocket::~CSocket()
{
	ReleaseBehaviour();
}

// 初期化.
bool CSocket::Initialize()
{
#ifdef _WIN32
	pBehaviour = new CWindowsSocketBehaviour();
#else
	pBehaviour = new CNullSocketBehaviour();
#endif
	if (!pBehaviour->Initialize())
	{
		ReleaseBehaviour();
		return false;
	}

	return true;
}


// 挙動インタフェースの解放.
void CSocket::ReleaseBehaviour()
{
	if (pBehaviour == NULL) { return; }

	pBehaviour->Release();
	delete pBehaviour;
	pBehaviour = NULL;
}

}
}
