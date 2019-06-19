#ifndef __SERVLET_H__
#define __SERVLET_H__

#include "../Peer/PeerBase.h"
#include "../Socket/Socket.h"
#include "Servlet.h"

namespace YanaPServer
{
namespace Servlet
{

class CServletFinder;
class IHttpServerEvent;

/**
 * @class CServletPeer
 * @brief HTTP接続を処理するクラス。
 *        Java Servletみたいなモノ。
 *        それを扱うPeer
 */
class CServletPeer : public YanaPServer::Peer::CPeerBase
{

public:

	/**
	 * @brief コンストラクタ
	 * @param[in] pSocket ソケット
	 * @param[in] pInFinder ServletFinder
	 * @param[in] pInHttpServerEvent サーバイベント
	 */
	CServletPeer(YanaPServer::Socket::ISocket *pSocket, CServletFinder *pInFinder, IHttpServerEvent *pInHttpServerEvent);

	/**
	 * @brief デストラクタ
	 */
	virtual ~CServletPeer();

	/**
	 * @fn virtual void OnRecv(const char *pData, unsigned int Size) override
	 * @brief 受信した
	 * @param[in] pData データ
	 * @param[in] Size データ長
	 */
	virtual void OnRecv(const char *pData, unsigned int Size) override;

	/** 
	 * @fn virtual void OnSend(unsigned int Size) override
	 * @brief 送信した
	 * @param[in] Size 送信したデータ長
	 */
	virtual void OnSend(unsigned int Size) override;

private:

	// ServletFinder
	CServletFinder *pFinder;

	// 送信サイズ
	unsigned int SendSize;

	// HTTPサーバイベント
	IHttpServerEvent *pHttpServerEvent;


	// レスポンス送信.
	void SendResponse(const SHttpRequest &Request, const SHttpResponse &Response);

};

}
}

#endif		// #ifndef __SERVLET_H__
