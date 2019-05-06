#include "Socket/Listen/ListenSocket.h"
#include "Socket/Listen/WindowsListenSocket.h"
#include "Socket/Listen/NullListenSocket.h"

namespace YanaPServer
{
namespace Socket
{
namespace Listen
{

// ListenSocket�I�u�W�F�N�g�擾.
IListenSocket &CListenSocket::Get()
{
#ifdef _WIN32
	return CWindowsListenSocket::GetInstance();
#else
	return CNullListenSocket::GetInstance();
#endif
}

}
}
}
