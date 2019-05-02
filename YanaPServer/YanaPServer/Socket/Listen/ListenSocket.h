#ifndef __LISTENSOCKET_H__
#define __LISTENSOCKET_H__

#include <functional>

namespace YanaPServer
{
namespace Socket
{
class ISocket;

namespace Listen
{

/**
 * @class IListenSocket
 * @brief Listen用Socketインタフェース
 */
class IListenSocket
{

public:

	/**
	 * @brief デストラクタ
	 */
	virtual ~IListenSocket() {}

	/**
	 * @fn virtual void Poll() = 0;
	 * @brief 毎フレーム呼び出す処理
	 */
	virtual void Poll() = 0;

	/**
	 * @fn virtual bool Listen(unsigned int Port) = 0
	 * @brief Listen開始
	 * @param[in] Port ポート番号
	 * @param[in] AcceptCallback Acceptした時のコールバック関数
	 * @return 正常に処理が終了したらtrueを返す。
	 */
	virtual bool Listen(unsigned int Port, const std::function<void(ISocket *)> &AcceptCallback) = 0;

};

/**
 * @class CListenSocket
 * @brief Listen用Socketクラス
 */
class CListenSocket
{

public:

	/**
	 * @fn static IListenSocket &Get()
	 * @brief Socket取得
	 * @return IListenSocketオブジェクト
	 */
	static IListenSocket &Get();
	
};

}
}
}

#endif		// #ifndef __LISTENSOCKET_H__
