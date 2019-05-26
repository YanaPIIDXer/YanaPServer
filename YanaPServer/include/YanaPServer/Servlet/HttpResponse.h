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
 * @brief HTTP�X�e�[�^�X�R�[�h
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
 * @brief HTTP���X�|���X
 */
struct SHttpResponse
{
	//! �X�e�[�^�X�R�[�h
	EHttpStatusCode StatusCode;

	//! �R���e���c�𗬂����ރX�g���[��
	Util::Stream::CSimpleStream ContentStream;

	//! Cookie�}�b�v
	std::map<std::string, std::string> CookieMap;
};

}
}

#endif		// #ifndef __HTTPRESPONSE_H__
