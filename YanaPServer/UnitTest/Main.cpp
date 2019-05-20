#include <iostream>

// MemoryStream
#include "YanaPServer/Util/Stream/MemorySizeCaliculator.h"
#include "YanaPServer/Util/Stream/MemoryStreamWriter.h"
#include "YanaPServer/Util/Stream/MemoryStreamReader.h"
using namespace YanaPServer::Util::Stream;

// シリアライズ
bool Serialize(IMemoryStream *pStream, int *pTest1, short *pTest2, std::string *pTest3)
{
	if (!pStream->Serialize(pTest1)) { return false; }
	if (!pStream->Serialize(pTest2)) { return false; }
	if (!pStream->Serialize(pTest3)) { return false; }
	return true;
}

// MemoryStreamのテスト
bool TestMemoryStream()
{
	int Test1 = 123;
	short Test2 = 456;
	std::string Test3 = "Hoge";
	
	CMemorySizeCaliculator SizeCaliculator;
	if (!Serialize(&SizeCaliculator, &Test1, &Test2, &Test3))
	{
		std::cout << "SizeCaliculator Serialize Failed." << std::endl;
		return false;
	}

	CMemoryStreamWriter StreamWriter(SizeCaliculator.GetSize());
	if (!Serialize(&StreamWriter, &Test1, &Test2, &Test3))
	{
		std::cout << "StreamWriter Serialize Failed." << std::endl;
		return false;
	}

	int Test4 = 0;
	short Test5 = 0;
	std::string Test6 = "";
	CMemoryStreamReader StreamReader(StreamWriter.GetBuffer(), StreamWriter.GetSize());
	if (!Serialize(&StreamReader, &Test4, &Test5, &Test6))
	{
		std::cout << "StreamReader Serialize Failed." << std::endl;
		return false;
	}

	std::cout << "Test4:" << Test4 << std::endl;
	std::cout << "Test5:" << Test5 << std::endl;
	std::cout << "Test6:" << Test6 << std::endl;

	if (Test4 != Test1 || Test5 != Test2 || Test6 != Test3)
	{
		std::cout << "Serialized Data Not Matched." << std::endl;
		return false;
	}

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
	std::cout << "TestMemoryStream OK." << std::endl;

	getchar();
	return 0;
}
