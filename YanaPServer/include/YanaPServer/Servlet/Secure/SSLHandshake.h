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

	// レコードタイプ
	enum ERecordType
	{
		Handshake = 0x16,
		ChangeCipherSpec = 0x14,
		Alert = 0x15,
		ApplicationData = 0x17,
	};

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

	// 暗号化方式
	enum ECipherSuite
	{
		SSL_RSA_WITH_RC4_128_MD5 = 0x0004,
		SSL_RSA_WITH_RC4_128_SHA = 0x0005,
		TLS_RSA_WITH_3DES_EDE_CBC_SHA = 0x000A,
	};

	// アラートレベル
	enum EAlertLevel
	{
		Warning = 0x01,
		Fatal = 0x02,
	};

	// アラートの種類
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

	// 処理中か？
	bool bIsProcessing;

	// バージョン
	unsigned short Version;

	// クライアント側から投げられた乱数
	char ClientRandom[32];

	// サーバから投げる乱数
	char ServerRandom[32];

	// 秘密鍵
	YanaPServer::Util::Secure::CASN1 PrivateKey;

	// マスタシークレット
	boost::multiprecision::cpp_int MasterSecret;


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
	void MakeSSLRecordPacket(ERecordType Type, YanaPServer::Util::ISerializable *pPacket, YanaPServer::Servlet::Secure::Packet::CSSLRecord &OutRecord);

	// SSLハンドシェイクレコードパケットを生成.
	void MakeSSLHandshakeRecordPacket(unsigned char MessageType, YanaPServer::Util::ISerializable *pPacket, YanaPServer::Servlet::Secure::Packet::CSSLHandshakeRecord &OutRecord);

	// 秘密鍵の読み込み
	void LoadPrivateKey();

	// Alertを送信。
	void SendAlert(EAlertLevel Level, EAlertDescription Description);

	// PRF計算
	void CalcPRF(const std::string &Secret, const std::string &Label, const std::string &Seed, std::vector<unsigned char> &OutBytes);

};

}
}
}

#endif		// #ifndef __SSLHANDSHAKE_H__
