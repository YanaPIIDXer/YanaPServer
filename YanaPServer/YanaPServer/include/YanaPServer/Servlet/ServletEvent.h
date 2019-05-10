#ifndef __SERVLETEVENT_H__
#define __SERVLETEVENT_H__

#include "HttpRequest.h"

namespace YanaPServer
{
namespace Servlet
{

/**
 * @class IServletEvent
 * @brief Servlet�����s����C�x���g�̃C���^�t�F�[�X
 */
class IServletEvent
{

public:

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~IServletEvent() {}

	/**
	 * @fn virtual void OnPost() = 0
	 * @brief POST���N�G�X�g��������ꂽ���Ɏ��s�����C�x���g
	 * @param[in] Request ���N�G�X�g
	 */
	virtual void OnPost(const SHttpRequest &Request) = 0;

	/**
	 * @fn virtual void OnGet() = 0
	 * @brief GET���N�G�X�g��������ꂽ���Ɏ��s�����C�x���g
	 * @param[in] Request ���N�G�X�g
	 */
	virtual void OnGet(const SHttpRequest &Request) = 0;

	/**
	 * @fn virtual void OnError() = 0
	 * @brief �G���[���̃C�x���g
	 * @param[in] Request ���N�G�X�g
	 */
	virtual void OnError(const SHttpRequest &Request) = 0;

};

}
}

#endif		// #ifndef __SERVLETEVENT_H__
