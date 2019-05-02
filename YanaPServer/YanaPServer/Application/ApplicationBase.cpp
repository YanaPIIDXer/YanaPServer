#include "ApplicationBase.h"
#include "YanaPServer/Socket/Listen/ListenSocket.h"
using namespace YanaPServer::Socket::Listen;

namespace YanaPServer
{
namespace Application
{

// コンストラクタ
CApplicationBase::CApplicationBase(unsigned int ListenPort, const std::function<void(PeerPtr)> &OnConnectFunction)
	: OnConnect(OnConnectFunction)
{
	CListenSocket::Get().Listen(ListenPort,
		std::bind(&CApplicationBase::OnListen, this, std::placeholders::_1));
}

// デストラクタ
CApplicationBase::~CApplicationBase()
{
	Peers.clear();
}

// 毎フレームの処理.
void CApplicationBase::Poll()
{
	CListenSocket::Get().Poll();

	PeerList::iterator It = Peers.begin();
	while (It != Peers.end())
	{
		if (!(*It)->IsValid())
		{
			It = Peers.erase(It);
		}
		else
		{
			(*It)->Poll();
			++It;
		}
	}
}


// Listenした。
void CApplicationBase::OnListen(ISocket *pSocket)
{
	CPeerBase *pPeer = CreatePeer(pSocket);
	if (pPeer == nullptr) { return; }

	PeerSharedPtr pSharedPeer = PeerSharedPtr(pPeer);
	Peers.push_back(pSharedPeer);

	OnConnect(pSharedPeer);
}

}
}