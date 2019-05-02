#include "ListenSocket.h"
#include "WindowsListenSocket.h"
#include "NullListenSocket.h"

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
