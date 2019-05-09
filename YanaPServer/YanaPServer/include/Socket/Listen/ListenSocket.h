#ifndef __LISTENSOCKET_H__
#define __LISTENSOCKET_H__

#include <functional>

namespace YanaPServer
{
namespace Socket
{
class ISocket;

namespace Listen
{

/**
 * @class IListenSocket
 * @brief Listen�pSocket�C���^�t�F�[�X
 */
class IListenSocket
{

public:

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~IListenSocket() {}

	/**
	 * @fn virtual void Poll() = 0;
	 * @brief ���t���[���Ăяo������
	 */
	virtual void Poll() = 0;

	/**
	 * @fn virtual bool StartListen(unsigned int Port) = 0
	 * @brief Listen�J�n
	 * @param[in] Port �|�[�g�ԍ�
	 * @param[in] AcceptCallback Accept�������̃R�[���o�b�N�֐�
	 * @return ����ɏ������I��������true��Ԃ��B
	 */
	virtual bool StartListen(unsigned int Port, const std::function<void(ISocket *)> &AcceptCallback) = 0;

};

/**
 * @class CListenSocket
 * @brief Listen�pSocket�N���X
 */
class CListenSocket
{

public:

	/**
	 * @fn static IListenSocket &Get()
	 * @brief Socket�擾
	 * @return IListenSocket�I�u�W�F�N�g
	 */
	static IListenSocket &Get();
	
};

}
}
}

#endif		// #ifndef __LISTENSOCKET_H__
