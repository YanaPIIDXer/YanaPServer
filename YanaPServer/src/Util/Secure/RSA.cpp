#include "Util/Secure/RSA.h"
#include <random>
#include <vector>

namespace YanaPServer
{
namespace Util
{
namespace Secure
{

// �R���X�g���N�^
CRSA::CRSA()
	: PrivateKey(0)
{
}

// ����.
bool CRSA::Create()
{
	std::vector<ULongLong> Prime;
	bool bFlag = false;

	// �R���̑f����񋓁B
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

	// �Q�̑f���������_���ɑI���B
	ULongLong A = 0, B = 0;
	std::random_device Rnd;
	do
	{
		A = Prime[Rnd() % Prime.size()];
		B = Prime[Rnd() % Prime.size()];
	} while (A == B);

	// ���J���̂P�ƂȂ郋�[�����쐬�B
	OpenKey.Rule = A * B;

	// �����P�̌��J�������߂�B
	while (true)
	{
		OpenKey.Public = Rnd() % ((ULongLong)OpenKey.Rule - 1);
		if (CalcGCD(OpenKey.Public, (A - 1) * (B - 1)) == 1) { break; }
		OpenKey.Public = 0;
	}

	// �閧�������߂�B
	for (int i = 2; (int)OpenKey.Public * i % ((A - 1) * (B - 1)) != 1; i++)
	{
		PrivateKey = i + 1;
	}
	return true;
}

// �Í���.
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

// ������.
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


// �ő���񐔂����߂�B
ULongLong CRSA::CalcGCD(ULongLong M, ULongLong N)
{
	if (M == 0 || N == 0) { return 0; }

	// ���[�O���b�g�ݏ��@
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
