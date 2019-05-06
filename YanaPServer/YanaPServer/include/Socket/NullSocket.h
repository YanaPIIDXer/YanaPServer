#ifndef __NULLSOCKETBEHAVIOUR_H__
#define __NULLSOCKETBEHAVIOUR_H__

#include "Socket.h"

namespace YanaPServer
{
namespace Socket
{

/**
 * @class CNullSocket
 * @brief 何もしないSocket
 *		  未定義のプラットフォームで使用される。
 */
class CNullSocket : public ISocket
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CNullSocket() {}

	/**
	 * @brief デストラクタ
	 */
	virtual ~CNullSocket() {}

	/**
	 * @fn virtual void Poll() override
	 * @brief 毎フレーム実行する処理
	 */
	virtual void Poll() override {}

	/**
	 * @fn virtual bool IsValid() const override
	 * @brief 有効か？
	 * @return 有効にはならないので常にfalseを返す。
	 */
	virtual bool IsValid() const override { return false; }

	/**
	 * @fn virtual bool Send(const char *pData, unsigned int Size) override
	 * @brief 送信
	 * @param[in] pData データ
	 * @param[in] Size 送信サイズ
	 * @return 何もしないので常にfalseを返す。
	 */
	virtual bool Send(const char *pData, unsigned int Size) override { return false; }

	/**
	 * @fn virtual void SetReceiveCallback(const std::function<void(const char *, unsigned int)> &Callback) override
	 * @brief 受信コールバックを設定
	 * @param[in] Callback コールバック関数
	 */
	virtual void SetReceiveCallback(const std::function<void(const char *, unsigned int)> &Callback) override {}

	/**
	 * @fn virtual void Release() override
	 * @brief 解放
	 */
	virtual void Release() override {}

};

}
}

#endif		// #ifndef __NULLSOCKETBEHAVIOUR_H__
