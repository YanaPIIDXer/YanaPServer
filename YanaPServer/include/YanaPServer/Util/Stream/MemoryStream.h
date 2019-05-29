#ifndef __MEMORYSTREAM_H__
#define __MEMORYSTREAM_H__

#include <string>

namespace YanaPServer
{
namespace Util
{

class ISerializable;

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
	 * @fn virtual bool Serialize(int *pData) = 0
	 * @brief intのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(int *pData) = 0;

	/**
	 * @fn virtual bool Serialize(unsigned int *pData) = 0
	 * @brief unsigned intのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(unsigned int *pData) = 0;

	/**
	 * @fn virtual bool Serialize(short *pData) = 0
	 * @brief shortのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(short *pData) = 0;

	/**
	 * @fn virtual bool Serialize(unsigned short *pData) = 0
	 * @brief unsigned shortのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(unsigned short *pData) = 0;

	/**
	 * @fn virtual bool Serialize(char *pData) = 0
	 * @brief charのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(char *pData) = 0;

	/**
	 * @fn virtual bool Serialize(unsigned char *pData) = 0
	 * @brief unsigned charのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(unsigned char *pData) = 0;

	/**
	 * @fn virtual bool Serialize(float *pData) = 0
	 * @brief floatのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(float *pData) = 0;

	/**
	 * @fn virtual bool Serialize(std::string *pData) = 0
	 * @brief 文字列のシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(std::string *pData) = 0;

	/**
	 * @fn virtual bool Serialize(ISerializable *pData) = 0
	 * @brief シリアライズ可能なオブジェクトのシリアライズ
	 * @param[in] pData データ
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(ISerializable *pData) = 0;

	/**
	 * @fn virtual bool Serialize(void *pData, unsigned int DataSize) = 0
	 * @brief 任意のデータをシリアライズ
	 * @param[in] pData データ
	 * @param[in] DataSize データ長
	 * @return 成功したらtrueを返す。
	 */
	virtual bool Serialize(void *pData, unsigned int DataSize) = 0;

	/**
	 * @fn virtual bool IsError() const = 0
	 * @brief エラーが発生しているか？
	 * @return エラーが発生していたらtrueを返す。
	 */
	virtual bool IsError() const = 0;

	/**
	 * @fn virtual bool IsReadMode() const = 0
	 * @brief 読み込みモードか？
	 * @return 読み込みモードならtrueを返す。
	 */
	virtual bool IsReadMode() const = 0;

};

}
}
}

#endif		// #ifndef __MEMORYSTRAM_H__
