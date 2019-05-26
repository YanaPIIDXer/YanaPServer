#ifndef __HTTPCOOKIEINFO_H__
#define __HTTPCOOKIEINFO_H__

#include <string>

namespace YanaPServer
{
namespace Servlet
{

/**
 * @struct SHttpCookieInfo
 * @brief Cookie���
 */
struct SHttpCookieInfo
{

	/**
	 * @brief �R���X�g���N�^
	 */
	SHttpCookieInfo()
		: bIsEnable(false)
		, Name("")
		, Value("")
	{
	}

	//! �L�����H
	bool bIsEnable;

	//! ���O
	std::string Name;

	//! �l
	std::string Value;

};

}
}

#endif		// #ifndef __HTTPCOOKIEINFO_H__
