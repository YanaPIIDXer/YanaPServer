#ifndef __SERVLETEVENT_H__
#define __SERVLETEVENT_H__

#include "HttpRequest.h"
#include <sstream>
#include "../Util/Stream/StringStream.h"

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
	 * @fn virtual void OnPost(const SHttpRequest &Request, YanaPServer::Util::Stream::CStringStream &ResponseStream) = 0
	 * @brief POST���N�G�X�g��������ꂽ���Ɏ��s�����C�x���g
	 * @param[in] Request ���N�G�X�g
	 * @param[in] ResponseStream ���X�|���X�X�g���[��
	 */
	virtual void OnPost(const SHttpRequest &Request, YanaPServer::Util::Stream::CStringStream &ResponseStream) = 0;

	/**
	 * @fn virtual void OnGet(const SHttpRequest &Request, YanaPServer::Util::Stream::CStringStream &ResponseStream) = 0
	 * @brief GET���N�G�X�g��������ꂽ���Ɏ��s�����C�x���g
	 * @param[in] Request ���N�G�X�g
	 * @param[in] ResponseStream ���X�|���X�X�g���[��
	 */
	virtual void OnGet(const SHttpRequest &Request, YanaPServer::Util::Stream::CStringStream &ResponseStream) = 0;

	/**
	 * @fn virtual void OnError(const SHttpRequest &Request, YanaPServer::Util::Stream::CStringStream &ResponseStream) = 0
	 * @brief �G���[���̃C�x���g
	 * @param[in] Request ���N�G�X�g
	 * @param[in] ResponseStream ���X�|���X�X�g���[��
	 */
	virtual void OnError(const SHttpRequest &Request, YanaPServer::Util::Stream::CStringStream &ResponseStream) = 0;

};

}
}

#endif		// #ifndef __SERVLETEVENT_H__