#include "Util/Stream/MemoryStreamWriter.h"
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
CMemoryStreamWriter::CMemoryStreamWriter(unsigned int InBufferSize)
	: pBuffer(nullptr)
	, BufferSize(InBufferSize)
	, CurrentPosition(0)
	, bIsError(false)
{
	pBuffer = new char[BufferSize];
}

// �f�X�g���N�^
CMemoryStreamWriter::~CMemoryStreamWriter()
{
	delete[] pBuffer;
}

// int�̃V���A���C�Y
bool CMemoryStreamWriter::Serialize(const int *pData)
{
	int Data = CEndianConverter::Convert(*pData);
	return Write(&Data, sizeof(int));
}

// unsigned int�̃V���A���C�Y
bool CMemoryStreamWriter::Serialize(const unsigned int *pData)
{
	unsigned int Data = CEndianConverter::Convert(*pData);
	return Write(&Data, sizeof(unsigned int));
}

// ������̃V���A���C�Y
bool CMemoryStreamWriter::Serialize(const char *pData)
{
	// �T�C�Y
	size_t Size = strlen(pData);
	if (!Serialize(&Size)) { return false; }

	// ���ۂ̕�����.
	return Write(pData, Size);
}


// ��������
bool CMemoryStreamWriter::Write(const void *pData, unsigned int Size)
{
	if (CurrentPosition + Size > BufferSize)
	{
		// �o�b�t�@�T�C�Y���I�[�o�[������G���[
		bIsError = true;
		return false;
	}

	memcpy((pBuffer + CurrentPosition), pData, Size);
	CurrentPosition += Size;
	return true;
}

}
}
}
