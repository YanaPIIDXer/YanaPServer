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
	, BufferSize(0)
	, CurrentPosition(0)
{
}

// �f�X�g���N�^
CDynamicMemoryStreamWriter::~CDynamicMemoryStreamWriter()
{
	delete[] pBuffer;
}

// int�̃V���A���C�Y
bool CDynamicMemoryStreamWriter::Serialize(int *pData)
{
	int Data = CEndianConverter::Convert(*pData);
	return Write(&Data, sizeof(int));
}

// unsigned int�̃V���A���C�Y
bool CDynamicMemoryStreamWriter::Serialize(unsigned int *pData)
{
	unsigned int Data = CEndianConverter::Convert(*pData);
	return Write(&Data, sizeof(unsigned int));
}

// ������̃V���A���C�Y
bool CDynamicMemoryStreamWriter::Serialize(char *pData)
{
	// �T�C�Y
	size_t Size = strlen(pData);
	if (!Serialize(&Size)) { return false; }

	// ���ۂ̕�����.
	return Write(pData, Size);
}


// ��������
bool CDynamicMemoryStreamWriter::Write(void *pData, unsigned int Size)
{
	unsigned char *pTmp = new unsigned char[CurrentPosition + Size];
	if (pBuffer != nullptr)
	{
		memcpy(pTmp, pBuffer, CurrentPosition);
	}
	delete pBuffer;
	pBuffer = pTmp;

	memcpy((pBuffer + CurrentPosition), pData, Size);
	CurrentPosition += Size;
	return true;
}

}
}
}
