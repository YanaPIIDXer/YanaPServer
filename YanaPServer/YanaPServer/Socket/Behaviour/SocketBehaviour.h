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
	 * @fn virtual bool Initialize() = 0
	 * @brief 初期化
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Initialize() = 0;

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
