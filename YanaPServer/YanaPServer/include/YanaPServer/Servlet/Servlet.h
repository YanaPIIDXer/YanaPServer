#ifndef __SERVLET_H__
#define __SERVLET_H__

#include "../Peer/PeerBase.h"
#include "../Socket/Socket.h"

namespace YanaPServer
{
namespace Servlet
{

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

	/**
	 * @fn virtual void OnRecv(const char *pData, unsigned int Size) override
	 * @brief 受信した
	 * @param[in] pData データ
	 * @param[in] Size データ長
	 */
	virtual void OnRecv(const char *pData, unsigned int Size) override;

private:

};

}
}

#endif		// #ifndef __SERVLET_H__
