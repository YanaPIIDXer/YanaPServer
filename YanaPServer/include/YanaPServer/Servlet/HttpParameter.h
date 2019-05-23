#ifndef __HTTPPARAMETER_H__
#define __HTTPPARAMETER_H__

#include <vector>
#include <map>

namespace YanaPServer
{
namespace Servlet
{

// 別名定義.
typedef std::vector<std::string> ParamList;

/**
 * @class CHttpParameter
 * @brief HTTPパラメータ
 */
class CHttpParameter
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CHttpParameter();

	/**
	 * @brief デストラクタ
	 */
	~CHttpParameter() {}

	/**
	 * @fn void Add(const std::string &ParamName, const char *pValue)
	 * @brief 追加
	 * @param[in] ParamName パラメータ名
	 * @param[in] pValue 値
	 */
	void Add(const std::string &ParamName, const char *pValue);

	/**
	 * @fn const char *Get(const std::string &ParamName, unsigned int Index = 0) const
	 * @brief 取得
	 * @param[in] ParamName パラメータ名
	 * @param[in] Index インデックス
	 * @return 値
	 */
	const char *Get(const std::string &ParamName, unsigned int Index = 0) const;

	/**
	 * @fn unsigned int GetCount(const std::string &ParamName) const
	 * @brief 同名パラメータの個数を取得
	 * @param[in] ParamName パラメータ名
	 * @return 同名パラメータの個数
	 */
	unsigned int GetCount(const std::string &ParamName) const;

private:

	// パラメータマップ
	std::map<std::string, ParamList> ParamMap;

};

}
}

#endif		// #ifndef __HTTPPARAMETER_H__
