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
		ServerCertificate = 0x0B,
		ServerHelloDone = 0x0E,

		ClientKeyExchange = 0x10,

		Finished = 0x14,
	};

	// 送信State
	enum class ESendState
	{
		ServerHello,
		ServerCertificate,
		ServerHelloDone,
		End,
	};

	// 暗号化方式
	enum ECipherSuite
	{
		SSL_RSA_WITH_RC4_128_MD5 = 0x0004,
		SSL_RSA_WITH_RC4_128_SHA = 0x0005,
		TLS_RSA_WITH_3DES_EDE_CBC_SHA = 0x000A,
	};

	// Peer
	CServletPeer *pPeer;

	// 処理中か？
	bool bIsProcessing;

	// バージョン
	unsigned short Version;

	// 現在処理中のメッセージ
	ESendState CurrentState;

	// クライアント側から投げられた乱数
	char ClientRandom[28];

	// サーバから投げる乱数
	char ServerRandom[28];

	// 秘密鍵
	std::vector<unsigned char> PrivateKey;


	// データを受信した。
	void OnRecvData(YanaPServer::Util::Stream::IMemoryStream *pStream);

	// 暗号化されたデータを受信した。
	void OnRecvEncryptedData(YanaPServer::Util::Stream::IMemoryStream *pStream);

	// ClientHelloを受信した。
	void OnRecvClientHello(YanaPServer::Util::Stream::IMemoryStream *pStream);

	// ServerCertificateを送信。
	void SendServerCertificate();

	// ServerHelloDoneを送信。
	void SendServerHelloDone();

	// ClientKeyExchangeを受信した。
	void OnRecvClientKeyExchange(YanaPServer::Util::Stream::IMemoryStream *pStream);

	// ハンドシェイクパケットを送信.
	void SendHandshakePacket(unsigned char MessageType, YanaPServer::Util::ISerializable *pPacket);

	// SSLRecordパケットを生成.
	void MakeSSLRecordPacket(YanaPServer::Util::ISerializable *pPacket, YanaPServer::Servlet::Secure::Packet::CSSLRecord &OutRecord);

	// SSLハンドシェイクレコードパケットを生成.
	void MakeSSLHandshakeRecordPacket(unsigned char MessageType, YanaPServer::Util::ISerializable *pPacket, YanaPServer::Servlet::Secure::Packet::CSSLHandshakeRecord &OutRecord);

	// 秘密鍵の読み込み
	void LoadPrivateKey();

};

}
}
}

#endif		// #ifndef __SSLHANDSHAKE_H__
