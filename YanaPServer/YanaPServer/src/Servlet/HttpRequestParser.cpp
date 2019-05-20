#include "Servlet/HttpRequestParser.h"

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

	// GETパラメータ
	unsigned int ParamParser = OutResult.Path.find_first_of('?');
	if (ParamParser != std::string::npos)
	{
		std::string ParamStr = OutResult.Path.substr(ParamParser + 1);
		OutResult.Path = OutResult.Path.substr(0, ParamParser);
		ParseParam(OutResult.Parameter, ParamStr);
	}

	// その次にプロトコルバージョン
	OutResult.ProtocolVersion = Datas[2];

	// 空行（POSTパラメータの開始）まで読み飛ばす
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
		// 一旦全部結合。
		std::string ParamStr = "";
		for (; ParamParser < Lines.size(); ParamParser++)
		{
			ParamStr += Lines[ParamParser];
		}

		// パラメータパース
		ParseParam(OutResult.Parameter, ParamStr);
	}

	return true;
}


// パラメータのパース
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
			// 「ParamName=Value」の形になっていない場合はとりあえず空文字を突っ込んでおく。
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
	unsigned int First = 0;
	unsigned int Last = Str.find_first_of(Delimiter);
	if (Last == std::string::npos)
	{
		// 区切り文字が見つからなかった場合はそのまま文字列をブチ込んで終了。
		OutResult.push_back(Str);
		return;
	}

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
