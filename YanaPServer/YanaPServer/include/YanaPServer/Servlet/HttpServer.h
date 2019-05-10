#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__

#include "../Application/ApplicationBase.h"
#include "../Peer/PeerBase.h"
#include "ServletFinder.h"

namespace YanaPServer
{
namespace Servlet
{

class IServlet;

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

};

}
}

#endif		// #ifndef __HTTPSERVER_H__
