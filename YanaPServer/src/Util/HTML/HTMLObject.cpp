#include "Util/HTML/HTMLObject.h"
#include <sstream>
#include <algorithm>

namespace YanaPServer
{
namespace Util
{
namespace HTML
{

// =============== CHTMLForm =====================

// テキストボックスを生成.
CHTMLText *CHTMLForm::MakeTextBox(const char *pName, const char *pDefaultValue, bool bAppendNewLine)
{
	std::string Code = "<input type=\"text\" name=\"";
	Code += pName;
	Code += "\" value=\"";
	Code += pDefaultValue;
	Code += "\">";

	CHTMLText *pText = new CHTMLText(Code, bAppendNewLine);
	return pText;
}

// チェックボックスを生成.
CHTMLText *CHTMLForm::MakeCheckBox(const char *pName, bool bDefaltValue, bool bAppendNewLine)
{
	std::string Code = "<input type=\"checkbox\" name=\"";
	Code += pName;
	Code += "\"";
	if (bDefaltValue)
	{
		Code += " checked=\"checked\"";
	}
	Code += ">";

	CHTMLText *pText = new CHTMLText(Code, bAppendNewLine);
	return pText;
}

// 送信ボタンを生成.
CHTMLText *CHTMLForm::MakeSubmitButton(const char *pName, const char *pValue, bool bAppendNewLine)
{
	std::string Code = "<input type=\"submit\" name=\"";
	Code += pName;
	Code += "\" value=\"";
	Code += pValue;
	Code += "\">";

	CHTMLText *pText = new CHTMLText(Code, bAppendNewLine);
	return pText;
}

// 構築.
void CHTMLForm::Generate(std::string &OutCode) const
{
	OutCode += "<form method=\"";
	switch (Method)
	{
	case EMethod::POST:

		OutCode += "POST\"";
		break;

	case EMethod::GET:

		OutCode += "GET\"";
		break;
	}

	OutCode += " action=\"";
	OutCode += pActionTarget;
	OutCode += "\">\n";

	for (const auto &pObject : Objects)
	{
		OutCode += "\t";
		pObject->Generate(OutCode);
	}

	OutCode += "</form>\n";
}


// ================== CHTMLTable ===================

// 構築.
void CHTMLTable::Generate(std::string &OutCode) const
{
	std::stringstream Stream;
	Stream << "<table border=";
	Stream << Border;
	Stream << ">\n";
	OutCode += Stream.str();

	OutCode += "\t<tr>\n";
	for (const auto *pColumn : Columns)
	{
		OutCode += "\t\t<th>";
		OutCode += pColumn->GetName();
		OutCode += "</th>\n";
	}
	OutCode += "\t</tr>\n";

	unsigned int Count = 0;
	for (const auto *pColumn : Columns)
	{
		Count = std::max<unsigned int>(Count, pColumn->GetObjectCount());
	}

	for (unsigned int i = 0; i < Count; i++)
	{
		OutCode += "\t<tr>\n";
		for (const auto *pColumn : Columns)
		{
			OutCode += "\t\t<td>";
			OutCode += pColumn->GetCode(i);
			OutCode += "</td>\n";
		}
		OutCode += "\t</tr>\n";
	}

	OutCode += "</table>\n";
}

}
}
}
