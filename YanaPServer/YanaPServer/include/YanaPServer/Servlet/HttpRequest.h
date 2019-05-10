#ifndef __HTTPREQUEST_H__
#define __HTTPREQUEST_H__

#include <string>

namespace YanaPServer
{
namespace Servlet
{
/**
 * @enum EHttpMethod
 * @brief HTTP���\�b�h
 */
enum class EHttpMethod
{
	//! ����
	Invalid,

	//! POST
	POST,

	//! GET
	GET,
};

/**
 * @struct SHttpRequest
 * @brief HTTP���N�G�X�g
 */
struct SHttpRequest
{

	/**
	 * @brief �R���X�g���N�^
	 */
	SHttpRequest()
		: Method(EHttpMethod::Invalid)
		, Path("")
	{
	}

	//! ���\�b�h
	EHttpMethod Method;

	//! �p�X
	std::string Path;

};

}
}

#endif		// #ifndef __HTTPREQUEST_H__
