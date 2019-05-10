#ifndef __STRINGSTREAM_H__
#define __STRINGSTREAM_H__

namespace YanaPServer
{
namespace Util
{
namespace Stream
{

/**
 * @class CStringStream
 * @brief 文字列ストリーム
 * @detail Appendするたびに内部でnewとdeleteが走るので注意。
 */
class CStringStream
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CStringStream();

	/**
	 * @brief デストラクタ
	 */
	~CStringStream();

	/**
	 * @fn void Append(const char *pStr)
	 * @brief 追加
	 * @param[in] pStr 追加する文字列
	 */
	void Append(const char *pStr);

	/**
	 * @fn const char *GetBuffer() const
	 * @brief 文字列取得
	 * @return 文字列
	 */
	const char *Get() const { return pBuffer; }

	/**
	 * @fn unsigned int GetLength() const
	 * @brief 文字列長取得
	 * @return 文字列長
	 */
	unsigned int GetLength() const { return Length; }

private:

	// バッファ
	char *pBuffer;

	// 文字列長.
	unsigned int Length;

};

}
}
}

#endif		// #ifndef __STRINGSTREAM_H__
