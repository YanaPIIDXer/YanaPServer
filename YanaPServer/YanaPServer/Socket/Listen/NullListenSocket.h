#ifndef __NULLLISTENSOCKET_H__
#define __NULLLISTENSOCKET_H__

#include "ListenSocket.h"

namespace YanaPServer
{
namespace Socket
{
namespace Listen
{

/**
 * @class NullListenSocket
 * @brief �������Ȃ�ListenSocket�N���X
 *		  ����`�̃v���b�g�t�H�[���Ŏg�p����B
 * @detail �V���O���g���N���X
 */
class CNullListenSocket : public IListenSocket
{

public:

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CNullListenSocket() {}

	/**
	 * @fn virtual bool Listen(unsigned int Port)
	 * @brief Listen�J�n
	 * @param[in] Port �|�[�g�ԍ�
	 * @return �������Ȃ��̂ŏ��false��Ԃ��B
	 */
	virtual bool Listen(unsigned int Port) { return false; }

	// ============= Singleton ============
public:

	/**
	 * @fn static CNullListenSocket &GetInstance()
	 * @brief �V���O���g���C���X�^���X�擾
	 * @return �V���O���g���C���X�^���X
	 */
	static CNullListenSocket &GetInstance() { return Instance; }

private:

	CNullListenSocket() {}
	static CNullListenSocket Instance;

};

}
}
}

#endif		// #ifndef __NULLLISTENSOCKET_H__
