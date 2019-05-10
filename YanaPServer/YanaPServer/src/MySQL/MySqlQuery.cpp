#include "MySQL/MySqlQuery.h"

namespace YanaPServer
{
namespace MySQL
{

// コンストラクタ
CMySqlQuery::CMySqlQuery(MYSQL *pInConnection, const char *pInQuery)
	: pConnection(pInConnection)
	, pQuery(pInQuery)
	, pStatement(NULL)
{
}

// デストラクタ
CMySqlQuery::~CMySqlQuery()
{
	Close();
}

// int型のバインド
void CMySqlQuery::BindInt(int *pPtr)
{
	Binds.AddInt(pPtr);
}

// unsigned int型のバインド
void CMySqlQuery::BindInt(unsigned int *pPtr)
{
	Binds.AddInt(pPtr);
}

// short型のバインド
void CMySqlQuery::BindShort(short *pPtr)
{
	Binds.AddShort(pPtr);
}

// unsigned short型のバインド
void CMySqlQuery::BindShort(unsigned short *pPtr)
{
	Binds.AddShort(pPtr);
}

// char型のバインド
void CMySqlQuery::BindChar(char *pPtr)
{
	Binds.AddChar(pPtr);
}

// unsigned char型のバインド
void CMySqlQuery::BindChar(unsigned char *pPtr)
{
	Binds.AddChar(pPtr);
}

// float型のバインド
void CMySqlQuery::BindFloat(float *pPtr)
{
	Binds.AddFloat(pPtr);
}

// 文字列のバインド
void CMySqlQuery::BindString(char *pPtr)
{
	Binds.AddString(pPtr, false);
}

// ワイド文字列のバインド
void CMySqlQuery::BindWString(wchar_t *pPtr)
{
	Binds.AddWString(pPtr, false);
}

// 時間のバインド
void CMySqlQuery::BindTime(MYSQL_TIME *pPtr)
{
	Binds.AddTime(pPtr);
}

// 結果のint型バインド
void CMySqlQuery::BindResultInt(int *pPtr)
{
	Results.AddInt(pPtr);
}

// 結果のunsigned int型のバインド
void CMySqlQuery::BindResultInt(unsigned int *pPtr)
{
	Results.AddInt(pPtr);
}

// 結果のshort型のバインド
void CMySqlQuery::BindResultShort(short *pPtr)
{
	Results.AddShort(pPtr);
}

// 結果のunsigned short型のバインド
void CMySqlQuery::BindResultShort(unsigned short *pPtr)
{
	Results.AddShort(pPtr);
}

// 結果のchar型バインド
void CMySqlQuery::BindResultChar(char *pPtr)
{
	Results.AddChar(pPtr);
}

// 結果のunsigned char型バインド
void CMySqlQuery::BindResultChar(unsigned char *pPtr)
{
	Results.AddChar(pPtr);
}

// 結果のfloat型バインド
void CMySqlQuery::BindResultFloat(float *pPtr)
{
	Results.AddFloat(pPtr);
}

// 結果の文字列バインド
void CMySqlQuery::BindResultString(char *pPtr)
{
	Results.AddString(pPtr, true);
}

// 結果のワイド文字列バインド
void CMySqlQuery::BindResultWString(wchar_t *pPtr)
{
	Results.AddWString(pPtr, true);
}

// 結果の時間バインド
void CMySqlQuery::BindResultTime(MYSQL_TIME *pPtr)
{
	Results.AddTime(pPtr);
}

// クエリ実行.
bool CMySqlQuery::ExecuteQuery()
{
	pStatement = mysql_stmt_init(pConnection);
	if (pStatement == NULL) { return false; }

	int Result = mysql_stmt_prepare(pStatement, pQuery, strlen(pQuery));
	if (Result != 0) { return false; }

	MYSQL_BIND *pBinds = Binds.Get();
	if (pBinds != NULL)
	{
		Result = mysql_stmt_bind_param(pStatement, pBinds);
		if (Result != 0) { return false; }
	}

	MYSQL_BIND *pResults = Results.Get();
	if (pResults != NULL)
	{
		Result = mysql_stmt_bind_result(pStatement, pResults);
		if (Result != 0) { return false; }
	}

	Result = mysql_stmt_execute(pStatement);
	if (Result != 0) { return false; }

	return true;
}

// フェッチ
bool CMySqlQuery::Fetch()
{
	if (pStatement == NULL) { return false; }

	int Result = mysql_stmt_fetch(pStatement);
	return (Result == 0 || Result == MYSQL_DATA_TRUNCATED);
}

// 閉じる
void CMySqlQuery::Close()
{
	if (pStatement == NULL) { return; }

	mysql_stmt_close(pStatement);
	pStatement = NULL;
}

}
}
