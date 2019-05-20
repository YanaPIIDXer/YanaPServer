#include "Servlet/HttpRequestParser.h"

#include <iostream>

namespace YanaPServer
{
namespace Servlet
{

// �R���X�g���N�^
CHttpRequestParser::CHttpRequestParser()
{
}

// �p�[�X
bool CHttpRequestParser::Parse(const char *pData, SHttpRequest &OutResult)
{
	// �P�s�ڂ����o���B
	std::vector<std::string> Lines;
	Split(pData, "\n", Lines);

	if (Lines.size() == 0) { return false; }

	// �P�s�ڂ���́B
	std::vector<std::string> Datas;
	Split(Lines[0].c_str(), " ", Datas);

	// �ŏ��Ƀ��\�b�h������B
	if (Datas[0] == "POST")
	{
		OutResult.Method = EHttpMethod::POST;
	}
	else if (Datas[0] == "GET")
	{
		OutResult.Method = EHttpMethod::GET;
	}

	// ���Ƀp�X������B
	OutResult.Path = Datas[1];

	// ���̎��Ƀv���g�R���o�[�W����
	OutResult.ProtocolVersion = Datas[2];

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
