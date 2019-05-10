#ifndef __DYNAMICMEMORYSTREAMWRITER_H__
#define __DYNAMICMEMORYSTREAMWRITER_H__

#include "MemoryStream.h"

namespace YanaPServer
{
namespace Util
{
namespace Stream
{

/**
 * @class CDynamicMemoryStreamWriter
 * @brief 動的にメモリを確保しながら書き込むストリームクラス
 * @detail 通常はSizeCaliculator → StreamWriterの流れで書き込むが、
 *         ストリームに書き込んでいる最中に動的な処理を組んだりするケースでは
 *         こちらのクラスを使う事。
 *         ※中身でnew、deleteを繰り返すので注意。
 */
class CDynamicMemoryStreamWriter : public IMemoryStream
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CDynamicMemoryStreamWriter();

	/**
	 * @brief デストラクタ
	 */
	virtual ~CDynamicMemoryStreamWriter();

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
	 * @fn virtual bool Serialize(chat *pData) override
	 * @brief 文字列のシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(char *pData) override;

	/**
	 * @fn virtual bool IsError() const override
	 * @brief エラーが発生しているか？
	 * @return エラーは起きないので常にfalseを返す。
	 */
	virtual bool IsError() const override { return false; }

	/**
	 * @fn unsigned char *GetBuffer() const
	 * @brief バッファを取得。
	 * @detail バッファの先頭位置を返す。
	 * @return バッファ
	 */
	unsigned char *GetBuffer() const { return pBuffer; }

	/**
	 * @fn unsigned int GetSize() const
	 * @brief サイズを取得
	 * @return サイズ
	 */
	unsigned int GetSize() const { return CurrentPosition; }

private:

	// バッファ
	unsigned char *pBuffer;

	// バッファサイズ
	unsigned int BufferSize;

	// 現在の位置.
	unsigned int CurrentPosition;


	// 書き込み
	bool Write(void *pData, unsigned int Size);

};

}
}
}

#endif		// #ifndef __DYNAMICMEMORYSTREAMWRITER_H__
