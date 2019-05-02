#include "ListenSocket.h"
#include "WindowsListenSocket.h"
#include "NullListenSocket.h"

namespace YanaPServer
{
namespace Socket
{
namespace Listen
{

// ListenSocketオブジェクト取得.
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
