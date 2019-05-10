#include "Util/Stream/DynamicMemoryStreamWriter.h"
#include <memory.h>
#include <string.h>
#include "Util/EndianConverter.h"

namespace YanaPServer
{
namespace Util
{
namespace Stream
{

// �R���X�g���N�^
CDynamicMemoryStreamWriter::CDynamicMemoryStreamWriter()
	: pBuffer(nullptr)
	, CurrentPosition(0)
{
}

// �f�X�g���N�^
CDynamicMemoryStreamWriter::~CDynamicMemoryStreamWriter()
{
	delete[] pBuffer;
}

// int�̃V���A���C�Y
bool CDynamicMemoryStreamWriter::Serialize(const int *pData)
{
	int Data = CEndianConverter::Convert(*pData);
	return Write(&Data, sizeof(int));
}

// unsigned int�̃V���A���C�Y
bool CDynamicMemoryStreamWriter::Serialize(const unsigned int *pData)
{
	unsigned int Data = CEndianConverter::Convert(*pData);
	return Write(&Data, sizeof(unsigned int));
}

// ������̃V���A���C�Y
bool CDynamicMemoryStreamWriter::Serialize(const char *pData)
{
	size_t Size = strlen(pData) + 1;
	return Write(pData, Size);
}


// ��������
bool CDynamicMemoryStreamWriter::Write(const void *pData, unsigned int Size)
{
	char *pTmp = new char[CurrentPosition + Size];
	if (pBuffer != nullptr)
	{
		memcpy(pTmp, pBuffer, CurrentPosition);
		delete pBuffer;
	}
	pBuffer = pTmp;

	memcpy((pBuffer + CurrentPosition), pData, Size);
	CurrentPosition += Size;
	return true;
}

}
}
}
