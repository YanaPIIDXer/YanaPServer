#include "Socket/Listen/ListenSocket.h"
#include "Socket/Listen/WindowsListenSocket.h"
#include "Socket/Listen/NullListenSocket.h"

namespace YanaPServer
{
namespace Socket
{
namespace Listen
{

// �\�z.
bool CListenSocket::Build(unsigned int Port, const std::function<void(ISocket *)> &AcceptCallback)
{
	IListenSocket &ListenSocket = Get();

	if (!ListenSocket.Init()) { return false; }
	if (!ListenSocket.Bind(Port)) { return false; }
	if (!ListenSocket.Listen()) { return false; }

	ListenSocket.SetAcceptCallback(AcceptCallback);
	return true;
}


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
