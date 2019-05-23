#include "Servlet/HttpRequestParser.h"

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

	// GET�p�����[�^
	unsigned int ParamParser = OutResult.Path.find_first_of('?');
	if (ParamParser != std::string::npos)
	{
		std::string ParamStr = OutResult.Path.substr(ParamParser + 1);
		OutResult.Path = OutResult.Path.substr(0, ParamParser);
		ParseParam(OutResult.Parameter, ParamStr);
	}

	// ���̎��Ƀv���g�R���o�[�W����
	OutResult.ProtocolVersion = Datas[2];

	// ��s�iPOST�p�����[�^�̊J�n�j�܂œǂݔ�΂�
	for (ParamParser = 0; ParamParser < Lines.size(); ParamParser++)
	{
		if (Lines[ParamParser] == "\r")
		{
			ParamParser++;
			break;
		}
	}

	if (ParamParser < Lines.size())
	{
		// ��U�S�������B
		std::string ParamStr = "";
		for (; ParamParser < Lines.size(); ParamParser++)
		{
			ParamStr += Lines[ParamParser];
		}

		// �p�����[�^�p�[�X
		ParseParam(OutResult.Parameter, ParamStr);
	}

	return true;
}


// �p�����[�^�̃p�[�X
void CHttpRequestParser::ParseParam(CHttpParameter &OutParams, const std::string &ParamStr)
{
	if (ParamStr == "") { return; }

	std::vector<std::string> Params;
	Split(ParamStr.c_str(), "&", Params);

	for (const auto &Param : Params)
	{
		std::vector<std::string> ParamSet;
		Split(Param.c_str(), "=", ParamSet);
		if (ParamSet.size() <= 1)
		{
			// �uParamName=Value�v�̌`�ɂȂ��Ă��Ȃ��ꍇ�͂Ƃ肠�����󕶎���˂�����ł����B
			ParamSet.push_back("");
		}
		OutParams.Add(ParamSet[0].c_str(), ParamSet[1].c_str());
	}
}

// Split
void CHttpRequestParser::Split(const char *pData, const std::string &Delimiter, std::vector<std::string> &OutResult)
{
	OutResult.clear();

	std::string Str = pData;
	if (Str.find_first_of(Delimiter) == std::string::npos)
	{
		// ��؂蕶����������Ȃ������ꍇ�͂��̂܂ܕ�������u�`����ŏI���B
		OutResult.push_back(Str);
		return;
	}

	auto Offset = std::string::size_type(0);
	while (true)
	{
		auto Pos = Str.find(Delimiter, Offset);
		if (Pos == std::string::npos)
		{
			OutResult.push_back(Str.substr(Offset));
			break;
		}

		OutResult.push_back(Str.substr(Offset, Pos - Offset));
		Offset = Pos + Delimiter.length();
	}
}

}
}
