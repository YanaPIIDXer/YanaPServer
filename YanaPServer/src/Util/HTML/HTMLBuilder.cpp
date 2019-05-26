#include "Util/HTML/HTMLBuilder.h"

namespace YanaPServer
{
namespace Util
{
namespace HTML
{

// �R���X�g���N�^
CHTMLBuilder::CHTMLBuilder(const std::string &InTitle)
	: Title(InTitle)
{
}

// �f�X�g���N�^
CHTMLBuilder::~CHTMLBuilder()
{
}

// �\�z.
std::string CHTMLBuilder::Generate() const
{
	std::string HTML;

	HTML += "<html>\n";

	HTML += "<head>\n";
	HTML += "<title>" + Title + "</title>\n";
	HTML += "</head>\n";

	HTML += "<body>\n";
	for (const auto &pObject : Objects)
	{
		pObject->Generate(HTML);
	}
	HTML += "</body>\n";

	HTML += "</html>\n";

	return HTML;
}

// �e�L�X�g�ǉ�.
void CHTMLBuilder::AddText(const std::string &Text, bool bAppendNewLine)
{
	CHTMLText *pText = new CHTMLText(Text, bAppendNewLine);
	AddObject(pText);
}

// �����N�ǉ�.
void CHTMLBuilder::AddLink(const char *pURL, const char *pText, bool bAppendNewLine)
{
	CHTMLLink *pLink = new CHTMLLink(pURL, pText, bAppendNewLine);
	AddObject(pLink);
}

// �e�[�u���ǉ�.
CHTMLTable *CHTMLBuilder::AddTable(int Border)
{
	CHTMLTable *pTable = new CHTMLTable(Border);
	AddObject(pTable);

	return pTable;
}


// �t�H�[���ǉ�.
CHTMLForm *CHTMLBuilder::AddForm(CHTMLForm::EMethod Method, const char *pActionTarget)
{
	CHTMLForm *pForm = new CHTMLForm(Method, pActionTarget);
	AddObject(pForm);
	return pForm;
}

}
}
}
