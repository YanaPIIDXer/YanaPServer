#ifndef __RSA_H__
#define __RSA_H__

namespace YanaPServer
{
namespace Util
{
namespace Secure
{

typedef unsigned long long ULongLong;

/**
 * @struct SRSAKey
 * @brief RSA暗号化キー
 */
struct SRSAKey
{

	//! 公開キー
	ULongLong Public;

	//! ルール
	ULongLong Rule;


	/**
	 * @brief コンストラクタ
	 */
	SRSAKey()
		: Public(0)
		, Rule(0)
	{
	}

};

/**
 * @class RSA
 * @brief RSA暗号化
 */
class CRSA
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CRSA();

	/**
	 * @brief デストラクタ
	 */
	~CRSA() {}

	/**
	 * @fn bool Create()
	 * @brief 生成
	 * @return 成功したらtrueを返す
	 */
	bool Create();

	/**
	 * @fn ULongLong Encryption(ULongLong Value) const
	 * @brief 暗号化
	 * @param[in] Value 値
	 * @return 暗号化された値
	 */
	ULongLong Encryption(ULongLong Value) const;

	/**
	 * @fn ULongLong Decryption(ULongLong Value) const
	 * @brief 複合化
	 * @param[in] Value 値
	 * @return 複合化された値
	 */
	ULongLong Decryption(ULongLong Value) const;

private:

	// 公開鍵.
	SRSAKey OpenKey;

	// 秘密鍵
	ULongLong PrivateKey;


	// 最大公約数を求める。
	static ULongLong CalcGCD(ULongLong M, ULongLong N);

};

}
}
}

#endif		// #ifndef __RSA_H__
