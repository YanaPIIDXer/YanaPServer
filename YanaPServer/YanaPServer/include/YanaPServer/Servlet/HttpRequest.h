#ifndef __HTTPREQUEST_H__
#define __HTTPREQUEST_H__

#include <string>

namespace YanaPServer
{
namespace Servlet
{
/**
 * @enum EHttpMethod
 * @brief HTTPメソッド
 */
enum class EHttpMethod
{
	//! 無効
	Invalid,

	//! POST
	POST,

	//! GET
	GET,
};

/**
 * @struct SHttpRequest
 * @brief HTTPリクエスト
 */
struct SHttpRequest
{

	/**
	 * @brief コンストラクタ
	 */
	SHttpRequest()
		: Method(EHttpMethod::Invalid)
		, Path("")
	{
	}

	//! メソッド
	EHttpMethod Method;

	//! パス
	std::string Path;

};

}
}

#endif		// #ifndef __HTTPREQUEST_H__
