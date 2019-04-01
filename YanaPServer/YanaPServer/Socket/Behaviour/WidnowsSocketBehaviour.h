#ifndef __WINDOWSSOCKETBEHAVIOUR_H__
#define __WINDOWSSOCKETBEHAVIOUR_H__

#ifdef _WIN32

#include "SocketBehaviour.h"
#include <WinSock2.h>

namespace YanaPServer
{
namespace Socket
{
namespace Behaviour
{

/**
 * @class CWindowsSocketBehaviour
 * @brief Windowsでのソケットの挙動を実装するクラス
 */
class CWindowsSocketBehaviour : public ISocketBehaviour
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CWindowsSocketBehaviour();

	/**
	 * @brief デストラクタ
	 */
	virtual ~CWindowsSocketBehaviour();

	/**
	 * @fn virtual void Release()
	 * @brief 解放処理
	 */
	virtual void Release();

private:

	// ソケット
	SOCKET Socket;

};

}
}
}

#endif		// #ifdef _WIN32

#endif		// #ifndef __WINDOWSSOCKETBEHAVIOUR_H__
