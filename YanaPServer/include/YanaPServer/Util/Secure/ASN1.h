#ifndef __ASN1_H__
#define __ASN1_H__

#include "Util/Serializable.h"
#include <vector>

namespace YanaPServer
{
namespace Util
{
namespace Secure
{

/**
 * @class CBER
 * @brief Basic Encoding Rule�t�H�[�}�b�g
 */
class CBER : public YanaPServer::Util::ISerializable
{

public:

	//1 Class
	unsigned char Class;

	//! P/C
	unsigned char PC;

	//! TagNumber
	unsigned char TagNumber;

	//! Content
	std::vector<unsigned char> Content;

	//! �q�v�f�iPC��1�������ꍇ�Ɏg�p�����j
	CBER *pChild;

	/**
	 * @brief �R���X�g���N�^
	 */
	CBER()
	 : Class(0)
	 , PC(0)
	 , TagNumber(0)
	 , pChild(nullptr)
	{
	}

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CBER()
	{
		delete pChild;
	}

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief �V���A���C�Y
	 * @param[in] pStream �X�g���[��
	 * @return ����������true��Ԃ�
	 */
	virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	{
		unsigned char Identifier = 0;
		unsigned char Length = 0;
		pStream->Serialize(&Identifier);
		pStream->Serialize(&Length);

		Class = ((Identifier & 0xC0) >> 6);
		PC = ((Identifier & 0x20) >> 5);
		TagNumber = (Identifier & 0x1F);

		if (PC == 1)
		{
			pChild = new CBER();
			return pChild->Serialize(pStream);
		}
		
		if (Length < 0x7F)
		{
			for (unsigned char i = 0; i < Length; i++)
			{
				unsigned char Data = 0;
				pStream->Serialize(&Data);
				Content.push_back(Data);
			}
		}
		else if (Length == 0x80)
		{
			while (true)
			{
				unsigned char Data = 0;
				pStream->Serialize(&Data);
				if (Data == 0x00)
				{
					unsigned char Data2 = 0;
					pStream->Serialize(&Data2);
					if (Data2 == 0x00) { break; }

					Content.push_back(Data);
					Content.push_back(Data2);
				}
				else
				{
					Content.push_back(Data);
				}
			}
		}
		else
		{
			unsigned char Bytes = (Length & 0x7F);
			Length = 0;
			for (unsigned char i = 0; i < Bytes; i++)
			{
				unsigned char Data = 0;
				pStream->Serialize(&Data);
				Length |= (Data << i);
			}

			for (unsigned char i = 0; i < Length; i++)
			{
				unsigned char Data = 0;
				pStream->Serialize(&Data);
				Content.push_back(Data);
			}
		}

		return !pStream->IsError();
	}
};

/**
 * @class CASN1
 * @brief ASN1�f�[�^
 */
class CASN1 : public YanaPServer::Util::ISerializable
{

public:

	//! BER�f�[�^���X�g
	std::vector<CBER *> BERs;

	/**
	 * @brief �R���X�g���N�^
	 */
	CASN1() {}

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CASN1()
	{
		for (auto *pBER : BERs)
		{
			delete pBER;
		}
		BERs.clear();
	}

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief �V���A���C�Y
	 * @param[in] pStream �X�g���[��
	 * @return ����������true��Ԃ�
	 */
	virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	{
		while (true)
		{
			CBER *pBER = new CBER();
			if (!pBER->Serialize(pStream))
			{
				delete pBER;
				break;
			}
			BERs.push_back(pBER);
		}

		return true;
	}
};

}
}
}

#endif		// #ifndef __ASN1_H__
