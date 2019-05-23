#ifndef __MEMORYSTREAMWRITER_H__
#define __MEMORYSTREAMWRITER_H__

#include "MemoryStream.h"
#include "../Serializable.h"

namespace YanaPServer
{
namespace Util
{
namespace Stream
{

/**
 * @class CMemoryStreamWriter
 * @brief 書き込み用ストリーム
 */
class CMemoryStreamWriter : public IMemoryStream
{

public:

	/**
	 * @brief コンストラクタ
	 * @param[in] InBufferSize バッファサイズ
	 */
	CMemoryStreamWriter(unsigned int InBufferSize);

	/**
	 * @brief デストラクタ
	 */
	virtual ~CMemoryStreamWriter();

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
	 * @fn virtual bool Serialize(ISerializable *pData) override
	 * @brief シリアライズ可能なオブジェクトのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(ISerializable *pData) override { return pData->Serialize(this); }

	/**
	 * @fn virtual bool IsError() const override
	 * @brief エラーが発生しているか？
	 * @return エラーが発生していたらtrueを返す。
	 */
	virtual bool IsError() const override { return bIsError; }

	/**
	 * @fn const char *GetBuffer() const
	 * @brief バッファを取得。
	 * @detail バッファの先頭位置を返す。
	 * @return バッファ
	 */
	const char *GetBuffer() const { return pBuffer; }

	/**
	 * @fn unsigned int GetSize() const
	 * @brief サイズを取得
	 * @return サイズ
	 */
	unsigned int GetSize() const { return CurrentPosition; }

private:

	// バッファ
	char *pBuffer;

	// バッファサイズ
	unsigned int BufferSize;

	// 現在の位置.
	unsigned int CurrentPosition;

	// エラーが起きているか？
	bool bIsError;


	// 書き込み
	bool Write(const void *pData, unsigned int Size);

};

}
}
}

#endif		// #ifndef __MEMORYSTREAMWRITER_H__
