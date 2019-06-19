#include "Peer/PeerBase.h"
#include "Util/Stream/MemorySizeCaliculator.h"
#include "Util/Stream/MemoryStreamWriter.h"

using namespace YanaPServer::Socket;
using namespace YanaPServer::Util;
using namespace YanaPServer::Util::Stream;

namespace YanaPServer
{
namespace Peer
{

// コンストラクタ
CPeerBase::CPeerBase(YanaPServer::Socket::ISocket *pSocket)
	: Socket(pSocket)
	, bDisconnect(false)
{
	Socket.SetEventListener(this);
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

	Socket.Poll();

	if (bDisconnect)
	{
		ReleaseSocket();
	}
}

// ソケットイベントをオーバーライドするイベントリスナをセット
void CPeerBase::SetOverrideEventListener(ISocketEventListener *pListener)
{
	Socket.SetEventListener(pListener);
}

// 送信.
void CPeerBase::Send(const char *pData, unsigned int Size)
{
	if (!IsValid()) { return; }

	Socket.Send(pData, Size);
}

// シリアライズ可能なオブジェクトを送信.
void CPeerBase::Send(ISerializable *pObject)
{
	// まずはサイズを計算
	CMemorySizeCaliculator SizeCaliculator;
	pObject->Serialize(&SizeCaliculator);

	// シリアライズ本番
	CMemoryStreamWriter StreamWriter(SizeCaliculator.GetSize());
	pObject->Serialize(&StreamWriter);

	// 送信
	Send(StreamWriter.GetBuffer(), StreamWriter.GetSize());
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
	Socket.Release(ESocketDisconnectReason::Destruct);
}

}
}
