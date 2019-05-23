#ifndef __HTTPREQUEST_H__
#define __HTTPREQUEST_H__

#include <string>
#include "HttpParameter.h"

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
		, ProtocolVersion("")
	{
	}

	//! ���\�b�h
	EHttpMethod Method;

	//! �p�X
	std::string Path;

	//! �v���g�R���o�[�W����
	std::string ProtocolVersion;

	//! �p�����[�^
	CHttpParameter Parameter;

};

}
}

#endif		// #ifndef __HTTPREQUEST_H__
