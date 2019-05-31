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
 * @brief SSLハンドシェイク
 */
class CSSLHandshake
{

public:

	/**
	 * @brief コンストラクタ
	 * @param[in] pInPeer Peer
	 */
	CSSLHandshake(CServletPeer *pInPeer);

	/**
	 * @brief デストラクタ
	 */
	~CSSLHandshake();

	/**
	 * @fn void OnRecv(const char *pData, unsigned int Size)
	 * @brief 受信した
	 * @param[in] pData データ
	 * @param[in] Size データ長
	 */
	void OnRecv(const char *pData, unsigned int Size);

	/**
	 * @fn bool IsProcessing() const
	 * @brief 処理中か？
	 * @return 処理中ならtrueを返す。
	 */
	bool IsProcessing() const { return bIsProcessing; }

private:

	// メッセージタイプ
	enum EMessageType
	{
		ClientHello = 0x01,
		ServerHello = 0x02,
		ServerCertificate = 0x0b,
	};

	// 暗号化方式
	enum ECipherSuite
	{
		SSL_RSA_WITH_RC4_128_MD5 = 0x0004,
		SSL_RSA_WITH_RC4_128_SHA = 0x0005,
	};

	// Peer
	CServletPeer *pPeer;

	// 処理中か？
	bool bIsProcessing;

	// バージョン
	unsigned short Version;


	// ClientHelloを受信した。
	void OnRecvClientHello(YanaPServer::Util::Stream::IMemoryStream *pStream);

	// ServerCertificateを送信。
	void SendServerCertificate();

	// ハンドシェイクパケットを送信.
	void SendHandshakePacket(unsigned char MessageType, YanaPServer::Util::ISerializable *pPacket);

	// SSLRecordパケットを生成.
	void MakeSSLRecordPacket(YanaPServer::Util::ISerializable *pPacket, YanaPServer::Servlet::Secure::Packet::CSSLRecord &OutRecord);

	// SSLハンドシェイクレコードパケットを生成.
	void MakeSSLHandshakeRecordPacket(unsigned char MessageType, YanaPServer::Util::ISerializable *pPacket, YanaPServer::Servlet::Secure::Packet::CSSLHandshakeRecord &OutRecord);

};

}
}
}

#endif		// #ifndef __SSLHANDSHAKE_H__
