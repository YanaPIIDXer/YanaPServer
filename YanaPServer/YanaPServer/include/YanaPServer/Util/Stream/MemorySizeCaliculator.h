#ifndef __MEMORYSIZECALICULATOR_H__
#define __MEMORYSIZECALICULATOR_H__

#include "MemoryStream.h"

namespace YanaPServer
{
namespace Util
{
namespace Stream
{

/**
 * @class CMemorySizeCaliculator
 * @brief サイズ計算ストリーム
 */
class CMemorySizeCaliculator : public IMemoryStream
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CMemorySizeCaliculator();

	/**
	 * @brief デストラクタ
	 */
	virtual ~CMemorySizeCaliculator() {}

	/**
	 * @fn virtual bool Serialize(int *pData) override
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
	 * @return エラーなんて無いので常にfalseを返す。
	 */
	virtual bool IsError() const override { return false; }

	/**
	 * @fn unsigned int GetSize() const
	 * @brief サイズ取得
	 * @return サイズ
	 */
	unsigned int GetSize() const { return Size; }

private:

	// サイズ
	unsigned int Size;

};

}
}
}

#endif		// #ifndef __MEMORYSIZECALICULATOR_H__
