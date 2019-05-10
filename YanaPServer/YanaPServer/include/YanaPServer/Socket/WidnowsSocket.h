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
	 */
	CWindowsSocket();

	/**
	 * @brief コンストラクタ
	 * @param[in] InSocket ソケット
	 */
	CWindowsSocket(const SOCKET &InSocket);

	/**
	 * @brief デストラクタ
	 */
	virtual ~CWindowsSocket();

	/**
	 * @fn virtual void Poll() override
	 * @brief 毎フレーム実行する処理
	 */
	virtual void Poll() override;

	/**
	 * @fn virtual bool Connect(const char *pHost, unsigned int Port) override
	 * @brief 接続
	 * @param[in] pHost ホスト
	 * @param[in] Port ポート
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Connect(const char *pHost, unsigned int Port) override;

	/**
	 * @fn virtual void SetEventListener() override
	 * @brief イベントリスナをセット
	 * @param[in] pListener イベントリスナ
	 */
	virtual void SetEventListener(ISocketEventListener *pListener) override { pEventListener = pListener; }

	/**
	 * @fn virtual bool IsValid() const override
	 * @brief 有効か？
	 * @return 有効ならtrueを返す。
	 */
	virtual bool IsValid() const override { return (Socket != INVALID_SOCKET); }

	/**
	 * @fn virtual bool Send(const char *pData, unsigned int Size) override
	 * @brief 送信
	 * @param[in] pData データ
	 * @param[in] Size 送信サイズ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Send(const char *pData, unsigned int Size) override;

	/**
	 * @fn virtual void Release() override
	 * @brief 解放処理
	 */
	virtual void Release() override;

private:

	// State
	class EState
	{
	public:
		enum
		{
			// 何もしていない
			None,

			// 接続中.
			Connecting,

			// 接続した
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

	// イベントリスナ
	ISocketEventListener *pEventListener;


	// 送信処理.
	void SendProc();

	// 受信処理.
	void RecvProc();

};

}
}

#endif		// #ifdef _WIN32

#endif		// #ifndef __WINDOWSSOCKETBEHAVIOUR_H__
