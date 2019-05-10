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
bool CDynamicMemoryStreamWriter::Serialize(const int *pData)
{
	int Data = CEndianConverter::Convert(*pData);
	return Write(&Data, sizeof(int));
}

// unsigned intのシリアライズ
bool CDynamicMemoryStreamWriter::Serialize(const unsigned int *pData)
{
	unsigned int Data = CEndianConverter::Convert(*pData);
	return Write(&Data, sizeof(unsigned int));
}

// 文字列のシリアライズ
bool CDynamicMemoryStreamWriter::Serialize(const char *pData)
{
	// サイズ
	size_t Size = strlen(pData);
	if (!Serialize(&Size)) { return false; }

	// 実際の文字列.
	return Write(pData, Size);
}


// 書き込み
bool CDynamicMemoryStreamWriter::Write(const void *pData, unsigned int Size)
{
	char *pTmp = new char[CurrentPosition + Size];
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
