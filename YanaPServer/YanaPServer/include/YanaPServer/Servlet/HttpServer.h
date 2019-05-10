#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__

#include "../Application/ApplicationBase.h"
#include "../Peer/PeerBase.h"

namespace YanaPServer
{
namespace Servlet
{

/**
 * @class CHttpServer
 * @brief HTTPサーバ
 */
class CHttpServer : public YanaPServer::Application::CApplicationBase
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CHttpServer();

	/**
	 * @brief デストラクタ
	 */
	virtual ~CHttpServer();

protected:

	/**
	 * @fn virtual CPeerBase *CreatePeer(ISocket *pSocket) = 0
	 * @brief Peer生成
	 * @param[in] pSocket ソケット
	 * @return CPeerBaseを派生したオブジェクトを生成して返す。
	 */
	virtual YanaPServer::Peer::CPeerBase *CreatePeer(YanaPServer::Socket::ISocket *pSocket) override;

private:

};

}
}

#endif		// #ifndef __HTTPSERVER_H__
