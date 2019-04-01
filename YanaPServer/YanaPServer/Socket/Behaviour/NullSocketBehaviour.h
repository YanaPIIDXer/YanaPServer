#ifndef __NULLSOCKETBEHAVIOUR_H__
#define __NULLSOCKETBEHAVIOUR_H__

#include "SocketBehaviour.h"

namespace YanaPServer
{
namespace Socket
{
namespace Behaviour
{

/**
 * @class CNullSocketBehaviour
 * @brief 何もしないSocketBehaviour
 *		  未定義のプラットフォームで使用される。
 */
class CNullSocketBehaviour : public ISocketBehaviour
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CNullSocketBehaviour() {}

	/**
	 * @brief デストラクタ
	 */
	virtual ~CNullSocketBehaviour() {}

	/**
	 * @fn virtual void Release()
	 * @brief 解放
	 */
	virtual void Release() {}

};

}
}
}

#endif		// #ifndef __NULLSOCKETBEHAVIOUR_H__
