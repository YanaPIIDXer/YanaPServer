#ifdef _WIN32
#include "WidnowsSocket.h"

namespace YanaPServer
{
namespace Socket
{

// �R���X�g���N�^
CWindowsSocket::CWindowsSocket(const SOCKET &InSocket)
	: Socket(InSocket)
{
}

// �f�X�g���N�^
CWindowsSocket::~CWindowsSocket()
{
	Release();
}

// ���.
void CWindowsSocket::Release()
{
	if (Socket == INVALID_SOCKET) { return; }

	closesocket(Socket);
	Socket = INVALID_SOCKET;
}

}
}

#endif		// #ifdef _WIN32
