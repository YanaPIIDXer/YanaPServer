#include <iostream>
#include <string>
#include "YanaPServer/Socket/WidnowsSocket.h"
#include "YanaPServer/Socket/SocketEventListener.h"

using namespace YanaPServer::Socket;

// ソケットイベント
class SocketEvent : public ISocketEventListener
{

public:

	// コンストラクタ
	SocketEvent()
	{
	}

	// デストラクタ
	virtual ~SocketEvent()
	{
	}

	// 接続された
	virtual void OnConnect() override
	{
		std::cout << "Connected." << std::endl;
	}

	// 受信した。
	virtual void OnRecv(const char * pData, unsigned int Size) override
	{
		std::cout << "RecvData Size:" << Size << std::endl;
		std::cout << "Data:" << pData << std::endl;
	}

	// 切断された。
	virtual void OnDisconnect(ESocketDisconnectReason Reason) override
	{
		std::cout << "Disconnect." << std::endl;
		std::cout << "Reason:";
		switch (Reason)
		{
			case ESocketDisconnectReason::Destruct:

				std::cout << "Destruct" << std::endl;
				break;

			case ESocketDisconnectReason::SendError:

				std::cout << "SendError" << std::endl;
				break;

			case ESocketDisconnectReason::RecvError:

				std::cout << "RecvError" << std::endl;
				break;

		}
	}

};

int main()
{
	std::cout << "Test Client" << std::endl;

	CWindowsSocket Socket;
	SocketEvent Event;
	Socket.SetEventListener(&Event);
	if (!Socket.Connect("127.0.0.1", 4424))
	{
		std::cout << "Connect Failed." << std::endl;

		std::string Dummy;
		std::cin >> Dummy;

		return 1;
	}

	while (true)
	{
		Socket.Poll();
		std::string SendData;
		std::cout << "送信データ：";
		std::cin >> SendData;
		if (Socket.Send(SendData.c_str(), SendData.size() + 1))
		{
			std::cout << "Send Success." << std::endl;
		}
		else
		{
			std::cout << "Send Failed." << std::endl;
			break;
		}
	}

	std::string Dummy;
	std::cin >> Dummy;
	
	return 0;
}
