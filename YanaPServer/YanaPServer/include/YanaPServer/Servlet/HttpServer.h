#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__

#include "../Application/ApplicationBase.h"
#include "../Peer/PeerBase.h"

namespace YanaPServer
{
namespace Servlet
{

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

protected:

	/**
	 * @fn virtual CPeerBase *CreatePeer(ISocket *pSocket) = 0
	 * @brief Peer����
	 * @param[in] pSocket �\�P�b�g
	 * @return CPeerBase��h�������I�u�W�F�N�g�𐶐����ĕԂ��B
	 */
	virtual YanaPServer::Peer::CPeerBase *CreatePeer(YanaPServer::Socket::ISocket *pSocket) override;

private:

};

}
}

#endif		// #ifndef __HTTPSERVER_H__
