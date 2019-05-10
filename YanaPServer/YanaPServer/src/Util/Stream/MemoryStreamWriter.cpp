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

// コンストラクタ
CMemoryStreamWriter::CMemoryStreamWriter(unsigned int InBufferSize)
	: pBuffer(nullptr)
	, BufferSize(InBufferSize)
	, CurrentPosition(0)
	, bIsError(false)
{
	pBuffer = new unsigned char[BufferSize];
}

// デストラクタ
CMemoryStreamWriter::~CMemoryStreamWriter()
{
	delete[] pBuffer;
}

// intのシリアライズ
bool CMemoryStreamWriter::Serialize(int *pData)
{
	int Data = CEndianConverter::Convert(*pData);
	return Write(&Data, sizeof(int));
}

// unsigned intのシリアライズ
bool CMemoryStreamWriter::Serialize(unsigned int *pData)
{
	unsigned int Data = CEndianConverter::Convert(*pData);
	return Write(&Data, sizeof(unsigned int));
}

// 文字列のシリアライズ
bool CMemoryStreamWriter::Serialize(char *pData)
{
	// サイズ
	size_t Size = strlen(pData);
	if (!Serialize(&Size)) { return false; }

	// 実際の文字列.
	return Write(pData, Size);
}


// 書き込み
bool CMemoryStreamWriter::Write(void *pData, unsigned int Size)
{
	if (CurrentPosition + Size > BufferSize)
	{
		// バッファサイズをオーバーしたらエラー
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
