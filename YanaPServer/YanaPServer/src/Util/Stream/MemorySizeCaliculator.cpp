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
bool CMemorySizeCaliculator::Serialize(int *pData)
{
	Size += sizeof(int);
	return true;
}

// unsigned int�̃V���A���C�Y
bool CMemorySizeCaliculator::Serialize(unsigned int *pData)
{
	Size += sizeof(unsigned int);
	return true;
}

// ������̃V���A���C�Y
bool CMemorySizeCaliculator::Serialize(char *pData)
{
	Size += sizeof(size_t);		// ������.
	Size += strlen(pData);		// ������.
	return true;
}

}
}
}