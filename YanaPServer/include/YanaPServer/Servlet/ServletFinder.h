#ifndef __SERVLETFINDER_H__
#define __SERVLETFINDER_H__

#include <map>
#include <string>

namespace YanaPServer
{
namespace Servlet
{

class IServlet;

/**
 * @class CServletFinder
 * @brief Servlet検索
 */
class CServletFinder
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CServletFinder();

	/**
	 * @brief デストラクタ
	 */
	~CServletFinder() {}

	/**
	 * @fn void Add(IServlet *pServlet)
	 * @brief Servlet追加
	 * @param[in] pServlet Servlet
	 */
	void Add(IServlet *pServlet);

	/**
	 * @fn IServlet *Find(const char *pPath) const
	 * @brief 検索
	 * @param[in] pPath パス
	 * @return Servletオブジェクト
	 */
	IServlet *Find(const char *pPath) const;

private:

	// Servletマップ
	std::map<std::string, IServlet *> ServletMap;

};

}
}

#endif		// #ifndef __SERVLETFINDER_H__
