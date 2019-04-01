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
	 * @fn virtual void Release()
	 * @brief 解放
	 */
	virtual void Release() {}

};

}
}

#endif		// #ifndef __NULLSOCKETBEHAVIOUR_H__
