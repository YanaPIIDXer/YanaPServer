#ifndef __HTTPRESPONSE_H__
#define __HTTPRESPONSE_H__

#include "../Util/Stream/SimpleStream.h"
#include "HttpCookieInfo.h"

namespace YanaPServer
{
namespace Servlet
{

/**
 * @struct SHttpResponse
 * @brief HTTPレスポンス
 */
struct SHttpResponse
{

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
