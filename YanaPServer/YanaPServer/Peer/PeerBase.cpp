#include "PeerBase.h"

namespace YanaPServer
{
namespace Peer
{

// コンストラクタ
CPeerBase::CPeerBase(ISocket *pInSocket)
	: pSocket(pInSocket)
{
}

// デストラクタ
CPeerBase::~CPeerBase()
{
	ReleaseSocket();
}


// ソケット解放.
void CPeerBase::ReleaseSocket()
{
	if (pSocket == nullptr) { return; }

	pSocket->Release();
	delete pSocket;
	pSocket = nullptr;
}

}
}
