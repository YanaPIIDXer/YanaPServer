#include "Util/Stream/StringStream.h"
#include <string.h>
#include <memory.h>

namespace YanaPServer
{
namespace Util
{
namespace Stream
{

// �R���X�g���N�^
CStringStream::CStringStream()
	: pBuffer(nullptr)
	, Length(0)
{
	pBuffer = new char[1];
	pBuffer[0] = '\0';
}

// �f�X�g���N�^
CStringStream::~CStringStream()
{
	delete[] pBuffer;
}

// �ǉ�.
void CStringStream::Append(const char *pStr)
{
	size_t StrLength = strlen(pStr);
	int NewBufferSize = Length + StrLength + 1;
	char *pTmp = new char[NewBufferSize];
	memset(pTmp, 0, NewBufferSize);
	memcpy(pTmp, pBuffer, Length);

	delete[] pBuffer;
	pBuffer = pTmp;

	memcpy((pBuffer + Length), pStr, StrLength);
	Length += StrLength;
}

// �����ɉ��s��t�����Ēǉ�.
void CStringStream::AppendLine(const char *pStr)
{
	size_t StrLength = strlen(pStr);
	int NewBufferSize = Length + StrLength + 2;
	char *pTmp = new char[NewBufferSize];
	memset(pTmp, 0, NewBufferSize);
	memcpy(pTmp, pBuffer, Length);

	delete[] pBuffer;
	pBuffer = pTmp;

	memcpy((pBuffer + Length), pStr, StrLength);
	(*(pBuffer + Length + StrLength)) = '\n';
	Length += StrLength + 1;
}

}
}
}
