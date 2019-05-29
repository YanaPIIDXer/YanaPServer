#ifndef __SSLHANDSHAKE_H__
#define __SSLHANDSHAKE_H__

#include "Util/Stream/MemoryStream.h"

namespace YanaPServer
{
namespace Servlet
{

class CServletPeer;

namespace Secure
{

/**
 * @class CSSLHandshake
 * @brief SSL�n���h�V�F�C�N
 */
class CSSLHandshake
{

public:

	/**
	 * @brief �R���X�g���N�^
	 * @param[in] pInPeer Peer
	 */
	CSSLHandshake(CServletPeer *pInPeer);

	/**
	 * @brief �f�X�g���N�^
	 */
	~CSSLHandshake();

	/**
	 * @fn void OnRecv(const char *pData, unsigned int Size)
	 * @brief ��M����
	 * @param[in] pData �f�[�^
	 * @param[in] Size �f�[�^��
	 */
	void OnRecv(const char *pData, unsigned int Size);

private:

	// ���b�Z�[�W�^�C�v
	enum EMessageType
	{
		ClientHello = 0x01,
	};

	// Peer
	CServletPeer *pPeer;


	// ClientHello����M�����B
	void OnRecvClientHello(unsigned short Version, YanaPServer::Util::Stream::IMemoryStream *pStream);

};

}
}
}

#endif		// #ifndef __SSLHANDSHAKE_H__
