#ifndef __BASE64_H__
#define __BASE64_H__

#include <string>
#include <vector>

namespace YanaPServer
{
namespace Util
{
namespace Secure
{

/**
 * @class CBase64
 * @brief Base64を扱うクラス
 * @detail スタティッククラス
 */
class CBase64
{

public:

	/**
	 * @fn static bool Decode(const std::string &Src, std::vector<char> &OutResult)
	 * @brief デコード
	 * @param[in] Src Base64で変換されている文字列
	 * @param[out] OutResult デコード結果
	 * @return 成功したらtrueを返す。
	 */
	static bool Decode(const std::string &Src, std::vector<char> &OutResult);

private:

	// テーブル
	static const std::string Table;

private:

	// ====== 封印 =====
	CBase64();
	CBase64(const CBase64 &Arg);
	CBase64 operator =(const CBase64 &Arg);

};

}
}
}

#endif		// #ifndef __BASE64_H__
