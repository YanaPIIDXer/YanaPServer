#ifndef __SOCKETBEHAVIOUR_H__
#define __SOCKETBEHAVIOUR_H__

namespace YanaPServer
{
namespace Socket
{
namespace Behaviour
{

/**
* @class ISocketBehaviour
* @brief �\�P�b�g�̋������������邽�߂̃C���^�t�F�[�X
*/
class ISocketBehaviour
{

public:

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~ISocketBehaviour() {}

	/**
	 * @fn virtual void Release() = 0
	 * @brief ���
	 */
	virtual void Release() = 0;

};

}
}
}

#endif		// #ifndef __SOCKETBEHAVIOUR_H__
