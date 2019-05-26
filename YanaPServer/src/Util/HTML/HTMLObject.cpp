#include "Util/HTML/HTMLObject.h"

namespace YanaPServer
{
namespace Util
{
namespace HTML
{

// テキストボックスを生成.
CHTMLText *CHTMLForm::MakeTextBox(const char *pName, const char *pDefaultValue, bool bAppendNewLine)
{
	std::string Code = "<input type=\text\" name=\"";
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


}
}
}
