#include <iostream>
#include <string>
#include "YanaPServer/Socket/WidnowsSocket.h"
#include "YanaPServer/Socket/SocketEventListener.h"

using namespace YanaPServer::Socket;

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
		std::cout << "Data:" << pData << std::endl;
	}

	// �ؒf���ꂽ�B
	virtual void OnDisconnect() override
	{
		std::cout << "Disconnect." << std::endl;
	}

};

int main()
{
	std::cout << "Test Client" << std::endl;

	CWindowsSocket Socket;
	SocketEvent Event;
	Socket.SetEventListener(&Event);
	if (!Socket.Connect("127.0.0.1", 4424)) { return 1; }

	while (true)
	{
		Socket.Poll();
		std::string SendData;
		std::cout << "���M�f�[�^�F";
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
