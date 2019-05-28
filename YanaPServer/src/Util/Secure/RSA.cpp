#include "Util/Secure/RSA.h"
#include <random>
#include <vector>

namespace YanaPServer
{
namespace Util
{
namespace Secure
{

// コンストラクタ
CRSA::CRSA()
	: PrivateKey(0)
{
}

// 生成.
bool CRSA::Create()
{
	std::vector<ULongLong> Prime;
	bool bFlag = false;

	// ３桁の素数を列挙。
	for (ULongLong i = 10; i < 100; i++)
	{
		for (ULongLong j = 2; j < i / 2; j++)
		{
			if (i % j == 0)
			{
				bFlag = true;
			}
		}

		if (!bFlag)
		{
			Prime.push_back(i);
		}
		bFlag = false;
	}

	// ２つの素数をランダムに選択。
	ULongLong A = 0, B = 0;
	std::random_device Rnd;
	do
	{
		A = Prime[Rnd() % Prime.size()];
		B = Prime[Rnd() % Prime.size()];
	} while (A == B);

	// 公開鍵の１つとなるルールを作成。
	OpenKey.Rule = A * B;

	// もう１つの公開鍵を求める。
	while (true)
	{
		OpenKey.Public = Rnd() % ((ULongLong)OpenKey.Rule - 1);
		if (CalcGCD(OpenKey.Public, (A - 1) * (B - 1)) == 1) { break; }
		OpenKey.Public = 0;
	}

	// 秘密鍵を求める。
	for (int i = 2; (int)OpenKey.Public * i % ((A - 1) * (B - 1)) != 1; i++)
	{
		PrivateKey = i + 1;
	}
	return true;
}

// 暗号化.
ULongLong CRSA::Encryption(ULongLong Value) const
{
	ULongLong Result = Value;
	for (ULongLong i = 1; i < OpenKey.Public; i++)
	{
		Result *= Value;
		while (Result >= OpenKey.Rule)
		{
			Result -= OpenKey.Rule;
		}
	}
	return Result;
}

// 複合化.
ULongLong CRSA::Decryption(ULongLong Value) const
{
	ULongLong Result = Value;
	for (ULongLong i = 1; i < PrivateKey; i++)
	{
		Result *= Value;
		while (Result >= OpenKey.Rule)
		{
			Result -= OpenKey.Rule;
		}
	}
	return Result;
}


// 最大公約数を求める。
ULongLong CRSA::CalcGCD(ULongLong M, ULongLong N)
{
	if (M == 0 || N == 0) { return 0; }

	// ユーグリット互除法
	while (M != N)
	{
		if (M >= N)
		{
			M = M - N;
		}
		else
		{
			N = N - M;
		}
	}

	return M;
}

}
}
}
