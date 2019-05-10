#include "MySQL/MySqlConnection.h"

namespace YanaPServer
{
namespace MySQL
{

// コンストラクタ
CMySqlConnection::CMySqlConnection()
	: pConnection(NULL)
{
}

// デストラクタ
CMySqlConnection::~CMySqlConnection()
{
	Disconnect();
}

// 接続.
bool CMySqlConnection::Connect(const char *pHost, const char *pUserName, const char *pPassword, const char *pDBName)
{
	if (pConnection != NULL)
	{
		Disconnect();
	}

	pConnection = mysql_init(NULL);
	if (pConnection == NULL) { return false; }

	mysql_options(pConnection, MYSQL_SET_CHARSET_NAME, "utf8");

	if (!mysql_real_connect(pConnection, pHost, pUserName, pPassword, pDBName, 0, NULL, 0)) { return false; }

	return true;
}

// 単純なクエリ実行.
bool CMySqlConnection::SimpleQuery(const char *pQuery) const
{
	if (pConnection == NULL) { return false; }

	int Result = mysql_query(pConnection, pQuery);
	return (Result == 0);
}

// クエリ生成.
CMySqlQuery CMySqlConnection::CreateQuery(const char *pQuery) const
{
	CMySqlQuery Query(pConnection, pQuery);
	return Query;
}

// 切断
void CMySqlConnection::Disconnect()
{
	if (pConnection == NULL) { return; }

	mysql_close(pConnection);
	pConnection = NULL;
}

}
}
