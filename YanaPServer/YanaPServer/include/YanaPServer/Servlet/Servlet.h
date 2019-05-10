#ifndef __SERVLETEVENT_H__
#define __SERVLETEVENT_H__

#include "HttpRequest.h"
#include <sstream>
#include "../Util/Stream/DynamicMemoryStreamWriter.h"

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
	 * @fn virtual void OnPost() = 0
	 * @brief POSTリクエストが投げられた時に実行されるイベント
	 * @param[in] Request リクエスト
	 * @param[in] ResponseStream レスポンスストリーム
	 */
	virtual void OnPost(const SHttpRequest &Request, YanaPServer::Util::Stream::CDynamicMemoryStreamWriter &ResponseStream) = 0;

	/**
	 * @fn virtual void OnGet() = 0
	 * @brief GETリクエストが投げられた時に実行されるイベント
	 * @param[in] Request リクエスト
	 * @param[in] ResponseStream レスポンスストリーム
	 */
	virtual void OnGet(const SHttpRequest &Request, YanaPServer::Util::Stream::CDynamicMemoryStreamWriter &ResponseStream) = 0;

	/**
	 * @fn virtual void OnError() = 0
	 * @brief エラー時のイベント
	 * @param[in] Request リクエスト
	 * @param[in] ResponseStream レスポンスストリーム
	 */
	virtual void OnError(const SHttpRequest &Request, YanaPServer::Util::Stream::CDynamicMemoryStreamWriter &ResponseStream) = 0;

};

}
}

#endif		// #ifndef __SERVLETEVENT_H__
