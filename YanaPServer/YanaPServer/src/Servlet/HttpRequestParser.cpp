#include "Servlet/HttpRequestParser.h"

#include <iostream>

namespace YanaPServer
{
namespace Servlet
{

// コンストラクタ
CHttpRequestParser::CHttpRequestParser()
{
}

// パース
bool CHttpRequestParser::Parse(const char *pData, SHttpRequest &OutResult)
{
	// １行目を取り出す。
	std::vector<std::string> Lines;
	Split(pData, "\n", Lines);

	if (Lines.size() == 0) { return false; }

	// １行目を解析。
	std::vector<std::string> Datas;
	Split(Lines[0].c_str(), " ", Datas);

	// 最初にメソッドが来る。
	if (Datas[0] == "POST")
	{
		OutResult.Method = EHttpMethod::POST;
	}
	else if (Datas[0] == "GET")
	{
		OutResult.Method = EHttpMethod::GET;
	}

	// 次にパスが来る。
	OutResult.Path = Datas[1];

	return true;
}


// Split
void CHttpRequestParser::Split(const char *pData, const std::string &Delimiter, std::vector<std::string> &OutResult)
{
	OutResult.clear();

	std::string Str = pData;
	unsigned int First = 0;
	unsigned int Last = Str.find_first_of(Delimiter);
	while (First < Str.size())
	{
		std::string SubStr(Str, First, Last - First);
		OutResult.push_back(SubStr);

		First = Last + 1;
		Last = Str.find_first_of(Delimiter, First);
		if (Last == std::string::npos)
		{
			Last = Str.size();
		}
	}
}

}
}
