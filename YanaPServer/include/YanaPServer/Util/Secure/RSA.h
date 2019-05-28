#ifndef __RSA_H__
#define __RSA_H__

namespace YanaPServer
{
namespace Util
{
namespace Secure
{

typedef unsigned long long ULongLong;

/**
 * @struct SRSAKey
 * @brief RSA�Í����L�[
 */
struct SRSAKey
{

	//! ���J�L�[
	ULongLong Public;

	//! ���[��
	ULongLong Rule;


	/**
	 * @brief �R���X�g���N�^
	 */
	SRSAKey()
		: Public(0)
		, Rule(0)
	{
	}

};

/**
 * @class RSA
 * @brief RSA�Í���
 */
class CRSA
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CRSA();

	/**
	 * @brief �f�X�g���N�^
	 */
	~CRSA() {}

	/**
	 * @fn bool Create()
	 * @brief ����
	 * @return ����������true��Ԃ�
	 */
	bool Create();

	/**
	 * @fn ULongLong Encryption(ULongLong Value) const
	 * @brief �Í���
	 * @param[in] Value �l
	 * @return �Í������ꂽ�l
	 */
	ULongLong Encryption(ULongLong Value) const;

	/**
	 * @fn ULongLong Decryption(ULongLong Value) const
	 * @brief ������
	 * @param[in] Value �l
	 * @return ���������ꂽ�l
	 */
	ULongLong Decryption(ULongLong Value) const;

private:

	// ���J��.
	SRSAKey OpenKey;

	// �閧��
	ULongLong PrivateKey;


	// �ő���񐔂����߂�B
	static ULongLong CalcGCD(ULongLong M, ULongLong N);

};

}
}
}

#endif		// #ifndef __RSA_H__
