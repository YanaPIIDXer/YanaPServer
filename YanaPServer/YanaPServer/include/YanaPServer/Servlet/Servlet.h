#ifndef __SERVLET_H__
#define __SERVLET_H__

#include "../Peer/PeerBase.h"
#include "../Socket/Socket.h"

/**
 * @class CServlet
 * @brief HTTP接続を処理するクラス。
 *        Java Servletみたいなモノ。
 */
class CServlet : public YanaPServer::Peer::CPeerBase
{

public:

	/**
	 * @brief コンストラクタ
	 * @param[in] pSocket ソケット
	 */
	CServlet(YanaPServer::Socket::ISocket *pSocket);

	/**
	 * @brief デストラクタ
	 */
	virtual ~CServlet();

private:

};

#endif		// #ifndef __SERVLET_H__
