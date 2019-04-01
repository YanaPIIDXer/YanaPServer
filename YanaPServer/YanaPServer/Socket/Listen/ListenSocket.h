#ifndef __LISTENSOCKET_H__
#define __LISTENSOCKET_H__

namespace YanaPServer
{
namespace Socket
{
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
	 * @fn virtual bool Listen(unsigned int Port) = 0
	 * @brief Listen�J�n
	 * @param[in] Port �|�[�g�ԍ�
	 * @return ����ɏ������I��������true��Ԃ��B
	 */
	virtual bool Listen(unsigned int Port) = 0;

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
