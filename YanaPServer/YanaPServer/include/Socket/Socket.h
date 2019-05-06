#ifndef __SOCKETBEHAVIOUR_H__
#define __SOCKETBEHAVIOUR_H__

#include <functional>

namespace YanaPServer
{
namespace Socket
{

/**
 * @class ISocket
 * @brief ソケットの挙動を実装するためのインタフェース
 */
class ISocket
{

public:

	/**
	 * @brief デストラクタ
	 */
	virtual ~ISocket() {}

	/**
	 * @fn virtual void Poll() = 0
	 * @brief 毎フレーム実行する処理
	 */
	virtual void Poll() = 0;

	/**
	 * @fn virtual bool IsValid()
	 * @brief 有効か？
	 * @return 有効ならtrueを返す。
	 */
	virtual bool IsValid() const = 0;

	/**
	 * @fn virtual bool Send(const char *pData, unsigned int Size) = 0
	 * @brief 送信
	 * @param[in] pData データ
	 * @param[in] Size 送信サイズ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Send(const char *pData, unsigned int Size) = 0;

	/**
	 * @fn virtual void SetReceiveCallback(const std::function<void(const char *, unsigned int)> &Callback) = 0
	 * @brief 受信コールバックを設定
	 * @param[in] Callback コールバック関数
	 */
	virtual void SetReceiveCallback(const std::function<void(const char *, unsigned int)> &Callback) = 0;

	/**
	 * @fn virtual void Release() = 0
	 * @brief 解放
	 */
	virtual void Release() = 0;

	/**
	 * @fn virtual void SetReleaseCallback(const std::function<void()> &Callback) = 0
	 * @brief 解放コールバックを設定
	 * @param[in] Callback 解放コールバック
	 */
	virtual void SetReleaseCallback(const std::function<void()> &Callback) = 0;

};

}
}

#endif		// #ifndef __SOCKETBEHAVIOUR_H__
