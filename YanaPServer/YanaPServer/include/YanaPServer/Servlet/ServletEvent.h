#ifndef __SERVLETEVENT_H__
#define __SERVLETEVENT_H__

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
	 * @brief POSTリクエストが投げられた時に実行されるイベント
	 */
	virtual void OnPost() = 0;

	/**
	 * @brief GETリクエストが投げられた時に実行されるイベント
	 */
	virtual void OnGet() = 0;

};

}
}

#endif		// #ifndef __SERVLETEVENT_H__
