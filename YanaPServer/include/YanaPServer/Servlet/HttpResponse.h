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

	//! Cookie���
	SHttpCookieInfo CookieInfo;

	/**
	 * @fn void SetCookie(const char *pName, const char *pValue)
	 * @brief Cookie��ݒ�
	 * @param[in] pName ���O
	 * @param[in] pValue �l
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
