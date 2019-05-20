#include "Peer/PeerBase.h"

namespace YanaPServer
{
namespace Peer
{

using namespace YanaPServer::Socket;

// コンストラクタ
CPeerBase::CPeerBase(YanaPServer::Socket::ISocket *pInSocket)
	: pSocket(pInSocket)
	, bDisconnect(false)
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

	if (bDisconnect)
	{
		ReleaseSocket();
	}
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
	// SocketのPoll処理中に切断される可能性があるので、
	// 即解体はせずにフラグだけ立てておく。
	// Poll処理後、切断フラグが立っていれば解体。
	bDisconnect = true;
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
