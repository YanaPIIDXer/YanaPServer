#include <iostream>
#include <string>
#include "YanaPServer/Socket/WidnowsSocket.h"
#include "YanaPServer/Socket/SocketEventListener.h"
#include "YanaPServer/Util/Stream/StringStream.h"

using namespace YanaPServer::Socket;
using namespace YanaPServer::Util::Stream;

// �\�P�b�g�C�x���g
class SocketEvent : public ISocketEventListener
{

public:

	// �R���X�g���N�^
	SocketEvent()
	{
	}

	// �f�X�g���N�^
	virtual ~SocketEvent()
	{
	}

	// �ڑ����ꂽ
	virtual void OnConnect() override
	{
		std::cout << "Connected." << std::endl;
	}

	// ��M�����B
	virtual void OnRecv(const char * pData, unsigned int Size) override
	{
		std::cout << "RecvData Size:" << Size << std::endl;
		std::cout << "===== Data =====" << std::endl;
		std::cout << pData << std::endl;
	}

	// ���M�����B
	virtual void OnSend(unsigned int Size)
	{
	}

	// �ؒf���ꂽ�B
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

	CStringStream Header;
	Header.Append("GET / HTTP/1.1\n");
	Header.Append("HOST: localhost:4423\n");
	Header.Append("\n\n");
	Socket.Send(Header.Get(), Header.GetLength() + 1);

	while (Socket.IsValid())
	{
		Socket.Poll();
	}

	std::string Dummy;
	std::cin >> Dummy;
	
	return 0;
}
