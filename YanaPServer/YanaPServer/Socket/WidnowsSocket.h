#ifndef __WINDOWSSOCKETBEHAVIOUR_H__
#define __WINDOWSSOCKETBEHAVIOUR_H__

#ifdef _WIN32

#include "Socket.h"
#include <WinSock2.h>

namespace YanaPServer
{
namespace Socket
{

/**
 * @class CWindowsSocket
 * @brief Windowsでのソケットの挙動を実装するクラス
 */
class CWindowsSocket : public ISocket
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CWindowsSocket(const SOCKET &InSocket);

	/**
	 * @brief デストラクタ
	 */
	virtual ~CWindowsSocket();

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

#endif		// #ifdef _WIN32

#endif		// #ifndef __WINDOWSSOCKETBEHAVIOUR_H__
