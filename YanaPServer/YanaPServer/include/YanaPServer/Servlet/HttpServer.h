#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__

#include "../Application/ApplicationBase.h"
#include "../Peer/PeerBase.h"

namespace YanaPServer
{
namespace Servlet
{

class IServletEvent;

/**
 * @class CHttpServer
 * @brief HTTPサーバ
 */
class CHttpServer : public YanaPServer::Application::CApplicationBase
{

public:

	/**
	 * @brief コンストラクタ
	 * @param[in] pInServletEvent サーブレットイベントインタフェース
	 */
	CHttpServer(IServletEvent *pInServletEvent);

	/**
	 * @brief デストラクタ
	 */
	virtual ~CHttpServer();

protected:

	/**
	 * @fn virtual CPeerBase *CreatePeer(YanaPServer::Socket::ISocket *pSocket) override final
	 * @brief Peer生成
	 * @param[in] pSocket ソケット
	 * @return CPeerBaseを派生したオブジェクトを生成して返す。
	 */
	virtual YanaPServer::Peer::CPeerBase *CreatePeer(YanaPServer::Socket::ISocket *pSocket) override;

private:

	// サーブレットイベントインタフェース
	IServletEvent *pServletEvent;

};

}
}

#endif		// #ifndef __HTTPSERVER_H__
