#ifndef __PEERBASE_H__
#define __PEERBASE_H__

#include "Socket/Socket.h"
#include "Socket/SocketEventListener.h"
using namespace YanaPServer::Socket;

namespace YanaPServer
{
namespace Peer
{

/**
 * @class CPeerBase
 * @brief ピア基底クラス
 * @detail 基本的にはコイツを派生したクラスのweak_ptrを利用者側で管理する。
 *	       切断時には勝手に消失する（親になるshared_ptrが消える）ので、
 *	       コイツを使って何かやる時はexpired()チェックしないと死なますよ。
 */
class CPeerBase : public ISocketEventListener
{

public:
	
	/**
	 * @brief コンストラクタ
	 * @param[in] pInSocket ソケット
	 */
	CPeerBase(ISocket *pInSocket);

	/**
	 * @brief デストラクタ
	 */
	virtual ~CPeerBase() = 0;

	/**
	 * @fn void Poll()
	 * @brief 毎フレームの処理
	 */
	void Poll();

	/**
	 * @fn void SetOverrideEventListener(ISocketEventListener *pListener)
	 * @brief ソケットイベントをオーバーライドするイベントリスナをセット
	 * @detail イベントリスナのメモリ管理（delete等）は行わないので注意。
	 * @param[in] pListener イベントリスナ
	 */
	void SetOverrideEventListener(ISocketEventListener *pListener);

	/**
	 * @fn void RemoveOverrideEventListener()
	 * @brief ソケットイベントをオーバーライドするイベントリスナを解除。
	 */
	void RemoveOverrideEventListener() { SetOverrideEventListener(this); }

	/**
	 * @fn bool IsValid() const
	 * @brief 有効か？
	 * @return 有効ならtrueを返す。
	 */
	bool IsValid() const { return (pSocket != nullptr && pSocket->IsValid()); }

	/**
	 * @fn void Send(const char *pData, unsigned int Size)
	 * @brief 送信
	 * @param[in] pData データ
	 * @param[in] Size データ長
	 */
	void Send(const char *pData, unsigned int Size);

	/**
	 * @fn virtual void OnDisconnect() override
	 * @brief 切断された
	 */
	virtual void OnDisconnect() override {}

private:

	// ソケット
	ISocket *pSocket;


	// ソケット解放.
	void ReleaseSocket();

};

}
}

#endif		// #ifndef __PEERBASE_H__
