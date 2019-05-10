#ifndef __MEMORYSTREAMWRITER_H__
#define __MEMORYSTREAMWRITER_H__

#include "MemoryStream.h"

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
	 * @fn virtual bool Serialize(const int *pData) = 0
	 * @brief intのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(const int *pData) override;

	/**
	 * @fn virtual bool Serialize(const unsigned int *pData) override
	 * @brief unsigned intのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(const unsigned int *pData) override;

	/**
	 * @fn virtual bool Serialize(const chat *pData) override
	 * @brief 文字列のシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(const char *pData) override;

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
