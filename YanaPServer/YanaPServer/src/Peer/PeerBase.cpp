#include "Peer/PeerBase.h"

namespace YanaPServer
{
namespace Peer
{

using namespace YanaPServer::Socket;

// コンストラクタ
CPeerBase::CPeerBase(YanaPServer::Socket::ISocket *pInSocket)
	: pSocket(pInSocket)
{
	pSocket->SetEventListener(this);
}

// デストラクタ
CPeerBase::~CPeerBase()
{
	ReleaseSocket();
}

// 毎フレームの処理.
void CPeerBase::Poll()
{
	if (!IsValid()) { return; }

	pSocket->Poll();
}

// ソケットイベントをオーバーライドするイベントリスナをセット
void CPeerBase::SetOverrideEventListener(ISocketEventListener *pListener)
{
	pSocket->SetEventListener(pListener);
}

// 送信.
void CPeerBase::Send(const char *pData, unsigned int Size)
{
	if (!IsValid()) { return; }

	pSocket->Send(pData, Size);
}

// 切断.
void CPeerBase::Disconnect()
{
	if (!IsValid()) { return; }

	ReleaseSocket();
}


// ソケット解放.
void CPeerBase::ReleaseSocket()
{
	if (pSocket == nullptr) { return; }

	pSocket->Release(ESocketDisconnectReason::Destruct);
	delete pSocket;
	pSocket = nullptr;
}

}
}
