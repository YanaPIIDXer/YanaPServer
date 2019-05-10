#ifndef __SERVLETEVENT_H__
#define __SERVLETEVENT_H__

namespace YanaPServer
{
namespace Servlet
{

/**
 * @class IServletEvent
 * @brief Servlet�����s����C�x���g�̃C���^�t�F�[�X
 */
class IServletEvent
{

public:

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~IServletEvent() {}

	/**
	 * @brief POST���N�G�X�g��������ꂽ���Ɏ��s�����C�x���g
	 */
	virtual void OnPost() = 0;

	/**
	 * @brief GET���N�G�X�g��������ꂽ���Ɏ��s�����C�x���g
	 */
	virtual void OnGet() = 0;

};

}
}

#endif		// #ifndef __SERVLETEVENT_H__
