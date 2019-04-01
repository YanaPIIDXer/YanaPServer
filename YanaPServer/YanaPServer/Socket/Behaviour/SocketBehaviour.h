#ifndef __SOCKETBEHAVIOUR_H__
#define __SOCKETBEHAVIOUR_H__

namespace YanaPServer
{
namespace Socket
{
namespace Behaviour
{

/**
* @class ISocketBehaviour
* @brief ソケットの挙動を実装するためのインタフェース
*/
class ISocketBehaviour
{

public:

	/**
	 * @brief デストラクタ
	 */
	virtual ~ISocketBehaviour() {}

	/**
	 * @fn virtual void Release() = 0
	 * @brief 解放
	 */
	virtual void Release() = 0;

};

}
}
}

#endif		// #ifndef __SOCKETBEHAVIOUR_H__
