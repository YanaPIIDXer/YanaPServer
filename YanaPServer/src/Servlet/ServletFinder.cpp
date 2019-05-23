#include "Servlet/ServletFinder.h"
#include "Servlet/Servlet.h"

namespace YanaPServer
{
namespace Servlet
{

// コンストラクタ
CServletFinder::CServletFinder()
{
}

// Servlet追加
void CServletFinder::Add(IServlet *pServlet)
{
	ServletMap[pServlet->GetPath()] = pServlet;
}

// 検索
IServlet *CServletFinder::Find(const char *pPath) const
{
	const auto &It = ServletMap.find(pPath);
	if (It == ServletMap.end()) { return nullptr; }
	return It->second;
}

}
}
