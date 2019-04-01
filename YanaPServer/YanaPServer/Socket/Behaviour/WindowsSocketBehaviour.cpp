#ifdef _WIN32
#include "WidnowsSocketBehaviour.h"

namespace YanaPServer
{
namespace Socket
{
namespace Behaviour
{

// �R���X�g���N�^
CWindowsSocketBehaviour::CWindowsSocketBehaviour()
	: Socket(INVALID_SOCKET)
{
}

// �f�X�g���N�^
CWindowsSocketBehaviour::~CWindowsSocketBehaviour()
{
	Release();
}

// ���.
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
