#ifndef __WINDOWSSOCKETBEHAVIOUR_H__
#define __WINDOWSSOCKETBEHAVIOUR_H__

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
	 * @fn virtual bool Initialize()
	 * @brief 初期化
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Initialize();

	/**
	 * @fn virtual void Release()
	 * @brief 解放処理
	 */
	virtual void Release();

private:

	// 初期化されているか？
	bool bInitialized;

};

}
}
}

#endif		// #ifndef __WINDOWSSOCKETBEHAVIOUR_H__
