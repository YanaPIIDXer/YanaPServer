#ifndef __MYSQLBINDS_H__
#define __MYSQLBINDS_H__

#ifdef _WIN32
#include <windows.h>
#include <mysql.h>
#else
#include <mysql/mysql.h>
#endif

#include <vector>

namespace YanaPServer
{
namespace MySQL
{

/**
 * @class CMySqlBinds
 * @brief バインド
 * @detail 利用者がこのクラスを直接操作する事はない。
 *         （CMySqlQueryクラスを使用する。）
 */
class CMySqlBinds
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CMySqlBinds();

	/**
	 * @brief デストラクタ
	 */
	~CMySqlBinds();

	/**
	 * @fn void AddInt(int *pPtr)
	 * @brief int追加
	 * @param[in] pPtr 変数へのポインタ
	 */
	void AddInt(int *pPtr);

	/**
	 * @fn void AddInt(unsigned int *pPtr)
	 * @brief unsigned int追加
	 * @param[in] pPtr 変数へのポインタ
	 */
	void AddInt(unsigned int *pPtr);

	/**
	 * @fn void AddShort(short *pPtr)
	 * @brief short追加
	 * @param[in] pPtr 変数へのポインタ
	 */
	void AddShort(short *pPtr);

	/**
	 * @fn void AddShort(unsigned short *pPtr)
	 * @brief unsigned short追加
	 * @param[in] pPtr 変数へのポインタ
	 */
	void AddShort(unsigned short *pPtr);

	/**
	 * @fn void AddChar(char *pPtr)
	 * @brief char追加
	 * @param[in] pPtr 変数へのポインタ
	 */
	void AddChar(char *pPtr);

	/**
	 * @fn void AddChar(unsigned char *pPtr)
	 * @brief unsigned char追加
	 * @param[in] pPtr 変数へのポインタ
	 */
	void AddChar(unsigned char *pPtr);

	/**
	 * @fn void AddFloat(float *pPtr)
	 * @brief float追加
	 * @param[in] pPtr 変数へのポインタ
	 */
	void AddFloat(float *pPtr);

	/**
	 * @fn void AddString(char *pPtr)
	 * @brief 文字列追加
	 * @param[in] pPtr 変数へのポインタ
	 * @param[in] bForResult 結果へのバインドか？
	 */
	void AddString(char *pPtr, bool bForResult);

	/**
	 * @fn void AddWString(wchar_t *pPtr)
	 * @brief ワイド文字列追加
	 * @param[in] pPtr 変数へのポインタ
	 * @param[in] bForResult 結果へのバインドか？
	 */
	void AddWString(wchar_t *pPtr, bool bForResult);

	/**
	 * @fn void AddTime(MYSQL_TIME *pPtr)
	 * @brief 時間追加
	 * @param[in] pPtr 変数へのポインタ
	 */
	void AddTime(MYSQL_TIME *pPtr);

	/**
	 * @fn MYSQL_BIND *Get() 
	 * @brief 取得
	 * @return バインドオブジェクト
	 */
	MYSQL_BIND *Get() { return pBinds; }

private:

	// String型のバッファ長.
	static const int StringBufferLength;

	// バインド
	MYSQL_BIND *pBinds;

	// 配列長.
	int Length;

	// 領域拡張.
	void Reallocate();

};

}
}

#endif		// #ifndef __MYSQLBINDS_H__
