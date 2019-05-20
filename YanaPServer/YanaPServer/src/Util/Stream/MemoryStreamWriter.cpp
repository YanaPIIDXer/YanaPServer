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

// short�̃V���A���C�Y
bool CMemoryStreamWriter::Serialize(const short *pData)
{
	short Data = CEndianConverter::Convert(*pData);
	return Write(&Data, sizeof(short));
}

// unsigned short�̃V���A���C�Y
bool CMemoryStreamWriter::Serialize(const unsigned short *pData)
{
	unsigned short Data = CEndianConverter::Convert(*pData);
	return Write(&Data, sizeof(unsigned short));
}

// float�̃V���A���C�Y
bool CMemoryStreamWriter::Serialize(const float *pData)
{
	float Data = CEndianConverter::Convert(*pData);
	return Write(&Data, sizeof(float));
}

// ������̃V���A���C�Y
bool CMemoryStreamWriter::Serialize(const char *pData)
{
	// ������.
	unsigned int Length = strlen(pData);
	if (!Serialize(&Length)) { return false; }

	// ������.
	return Write(pData, Length);
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
