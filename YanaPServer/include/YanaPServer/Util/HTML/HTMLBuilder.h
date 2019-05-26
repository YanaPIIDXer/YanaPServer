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
 * @brief �g�s�l�k�\�z�N���X
 */
class CHTMLBuilder
{

public:

	/**
	 * @brief �R���X�g���N�^
	 * @param[in] InTitle �y�[�W�̃^�C�g��
	 */
	CHTMLBuilder(const std::string &InTitle);

	/**
	 * @�f�X�g���N�^
	 */
	~CHTMLBuilder();

	/**
	 * @fn std::string Generate() const
	 * @brief �\�z
	 * @return �\�z���ꂽHTML
	 */
	std::string Generate() const;

	/**
	 * @fn void AddText(const std::string &Text, bool bAppendNewLine)
	 * @brief �e�L�X�g�ǉ�
	 * @param[in] Text�e�L�X�g
	 * @param[in] bAppendNewLine ���s���邩�H
	 */
	void AddText(const std::string &Text, bool bAppendNewLine = true);

	/**
	 * @fn void AddLink(const char *pURL, const char *pText, bool bAppendNewLine)
	 * @brief �����N�ǉ�
	 * @param[in] pURL URL
	 * @param[in] pText �e�L�X�g
	 * @param[in] bAppendNewLine ���s���邩�H
	 */
	void AddLink(const char *pURL, const char *pText, bool bAppendNewLine = true);

private:

	// �y�[�W�̃^�C�g��
	std::string Title;

	// �I�u�W�F�N�g�Q.
	std::vector<IHTMLObject *> Objects;

};

}
}
}

#endif		// #ifndef __HTMLBUILDER_H__
