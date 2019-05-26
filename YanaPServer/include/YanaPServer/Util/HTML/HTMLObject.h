#ifndef __HTMLOBJECT_H__
#define __HTMLOBJECT_H__

#include <string>

namespace YanaPServer
{
namespace Util
{
namespace HTML
{

/**
 * @class IHTMLObject
 * @brief HTMLの要素インタフェース
 */
class IHTMLObject
{

public:

	/**
	 * @brief デストラクタ
	 */
	virtual ~IHTMLObject() {}

	/**
	 * @fn virtual void Generate(std::string &OutCode) const = 0
	 * @brief 構築
	 * @param[out] OutCode 構築されたHTMLコード
	 */
	virtual void Generate(std::string &OutCode) const = 0;

};

/**
 * @class CHTMLText
 * @brief 単純なHTMLテキスト
 */
class CHTMLText : public IHTMLObject
{

public:

	/**
	 * @brief コンストラクタ
	 * @param[in] InText テキストデータ
	 * @param[in] bAppendNewLine 改行するか？
	 */
	CHTMLText(const std::string &InText, bool bAppendNewLine = true)
		: Text(InText)
	{
		if (bAppendNewLine)
		{
			Text += "<br />";
		}
	}

	/**
	 * @brief デストラクタ
	 */
	virtual ~CHTMLText() {}

	/**
	 * @fn virtual void Generate(std::string &OutCode) const override
	 * @brief 構築
	 * @param[out] OutCode 構築されたHTMLコード
	 */
	virtual void Generate(std::string &OutCode) const override
	{
		OutCode += Text;
		OutCode += "\n";
	}

private:

	// テキストデータ
	std::string Text;

};

/**
 * @class CHTMLLink
 * @brief 他ページへのリンク
 */
class CHTMLLink : public IHTMLObject
{

public:

	/**
	 * @brief コンストラクタ
	 * @param[in] pInURL URL
	 * @param[in] pInText 表示するテキスト
	 * @param[in] bInAppendNewLine 改行するか？
	 */
	CHTMLLink(const char *pInURL, const char *pInText, bool bInAppendNewLine = true)
		: pURL(pInURL)
		, pText(pInText)
		, bAppendNewLine(bInAppendNewLine)
	{
	}

	/**
	 * @brief デストラクタ
	 */
	virtual ~CHTMLLink() {}

	/**
	 * @fn virtual void Generate(std::string &OutCode) const override
	 * @brief 構築
	 * @param[out] OutCode 構築されたHTMLコード
	 */
	virtual void Generate(std::string &OutCode) const override
	{
		OutCode += "<a href=\"";
		OutCode += pURL;
		OutCode += "\">";
		OutCode += pText;
		OutCode += "</a>";
		if (bAppendNewLine)
		{
			OutCode += "<br />";
		}
		OutCode += "\n";
	}

private:

	// URL
	const char *pURL;

	// テキスト
	const char *pText;

	// 改行するか？
	bool bAppendNewLine;

};

}
}
}

#endif		// #ifndef __HTMLOBJECT_H__
