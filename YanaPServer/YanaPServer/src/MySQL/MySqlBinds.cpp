#include "MySql/MySqlBinds.h"

namespace YanaPServer
{
namespace MySQL
{

const int CMySqlBinds::StringBufferLength = 256;

// �R���X�g���N�^
CMySqlBinds::CMySqlBinds()
	: pBinds(NULL)
	, Length(0)
{
}

// �f�X�g���N�^
CMySqlBinds::~CMySqlBinds()
{
	delete[] pBinds;
	pBinds = NULL;
}

// int�ǉ�.
void CMySqlBinds::AddInt(int *pPtr)
{
	MYSQL_BIND Bind;
	memset(&Bind, 0, sizeof(Bind));
	Bind.buffer_type = MYSQL_TYPE_LONG;
	Bind.buffer = pPtr;
	Bind.buffer_length = sizeof(*pPtr);
	Bind.is_null = 0;

	Reallocate();
	pBinds[Length - 1] = Bind;
}

// unsigned int�^�ǉ�.
void CMySqlBinds::AddInt(unsigned int *pPtr)
{
	MYSQL_BIND Bind;
	memset(&Bind, 0, sizeof(Bind));
	Bind.buffer_type = MYSQL_TYPE_LONG;
	Bind.is_unsigned = true;
	Bind.buffer = pPtr;
	Bind.buffer_length = sizeof(*pPtr);
	Bind.is_null = 0;

	Reallocate();
	pBinds[Length - 1] = Bind;
}

// short�ǉ�.
void CMySqlBinds::AddShort(short *pPtr)
{
	MYSQL_BIND Bind;
	memset(&Bind, 0, sizeof(Bind));
	Bind.buffer_type = MYSQL_TYPE_SHORT;
	Bind.buffer = pPtr;
	Bind.buffer_length = sizeof(*pPtr);
	Bind.is_null = 0;

	Reallocate();
	pBinds[Length - 1] = Bind;
}

// unsigned short�ǉ�.
void CMySqlBinds::AddShort(unsigned short *pPtr)
{
	MYSQL_BIND Bind;
	memset(&Bind, 0, sizeof(Bind));
	Bind.buffer_type = MYSQL_TYPE_SHORT;
	Bind.buffer = pPtr;
	Bind.buffer_length = sizeof(*pPtr);
	Bind.is_unsigned = true;
	Bind.is_null = 0;

	Reallocate();
	pBinds[Length - 1] = Bind;
}

// char�ǉ�.
void CMySqlBinds::AddChar(char *pPtr)
{
	MYSQL_BIND Bind;
	memset(&Bind, 0, sizeof(Bind));
	Bind.buffer_type = MYSQL_TYPE_TINY;
	Bind.buffer = pPtr;
	Bind.buffer_length = sizeof(*pPtr);
	Bind.is_null = 0;

	Reallocate();
	pBinds[Length - 1] = Bind;
}

// unsigned char�ǉ�.
void CMySqlBinds::AddChar(unsigned char *pPtr)
{
	MYSQL_BIND Bind;
	memset(&Bind, 0, sizeof(Bind));
	Bind.buffer_type = MYSQL_TYPE_TINY;
	Bind.buffer = pPtr;
	Bind.buffer_length = sizeof(*pPtr);
	Bind.is_unsigned = true;
	Bind.is_null = 0;

	Reallocate();
	pBinds[Length - 1] = Bind;
}

// float�ǉ�.
void CMySqlBinds::AddFloat(float *pPtr)
{
	MYSQL_BIND Bind;
	memset(&Bind, 0, sizeof(Bind));
	Bind.buffer_type = MYSQL_TYPE_FLOAT;
	Bind.buffer = pPtr;
	Bind.buffer_length = sizeof(*pPtr);
	Bind.is_null = 0;

	Reallocate();
	pBinds[Length - 1] = Bind;
}

// ������ǉ�.
void CMySqlBinds::AddString(char *pPtr, bool bForResult)
{
	MYSQL_BIND Bind;
	memset(&Bind, 0, sizeof(Bind));
	Bind.buffer_type = MYSQL_TYPE_STRING;
	Bind.buffer = pPtr;
	if (!bForResult)
	{
		Bind.buffer_length = strlen(pPtr);
	}
	else
	{
		Bind.buffer_length = StringBufferLength;
	}
	Bind.is_null = 0;

	Reallocate();
	pBinds[Length - 1] = Bind;
}

// ���C�h������ǉ�.
void CMySqlBinds::AddWString(wchar_t *pPtr, bool bForResult)
{
	MYSQL_BIND Bind;
	memset(&Bind, 0, sizeof(Bind));
	Bind.buffer_type = MYSQL_TYPE_STRING;
	Bind.buffer = pPtr;
	if (!bForResult)
	{
		Bind.buffer_length = wcslen(pPtr);
	}
	else
	{
		Bind.buffer_length = StringBufferLength;
	}
	Bind.is_null = 0;

	Reallocate();
	pBinds[Length - 1] = Bind;
}

// ���Ԓǉ�.
void CMySqlBinds::AddTime(MYSQL_TIME *pPtr)
{
	MYSQL_BIND Bind;
	memset(&Bind, 0, sizeof(Bind));
	Bind.buffer_type = MYSQL_TYPE_DATE;
	Bind.buffer = pPtr;
	Bind.buffer_length = sizeof(*pPtr);
	Bind.is_null = 0;

	Reallocate();
	pBinds[Length - 1] = Bind;
}


// �̈�g��.
void CMySqlBinds::Reallocate()
{
	MYSQL_BIND *pTmp = pBinds;
	Length++;
	pBinds = new MYSQL_BIND[Length];
	for (int i = 0; i < Length - 1; i++)
	{
		pBinds[i] = pTmp[i];
	}

	delete[] pTmp;
}

}
}