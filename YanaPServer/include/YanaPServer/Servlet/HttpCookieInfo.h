#ifndef __HTTPCOOKIEINFO_H__
#define __HTTPCOOKIEINFO_H__

#include <string>

namespace YanaPServer
{
namespace Servlet
{

/**
 * @struct SHttpCookieInfo
 * @brief Cookie情報
 */
struct SHttpCookieInfo
{

	/**
	 * @brief コンストラクタ
	 */
	SHttpCookieInfo()
		: bIsEnable(false)
		, Name("")
		, Value("")
	{
	}

	//! 有効か？
	bool bIsEnable;

	//! 名前
	std::string Name;

	//! 値
	std::string Value;

};

}
}

#endif		// #ifndef __HTTPCOOKIEINFO_H__
