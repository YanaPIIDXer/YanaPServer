#include "Servlet/HttpParameter.h"

namespace YanaPServer
{
namespace Servlet
{

// コンストラクタ
CHttpParameter::CHttpParameter()
{
}

// 追加.
void CHttpParameter::Add(const std::string &ParamName, const char *pValue)
{
	if (ParamMap.find(ParamName) == ParamMap.end())
	{
		// 新規追加。
		ParamList List;
		ParamMap[ParamName] = List;
	}
	ParamMap[ParamName].push_back(pValue);
}

// 取得.
const char *CHttpParameter::Get(const std::string &ParamName, unsigned int Index) const
{
	const auto &It = ParamMap.find(ParamName);
	if (It == ParamMap.end()) { return nullptr; }
	if (It->second.size() <= Index) { return nullptr; }
	return It->second[Index].c_str();
}

// 同名パラメータの個数を取得.
unsigned int CHttpParameter::GetCount(const std::string &ParamName) const
{
	const auto &It = ParamMap.find(ParamName);
	if (It == ParamMap.end()) { return 0; }
	return It->second.size();
}

}
}
