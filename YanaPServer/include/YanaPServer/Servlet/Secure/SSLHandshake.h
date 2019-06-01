#ifndef __SSLHANDSHAKE_H__
#define __SSLHANDSHAKE_H__

#include "Util/Stream/MemoryStream.h"
#include "Servlet/Secure/Packet/SSLPacket.h"

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

	/**
	 * @fn bool IsProcessing() const
	 * @brief ���������H
	 * @return �������Ȃ�true��Ԃ��B
	 */
	bool IsProcessing() const { return bIsProcessing; }

	/**
	 * @fn void SendNext()
	 * @brief ���𑗐M
	 */
	void SendNext();

private:

	// ���b�Z�[�W�^�C�v
	enum EMessageType
	{
		ClientHello = 0x01,
		ServerHello = 0x02,
		ServerCertificate = 0x0B,
		ServerHelloDone = 0x0E,
	};

	// �Í�������
	enum ECipherSuite
	{
		SSL_RSA_WITH_RC4_128_MD5 = 0x0004,
		SSL_RSA_WITH_RC4_128_SHA = 0x0005,
	};

	// Peer
	CServletPeer *pPeer;

	// ���������H
	bool bIsProcessing;

	// �o�[�W����
	unsigned short Version;

	// ���ݏ������̃��b�Z�[�W
	EMessageType CurrentMessage;


	// ClientHello����M�����B
	void OnRecvClientHello(YanaPServer::Util::Stream::IMemoryStream *pStream);

	// ServerCertificate�𑗐M�B
	void SendServerCertificate();

	// ServerHelloDone�𑗐M�B
	void SendServerHelloDone();

	// �n���h�V�F�C�N�p�P�b�g�𑗐M.
	void SendHandshakePacket(unsigned char MessageType, YanaPServer::Util::ISerializable *pPacket);

	// SSLRecord�p�P�b�g�𐶐�.
	void MakeSSLRecordPacket(YanaPServer::Util::ISerializable *pPacket, YanaPServer::Servlet::Secure::Packet::CSSLRecord &OutRecord);

	// SSL�n���h�V�F�C�N���R�[�h�p�P�b�g�𐶐�.
	void MakeSSLHandshakeRecordPacket(unsigned char MessageType, YanaPServer::Util::ISerializable *pPacket, YanaPServer::Servlet::Secure::Packet::CSSLHandshakeRecord &OutRecord);

};

}
}
}

#endif		// #ifndef __SSLHANDSHAKE_H__
