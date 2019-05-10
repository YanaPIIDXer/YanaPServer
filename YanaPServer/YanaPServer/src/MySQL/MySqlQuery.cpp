#include "MySQL/MySqlQuery.h"

namespace YanaPServer
{
namespace MySQL
{

// �R���X�g���N�^
CMySqlQuery::CMySqlQuery(MYSQL *pInConnection, const char *pInQuery)
	: pConnection(pInConnection)
	, pQuery(pInQuery)
	, pStatement(NULL)
{
}

// �f�X�g���N�^
CMySqlQuery::~CMySqlQuery()
{
	Close();
}

// int�^�̃o�C���h
void CMySqlQuery::BindInt(int *pPtr)
{
	Binds.AddInt(pPtr);
}

// unsigned int�^�̃o�C���h
void CMySqlQuery::BindInt(unsigned int *pPtr)
{
	Binds.AddInt(pPtr);
}

// short�^�̃o�C���h
void CMySqlQuery::BindShort(short *pPtr)
{
	Binds.AddShort(pPtr);
}

// unsigned short�^�̃o�C���h
void CMySqlQuery::BindShort(unsigned short *pPtr)
{
	Binds.AddShort(pPtr);
}

// char�^�̃o�C���h
void CMySqlQuery::BindChar(char *pPtr)
{
	Binds.AddChar(pPtr);
}

// unsigned char�^�̃o�C���h
void CMySqlQuery::BindChar(unsigned char *pPtr)
{
	Binds.AddChar(pPtr);
}

// float�^�̃o�C���h
void CMySqlQuery::BindFloat(float *pPtr)
{
	Binds.AddFloat(pPtr);
}

// ������̃o�C���h
void CMySqlQuery::BindString(char *pPtr)
{
	Binds.AddString(pPtr, false);
}

// ���C�h������̃o�C���h
void CMySqlQuery::BindWString(wchar_t *pPtr)
{
	Binds.AddWString(pPtr, false);
}

// ���Ԃ̃o�C���h
void CMySqlQuery::BindTime(MYSQL_TIME *pPtr)
{
	Binds.AddTime(pPtr);
}

// ���ʂ�int�^�o�C���h
void CMySqlQuery::BindResultInt(int *pPtr)
{
	Results.AddInt(pPtr);
}

// ���ʂ�unsigned int�^�̃o�C���h
void CMySqlQuery::BindResultInt(unsigned int *pPtr)
{
	Results.AddInt(pPtr);
}

// ���ʂ�short�^�̃o�C���h
void CMySqlQuery::BindResultShort(short *pPtr)
{
	Results.AddShort(pPtr);
}

// ���ʂ�unsigned short�^�̃o�C���h
void CMySqlQuery::BindResultShort(unsigned short *pPtr)
{
	Results.AddShort(pPtr);
}

// ���ʂ�char�^�o�C���h
void CMySqlQuery::BindResultChar(char *pPtr)
{
	Results.AddChar(pPtr);
}

// ���ʂ�unsigned char�^�o�C���h
void CMySqlQuery::BindResultChar(unsigned char *pPtr)
{
	Results.AddChar(pPtr);
}

// ���ʂ�float�^�o�C���h
void CMySqlQuery::BindResultFloat(float *pPtr)
{
	Results.AddFloat(pPtr);
}

// ���ʂ̕�����o�C���h
void CMySqlQuery::BindResultString(char *pPtr)
{
	Results.AddString(pPtr, true);
}

// ���ʂ̃��C�h������o�C���h
void CMySqlQuery::BindResultWString(wchar_t *pPtr)
{
	Results.AddWString(pPtr, true);
}

// ���ʂ̎��ԃo�C���h
void CMySqlQuery::BindResultTime(MYSQL_TIME *pPtr)
{
	Results.AddTime(pPtr);
}

// �N�G�����s.
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

// �t�F�b�`
bool CMySqlQuery::Fetch()
{
	if (pStatement == NULL) { return false; }

	int Result = mysql_stmt_fetch(pStatement);
	return (Result == 0 || Result == MYSQL_DATA_TRUNCATED);
}

// ����
void CMySqlQuery::Close()
{
	if (pStatement == NULL) { return; }

	mysql_stmt_close(pStatement);
	pStatement = NULL;
}

}
}
