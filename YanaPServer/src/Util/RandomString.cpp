#include "Util/RandomString.h"
#include <random>

namespace YanaPServer
{
namespace Util
{

const char *CRandomString::pCharSet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

// コンストラクタ
CRandomString::CRandomString()
	: pStr(new char[1])
{
	pStr[0] = '\0';
}

// デストラクタ
CRandomString::~CRandomString()
{
	delete[] pStr;
}

// 生成.
void CRandomString::Generate(unsigned int Length)
{
	delete[] pStr;

	pStr = new char[Length + 1];
	
	std::random_device Rnd;
	unsigned int CharSetLength = strlen(pCharSet);
	for (unsigned int i = 0; i < Length; i++)
	{
		int Index = Rnd() % CharSetLength;
		pStr[i] = pCharSet[Index];
	}
	pStr[Length] = '\0';
}

}
}
