#include "WindowsListenSocket.h"
#ifdef _WIN32

namespace YanaPServer
{
namespace Socket
{
namespace Listen
{

CWindowsListenSocket CWindowsListenSocket::Instance;

// �R���X�g���N�^
CWindowsListenSocket::CWindowsListenSocket()
	: Socket(INVALID_SOCKET)
{
}

// �f�X�g���N�^
CWindowsListenSocket::~CWindowsListenSocket()
{
	if (Socket == INVALID_SOCKET) { return; }

	closesocket(Socket);
	WSACleanup();

	Socket = INVALID_SOCKET;
}

// Listen�J�n.
bool CWindowsListenSocket::Listen(unsigned int Port)
{
	if (Socket != INVALID_SOCKET) { return true; }		// �������ς݁B

	WSADATA WsaData;
	int Result = WSAStartup(MAKEWORD(2, 0), &WsaData);
	if (Result != 0) { return false; }

	Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (Socket == INVALID_SOCKET)
	{
		WSACleanup();
		return false;
	}

	sockaddr_in Addr;

	Addr.sin_family = AF_INET;
	Addr.sin_port = htons(Port);
	Addr.sin_addr.S_un.S_addr = INADDR_ANY;

	if (bind(Socket, (sockaddr *)(&Addr), sizeof(Addr)) == SOCKET_ERROR) { return false; }

	if (listen(Socket, 1) == SOCKET_ERROR) { return false; }

	return true;
}

}
}
}

#endif		// #ifdef _WIN32
