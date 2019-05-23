#include "Servlet/ServletFinder.h"
#include "Servlet/Servlet.h"

namespace YanaPServer
{
namespace Servlet
{

// �R���X�g���N�^
CServletFinder::CServletFinder()
{
}

// Servlet�ǉ�
void CServletFinder::Add(IServlet *pServlet)
{
	ServletMap[pServlet->GetPath()] = pServlet;
}

// ����
IServlet *CServletFinder::Find(const char *pPath) const
{
	const auto &It = ServletMap.find(pPath);
	if (It == ServletMap.end()) { return nullptr; }
	return It->second;
}

}
}
