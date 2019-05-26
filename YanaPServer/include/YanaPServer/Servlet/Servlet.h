#ifndef __SERVLETEVENT_H__
#define __SERVLETEVENT_H__

#include "HttpRequest.h"
#include "HttpResponse.h"
#include <sstream>

namespace YanaPServer
{
namespace Servlet
{

/**
 * @class IServlet
 * @brief Servletインタフェース
 */
class IServlet
{

public:

	/**
	 * @brief デストラクタ
	 */
	virtual ~IServlet() {}

	/**
	 * @fn virtual const char *GetPath() const = 0
	 * @brief Servletのパスを取得
	 * @return Servletのパス
	 */
	virtual const char *GetPath() const = 0;

	/**
	 * @fn virtual void OnPost(const SHttpRequest &Request, SHttpResponse &Response) = 0
	 * @brief POSTリクエストが投げられた時に実行されるイベント
	 * @param[in] Request リクエスト
	 * @param[in] Response レスポンス
	 */
	virtual void OnPost(const SHttpRequest &Request, SHttpResponse &Response) = 0;

	/**
	 * @fn virtual void OnGet(const SHttpRequest &Request, SHttpResponse &Response) = 0
	 * @brief GETリクエストが投げられた時に実行されるイベント
	 * @param[in] Request リクエスト
	 * @param[in] Response レスポンス
	 */
	virtual void OnGet(const SHttpRequest &Request, SHttpResponse &Response) = 0;

	/**
	 * @fn virtual void OnError(const SHttpRequest &Request, SHttpResponse &Response) = 0
	 * @brief エラー時のイベント
	 * @param[in] Request リクエスト
	 * @param[in] Response レスポンス
	 */
	virtual void OnError(const SHttpRequest &Request, SHttpResponse &Response) = 0;

};

}
}

#endif		// #ifndef __SERVLETEVENT_H__
