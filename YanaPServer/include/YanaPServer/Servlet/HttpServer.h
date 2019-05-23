#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__

#include "../Application/ApplicationBase.h"
#include "../Peer/PeerBase.h"
#include "ServletFinder.h"
#include "HttpServerEvent.h"

namespace YanaPServer
{
namespace Servlet
{

class IServlet;

/**
 * @class CHttpDefaultServerEvent
 * @brief �W���̃T�[�o�C�x���g
 *        �I�[�o�[���C�h����N���X���`���Đݒ肵�Ȃ��ꍇ�̓R�C�c���g�p�����B
 * @detail �V���O���g���N���X
 */
class CHttpDefaultServerEvent : public IHttpServerEvent
{

public:

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CHttpDefaultServerEvent() {}

	/**
	 * @fn virtual void OnError(const SHttpRequest &Request, YanaPServer::Util::Stream::CStringStream &ResponseStream) override
	 * @brief �G���[����
	 * @param[in] Request HTTP���N�G�X�g
	 * @param[in] ResponseStream  ������X�g���[��
	 */
	virtual void OnError(const SHttpRequest &Request, YanaPServer::Util::Stream::CStringStream &ResponseStream) override
	{
		ResponseStream.AppendLine("Error.");
	}

	/**
	 * @fn virtual void OnNotFound(const SHttpRequest &Request, YanaPServer::Util::Stream::CStringStream &ResponseStream) override
	 * @brief �Ή�Servlet��������Ȃ�����
	 * @param[in] Request HTTP���N�G�X�g
	 * @param[in] ResponseStream  ������X�g���[��
	 */
	virtual void OnNotFound(const SHttpRequest &Request, YanaPServer::Util::Stream::CStringStream &ResponseStream) override
	{
		ResponseStream.Append(Request.Path.c_str());
		ResponseStream.AppendLine(" 404 NotFound.");
	}

	// ========= Singleton =============

public:

	/**
	 * @fn static CHttpDefaultServerEvent &GetInstance()
	 * @brief Singleton�C���X�^���X�擾
	 * @return Singleton�C���X�^���X
	 */
	static CHttpDefaultServerEvent &GetInstance() { return Instance; }

private:

	CHttpDefaultServerEvent() {}
	static CHttpDefaultServerEvent Instance;

};

/**
 * @class CHttpServer
 * @brief HTTP�T�[�o
 */
class CHttpServer : public YanaPServer::Application::CApplicationBase
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CHttpServer();

	/**
	 * @brief �R���X�g���N�^
	 * @param[in] pInEvent �T�[�o�C�x���g
	 */
	CHttpServer(IHttpServerEvent *pInEvent);

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CHttpServer();

	/**
	 * @fn void AddServlet(IServlet *pServlet)
	 * @brief Servlet�ǉ��B
	 * @param[in] pServlet Servlet
	 */
	void AddServlet(IServlet *pServlet);

protected:

	/**
	 * @fn virtual CPeerBase *CreatePeer(YanaPServer::Socket::ISocket *pSocket) override final
	 * @brief Peer����
	 * @param[in] pSocket �\�P�b�g
	 * @return CPeerBase��h�������I�u�W�F�N�g�𐶐����ĕԂ��B
	 */
	virtual YanaPServer::Peer::CPeerBase *CreatePeer(YanaPServer::Socket::ISocket *pSocket) override;

private:

	// ServletFinder
	CServletFinder ServletFinder;

	// �T�[�o�C�x���g
	IHttpServerEvent *pEvent;

};

}
}

#endif		// #ifndef __HTTPSERVER_H__
