#ifndef __WINDOWSSOCKETBEHAVIOUR_H__
#define __WINDOWSSOCKETBEHAVIOUR_H__

#ifdef _WIN32

#include "Socket.h"
#include <WinSock2.h>
#include <string>
#include <queue>

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
	 * @param[in] InSocket ソケット
	 */
	CWindowsSocket(const SOCKET &InSocket);

	/**
	 * @brief コンストラクタ
	 * @param[in] Host ホスト
	 * @param[in] Port ポート番号
	 */
	CWindowsSocket(const std::string &Host, unsigned int Port);

	/**
	 * @brief デストラクタ
	 */
	virtual ~CWindowsSocket();

	/**
	 * @fn virtual void Poll()
	 * @brief 毎フレーム実行する処理
	 */
	virtual void Poll();

	/**
	 * @fn virtual bool IsValid() const
	 * @brief 有効か？
	 * @return 有効ならtrueを返す。
	 */
	virtual bool IsValid() const { return (Socket != INVALID_SOCKET); }

	/**
	 * @fn virtual bool Send(const char *pData, unsigned int Size)
	 * @brief 送信
	 * @param[in] pData データ
	 * @param[in] Size 送信サイズ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Send(const char *pData, unsigned int Size);

	/**
	 * @fn virtual void Release()
	 * @brief 解放処理
	 */
	virtual void Release();

private:

	// State
	class EState
	{
	public:
		enum
		{
			Connecting,
			Connected,
		};
	};

	// ソケット
	SOCKET Socket;

	// ノンブロッキングモード
	u_long NonBlockingMode;

	// ステート
	unsigned char State;

	// 接続先アドレス
	sockaddr_in ConnectAddr;

	// データキュー
	std::queue<char> DataQueue;


	// 送信処理.
	void SendProc();

};

}
}

#endif		// #ifdef _WIN32

#endif		// #ifndef __WINDOWSSOCKETBEHAVIOUR_H__
