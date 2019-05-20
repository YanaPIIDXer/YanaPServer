#include <iostream>
#include "YanaPServer/Application/ApplicationBase.h"
#include "YanaPServer/Peer/PeerBase.h"

using namespace YanaPServer::Application;
using namespace YanaPServer::Peer;
using namespace YanaPServer::Socket;

// Peer
class Peer : public CPeerBase
{

public:

	// �R���X�g���N�^
	Peer(ISocket *pSocket)
		: CPeerBase(pSocket)
	{
	}

	// �f�X�g���N�^
	virtual ~Peer()
	{
	}

	// �ڑ����ꂽ�B
	virtual void OnConnect() override
	{
		std::cout << "Peer Connected." << std::endl;
	}

	// ��M����
	virtual void OnRecv(const char * pData, unsigned int Size) override
	{
		std::cout << "Recv Data:" << pData << std::endl;

		// ���̂܂ܑ���Ԃ��B
		Send(pData, Size);
	}

	// �ؒf���ꂽ�B
	virtual void OnDisconnect() override
	{
		std::cout << "Peer Disconnected." << std::endl;
	}

private:


};

// �T�[�o
class Server : public CApplicationBase
{

public:

	// �R���X�g���N�^
	Server()
		: CApplicationBase([this](PeerPtr pPeer)
	{
	})
	{
	}

	// �f�X�g���N�^
	virtual ~Server()
	{
	}

protected:

	// Peer����.
	virtual YanaPServer::Peer::CPeerBase *CreatePeer(YanaPServer::Socket::ISocket * pSocket) override
	{
		return new Peer(pSocket);
	}


private:

};

int main()
{
	std::cout << "Test Server" << std::endl;

	Server Sv;
	if (!Sv.StartListen(4424)) { return 1; }

	while(Sv.Service()){}

	return 0;
}
