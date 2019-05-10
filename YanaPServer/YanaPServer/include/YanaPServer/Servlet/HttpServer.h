#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__

#include "../Application/ApplicationBase.h"
#include "../Peer/PeerBase.h"

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

private:

};

#endif		// #ifndef __HTTPSERVER_H__
