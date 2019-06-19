#ifndef __HTTPSESSION_H__
#define __HTTPSESSION_H__

#include <map>
#include <string>
#include <memory>

namespace YanaPServer
{
namespace Servlet
{

class CHttpSession;
typedef std::auto_ptr<CHttpSession> HttpSessionPtr;

/**
 * @class CHttpSession
 * @brief HTTP�Z�b�V����
 */
class CHttpSession
{

private:		// �ʖ���`.

	typedef std::map<std::string, std::string> DataMap;

public:

	/**
	 * @fn static HttpSessionPtr OpenOrCreate(const std::string &SessionId)
	 * @brief �J�� or ����
	 * @param[in] SessionId �Z�b�V�����h�c�i�󕶎��̏ꍇ�͐V�K�쐬�j
	 * @return HTTP�Z�b�V�����ւ̃|�C���^�iauto_ptr�j
	 */
	static HttpSessionPtr OpenOrCreate(const std::string &SessionId);

	/**
	 * @brief �f�X�g���N�^
	 */
	~CHttpSession();

	/**
	 * @fn void Set(const std::string &VariableName, const std::string &Value)
	 * @brief �Z�b�g
	 * @param[in] VariableName �ϐ���
	 * @param[in] Value �l
	 */
	void Set(const std::string &VariableName, const std::string &Value);

	/**
	 * @fn void Get(const std::string &VariableName, std::string &OutValue) const
	 * @brief �擾
	 * @param[in] VariableName �ϐ���
	 * @param[out] OutValue �l
	 */
	void Get(const std::string &VariableName, std::string &OutValue) const;

	/**
	 * @fn const std::string &GetSessionId() const
	 * @brief �Z�b�V�����h�c�擾
	 * @return �Z�b�V�����h�c
	 */
	const std::string &GetSessionId() const { return SessionId; }

private:

	// �t�@�C���f�B���N�g��
	static const std::string FileDirectory;

	// �Z�b�V�����h�c
	std::string SessionId;

	// �f�[�^�}�b�v
	DataMap Datas;


	// �R���X�g���N�^
	CHttpSession(const std::string &InSessionId);

	// �t�@�C�����J��
	void OpenFile();

	// �t�@�C���ɕۑ�.
	void SaveFile();

};

}
}

#endif		// #ifndef __HTTPSESSION_H__
