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
 * @brief HTTPセッション
 */
class CHttpSession
{

private:		// 別名定義.

	typedef std::map<std::string, std::string> DataMap;

public:

	/**
	 * @fn static HttpSessionPtr OpenOrCreate(const std::string &SessionId)
	 * @brief 開く or 生成
	 * @param[in] SessionId セッションＩＤ（空文字の場合は新規作成）
	 * @return HTTPセッションへのポインタ（auto_ptr）
	 */
	static HttpSessionPtr OpenOrCreate(const std::string &SessionId);

	/**
	 * @brief デストラクタ
	 */
	~CHttpSession();

	/**
	 * @fn void Set(const std::string &VariableName, const std::string &Value)
	 * @brief セット
	 * @param[in] VariableName 変数名
	 * @param[in] Value 値
	 */
	void Set(const std::string &VariableName, const std::string &Value);

	/**
	 * @fn void Get(const std::string &VariableName, std::string &OutValue) const
	 * @brief 取得
	 * @param[in] VariableName 変数名
	 * @param[out] OutValue 値
	 */
	void Get(const std::string &VariableName, std::string &OutValue) const;

	/**
	 * @fn const std::string &GetSessionId() const
	 * @brief セッションＩＤ取得
	 * @return セッションＩＤ
	 */
	const std::string &GetSessionId() const { return SessionId; }

private:

	// ファイルディレクトリ
	static const std::string FileDirectory;

	// セッションＩＤ
	std::string SessionId;

	// データマップ
	DataMap Datas;


	// コンストラクタ
	CHttpSession(const std::string &InSessionId);

	// ファイルを開く
	void OpenFile();

	// ファイルに保存.
	void SaveFile();

};

}
}

#endif		// #ifndef __HTTPSESSION_H__
