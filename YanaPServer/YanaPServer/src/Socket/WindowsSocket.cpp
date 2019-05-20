#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Socket/WidnowsSocket.h"
#include "Socket/Windows/WinSockManager.h"
#include "Socket/SocketEventListener.h"

namespace YanaPServer
{
namespace Socket
{

// コンストラクタ
CWindowsSocket::CWindowsSocket()
	: Socket(INVALID_SOCKET)
	, NonBlockingMode(1)
	, State(EState::None)
	, pEventListener(nullptr)
{
}

// コンストラクタ
CWindowsSocket::CWindowsSocket(const SOCKET &InSocket)
	: Socket(InSocket)
	, NonBlockingMode(1)
	, State(EState::Connected)
	, pEventListener(nullptr)
{
	ioctlsocket(Socket, FIONBIO, &NonBlockingMode);
}

// デストラクタ
CWindowsSocket::~CWindowsSocket()
{
	Release(ESocketDisconnectReason::Destruct);
}

// 毎フレーム実行する処理
void CWindowsSocket::Poll()
{
	if (!IsValid()) { return; }

	switch (State)
	{
		case EState::Connecting:

			if (connect(Socket, (sockaddr *)&ConnectAddr, sizeof(ConnectAddr)))
			{
				State = EState::Connected;
				if (pEventListener != nullptr)
				{
					pEventListener->OnConnect();
				}
			}
			break;

		case EState::Connected:

			SendProc();
			RecvProc();
			break;
	}
}

// 接続.
bool CWindowsSocket::Connect(const char *pHost, unsigned int Port)
{
	if (!Windows::CWinSockManager::GetInstance().Initialize()) { return false; }

	// 接続中だった場合は切断。
	if (IsValid())
	{
		Release(ESocketDisconnectReason::Destruct);
	}

	Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (Socket == INVALID_SOCKET) { return false; }

	ConnectAddr.sin_family = AF_INET;
	ConnectAddr.sin_port = htons(Port);
	ConnectAddr.sin_addr.S_un.S_addr = inet_addr(pHost);

	ioctlsocket(Socket, FIONBIO, &NonBlockingMode);

	State = EState::Connecting;

	return true;
}

// 送信.
bool CWindowsSocket::Send(const char *pData, unsigned int Size)
{
	if (!IsValid()) { return false; }

	for (unsigned int i = 0; i < Size; i++)
	{
		DataQueue.push(pData[i]);
	}
	return true;
}

// 解放.
void CWindowsSocket::Release(ESocketDisconnectReason Reason)
{
	if (Socket == INVALID_SOCKET) { return; }

	closesocket(Socket);
	Socket = INVALID_SOCKET;

	if (pEventListener != nullptr)
	{
		pEventListener->OnDisconnect(Reason);
	}
}


// 送信処理.
void CWindowsSocket::SendProc()
{
	if (Socket == INVALID_SOCKET) { return; }

	if (DataQueue.size() == 0) { return; }

	int SendSize = send(Socket, &DataQueue.front(), DataQueue.size(), 0);
	if (SendSize == SOCKET_ERROR)
	{
		Release(ESocketDisconnectReason::SendError);
		return;
	}

	for (int i = 0; i < SendSize; i++)
	{
		DataQueue.pop();
	}
}

// 受信処理.
void CWindowsSocket::RecvProc()
{
	if (Socket == INVALID_SOCKET) { return; }

	// イベントリスナが設定されていない場合は何もしない。
	if (pEventListener == nullptr) { return; }

	static const int BufferSize = 2048;
	char Buffer[BufferSize];
	memset(Buffer, 0, BufferSize);

	int RecvSize = recv(Socket, Buffer, BufferSize, 0);
	if (RecvSize == SOCKET_ERROR)
	{
		Release(ESocketDisconnectReason::RecvError);
		return;
	}

	pEventListener->OnRecv(Buffer, RecvSize);
}

}
}

#endif		// #ifdef _WIN32
