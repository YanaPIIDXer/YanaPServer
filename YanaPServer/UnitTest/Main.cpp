#include <iostream>

// MemoryStream
#include "YanaPServer/Util/Stream/MemorySizeCaliculator.h"
#include "YanaPServer/Util/Stream/MemoryStreamWriter.h"
using namespace YanaPServer::Util::Stream;

// MemoryStream‚ÌƒeƒXƒg
bool TestMemoryStream()
{
	CMemorySizeCaliculator SizeCaliculator;

	CMemoryStreamWriter StreamWriter(SizeCaliculator.GetSize());

	return true;
}

int main()
{
	std::cout << "YanaPServer UnitTest" << std::endl;

	if (!TestMemoryStream())
	{
		std::cout << "TestMemoryStream Failed." << std::endl;
		getchar();
		return 1;
	}

	getchar();
	return 0;
}
