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

// ������.
bool CWindowsSocketBehaviour::Initialize()
{
	if (Socket != INVALID_SOCKET)
	{
		// ��U���.
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

// ���.
void CWindowsSocketBehaviour::Release()
{
	if (Socket == INVALID_SOCKET) { return; }

	WSACleanup();

	Socket = INVALID_SOCKET;
}

}
}
}

#endif		// #ifdef _WIN32
