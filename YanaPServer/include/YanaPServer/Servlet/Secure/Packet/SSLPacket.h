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
 * @brief SSL���R�[�h
 */
class CSSLRecord : public YanaPServer::Util::ISerializable
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CSSLRecord()
		: Type(0)
		, Version(0)
		, Length(0)
	{
	}

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CSSLRecord() {}

	//! �^�C�v
	unsigned char Type;

	//! �o�[�W����
	unsigned short Version;

	//! ����
	unsigned short Length;

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief �V���A���C�Y
	 * @param[in] pStream �X�g���[��
	 * @return ����������true��Ԃ�
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
 * @brief SSL�n���h�V�F�C�N���R�[�h
 */
class CSSLHandshakeRecord : public YanaPServer::Util::ISerializable
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CSSLHandshakeRecord()
		: MessageType(0)
		, BodyLength(0)
	{
	}

	/**
	 * @brief �f�X�g���N�^ 
	 */
	virtual ~CSSLHandshakeRecord() {}

	//! ���b�Z�[�W�^�C�v
	unsigned char MessageType;

	//! �{�f�B�̒���
	unsigned int BodyLength;

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief �V���A���C�Y
	 * @param[in] pStream �X�g���[��
	 * @return ����������true��Ԃ�
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
			// �g�p����͉̂��R�o�C�g�B
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
 * @brief �A���[�g�p�P�b�g
 */
class CSSLAlert : public YanaPServer::Util::ISerializable
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CSSLAlert()
	{
	}

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CSSLAlert() {}

	//! �A���[�g���x��
	unsigned char Level;

	//! �^�C�v
	unsigned char Description;

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief �V���A���C�Y
	 * @param[in] pStream �X�g���[��
	 * @return ����������true��Ԃ�
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
 * @brief SSL�ʐM ClientHello�p�P�b�g
 */
class CSSLClientHello : public YanaPServer::Util::ISerializable
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CSSLClientHello()
		: ClientVersion(0)
		, Time(0)
	{
		memset(SessionId, 0, sizeof(SessionId));
	}

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CSSLClientHello() {}

	//! �N���C�A���g�o�[�W����
	unsigned short ClientVersion;

	//! ����
	unsigned int Time;

	//! ����
	char Random[28];

	//! �Z�b�V�����h�c
	unsigned char SessionId[32];

	//! �Í����������X�g
	std::vector<unsigned short> CipherSuite;

	//! ���k�������X�g
	std::vector<unsigned char> CompressionMethods;

	//! �g��
	std::vector<unsigned char> Extensions;

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief �V���A���C�Y
	 * @param[in] pStream �X�g���[��
	 * @return ����������true��Ԃ�
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
 * @brief ServerHello�p�P�b�g
 */
class CSSLServerHello : public YanaPServer::Util::ISerializable
{

public:

	/**
	 * @brief �R���X�g���N�^;
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
	 * @brief �f�X�g���N�^
	 */
	virtual ~CSSLServerHello() {}

	//! �o�[�W����
	unsigned short Version;

	//! ����
	unsigned int Time;

	//! ����
	char Random[28];

	//! �Z�b�V�����h�c
	std::vector<unsigned char> SessionId;

	//! �Í�������
	unsigned short CipherSuite;

	//! ���k����
	unsigned char CompressionMethod;

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief �V���A���C�Y
	 * @param[in] pStream �X�g���[��
	 * @return ����������true��Ԃ�
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

		// Extension�͖��g�p�B
		unsigned short ExtensionLength = 0;
		pStream->Serialize(&ExtensionLength);
		
		return !pStream->IsError();
	}
};

/**
 * @class CSSLServerCerticifate
 * @brief ServerCertificate�p�P�b�g
 */
class CSSLServerCertificate : public YanaPServer::Util::ISerializable
{

private:		// �ʖ���`.

	typedef std::vector<unsigned char> CertificateBytes;

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CSSLServerCertificate() {}

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CSSLServerCertificate() {}

	//! �ؖ������X�g
	std::vector<CertificateBytes> CertificateList;

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief �V���A���C�Y
	 * @param[in] pStream �X�g���[��
	 * @return ����������true��Ԃ�
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

	// ���R�o�C�g���������݁B
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
 * @brief ServerHelloDone�p�P�b�g
 */
class CSSLServerHelloDone : public YanaPServer::Util::ISerializable
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CSSLServerHelloDone() {}

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CSSLServerHelloDone() {}

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief �V���A���C�Y
	 * @param[in] pStream �X�g���[��
	 * @return ����������true��Ԃ�
	 */
	virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	{
		return !pStream->IsError();
	}
};

/**
 * @class CSSLClientKeyExchange
 * @brief ClientKeyExchange�p�P�b�g
 */
class CSSLClientKeyExchange : public YanaPServer::Util::ISerializable
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CSSLClientKeyExchange()
	{
	}

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CSSLClientKeyExchange() {}

	//! ���J���ňÍ������ꂽ�����_���ȕ�����
	std::vector<unsigned char> PreMasterSecret;

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief �V���A���C�Y
	 * @param[in] pStream �X�g���[��
	 * @return ����������true��Ԃ�
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
