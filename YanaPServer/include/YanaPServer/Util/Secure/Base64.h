#ifndef __BASE64_H__
#define __BASE64_H__

#include <string>
#include <vector>

namespace YanaPServer
{
namespace Util
{
namespace Secure
{

/**
 * @class CBase64
 * @brief Base64�������N���X
 * @detail �X�^�e�B�b�N�N���X
 */
class CBase64
{

public:

	/**
	 * @fn static bool Decode(const std::string &Src, std::vector<char> &OutResult)
	 * @brief �f�R�[�h
	 * @param[in] Src Base64�ŕϊ�����Ă��镶����
	 * @param[out] OutResult �f�R�[�h����
	 * @return ����������true��Ԃ��B
	 */
	static bool Decode(const std::string &Src, std::vector<char> &OutResult);

private:

	// �e�[�u��
	static const std::string Table;

private:

	// ====== ���� =====
	CBase64();
	CBase64(const CBase64 &Arg);
	CBase64 operator =(const CBase64 &Arg);

};

}
}
}

#endif		// #ifndef __BASE64_H__
