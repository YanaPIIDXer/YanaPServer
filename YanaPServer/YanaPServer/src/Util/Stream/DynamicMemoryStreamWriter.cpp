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

// コンストラクタ
CDynamicMemoryStreamWriter::CDynamicMemoryStreamWriter()
	: pBuffer(nullptr)
	, BufferSize(0)
	, CurrentPosition(0)
{
}

// デストラクタ
CDynamicMemoryStreamWriter::~CDynamicMemoryStreamWriter()
{
	delete[] pBuffer;
}

// intのシリアライズ
bool CDynamicMemoryStreamWriter::Serialize(int *pData)
{
	int Data = CEndianConverter::Convert(*pData);
	return Write(&Data, sizeof(int));
}

// unsigned intのシリアライズ
bool CDynamicMemoryStreamWriter::Serialize(unsigned int *pData)
{
	unsigned int Data = CEndianConverter::Convert(*pData);
	return Write(&Data, sizeof(unsigned int));
}

// 文字列のシリアライズ
bool CDynamicMemoryStreamWriter::Serialize(char *pData)
{
	// サイズ
	size_t Size = strlen(pData);
	if (!Serialize(&Size)) { return false; }

	// 実際の文字列.
	return Write(pData, Size);
}


// 書き込み
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
