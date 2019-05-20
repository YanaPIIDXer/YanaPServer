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

	// コンストラクタ
	Peer(ISocket *pSocket)
		: CPeerBase(pSocket)
	{
	}

	// デストラクタ
	virtual ~Peer()
	{
	}

	// 受信した
	virtual void OnRecv(const char * pData, unsigned int Size) override
	{
		// そのまま送り返す。
		Send(pData, Size);
	}

private:


};

// サーバ
class Server : public CApplicationBase
{

public:

	// コンストラクタ
	Server()
		: CApplicationBase([this](PeerPtr pPeer)
	{
	})
	{
	}

	// デストラクタ
	virtual ~Server()
	{
	}

protected:

	// Peer生成.
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
