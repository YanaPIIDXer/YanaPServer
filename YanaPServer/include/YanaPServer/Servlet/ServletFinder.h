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
 * @brief Servlet����
 */
class CServletFinder
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CServletFinder();

	/**
	 * @brief �f�X�g���N�^
	 */
	~CServletFinder() {}

	/**
	 * @fn void Add(IServlet *pServlet)
	 * @brief Servlet�ǉ�
	 * @param[in] pServlet Servlet
	 */
	void Add(IServlet *pServlet);

	/**
	 * @fn IServlet *Find(const char *pPath) const
	 * @brief ����
	 * @param[in] pPath �p�X
	 * @return Servlet�I�u�W�F�N�g
	 */
	IServlet *Find(const char *pPath) const;

private:

	// Servlet�}�b�v
	std::map<std::string, IServlet *> ServletMap;

};

}
}

#endif		// #ifndef __SERVLETFINDER_H__
