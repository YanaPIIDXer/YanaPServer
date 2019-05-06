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
	 * @fn virtual void Poll() override
	 * @brief 毎フレーム実行する処理
	 */
	virtual void Poll() override;

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
	 * @fn virtual void SetReceiveCallback(const std::function<void(const char *, unsigned int)> &Callback) override
	 * @brief 受信コールバックを設定
	 * @param[in] Callback コールバック関数
	 */
	virtual void SetReceiveCallback(const std::function<void(const char *, unsigned int)> &Callback) override { ReceiveCallback = Callback; }

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

	// 受信コールバック
	std::function<void(const char *, unsigned int)> ReceiveCallback;


	// 送信処理.
	void SendProc();

	// 受信処理.
	void RecvProc();

};

}
}

#endif		// #ifdef _WIN32

#endif		// #ifndef __WINDOWSSOCKETBEHAVIOUR_H__
