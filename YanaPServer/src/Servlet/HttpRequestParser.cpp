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

	// ２行目以降の解析.
	for (ParamParser = 0; ParamParser < Lines.size(); ParamParser++)
	{
		// ドメイン
		std::string Header = "Host: ";
		auto Pos = Lines[ParamParser].find(Header);
		if (Pos != std::string::npos)
		{
			OutResult.Domain = Lines[ParamParser];
			OutResult.Domain.replace(Pos, Header.length(), "");
			OutResult.Domain = OutResult.Domain.substr(0, OutResult.Domain.find(":"));
		}

		// Cookie
		Header = "Cookie: ";
		Pos = Lines[ParamParser].find(Header);
		if (Pos != std::string::npos)
		{
			std::string Line = Lines[ParamParser];
			Line.replace(Pos, Header.length(), "");
			std::vector<std::string> CookieLines;
			Split(Line.c_str(), "; ", CookieLines);
			for (const auto &CookieLine : CookieLines)
			{
				std::vector<std::string> CookieData;
				Split(CookieLine.c_str(), "=", CookieData);
				OutResult.CookieInfo[CookieData[0]] = CookieData[1];
			}
		}

		// 空行になったら終了。（それ以降はPOSTパラメータ）
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
	if (Str.find_first_of(Delimiter) == std::string::npos)
	{
		// 区切り文字が見つからなかった場合はそのまま文字列をブチ込んで終了。
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
