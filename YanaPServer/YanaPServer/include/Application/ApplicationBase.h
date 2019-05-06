#ifndef __APPLICATIONBASE_H__
#define __APPLICATIONBASE_H__
#include "Socket/Socket.h"
using namespace YanaPServer::Socket;
#include "Peer/PeerBase.h"
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
	 * @fn bool Service()
	 * @brief 毎フレームの処理
	 * @detail メインフレームで呼び出す事。
	 * @return メインループを終了する時はfalseを返す。
	 */
	bool Service();

protected:

	/**
	 * @fn virtual CPeerBase *CreatePeer(ISocket *pSocket) = 0
	 * @brief Peer生成
	 * @param[in] pSocket ソケット
	 * @return CPeerBaseを派生したオブジェクトを生成して返す。
	 */
	virtual CPeerBase *CreatePeer(ISocket *pSocket) = 0;

	/**
	 * @fn virtual bool Update()
	 * @brief 更新処理
	 * @return 何らかの要因でメインループを抜ける場合はfalseを返す
	 */
	virtual bool Update() { return true; }

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
