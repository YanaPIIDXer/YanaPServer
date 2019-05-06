#ifndef __SOCKETBEHAVIOUR_H__
#define __SOCKETBEHAVIOUR_H__

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
	 * @fn virtual void Release() = 0
	 * @brief 解放
	 */
	virtual void Release() = 0;

};

}
}

#endif		// #ifndef __SOCKETBEHAVIOUR_H__
