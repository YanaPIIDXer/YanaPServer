#ifndef __HTTPPARAMETER_H__
#define __HTTPPARAMETER_H__

#include <vector>
#include <map>

namespace YanaPServer
{
namespace Servlet
{

// �ʖ���`.
typedef std::vector<std::string> ParamList;

/**
 * @class CHttpParameter
 * @brief HTTP�p�����[�^
 */
class CHttpParameter
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CHttpParameter();

	/**
	 * @brief �f�X�g���N�^
	 */
	~CHttpParameter() {}

	/**
	 * @fn void Add(const std::string &ParamName, const char *pValue)
	 * @brief �ǉ�
	 * @param[in] ParamName �p�����[�^��
	 * @param[in] pValue �l
	 */
	void Add(const std::string &ParamName, const char *pValue);

	/**
	 * @fn const char *Get(const std::string &ParamName, unsigned int Index = 0) const
	 * @brief �擾
	 * @param[in] ParamName �p�����[�^��
	 * @param[in] Index �C���f�b�N�X
	 * @return �l
	 */
	const char *Get(const std::string &ParamName, unsigned int Index = 0) const;

	/**
	 * @fn unsigned int GetCount(const std::string &ParamName) const
	 * @brief �����p�����[�^�̌����擾
	 * @param[in] ParamName �p�����[�^��
	 * @return �����p�����[�^�̌�
	 */
	unsigned int GetCount(const std::string &ParamName) const;

private:

	// �p�����[�^�}�b�v
	std::map<std::string, ParamList> ParamMap;

};

}
}

#endif		// #ifndef __HTTPPARAMETER_H__
