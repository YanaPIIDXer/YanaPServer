#ifndef __MYSQLCONNECTION_H__
#define __MYSQLCONNECTION_H__

#ifdef _WIN32
#include <windows.h>
#include <mysql.h>
#else
#include <mysql/mysql.h>
#endif

#include "MySqlQuery.h"

namespace YanaPServer
{
namespace MySQL
{

/**
 * @class CMySqlConnection
 * @brief MySQL接続クラス
 */
class CMySqlConnection
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CMySqlConnection();

	/**
	 * @brief デストラクタ
	 */
	~CMySqlConnection();

	/**
	 * @fn bool Connect(const char *pHost, const char *pUserName, const char *pPassword, const char *pDBName)
	 * @brief 接続
	 * @param[in] pHost ホスト
	 * @param[in] pUserName ユーザ名
	 * @param[in] pPassword パスワード
	 * @param[in] pDBName ＤＢ名
	 * @return 成功したらtrueを返す
	 */
	bool Connect(const char *pHost, const char *pUserName, const char *pPassword, const char *pDBName);

	/**
	 * @fn bool SimpleQuery(const char *pQuery) const
	 * @brief 単純なクエリ実行
	 * @param[in] pQuery クエリ
	 * @return 成功したらtrueを返す
	 */
	bool SimpleQuery(const char *pQuery) const;

	/**
	 * @fn CMySqlQuery CreateQuery(const char *pQuery) const
	 * @brief クエリ生成
	 * @param[in] pQuery クエリ
	 * @return クエリオブジェクト
	 */
	CMySqlQuery CreateQuery(const char *pQuery) const;

	/**
	 * @fn void Disconnect()
	 * @brief 切断
	 */
	void Disconnect();

private:

	// MySQLへの接続.
	MYSQL *pConnection;

};

}
}

#endif		// #ifndef __MYSQLCONNECTION_H__
