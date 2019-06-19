#ifndef __SSLPACKET_H__
#define __SSLPACKET_H__

#include "Util/Serializable.h"
#include "Util/Stream/MemoryStream.h"
#include <vector>
#include <memory.h>

namespace YanaPServer
{
namespace Servlet
{
namespace Secure
{
namespace Packet
{

/**
 * @class CSSLRecord
 * @brief SSLレコード
 */
class CSSLRecord : public YanaPServer::Util::ISerializable
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CSSLRecord()
		: Type(0)
		, Version(0)
		, Length(0)
	{
	}

	/**
	 * @brief デストラクタ
	 */
	virtual ~CSSLRecord() {}

	//! タイプ
	unsigned char Type;

	//! バージョン
	unsigned short Version;

	//! 長さ
	unsigned short Length;

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief シリアライズ
	 * @param[in] pStream ストリーム
	 * @return 成功したらtrueを返す
	 */
	virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	{
		pStream->Serialize(&Type);
		pStream->Serialize(&Version);
		pStream->Serialize(&Length);
		return !pStream->IsError();
	}
};

/**
 * @class CSSLHandshakeRecord
 * @brief SSLハンドシェイクレコード
 */
class CSSLHandshakeRecord : public YanaPServer::Util::ISerializable
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CSSLHandshakeRecord()
		: MessageType(0)
		, BodyLength(0)
	{
	}

	/**
	 * @brief デストラクタ 
	 */
	virtual ~CSSLHandshakeRecord() {}

	//! メッセージタイプ
	unsigned char MessageType;

	//! ボディの長さ
	unsigned int BodyLength;

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief シリアライズ
	 * @param[in] pStream ストリーム
	 * @return 成功したらtrueを返す
	 */
	virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	{
		pStream->Serialize(&MessageType);

		if (pStream->GetType() != YanaPServer::Util::Stream::EStreamType::Write)
		{
			unsigned char Tmp[3];
			for (int i = 2; i >= 0; i--)
			{
				pStream->Serialize(&Tmp[i]);
			}
			if (pStream->GetType() == YanaPServer::Util::Stream::EStreamType::Read)
			{
				BodyLength = 0;
				memcpy(&BodyLength, Tmp, 3);
			}
		}
		else
		{
			unsigned char Tmp[4];
			memcpy(Tmp, &BodyLength, 4);
			// 使用するのは下３バイト。
			for (int i = 2; i >= 0; i--)
			{
				pStream->Serialize(&Tmp[i]);
			}
		}

		return !pStream->IsError();
	}
};

/**
 * @class CSSLAlert
 * @brief アラートパケット
 */
class CSSLAlert : public YanaPServer::Util::ISerializable
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CSSLAlert()
	{
	}

	/**
	 * @brief デストラクタ
	 */
	virtual ~CSSLAlert() {}

	//! アラートレベル
	unsigned char Level;

	//! タイプ
	unsigned char Description;

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief シリアライズ
	 * @param[in] pStream ストリーム
	 * @return 成功したらtrueを返す
	 */
	virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	{
		pStream->Serialize(&Level);
		pStream->Serialize(&Description);

		return !pStream->IsError();
	}
};

/**
 * @class CSSLClientHello
 * @brief SSL通信 ClientHelloパケット
 */
class CSSLClientHello : public YanaPServer::Util::ISerializable
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CSSLClientHello()
		: ClientVersion(0)
		, Time(0)
	{
		memset(SessionId, 0, sizeof(SessionId));
	}

	/**
	 * @brief デストラクタ
	 */
	virtual ~CSSLClientHello() {}

	//! クライアントバージョン
	unsigned short ClientVersion;

	//! 時間
	unsigned int Time;

	//! 乱数
	char Random[28];

	//! セッションＩＤ
	unsigned char SessionId[32];

	//! 暗号化方式リスト
	std::vector<unsigned short> CipherSuite;

	//! 圧縮方式リスト
	std::vector<unsigned char> CompressionMethods;

	//! 拡張
	std::vector<unsigned char> Extensions;

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief シリアライズ
	 * @param[in] pStream ストリーム
	 * @return 成功したらtrueを返す
	 */
	virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	{
		pStream->Serialize(&ClientVersion);
		pStream->Serialize(&Time);
		for (int i = 0; i < 28; i++)
		{
			pStream->Serialize(&Random[i]);
		}
		unsigned char CharBytes = 0;
		pStream->Serialize(&CharBytes);
		for (int i = 0; i < CharBytes; i++)
		{
			pStream->Serialize(&SessionId[i]);
		}
		unsigned short ShortBytes = 0;
		pStream->Serialize(&ShortBytes);
		for (int i = 0; i < ShortBytes / 2; i++)
		{
			unsigned short Data;
			pStream->Serialize(&Data);
			CipherSuite.push_back(Data);
		}
		pStream->Serialize(&CharBytes);
		for (int i = 0; i < CharBytes; i++)
		{
			unsigned char Data;
			pStream->Serialize(&Data);
			CompressionMethods.push_back(Data);
		}

		pStream->Serialize(&ShortBytes);
		for (int i = 0; i < ShortBytes; i++)
		{
			unsigned char Data;
			pStream->Serialize(&Data);
			Extensions.push_back(Data);
		}
		
		return !pStream->IsError();
	}
};

/**
 * @class CSSLServerHello
 * @brief ServerHelloパケット
 */
class CSSLServerHello : public YanaPServer::Util::ISerializable
{

public:

	/**
	 * @brief コンストラクタ;
	 */
	CSSLServerHello()
		: Version(0)
		, Time(0)
		, CipherSuite(0)
		, CompressionMethod(0)
	{
		memset(Random, 0, 28);
	}

	/**
	 * @brief デストラクタ
	 */
	virtual ~CSSLServerHello() {}

	//! バージョン
	unsigned short Version;

	//! 時間
	unsigned int Time;

	//! 乱数
	char Random[28];

	//! セッションＩＤ
	std::vector<unsigned char> SessionId;

	//! 暗号化方式
	unsigned short CipherSuite;

	//! 圧縮方式
	unsigned char CompressionMethod;

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief シリアライズ
	 * @param[in] pStream ストリーム
	 * @return 成功したらtrueを返す
	 */
	virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	{
		pStream->Serialize(&Version);
		pStream->Serialize(&Time);
		pStream->Serialize((void *)Random, 28);
		unsigned char Length = (unsigned char) SessionId.size();
		pStream->Serialize(&Length);
		for (unsigned int i = 0; i < SessionId.size(); i++)
		{
			pStream->Serialize(&SessionId[i]);
		}
		pStream->Serialize(&CipherSuite);
		pStream->Serialize(&CompressionMethod);

		// Extensionは未使用。
		unsigned short ExtensionLength = 0;
		pStream->Serialize(&ExtensionLength);
		
		return !pStream->IsError();
	}
};

/**
 * @class CSSLServerCerticifate
 * @brief ServerCertificateパケット
 */
class CSSLServerCertificate : public YanaPServer::Util::ISerializable
{

private:		// 別名定義.

	typedef std::vector<unsigned char> CertificateBytes;

public:

	/**
	 * @brief コンストラクタ
	 */
	CSSLServerCertificate() {}

	/**
	 * @brief デストラクタ
	 */
	virtual ~CSSLServerCertificate() {}

	//! 証明書リスト
	std::vector<CertificateBytes> CertificateList;

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief シリアライズ
	 * @param[in] pStream ストリーム
	 * @return 成功したらtrueを返す
	 */
	virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	{
		unsigned int Length = 0;
		for (const auto &Certificate : CertificateList)
		{
			Length += Certificate.size() + 3;
		}
		WriteThreeByte(Length, pStream);
		
		for (const auto &Certificate : CertificateList)
		{
			unsigned int CertificateLength = Certificate.size();
			WriteThreeByte(CertificateLength, pStream);
			pStream->Serialize((void *) &Certificate[0], CertificateLength);
		}

		return !pStream->IsError();
	}

private:

	// 下３バイトを書き込み。
	static void WriteThreeByte(unsigned int Data, YanaPServer::Util::Stream::IMemoryStream *pStream)
	{
		unsigned char Tmp[4];
		memcpy(Tmp, &Data, 4);
		for (int i = 2; i >= 0; i--)
		{
			pStream->Serialize(&Tmp[i]);
		}
	}
};

/**
 * @class CSSLServerHelloDone
 * @brief ServerHelloDoneパケット
 */
class CSSLServerHelloDone : public YanaPServer::Util::ISerializable
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CSSLServerHelloDone() {}

	/**
	 * @brief デストラクタ
	 */
	virtual ~CSSLServerHelloDone() {}

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief シリアライズ
	 * @param[in] pStream ストリーム
	 * @return 成功したらtrueを返す
	 */
	virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	{
		return !pStream->IsError();
	}
};

/**
 * @class CSSLClientKeyExchange
 * @brief ClientKeyExchangeパケット
 */
class CSSLClientKeyExchange : public YanaPServer::Util::ISerializable
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CSSLClientKeyExchange()
	{
	}

	/**
	 * @brief デストラクタ
	 */
	virtual ~CSSLClientKeyExchange() {}

	//! 公開鍵で暗号化されたランダムな文字列
	std::vector<unsigned char> PreMasterSecret;

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief シリアライズ
	 * @param[in] pStream ストリーム
	 * @return 成功したらtrueを返す
	 */
	virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	{
		unsigned short Length = 0;
		pStream->Serialize(&Length);

		PreMasterSecret.clear();
		PreMasterSecret.resize(Length);
		for (unsigned short i = 0; i < Length; i++)
		{
			unsigned char Data = 0;
			pStream->Serialize(&Data);
			PreMasterSecret[i] = Data;
		}

		return !pStream->IsError();
	}
};

}
}
}
}

#endif	// #ifndef __SSLPACKET_H__
