#include "Util/Stream/MemorySizeCaliculator.h"
#include <string.h>

namespace YanaPServer
{
namespace Util
{
namespace Stream
{

// コンストラクタ
CMemorySizeCaliculator::CMemorySizeCaliculator()
	: Size(0)
{
}

// intのシリアライズ
bool CMemorySizeCaliculator::Serialize(int *pData)
{
	Size += sizeof(int);
	return true;
}

// unsigned intのシリアライズ
bool CMemorySizeCaliculator::Serialize(unsigned int *pData)
{
	Size += sizeof(unsigned int);
	return true;
}

// 文字列のシリアライズ
bool CMemorySizeCaliculator::Serialize(char *pData)
{
	Size += sizeof(size_t);		// 文字列長.
	Size += strlen(pData);		// 文字数.
	return true;
}

}
}
}
