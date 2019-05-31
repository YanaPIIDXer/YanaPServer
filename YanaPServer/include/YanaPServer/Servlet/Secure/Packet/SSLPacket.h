#ifndef __SSLPACKET_H__
#define __SSLPACKET_H__

#include "Util/Serializable.h"
#include "Util/Stream/MemoryStream.h"
#include <vector>

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
		, Random("")
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
	unsigned int SessionId[32];

	//! 暗号化方式リスト
	std::vector<unsigned short> CipherSuite;

	//! 圧縮方式リスト
	std::vector<unsigned char> CompressionMethods;

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
		, Random("")
		, CipherSuite(0)
		, CompressionMethod(0)
	{
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
	std::vector<unsigned int> SessionId;

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
		unsigned char Length = (unsigned char)SessionId.size();
		pStream->Serialize(&Length);
		for (unsigned int i = 0; i < SessionId.size(); i++)
		{
			pStream->Serialize(&SessionId[i]);
		}
		pStream->Serialize(&CipherSuite);
		pStream->Serialize(&CompressionMethod);

		return !pStream->IsError();
	}
};

/**
 * @class CSSLServerCerticifate
 * @brief ServerCertificateパケット
 */
class CSSLServerCertificate : public YanaPServer::Util::ISerializable
{

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
	std::vector<char> CertificateList;

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief シリアライズ
	 * @param[in] pStream ストリーム
	 * @return 成功したらtrueを返す
	 */
	virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	{
		unsigned int Length = CertificateList.size();
		pStream->Serialize(&Length);

		pStream->Serialize(&CertificateList[0], Length);

		return !pStream->IsError();
	}
};

}
}
}
}

#endif	// #ifndef __SSLPACKET_H__
