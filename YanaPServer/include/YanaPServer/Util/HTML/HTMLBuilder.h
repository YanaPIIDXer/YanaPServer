#ifndef __HTMLBUILDER_H__
#define __HTMLBUILDER_H__

#include <string>
#include "HTMLObject.h"
#include <vector>

namespace YanaPServer
{
namespace Util
{
namespace HTML
{

/**
 * @class CHTMLBuilder
 * @brief ＨＴＭＬ構築クラス
 */
class CHTMLBuilder
{

public:

	/**
	 * @brief コンストラクタ
	 * @param[in] InTitle ページのタイトル
	 */
	CHTMLBuilder(const std::string &InTitle);

	/**
	 * @デストラクタ
	 */
	~CHTMLBuilder();

	/**
	 * @fn std::string Generate() const
	 * @brief 構築
	 * @return 構築されたHTML
	 */
	std::string Generate() const;

	/**
	 * @fn void AddText(const std::string &Text, bool bAppendNewLine)
	 * @brief テキスト追加
	 * @param[in] Textテキスト
	 * @param[in] bAppendNewLine 改行するか？
	 */
	void AddText(const std::string &Text, bool bAppendNewLine = true);

	/**
	 * @fn void AddLink(const char *pURL, const char *pText, bool bAppendNewLine)
	 * @brief リンク追加
	 * @param[in] pURL URL
	 * @param[in] pText テキスト
	 * @param[in] bAppendNewLine 改行するか？
	 */
	void AddLink(const char *pURL, const char *pText, bool bAppendNewLine = true);

private:

	// ページのタイトル
	std::string Title;

	// オブジェクト群.
	std::vector<IHTMLObject *> Objects;

};

}
}
}

#endif		// #ifndef __HTMLBUILDER_H__
