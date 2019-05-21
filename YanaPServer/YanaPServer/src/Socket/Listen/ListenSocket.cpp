#include "Socket/Listen/ListenSocket.h"
#include "Socket/Listen/WindowsListenSocket.h"
#include "Socket/Listen/LinuxListenSocket.h"
#include "Socket/Listen/NullListenSocket.h"

#include <iostream>

namespace YanaPServer
{
namespace Socket
{
namespace Listen
{

// 構築.
ListenSocketPtr CListenSocket::Build(unsigned int Port, const std::function<void(ISocket *)> &AcceptCallback)
{
	ListenSocketPtr pListenSocket = Create();

	std::cout << "Init" << std::endl;
	if (!pListenSocket->Init()) { return ListenSocketPtr(); }

	std::cout << "Bind" << std::endl;
	if (!pListenSocket->Bind(Port)) { return ListenSocketPtr(); }

	std::cout << "Listen" << std::endl;
	if (!pListenSocket->Listen()) { return ListenSocketPtr(); }

	std::cout << "OK" << std::endl;

	pListenSocket->SetAcceptCallback(AcceptCallback);
	return pListenSocket;
}


// ListenSocketオブジェクト取得.
ListenSocketPtr CListenSocket::Create()
{
	IListenSocket *pListenSocket = nullptr;
#ifdef _WIN32
	pListenSocket = new CWindowsListenSocket();
#elif defined _LINUX
	pListenSocket = new CLinuxListenSocket();
#else
	pListenSocket = new CNullListenSocket();
#endif

	return ListenSocketPtr(pListenSocket);
}

}
}
}
