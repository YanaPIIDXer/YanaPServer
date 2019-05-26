#include "Util/HTML/HTMLBuilder.h"

namespace YanaPServer
{
namespace Util
{
namespace HTML
{

// コンストラクタ
CHTMLBuilder::CHTMLBuilder(const std::string &InTitle)
	: Title(InTitle)
{
}

// デストラクタ
CHTMLBuilder::~CHTMLBuilder()
{
	for (auto *pObject : Objects)
	{
		delete pObject;
	}
	Objects.clear();
}

// 構築.
std::string CHTMLBuilder::Generate() const
{
	std::string HTML;

	HTML += "<html>\n";

	HTML += "<head>\n";
	HTML += "<title>" + Title + "</title>\n";
	HTML += "</head>\n";

	HTML += "<body>\n";
	for (const auto *pObject : Objects)
	{
		pObject->Generate(HTML);
	}
	HTML += "</body>\n";

	HTML += "</html>\n";

	return HTML;
}

// テキスト追加.
void CHTMLBuilder::AddText(const std::string &Text, bool bAppendNewLine)
{
	CHTMLText *pText = new CHTMLText(Text, bAppendNewLine);
	Objects.push_back(pText);
}

// リンク追加.
void CHTMLBuilder::AddLink(const char *pURL, const char *pText, bool bAppendNewLine)
{
	CHTMLLink *pLink = new CHTMLLink(pURL, pText, bAppendNewLine);
	Objects.push_back(pLink);
}

}
}
}
