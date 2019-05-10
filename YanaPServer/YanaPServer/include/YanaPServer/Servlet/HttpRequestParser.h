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
 * @brief HTTPリクエストパーサ
 */
class CHttpRequestParser
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CHttpRequestParser();

	/**
	 * @brief デストラクタ
	 */
	~CHttpRequestParser() {}

	/**
	 * @fn bool Parse(const char *pData, unsigned int Size)
	 * @brief パース
	 * @param[in] pData データ
	 * @param[out] OutResult 解析結果
	 * @return 成功したらtrueを返す。
	 */
	bool Parse(const char *pData, SHttpRequest &OutResult);

private:


	// Split
	static void Split(const char *pData, const std::string &Delimiter, std::vector<std::string> &OutResult);

};

}
}

#endif		// #ifndef __HTTPREQUESTPARSER_H__
