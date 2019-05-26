#ifndef __SERVLETEVENT_H__
#define __SERVLETEVENT_H__

#include "HttpRequest.h"
#include "HttpResponse.h"
#include <sstream>

namespace YanaPServer
{
namespace Servlet
{

/**
 * @class IServlet
 * @brief Servlet�C���^�t�F�[�X
 */
class IServlet
{

public:

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~IServlet() {}

	/**
	 * @fn virtual const char *GetPath() const = 0
	 * @brief Servlet�̃p�X���擾
	 * @return Servlet�̃p�X
	 */
	virtual const char *GetPath() const = 0;

	/**
	 * @fn virtual void OnPost(const SHttpRequest &Request, SHttpResponse &Response) = 0
	 * @brief POST���N�G�X�g��������ꂽ���Ɏ��s�����C�x���g
	 * @param[in] Request ���N�G�X�g
	 * @param[in] Response ���X�|���X
	 */
	virtual void OnPost(const SHttpRequest &Request, SHttpResponse &Response) = 0;

	/**
	 * @fn virtual void OnGet(const SHttpRequest &Request, SHttpResponse &Response) = 0
	 * @brief GET���N�G�X�g��������ꂽ���Ɏ��s�����C�x���g
	 * @param[in] Request ���N�G�X�g
	 * @param[in] Response ���X�|���X
	 */
	virtual void OnGet(const SHttpRequest &Request, SHttpResponse &Response) = 0;

	/**
	 * @fn virtual void OnError(const SHttpRequest &Request, SHttpResponse &Response) = 0
	 * @brief �G���[���̃C�x���g
	 * @param[in] Request ���N�G�X�g
	 * @param[in] Response ���X�|���X
	 */
	virtual void OnError(const SHttpRequest &Request, SHttpResponse &Response) = 0;

};

}
}

#endif		// #ifndef __SERVLETEVENT_H__
