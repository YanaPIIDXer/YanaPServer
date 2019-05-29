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
		, MessageType(0)
		, BodyLength(0)
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
		pStream->Serialize(&Type);
		pStream->Serialize(&Version);
		pStream->Serialize(&Length);
		pStream->Serialize(&MessageType);

		if (pStream->IsReadMode())
		{
			unsigned char Tmp[3];
			for (int i = 2; i >= 0; i--)
			{
				pStream->Serialize(&Tmp[i]);
			}
			BodyLength = 0;
			memcpy(&BodyLength, Tmp, 3);
		}
		else
		{
			unsigned char Tmp[4];
			memcpy(Tmp, &BodyLength, 4);
			// �g�p����͉̂��R�o�C�g�B
			for (int i = 3; i >= 0; i++)
			{
				pStream->Serialize(&Tmp[i]);
			}
		}

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
		, Random("")
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
	unsigned int SessionId[32];

	//! �Í����������X�g
	std::vector<unsigned short> CipherSuite;

	//! ���k�������X�g
	std::vector<unsigned char> CompressionMethods;

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
			char Data;
			pStream->Serialize(&Data);
			CompressionMethods.push_back(Data);
		}

		return !pStream->IsError();
	}
};

}
}
}
}

#endif	// #ifndef __SSLPACKET_H__
