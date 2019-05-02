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

// 送信
void CPeerBase::Send(const char *pData, unsigned int Size)
{
	if (!IsValid()) { return; }

	pSocket->Send(pData, Size);
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
