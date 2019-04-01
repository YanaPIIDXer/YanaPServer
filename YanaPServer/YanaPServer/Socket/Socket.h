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
	 * @fn virtual void Release() = 0
	 * @brief 解放
	 */
	virtual void Release() = 0;

};

}
}

#endif		// #ifndef __SOCKETBEHAVIOUR_H__
