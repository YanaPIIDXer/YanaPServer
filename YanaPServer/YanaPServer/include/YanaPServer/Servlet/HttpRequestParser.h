#ifndef __HTTPREQUESTPARSER_H__
#define __HTTPREQUESTPARSER_H__

#include <vector>
#include <string>
#include "HttpRequest.h"

namespace YanaPServer
{
namespace Servlet
{

/**
 * @class CHttpRequestParser
 * @brief HTTP���N�G�X�g�p�[�T
 */
class CHttpRequestParser
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CHttpRequestParser();

	/**
	 * @brief �f�X�g���N�^
	 */
	~CHttpRequestParser() {}

	/**
	 * @fn bool Parse(const char *pData, unsigned int Size)
	 * @brief �p�[�X
	 * @param[in] pData �f�[�^
	 * @param[out] OutResult ��͌���
	 * @return ����������true��Ԃ��B
	 */
	bool Parse(const char *pData, SHttpRequest &OutResult);

private:


	// Split
	static void Split(const char *pData, const std::string &Delimiter, std::vector<std::string> &OutResult);

};

}
}

#endif		// #ifndef __HTTPREQUESTPARSER_H__
