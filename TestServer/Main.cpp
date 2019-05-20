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

	// 接続された。
	virtual void OnConnect() override
	{
		std::cout << "Peer Connected." << std::endl;
	}

	// 受信した
	virtual void OnRecv(const char * pData, unsigned int Size) override
	{
		std::cout << "Recv Data:" << pData << std::endl;

		// そのまま送り返す。
		Send(pData, Size);
	}

	// 切断された。
	virtual void OnDisconnect(ESocketDisconnectReason Reason) override
	{
		std::cout << "Peer Disconnected." << std::endl;
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
