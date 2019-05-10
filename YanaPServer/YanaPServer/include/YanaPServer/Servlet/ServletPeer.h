#ifndef __SERVLET_H__
#define __SERVLET_H__

#include "../Peer/PeerBase.h"
#include "../Socket/Socket.h"
#include "Servlet.h"

namespace YanaPServer
{
namespace Servlet
{

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
	 * @param[in] pInServlet Servletインタフェース
	 */
	CServletPeer(YanaPServer::Socket::ISocket *pSocket, IServlet *pInServlet);

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

private:

	// Servletインタフェース
	IServlet *pServlet;


	// レスポンス送信.
	void SendResponse(std::stringstream &Stream);

};

}
}

#endif		// #ifndef __SERVLET_H__
