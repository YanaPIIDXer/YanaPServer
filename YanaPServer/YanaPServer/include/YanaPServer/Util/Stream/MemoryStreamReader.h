#ifndef __MEMORYSTREAMREADER_H__
#define __MEMORYSTREAMREADER_H__

#include "MemoryStream.h"

namespace YanaPServer
{
namespace Util
{
namespace Stream
{

/**
 * @class CMemoryStreamReader
 * @brief 読み込み用ストリーム
 */
class CMemoryStreamReader : public IMemoryStream
{

public:

	/**
 	 * @brief コンストラクタ
	 * @param[in] pInBuffer バッファ
 	 * @param[in] InBufferSize バッファサイズ
	 */
	CMemoryStreamReader(const char *pInBuffer, unsigned int InBufferSize);

	/**
	 * @brief デストラクタ
	 */
	virtual ~CMemoryStreamReader();

	/**
	 * @fn virtual bool Serialize(int *pData) = 0
	 * @brief intのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(int *pData) override;

	/**
	 * @fn virtual bool Serialize(unsigned int *pData) override
	 * @brief unsigned intのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(unsigned int *pData) override;

	/**
	 * @fn virtual bool Serialize(short *pData) override
	 * @brief shortのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(short *pData) override;

	/**
	 * @fn virtual bool Serialize(unsigned short *pData) override
	 * @brief unsigned shortのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(unsigned short *pData) override;

	/**
	 * @fn virtual bool Serialize(char *pData) override
	 * @brief charのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(char *pData) override;

	/**
	 * @fn virtual bool Serialize(unsigned char *pData) override
	 * @brief unsigned charのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(unsigned char *pData) override;

	/**
	 * @fn virtual bool Serialize(float *pData) override
	 * @brief floatのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(float *pData) override;

	/**
	 * @fn virtual bool Serialize(std::string *pData) override
	 * @brief 文字列のシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(std::string *pData) override;

	/**
	 * @fn virtual bool IsError() const override
	 * @brief エラーが発生しているか？
	 * @return エラーが発生していたらtrueを返す。
	 */
	virtual bool IsError() const override { return bIsError; }

private:

	// バッファ
	char *pBuffer;

	//バッファサイズ
	const unsigned int BufferSize;

	// 現在の位置.
	unsigned int CurrentPosition;

	// エラーが起きているか？
	bool bIsError;


	// 書き込み
	bool Read(void *pData, unsigned int Size);

};

}
}
}

#endif		// #ifndef __MEMORYSTREAMREADER_H__
