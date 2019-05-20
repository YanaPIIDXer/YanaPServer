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
	pBuffer = new char[BufferSize];
}

// デストラクタ
CMemoryStreamWriter::~CMemoryStreamWriter()
{
	delete[] pBuffer;
}

// intのシリアライズ
bool CMemoryStreamWriter::Serialize(const int *pData)
{
	int Data = CEndianConverter::Convert(*pData);
	return Write(&Data, sizeof(int));
}

// unsigned intのシリアライズ
bool CMemoryStreamWriter::Serialize(const unsigned int *pData)
{
	unsigned int Data = CEndianConverter::Convert(*pData);
	return Write(&Data, sizeof(unsigned int));
}

// 文字列のシリアライズ
bool CMemoryStreamWriter::Serialize(const char *pData)
{
	// 文字列長.
	unsigned int Length = strlen(pData);
	if (!Serialize(&Length)) { return false; }

	// 文字列.
	return Write(pData, Length);
}


// 書き込み
bool CMemoryStreamWriter::Write(const void *pData, unsigned int Size)
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
