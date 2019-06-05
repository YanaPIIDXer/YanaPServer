#ifndef __SSLHANDSHAKE_H__
#define __SSLHANDSHAKE_H__

#include "Util/Stream/MemoryStream.h"
#include "Servlet/Secure/Packet/SSLPacket.h"
#include "Util/Secure/ASN1.h"
#include "boost/multiprecision/cpp_int.hpp"

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

private:

	// ���R�[�h�^�C�v
	enum ERecordType
	{
		Handshake = 0x16,
		ChangeCipherSpec = 0x14,
		Alert = 0x15,
		ApplicationData = 0x17,
	};

	// ���b�Z�[�W�^�C�v
	enum EMessageType
	{
		ClientHello = 0x01,

		ServerHello = 0x02,
		ServerCertificate = 0x0B,
		ServerHelloDone = 0x0E,

		ClientKeyExchange = 0x10,

		Finished = 0x14,
	};

	// �Í�������
	enum ECipherSuite
	{
		SSL_RSA_WITH_RC4_128_MD5 = 0x0004,
		SSL_RSA_WITH_RC4_128_SHA = 0x0005,
		TLS_RSA_WITH_3DES_EDE_CBC_SHA = 0x000A,
	};

	// �A���[�g���x��
	enum EAlertLevel
	{
		Warning = 0x01,
		Fatal = 0x02,
	};

	// �A���[�g�̎��
	enum EAlertDescription
	{
		CloseNotify = 0,
		UnexpectedMessage = 10,
		HandshakeFailuer = 40,
		UnsupportedCertificate = 43,
		CertificateUnknown = 46,
		DecodeError = 50,
	};

	// Peer
	CServletPeer *pPeer;

	// ���������H
	bool bIsProcessing;

	// �o�[�W����
	unsigned short Version;

	// �N���C�A���g�����瓊����ꂽ����
	boost::multiprecision::cpp_int ClientRandom;

	// �T�[�o���瓊���闐��
	boost::multiprecision::cpp_int ServerRandom;

	// �閧��
	YanaPServer::Util::Secure::CASN1 PrivateKey;

	// �}�X�^�V�[�N���b�g
	boost::multiprecision::cpp_int MasterSecret;


	// �f�[�^����M�����B
	void OnRecvData(YanaPServer::Util::Stream::IMemoryStream *pStream);

	// �Í������ꂽ�f�[�^����M�����B
	void OnRecvEncryptedData(YanaPServer::Util::Stream::IMemoryStream *pStream);

	// ClientHello����M�����B
	void OnRecvClientHello(YanaPServer::Util::Stream::IMemoryStream *pStream);

	// ServerCertificate�𑗐M�B
	void SendServerCertificate();

	// ServerHelloDone�𑗐M�B
	void SendServerHelloDone();

	// ClientKeyExchange����M�����B
	void OnRecvClientKeyExchange(YanaPServer::Util::Stream::IMemoryStream *pStream);

	// �n���h�V�F�C�N�p�P�b�g�𑗐M.
	void SendHandshakePacket(unsigned char MessageType, YanaPServer::Util::ISerializable *pPacket);

	// SSLRecord�p�P�b�g�𐶐�.
	void MakeSSLRecordPacket(ERecordType Type, YanaPServer::Util::ISerializable *pPacket, YanaPServer::Servlet::Secure::Packet::CSSLRecord &OutRecord);

	// SSL�n���h�V�F�C�N���R�[�h�p�P�b�g�𐶐�.
	void MakeSSLHandshakeRecordPacket(unsigned char MessageType, YanaPServer::Util::ISerializable *pPacket, YanaPServer::Servlet::Secure::Packet::CSSLHandshakeRecord &OutRecord);

	// �閧���̓ǂݍ���
	void LoadPrivateKey();

	// Alert�𑗐M�B
	void SendAlert(EAlertLevel Level, EAlertDescription Description);

};

}
}
}

#endif		// #ifndef __SSLHANDSHAKE_H__
