#include "PeerBase.h"

namespace YanaPServer
{
namespace Peer
{

// コンストラクタ
PeerBase::PeerBase(ISocket *pInSocket)
	: pSocket(pInSocket)
{
}

// デストラクタ
PeerBase::~PeerBase()
{
	ReleaseSocket();
}


// ソケット解放.
void PeerBase::ReleaseSocket()
{
	if (pSocket == nullptr) { return; }

	pSocket->Release();
	delete pSocket;
	pSocket = nullptr;
}

}
}
