#include "Servlet/HttpParameter.h"

namespace YanaPServer
{
namespace Servlet
{

// �R���X�g���N�^
CHttpParameter::CHttpParameter()
{
}

// �ǉ�.
void CHttpParameter::Add(const std::string &ParamName, const char *pValue)
{
	if (ParamMap.find(ParamName) == ParamMap.end())
	{
		// �V�K�ǉ��B
		ParamList List;
		ParamMap[ParamName] = List;
	}
	ParamMap[ParamName].push_back(pValue);
}

// �擾.
const char *CHttpParameter::Get(const std::string &ParamName, unsigned int Index) const
{
	const auto &It = ParamMap.find(ParamName);
	if (It == ParamMap.end()) { return nullptr; }
	if (It->second.size() <= Index) { return nullptr; }
	return It->second[Index].c_str();
}

// �����p�����[�^�̌����擾.
unsigned int CHttpParameter::GetCount(const std::string &ParamName) const
{
	const auto &It = ParamMap.find(ParamName);
	if (It == ParamMap.end()) { return 0; }
	return It->second.size();
}

}
}
