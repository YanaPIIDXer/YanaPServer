#ifndef __HTTPSERVEREVENT_H__
#define __HTTPSERVEREVENT_H__

#include "HttpRequest.h"
#include "../Util/Stream/SimpleStream.h"

namespace YanaPServer
{
namespace Servlet
{

/**
 * @class IHttpServerEvent
 * @brief HTTP�T�[�o�C�x���g�C���^�t�F�[�X
 */
class IHttpServerEvent
{

public:

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~IHttpServerEvent() {}

	/**
	 * @fn virtual void OnError(const SHttpRequest &Request, YanaPServer::Util::Stream::CSimpleStream &ResponseStream) = 0
	 * @brief �G���[����
	 * @param[in] Request HTTP���N�G�X�g
	 * @param[in] ResponseStream  ������X�g���[��
	 */
	virtual void OnError(const SHttpRequest &Request, YanaPServer::Util::Stream::CSimpleStream &ResponseStream) = 0;

	/**
	 * @fn virtual void OnNotFound(const SHttpRequest &Request, YanaPServer::Util::Stream::CSimpleStream &ResponseStream) = 0
	 * @brief �Ή�Servlet��������Ȃ�����
	 * @param[in] Request HTTP���N�G�X�g
	 * @param[in] ResponseStream  ������X�g���[��
	 */
	virtual void OnNotFound(const SHttpRequest &Request, YanaPServer::Util::Stream::CSimpleStream &ResponseStream) = 0;

};

}
}

#endif		// #ifndef __HTTPSERVEREVENT_H__
