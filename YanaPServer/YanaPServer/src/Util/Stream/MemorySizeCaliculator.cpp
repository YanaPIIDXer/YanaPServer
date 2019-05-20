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
bool CMemorySizeCaliculator::Serialize(const int *pData)
{
	Size += sizeof(int);
	return true;
}

// unsigned intのシリアライズ
bool CMemorySizeCaliculator::Serialize(const unsigned int *pData)
{
	Size += sizeof(unsigned int);
	return true;
}

// shortのシリアライズ
bool CMemorySizeCaliculator::Serialize(const short *pData)
{
	Size += sizeof(short);
	return true;
}

// unsigned shortのシリアライズ
bool CMemorySizeCaliculator::Serialize(const unsigned short *pData)
{
	Size += sizeof(unsigned short);
	return true;
}

// floatのシリアライズ
bool CMemorySizeCaliculator::Serialize(const float *pData)
{
	Size += sizeof(float);
	return true;
}

// 文字列のシリアライズ
bool CMemorySizeCaliculator::Serialize(const char *pData)
{
	Size += sizeof(size_t);		// 文字列長.
	Size += strlen(pData);		// 文字数.
	return true;
}

}
}
}
