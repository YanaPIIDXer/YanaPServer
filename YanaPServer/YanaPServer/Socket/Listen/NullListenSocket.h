#ifndef __NULLLISTENSOCKET_H__
#define __NULLLISTENSOCKET_H__

#include "ListenSocket.h"

namespace YanaPServer
{
namespace Socket
{
class ISocket;

namespace Listen
{

/**
 * @class NullListenSocket
 * @brief 何もしないListenSocketクラス
 *		  未定義のプラットフォームで使用する。
 * @detail シングルトンクラス
 */
class CNullListenSocket : public IListenSocket
{

public:

	/**
	 * @brief デストラクタ
	 */
	virtual ~CNullListenSocket() {}

	/**
	 * @fn virtual void Poll()
	 * @brief 毎フレーム呼び出す処理
	 */
	virtual void Poll() {}

	/**
	 * @fn virtual bool Listen(unsigned int Port)
	 * @brief Listen開始
	 * @param[in] Port ポート番号
	 * @param[in] AcceptCallback Acceptした時のコールバック関数
	 * @return 何もしないので常にfalseを返す。
	 */
	virtual bool Listen(unsigned int Port, const std::function<void(ISocket *)> &AcceptCallback) { return false; }

	// ============= Singleton ============
public:

	/**
	 * @fn static CNullListenSocket &GetInstance()
	 * @brief シングルトンインスタンス取得
	 * @return シングルトンインスタンス
	 */
	static CNullListenSocket &GetInstance() { return Instance; }

private:

	CNullListenSocket() {}
	static CNullListenSocket Instance;

};

}
}
}

#endif		// #ifndef __NULLLISTENSOCKET_H__
