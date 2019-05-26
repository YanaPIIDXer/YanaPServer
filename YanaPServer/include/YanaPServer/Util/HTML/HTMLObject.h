#ifndef __HTMLOBJECT_H__
#define __HTMLOBJECT_H__

#include <string>
#include <vector>
#include <memory>

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

typedef std::shared_ptr<IHTMLObject> HTMLObjectSharedPtr;

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

/**
 * @class CHTMLForm
 * @brief HTMLフォーム
 */
class CHTMLForm : public IHTMLObject
{

public:

	/**
	 * @enum EMethod
	 * @brief HTMLメソッド
	 */
	enum class EMethod
	{
		POST,
		GET,
	};

	/**
	 * @brief コンストラクタ
	 * @param[in] InMethod HTMLメソッド
	 * @param[in] pInActionTarget アクションターゲット
	 */
	CHTMLForm(EMethod InMethod, const char *pInActionTarget)
		: Method(InMethod)
		, pActionTarget(pInActionTarget)
	{
	}

	/**
	 * @brief デストラクタ
	 */
	virtual ~CHTMLForm()
	{
	}

	/**
	 * @fn void AddObject(IHTMLObject *pObject)
	 * @brief オブジェクト追加
	 * @param[in] pObject HTMLオブジェクト
	 */
	void AddObject(IHTMLObject *pObject)
	{
		HTMLObjectSharedPtr pPtr(pObject);
		Objects.push_back(pPtr);
	}

	/**
	 * @fn void AddTextBox(const char *pName, const char *pDefaultValue = "", bool bAppendNewLine = true)
	 * @brief テキストボックスを追加
	 * @param[in] pName テキストボックスに付ける名前
	 * @param[in] pDefaultValue デフォルト値
	 * @param[in] bAppendNewLine 改行するか？
	 */
	void AddTextBox(const char *pName, const char *pDefaultValue = "", bool bAppendNewLine = true)
	{
		CHTMLText *pText = MakeTextBox(pName, pDefaultValue, bAppendNewLine);
		AddObject(pText);
	}

	/**
	 * @fn static CHTMLText *MakeTextBox(const char *pName, const char *pDefaultValue = "", bool bAppendNewLine = true)
	 * @brief テキストボックスを生成
	 * @param[in] pName テキストボックスに付ける名前
	 * @param[in] pDefaultValue デフォルト値
	 * @param[in] bAppendNewLine 改行するか？
	 * @return CHTMLTextオブジェクト
	 */
	static CHTMLText *MakeTextBox(const char *pName, const char *pDefaultValue = "", bool bAppendNewLine = true);

	/**
	 * @fn void AddCheckBox(const char *pName, bool bDefaultValue = false, bool bAppendNewLine = true)
	 * @brief チェックボックスを追加
	 * @param[in] pName チェックボックスに付ける名前
	 * @param[in] bDefaultValue デフォルト値
	 * @param[in] bAppendNewLine 改行するか？
	 */
	void AddCheckBox(const char *pName, bool bDefaultValue = false, bool bAppendNewLine = true)
	{
		CHTMLText *pText = MakeCheckBox(pName, bDefaultValue, bAppendNewLine);
		AddObject(pText);
	}

	/**
	 * @fn static CHTMLText *MakeCheckBox(const char *pName, bool bDefaultValue = false, bool bAppendNewLine = true)
	 * @brief チェックボックスを生成
	 * @param[in] pName チェックボックスに付ける名前
	 * @param[in] bDefaultValue デフォルト値
	 * @param[in] bAppendNewLine 改行するか？
	 * @return CHTMLTextオブジェクト
	 */
	static CHTMLText *MakeCheckBox(const char *pName, bool bDefaltValue = false, bool bAppendNewLine = true);
	
	/**
	 * @fn void AddSubmitButton(const char *pName, const char *pValue, bool bAppendNewLine = true)
	 * @brief 送信ボタンを追加
	 * @param[in] pName 送信ボタンに付ける名前
	 * @param[in] pValue デフォルト値
	 * @param[in] bAppendNewLine 改行するか？
	 */
	void AddSubmitButton(const char *pName, const char *pValue, bool bAppendNewLine = true)
	{
		CHTMLText *pText = MakeSubmitButton(pName, pValue, bAppendNewLine);
		AddObject(pText);
	}

	/**
	 * @fn static CHTMLText *MakeCheckBox(const char *pName, bool bDefaultValue = false, bool bAppendNewLine = true)
	 * @brief 送信ボタンを生成
	 * @param[in] pName 送信ボタンに付ける名前
	 * @param[in] bValue 表示文字列
	 * @param[in] bAppendNewLine 改行するか？
	 * @return CHTMLTextオブジェクト
	 */
	static CHTMLText *MakeSubmitButton(const char *pName, const char *pValue, bool bAppendNewLine = true);

	/**
	 * @fn virtual void Generate(std::string &OutCode) const override
	 * @brief 構築
	 * @param[out] OutCode 構築されたHTMLコード
	 */
	virtual void Generate(std::string &OutCode) const override
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
		OutCode += "\">";

		for (const auto &pObject : Objects)
		{
			pObject->Generate(OutCode);
		}

		OutCode += "</form>";
	}

private:

	// メソッド
	EMethod Method;

	// ターゲット
	const char *pActionTarget;

	// オブジェクト群
	std::vector<HTMLObjectSharedPtr> Objects;

};

}
}
}

#endif		// #ifndef __HTMLOBJECT_H__
