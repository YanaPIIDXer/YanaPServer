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
 * @brief HTML�̗v�f�C���^�t�F�[�X
 */
class IHTMLObject
{

public:

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~IHTMLObject() {}

	/**
	 * @fn virtual void Generate(std::string &OutCode) const = 0
	 * @brief �\�z
	 * @param[out] OutCode �\�z���ꂽHTML�R�[�h
	 */
	virtual void Generate(std::string &OutCode) const = 0;

};

/**
 * @class CHTMLText
 * @brief �P����HTML�e�L�X�g
 */
class CHTMLText : public IHTMLObject
{

public:

	/**
	 * @brief �R���X�g���N�^
	 * @param[in] InText �e�L�X�g�f�[�^
	 * @param[in] bAppendNewLine ���s���邩�H
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
	 * @brief �f�X�g���N�^
	 */
	virtual ~CHTMLText() {}

	/**
	 * @fn virtual void Generate(std::string &OutCode) const override
	 * @brief �\�z
	 * @param[out] OutCode �\�z���ꂽHTML�R�[�h
	 */
	virtual void Generate(std::string &OutCode) const override
	{
		OutCode += Text;
		OutCode += "\n";
	}

private:

	// �e�L�X�g�f�[�^
	std::string Text;

};

/**
 * @class CHTMLLink
 * @brief ���y�[�W�ւ̃����N
 */
class CHTMLLink : public IHTMLObject
{

public:

	/**
	 * @brief �R���X�g���N�^
	 * @param[in] pInURL URL
	 * @param[in] pInText �\������e�L�X�g
	 * @param[in] bInAppendNewLine ���s���邩�H
	 */
	CHTMLLink(const char *pInURL, const char *pInText, bool bInAppendNewLine = true)
		: pURL(pInURL)
		, pText(pInText)
		, bAppendNewLine(bInAppendNewLine)
	{
	}

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CHTMLLink() {}

	/**
	 * @fn virtual void Generate(std::string &OutCode) const override
	 * @brief �\�z
	 * @param[out] OutCode �\�z���ꂽHTML�R�[�h
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

	// �e�L�X�g
	const char *pText;

	// ���s���邩�H
	bool bAppendNewLine;

};

}
}
}

#endif		// #ifndef __HTMLOBJECT_H__
