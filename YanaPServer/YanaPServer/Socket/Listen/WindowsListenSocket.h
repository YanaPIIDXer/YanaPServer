#ifndef __WINDOWSLISTENSOCKET_H__
#define __WINDOWSLISTENSOCKET_H__

#ifdef _WIN32
#include <WinSock2.h>
#include "ListenSocket.h"

namespace YanaPServer
{
namespace Socket
{
namespace Listen
{

/**
 * @class CWindowsListenSocket
 * @brief WindowsのListen用ソケットクラス
 * @detail シングルトンクラス
 */
class CWindowsListenSocket : public IListenSocket
{

public:

	/**
	 * @brief デストラクタ
	 */
	virtual ~CWindowsListenSocket();

	/**
	 * @fn virtual bool Listen(unsigned int Port)
	 * @brief Listen開始
	 * @param[in] Port ポート番号
	 * @return 正常に処理が終了したらtrueを返す。
	 */
	virtual bool Listen(unsigned int Port);

private:

	// ソケット
	SOCKET Socket;

	// ======== Singleton =============
public:

	/**
		* @fn static CWindowsListenSocket &GetInstance()
		* @brief シングルトンインスタンス取得
		* @return シングルトンインスタンス
		*/
	static CWindowsListenSocket &GetInstance() { return Instance; }

private:

	CWindowsListenSocket();
	static CWindowsListenSocket Instance;

};

}
}
}

#endif		// #ifdef _WIN32


#endif			// #ifndef __WINDOWSLISTENSOCKET_H__
