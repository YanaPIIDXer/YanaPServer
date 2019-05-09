#include "Application/ApplicationBase.h"
#include "Socket/Listen/ListenSocket.h"
using namespace YanaPServer::Socket::Listen;

namespace YanaPServer
{
namespace Application
{

// �R���X�g���N�^
CApplicationBase::CApplicationBase(const std::function<void(PeerPtr)> &OnConnectFunction)
	: OnConnect(OnConnectFunction)
{
}

// �f�X�g���N�^
CApplicationBase::~CApplicationBase()
{
	Peers.clear();
}

// Listen�J�n.
bool CApplicationBase::StartListen(unsigned int Port)
{
	return CListenSocket::Build(Port,
		std::bind(&CApplicationBase::OnListen, this, std::placeholders::_1));
}

// ���t���[���̏���.
bool CApplicationBase::Service()
{
	CListenSocket::Poll();

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

	return Update();
}


// Listen�����B
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