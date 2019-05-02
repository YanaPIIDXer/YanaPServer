#ifndef __APPLICATIONBASE_H__
#define __APPLICATIONBASE_H__
#include "YanaPServer/Socket/Socket.h"
using namespace YanaPServer::Socket;
#include "YanaPServer/Peer/PeerBase.h"
using namespace YanaPServer::Peer;
#include <vector>
#include <memory>
#include <functional>

typedef std::weak_ptr<CPeerBase> PeerPtr;

namespace YanaPServer
{
namespace Application
{

/**
 * @class CApplicationBase
 * @brief アプリケーションメイン基底クラス
 */
class CApplicationBase
{

private:		// 別名定義.

	typedef std::shared_ptr<CPeerBase> PeerSharedPtr;
	typedef std::vector<PeerSharedPtr> PeerList;

public:

	/**
	 * @brief コンストラクタ
	 * @param[in] ListenPort 待機ポート
	 * @param[in] OnConnectFunction 接続時コールバック
	 */
	CApplicationBase(unsigned int ListenPort, const std::function<void(PeerPtr)> &OnConnectFunction);

	/**
	 * @brief デストラクタ
	 */
	virtual ~CApplicationBase();

	/**
	 * @fn void Poll()
	 * @brief 毎フレームの処理
	 * @detail メインフレームで呼び出す事。
	 */
	void Poll();

protected:

	/**
	 * @fn virtual CPeerBase *CreatePeer(ISocket *pSocket) = 0
	 * @brief Peer生成
	 * @param[in] pSocket ソケット
	 * @return CPeerBaseを派生したオブジェクトを生成して返す。
	 */
	virtual CPeerBase *CreatePeer(ISocket *pSocket) = 0;

private:

	// Peerリスト
	PeerList Peers;

	// 接続時コールバック
	std::function<void(PeerPtr)> OnConnect;


	// Listenした。
	void OnListen(ISocket *pSocket);

};

}
}

#endif		// #ifndef __APPLICATIONBASE_H__
