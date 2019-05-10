#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__

#include "../Application/ApplicationBase.h"
#include "../Peer/PeerBase.h"

namespace YanaPServer
{
namespace Servlet
{

class IServletEvent;

/**
 * @class CHttpServer
 * @brief HTTP�T�[�o
 */
class CHttpServer : public YanaPServer::Application::CApplicationBase
{

public:

	/**
	 * @brief �R���X�g���N�^
	 * @param[in] pInServletEvent �T�[�u���b�g�C�x���g�C���^�t�F�[�X
	 */
	CHttpServer(IServletEvent *pInServletEvent);

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CHttpServer();

protected:

	/**
	 * @fn virtual CPeerBase *CreatePeer(YanaPServer::Socket::ISocket *pSocket) override final
	 * @brief Peer����
	 * @param[in] pSocket �\�P�b�g
	 * @return CPeerBase��h�������I�u�W�F�N�g�𐶐����ĕԂ��B
	 */
	virtual YanaPServer::Peer::CPeerBase *CreatePeer(YanaPServer::Socket::ISocket *pSocket) override;

private:

	// �T�[�u���b�g�C�x���g�C���^�t�F�[�X
	IServletEvent *pServletEvent;

};

}
}

#endif		// #ifndef __HTTPSERVER_H__
