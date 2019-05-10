#ifndef __MEMORYSTREAM_H__
#define __MEMORYSTREAM_H__

namespace YanaPServer
{
namespace Util
{
namespace Stream
{

/**
 * @class IMemoryStream
 * @brief メモリストリーム
 */
class IMemoryStream
{

public:

	/**
	 * @brief デストラクタ
	 */
	virtual ~IMemoryStream() {}

	/**
	 * @fn virtual bool Serialize(const int *pData) = 0
	 * @brief intのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(const int *pData) = 0;

	/**
	 * @fn virtual bool Serialize(const unsigned int *pData) = 0
	 * @brief unsigned intのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(const unsigned int *pData) = 0;

	/**
	 * @fn virtual bool Serialize(const chat *pData) = 0
	 * @brief 文字列のシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(const char *pData) = 0;

	/**
	 * @fn virtual bool IsError() const = 0
	 * @brief エラーが発生しているか？
	 * @return エラーが発生していたらtrueを返す。
	 */
	virtual bool IsError() const = 0;

};

}
}
}

#endif		// #ifndef __MEMORYSTRAM_H__
