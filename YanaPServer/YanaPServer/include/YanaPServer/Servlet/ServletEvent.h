#ifndef __SERVLETEVENT_H__
#define __SERVLETEVENT_H__

#include "HttpRequest.h"
#include <sstream>

namespace YanaPServer
{
namespace Servlet
{

/**
 * @class IServletEvent
 * @brief Servletが実行するイベントのインタフェース
 */
class IServletEvent
{

public:

	/**
	 * @brief デストラクタ
	 */
	virtual ~IServletEvent() {}

	/**
	 * @fn virtual void OnPost() = 0
	 * @brief POSTリクエストが投げられた時に実行されるイベント
	 * @param[in] Request リクエスト
	 * @param[in] ResponseStream レスポンスストリーム
	 */
	virtual void OnPost(const SHttpRequest &Request, std::stringstream &ResponseStream) = 0;

	/**
	 * @fn virtual void OnGet() = 0
	 * @brief GETリクエストが投げられた時に実行されるイベント
	 * @param[in] Request リクエスト
	 * @param[in] ResponseStream レスポンスストリーム
	 */
	virtual void OnGet(const SHttpRequest &Request, std::stringstream &ResponseStream) = 0;

	/**
	 * @fn virtual void OnError() = 0
	 * @brief エラー時のイベント
	 * @param[in] Request リクエスト
	 * @param[in] ResponseStream レスポンスストリーム
	 */
	virtual void OnError(const SHttpRequest &Request, std::stringstream &ResponseStream) = 0;

};

}
}

#endif		// #ifndef __SERVLETEVENT_H__
