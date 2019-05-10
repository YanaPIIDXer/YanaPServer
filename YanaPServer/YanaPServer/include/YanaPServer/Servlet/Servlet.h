#ifndef __SERVLETEVENT_H__
#define __SERVLETEVENT_H__

#include "HttpRequest.h"
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
	 * @fn virtual void OnPost() = 0
	 * @brief POST���N�G�X�g��������ꂽ���Ɏ��s�����C�x���g
	 * @param[in] Request ���N�G�X�g
	 * @param[in] ResponseStream ���X�|���X�X�g���[��
	 */
	virtual void OnPost(const SHttpRequest &Request, std::stringstream &ResponseStream) = 0;

	/**
	 * @fn virtual void OnGet() = 0
	 * @brief GET���N�G�X�g��������ꂽ���Ɏ��s�����C�x���g
	 * @param[in] Request ���N�G�X�g
	 * @param[in] ResponseStream ���X�|���X�X�g���[��
	 */
	virtual void OnGet(const SHttpRequest &Request, std::stringstream &ResponseStream) = 0;

	/**
	 * @fn virtual void OnError() = 0
	 * @brief �G���[���̃C�x���g
	 * @param[in] Request ���N�G�X�g
	 * @param[in] ResponseStream ���X�|���X�X�g���[��
	 */
	virtual void OnError(const SHttpRequest &Request, std::stringstream &ResponseStream) = 0;

};

}
}

#endif		// #ifndef __SERVLETEVENT_H__
