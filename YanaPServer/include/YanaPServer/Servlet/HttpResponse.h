#ifndef __HTTPRESPONSE_H__
#define __HTTPRESPONSE_H__

#include "../Util/Stream/SimpleStream.h"
#include "HttpCookieInfo.h"

namespace YanaPServer
{
namespace Servlet
{

/**
 * @enum EHttpStatusCode
 * @brief HTTPステータスコード
 */
enum class EHttpStatusCode
{
	//! 200 OK
	OK,

	//! 404 Not Found
	NotFound,

	//! 400 Bad Request
	BadRequest,
};

/**
 * @struct SHttpResponse
 * @brief HTTPレスポンス
 */
struct SHttpResponse
{
	//! ステータスコード
	EHttpStatusCode StatusCode;

	//! コンテンツを流し込むストリーム
	Util::Stream::CSimpleStream ContentStream;

	//! Cookie情報
	SHttpCookieInfo CookieInfo;

	/**
	 * @fn void SetCookie(const char *pName, const char *pValue)
	 * @brief Cookieを設定
	 * @param[in] pName 名前
	 * @param[in] pValue 値
	 */
	void SetCookie(const char *pName, const char *pValue)
	{
		CookieInfo.bIsEnable = true;
		CookieInfo.Name = pName;
		CookieInfo.Value = pValue;
	}
};

}
}

#endif		// #ifndef __HTTPRESPONSE_H__
