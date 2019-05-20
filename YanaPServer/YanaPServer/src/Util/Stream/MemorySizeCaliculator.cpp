#include "Util/Stream/MemorySizeCaliculator.h"
#include <string.h>

namespace YanaPServer
{
namespace Util
{
namespace Stream
{

// �R���X�g���N�^
CMemorySizeCaliculator::CMemorySizeCaliculator()
	: Size(0)
{
}

// int�̃V���A���C�Y
bool CMemorySizeCaliculator::Serialize(const int *pData)
{
	Size += sizeof(int);
	return true;
}

// unsigned int�̃V���A���C�Y
bool CMemorySizeCaliculator::Serialize(const unsigned int *pData)
{
	Size += sizeof(unsigned int);
	return true;
}

// short�̃V���A���C�Y
bool CMemorySizeCaliculator::Serialize(const short *pData)
{
	Size += sizeof(short);
	return true;
}

// unsigned short�̃V���A���C�Y
bool CMemorySizeCaliculator::Serialize(const unsigned short *pData)
{
	Size += sizeof(unsigned short);
	return true;
}

// float�̃V���A���C�Y
bool CMemorySizeCaliculator::Serialize(const float *pData)
{
	Size += sizeof(float);
	return true;
}

// ������̃V���A���C�Y
bool CMemorySizeCaliculator::Serialize(const char *pData)
{
	Size += sizeof(size_t);		// ������.
	Size += strlen(pData);		// ������.
	return true;
}

}
}
}
