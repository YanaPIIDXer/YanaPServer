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

typedef std::shared_ptr<IHTMLObject> HTMLObjectSharedPtr;

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

/**
 * @class CHTMLForm
 * @brief HTML�t�H�[��
 */
class CHTMLForm : public IHTMLObject
{

public:

	/**
	 * @enum EMethod
	 * @brief HTML���\�b�h
	 */
	enum class EMethod
	{
		POST,
		GET,
	};

	/**
	 * @brief �R���X�g���N�^
	 * @param[in] InMethod HTML���\�b�h
	 * @param[in] pInActionTarget �A�N�V�����^�[�Q�b�g
	 */
	CHTMLForm(EMethod InMethod, const char *pInActionTarget)
		: Method(InMethod)
		, pActionTarget(pInActionTarget)
	{
	}

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CHTMLForm()
	{
	}

	/**
	 * @fn void AddObject(IHTMLObject *pObject)
	 * @brief �I�u�W�F�N�g�ǉ�
	 * @param[in] pObject HTML�I�u�W�F�N�g
	 */
	void AddObject(IHTMLObject *pObject)
	{
		HTMLObjectSharedPtr pPtr(pObject);
		Objects.push_back(pPtr);
	}

	/**
	 * @fn void AddTextBox(const char *pName, const char *pDefaultValue = "", bool bAppendNewLine = true)
	 * @brief �e�L�X�g�{�b�N�X��ǉ�
	 * @param[in] pName �e�L�X�g�{�b�N�X�ɕt���閼�O
	 * @param[in] pDefaultValue �f�t�H���g�l
	 * @param[in] bAppendNewLine ���s���邩�H
	 */
	void AddTextBox(const char *pName, const char *pDefaultValue = "", bool bAppendNewLine = true)
	{
		CHTMLText *pText = MakeTextBox(pName, pDefaultValue, bAppendNewLine);
		AddObject(pText);
	}

	/**
	 * @fn static CHTMLText *MakeTextBox(const char *pName, const char *pDefaultValue = "", bool bAppendNewLine = true)
	 * @brief �e�L�X�g�{�b�N�X�𐶐�
	 * @param[in] pName �e�L�X�g�{�b�N�X�ɕt���閼�O
	 * @param[in] pDefaultValue �f�t�H���g�l
	 * @param[in] bAppendNewLine ���s���邩�H
	 * @return CHTMLText�I�u�W�F�N�g
	 */
	static CHTMLText *MakeTextBox(const char *pName, const char *pDefaultValue = "", bool bAppendNewLine = true);

	/**
	 * @fn void AddCheckBox(const char *pName, bool bDefaultValue = false, bool bAppendNewLine = true)
	 * @brief �`�F�b�N�{�b�N�X��ǉ�
	 * @param[in] pName �`�F�b�N�{�b�N�X�ɕt���閼�O
	 * @param[in] bDefaultValue �f�t�H���g�l
	 * @param[in] bAppendNewLine ���s���邩�H
	 */
	void AddCheckBox(const char *pName, bool bDefaultValue = false, bool bAppendNewLine = true)
	{
		CHTMLText *pText = MakeCheckBox(pName, bDefaultValue, bAppendNewLine);
		AddObject(pText);
	}

	/**
	 * @fn static CHTMLText *MakeCheckBox(const char *pName, bool bDefaultValue = false, bool bAppendNewLine = true)
	 * @brief �`�F�b�N�{�b�N�X�𐶐�
	 * @param[in] pName �`�F�b�N�{�b�N�X�ɕt���閼�O
	 * @param[in] bDefaultValue �f�t�H���g�l
	 * @param[in] bAppendNewLine ���s���邩�H
	 * @return CHTMLText�I�u�W�F�N�g
	 */
	static CHTMLText *MakeCheckBox(const char *pName, bool bDefaltValue = false, bool bAppendNewLine = true);
	
	/**
	 * @fn void AddSubmitButton(const char *pName, const char *pValue, bool bAppendNewLine = true)
	 * @brief ���M�{�^����ǉ�
	 * @param[in] pName ���M�{�^���ɕt���閼�O
	 * @param[in] pValue �f�t�H���g�l
	 * @param[in] bAppendNewLine ���s���邩�H
	 */
	void AddSubmitButton(const char *pName, const char *pValue, bool bAppendNewLine = true)
	{
		CHTMLText *pText = MakeSubmitButton(pName, pValue, bAppendNewLine);
		AddObject(pText);
	}

	/**
	 * @fn static CHTMLText *MakeCheckBox(const char *pName, bool bDefaultValue = false, bool bAppendNewLine = true)
	 * @brief ���M�{�^���𐶐�
	 * @param[in] pName ���M�{�^���ɕt���閼�O
	 * @param[in] bValue �\��������
	 * @param[in] bAppendNewLine ���s���邩�H
	 * @return CHTMLText�I�u�W�F�N�g
	 */
	static CHTMLText *MakeSubmitButton(const char *pName, const char *pValue, bool bAppendNewLine = true);

	/**
	 * @fn virtual void Generate(std::string &OutCode) const override
	 * @brief �\�z
	 * @param[out] OutCode �\�z���ꂽHTML�R�[�h
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
		OutCode += "\">\n";

		for (const auto &pObject : Objects)
		{
			OutCode += "\t";
			pObject->Generate(OutCode);
		}

		OutCode += "</form>\n";
	}

private:

	// ���\�b�h
	EMethod Method;

	// �^�[�Q�b�g
	const char *pActionTarget;

	// �I�u�W�F�N�g�Q
	std::vector<HTMLObjectSharedPtr> Objects;

};

}
}
}

#endif		// #ifndef __HTMLOBJECT_H__
