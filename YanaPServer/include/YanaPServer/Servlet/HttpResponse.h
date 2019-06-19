#ifndef __HTTPRESPONSE_H__
#define __HTTPRESPONSE_H__

#include "../Util/Stream/SimpleStream.h"
#include <string>
#include <map>

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

	//! Content-Type
	std::string ContentType;

	//! コンテンツを流し込むストリーム
	Util::Stream::CSimpleStream ContentStream;

	//! Cookie情報
	std::map<std::string, std::string> CookieInfo;


	/**
	 * @brief コンストラクタ
	 */
	SHttpResponse()
		: StatusCode(EHttpStatusCode::OK)
		, ContentType("text/html")
	{
	}
};

}
}

#endif		// #ifndef __HTTPRESPONSE_H__
