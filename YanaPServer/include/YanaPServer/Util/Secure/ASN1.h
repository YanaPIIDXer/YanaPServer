#ifndef __ASN1_H__
#define __ASN1_H__

#include "Util/Serializable.h"
#include <vector>
#include "Util/Stream/MemoryStreamReader.h"

#include <iostream>

namespace YanaPServer
{
namespace Util
{
namespace Secure
{

/**
 * @class CBER
 * @brief Basic Encoding Ruleフォーマット
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

	//! 子要素群
	std::vector<CBER *> Children;

	/**
	 * @brief コンストラクタ
	 */
	CBER()
	 : Class(0)
	 , PC(0)
	 , TagNumber(0)
	{
	}

	/**
	 * @brief デストラクタ
	 */
	virtual ~CBER()
	{
		for (auto *pChild : Children)
		{
			delete pChild;
		}
		Children.clear();
	}

	/**
	 * @fn virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	 * @brief シリアライズ
	 * @param[in] pStream ストリーム
	 * @return 成功したらtrueを返す
	 */
	virtual bool Serialize(YanaPServer::Util::Stream::IMemoryStream *pStream) override
	{
		unsigned char Identifier = 0;
		unsigned int Length = 0;
		pStream->Serialize(&Identifier);
		pStream->Serialize(&Length, 1);

		if (pStream->IsError()) { return false; }

		Class = ((Identifier & 0xC0) >> 6);
		PC = ((Identifier & 0x20) >> 5);
		TagNumber = (Identifier & 0x1F);
		bool bHasEOF = (Length == 0x80);

		int Bytes = 0;
		if (Length >= 0x81)
		{
			Bytes = (Length & 0x7F);
			Length = 0;
			for (int i = Bytes - 1; i >= 0; i--)
			{
				unsigned int Data = 0;
				pStream->Serialize(&Data, 1);
				Length |= (Data << (i * 8));
			}
		}

		if (PC == 1)
		{
			// 別ストリームに流し込み、子要素を列挙する。
			char *pData = new char[Length];
			pStream->Serialize(pData, Length);
			YanaPServer::Util::Stream::CMemoryStreamReader StreamReader(pData, Length);

			while (StreamReader.IsLeftData())
			{
				CBER * pChild = new CBER();
				if (!pChild->Serialize(&StreamReader))
				{
					delete pChild;
					return false;
				}

				Children.push_back(pChild);
			}
			return true;
		}
		
		if (bHasEOF)
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
			for (unsigned int i = 0; i < Length; i++)
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
 * @brief ASN1データ
 */
class CASN1 : public YanaPServer::Util::ISerializable
{

public:

	//! BERデータリスト
	std::vector<CBER *> BERs;

	/**
	 * @brief コンストラクタ
	 */
	CASN1() {}

	/**
	 * @brief デストラクタ
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
	 * @brief シリアライズ
	 * @param[in] pStream ストリーム
	 * @return 成功したらtrueを返す
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
			std::cout << "Create BER Data. Child Count:" << pBER->Children.size() << std::endl;
			BERs.push_back(pBER);
		}

		return true;
	}
};

}
}
}

#endif		// #ifndef __ASN1_H__
