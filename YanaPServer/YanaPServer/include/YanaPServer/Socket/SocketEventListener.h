#ifndef __SOCKETEVENTLISTENER_H__
#define __SOCKETEVENTLISTENER_H__

namespace YanaPServer
{
namespace Socket
{

/**
 * @class ISocketEventListener
 * @brief ソケットイベントリスナ
 */
class ISocketEventListener
{
public:

	/**
	 * @brief デストラクタ
	 */
	virtual ~ISocketEventListener() {}

	/**
	 * @fn virtual void OnConnect() = 0
	 * @brief 接続された
	 */
	virtual void OnConnect() = 0;

	/**
	 * @fn virtual void OnRecv(const char *pData, unsigned int Size) = 0
	 * @brief 受信した
	 * @param[in] pData データ
	 * @param[in] Size データ長
	 */
	virtual void OnRecv(const char *pData, unsigned int Size) = 0;

	/**
	 * @fn virtual void OnDisconnect() = 0
	 * @brief 切断された
	 */
	virtual void OnDisconnect() = 0;

};

}
}
#endif		// #ifndef __SOCKETEVENTLISTENER_H__
