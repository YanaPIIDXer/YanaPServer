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

// �e�L�X�g�{�b�N�X�𐶐�.
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

// �`�F�b�N�{�b�N�X�𐶐�.
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

// ���M�{�^���𐶐�.
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

// �\�z.
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

	std::string FormCode = "\t";
	for (const auto &pObject : Objects)
	{
		pObject->Generate(FormCode);
	}
	// ���`.
	auto Pos = FormCode.find("\n");
	while (Pos != std::string::npos)
	{
		FormCode.replace(Pos, 1, "\n\t");
		Pos = FormCode.find("\n", Pos + 2);
	}
	Pos = FormCode.find_last_of("\n\t");
	if (Pos != std::string::npos)
	{
		FormCode.replace(Pos, 2, "");
	}

	OutCode += FormCode;

	OutCode += "</form>\n";
}


// ================== CHTMLTable ===================

// �\�z.
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
