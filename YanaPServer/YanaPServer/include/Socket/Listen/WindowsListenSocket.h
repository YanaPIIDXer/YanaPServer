#ifndef __WINDOWSLISTENSOCKET_H__
#define __WINDOWSLISTENSOCKET_H__

#ifdef _WIN32
#include <WinSock2.h>
#include "ListenSocket.h"

namespace YanaPServer
{
namespace Socket
{
class ISocket;

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
	 * @fn virtual void Poll()
	 * @brief 毎フレーム呼び出す処理
	 */
	virtual void Poll();

	/**
	 * @fn virtual bool StartListen(unsigned int Port)
	 * @brief Listen開始
	 * @param[in] Port ポート番号
	 * @param[in] AcceptCallback Acceptした時のコールバック関数
	 * @return 正常に処理が終了したらtrueを返す。
	 */
	virtual bool StartListen(unsigned int Port, const std::function<void(ISocket *)> &AcceptCallback);

private:

	// ソケット
	SOCKET Socket;

	// ノンブロッキングモード
	u_long NonBlockingMode;

	// Accept時のコールバック
	std::function<void(ISocket *)> OnAccept;


	// ソケットの初期化.
	bool Init();

	// バインド
	bool Bind(unsigned int Port);

	// リッスン
	bool Listen();

	// 解放.
	void Release();

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
