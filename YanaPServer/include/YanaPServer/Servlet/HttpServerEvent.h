#ifndef __HTTPSERVEREVENT_H__
#define __HTTPSERVEREVENT_H__

#include "HttpRequest.h"
#include "HttpResponse.h"

namespace YanaPServer
{
namespace Servlet
{

/**
 * @class IHttpServerEvent
 * @brief HTTPサーバイベントインタフェース
 */
class IHttpServerEvent
{

public:

	/**
	 * @brief デストラクタ
	 */
	virtual ~IHttpServerEvent() {}

	/**
	 * @fn virtual void OnError(const SHttpRequest &Request, SHttpResponse &Response) = 0
	 * @brief エラー発生
	 * @param[in] Request HTTPリクエスト
	 * @param[in] Response HTTPレスポンス
	 */
	virtual void OnError(const SHttpRequest &Request, SHttpResponse &Response) = 0;

	/**
	 * @fn virtual void OnNotFound(const SHttpRequest &Request, SHttpResponse &Response) = 0
	 * @brief 対応Servletが見つからなかった
	 * @param[in] Request HTTPリクエスト
	 * @param[in] Response HTTPレスポンス
	 */
	virtual void OnNotFound(const SHttpRequest &Request, SHttpResponse &Response) = 0;

};

}
}

#endif		// #ifndef __HTTPSERVEREVENT_H__
