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
			OutCode += "<br />\n";
		}
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
	 * @fn void AddText(const char *pText, bool bAppendNewLine = false)
	 * @brief �P���ȃe�L�X�g��ǉ�
	 * @param[in] pText �e�L�X�g
	 * @param[in] bAppendNewLine ���s���邩�H
	 */
	void AddText(const char *pText, bool bAppendNewLine = false)
	{
		CHTMLText *pObject = new CHTMLText(pText, bAppendNewLine);
		AddObject(pObject);
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
	virtual void Generate(std::string &OutCode) const override;

private:

	// ���\�b�h
	EMethod Method;

	// �^�[�Q�b�g
	const char *pActionTarget;

	// �I�u�W�F�N�g�Q
	std::vector<HTMLObjectSharedPtr> Objects;

};

/**
 * @class CHTMLTable
 * @brief HTML�e�[�u��
 */
class CHTMLTable : public IHTMLObject
{

public:

	/**
	 * @class CColumn
	 * @brief �J����
	 */
	class CColumn
	{
		
	public:

		/**
		 * @brief �R���X�g���N�^
		 * @param[in] pInName �J������
		 */
		CColumn(const char *pInName)
			: pName(pInName)
		{
		}

		/**
		 * @brief �f�X�g���N�^
		 */
		~CColumn()
		{
		}

		/**
		 * @fn const char *GetName() const
		 * @brief �J���������擾
		 * @return �J������
		 */
		const char *GetName() const { return pName; }

		/**
		 * @fn void AddItem(const char *pText)
		 * @brief �v�f�ǉ�
		 * @param[in] pText ������
		 */
		void AddItem(const char *pText)
		{
			CHTMLText *pObject = new CHTMLText(pText, false);
			AddItem(pObject);
		}

		/**
		 * @fn void AddItem(IHTMLObject *pObject)
		 * @brief �v�f�ǉ�
		 * @param[in] pObject �I�u�W�F�N�g
		 */
		void AddItem(IHTMLObject *pObject)
		{
			HTMLObjectSharedPtr pPtr(pObject);
			Objects.push_back(pPtr);
		}

		/**
		 * @fn unsigned int GetObjectCount() const
		 * @brief �I�u�W�F�N�g�̌����擾
		 * @return �I�u�W�F�N�g�̌�
		 */
		unsigned int GetObjectCount() const { return Objects.size(); }

		/**
		 * @fn std::string GetCode(unsigned int Index) const
		 * @brief HTML�R�[�h�擾
		 * @param[in] Index �C���f�b�N�X
		 * @return HTML�R�[�h
		 */
		std::string GetCode(unsigned int Index) const
		{
			std::string Code = "";
			if (Index < Objects.size())
			{
				Objects[Index]->Generate(Code);
			}
			return Code;
		}

	private:

		// �J������.
		const char *pName;

		// �I�u�W�F�N�g�Q
		std::vector<HTMLObjectSharedPtr> Objects;

	};

public:

	/**
	 * @brief �R���X�g���N�^
	 * @param[in] InBorder �{�[�_�[���C��
	 */
	CHTMLTable(int InBorder = 1)
		: Border(InBorder)
	{
	}

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CHTMLTable()
	{
		for (auto *pColumn : Columns)
		{
			delete pColumn;
		}
		Columns.clear();
	}

	/**
	 * @fn CColumn *AddColumn(const char *pColumnName)
	 * @brief �J�����ǉ�
	 * @param[in] pColumnName �J������
	 * @return �J�����I�u�W�F�N�g
	 */
	CColumn *AddColumn(const char *pColumnName)
	{
		CColumn *pColumn = new CColumn(pColumnName);
		Columns.push_back(pColumn);
		return pColumn;
	}

	/**
	 * @fn virtual void Generate(std::string &OutCode) const override
	 * @brief �\�z
	 * @param[out] OutCode �\�z���ꂽHTML�R�[�h
	 */
	virtual void Generate(std::string &OutCode) const override;

private:

	// �{�[�_�[���C��
	int Border;

	// �J�������X�g
	std::vector<CColumn *> Columns;

};

}
}
}

#endif		// #ifndef __HTMLOBJECT_H__