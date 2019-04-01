#ifndef __SOCKET_H__
#define __SOCKET_H__

namespace YanaPServer
{
namespace Socket
{
namespace Behaviour
{
class ISocketBehaviour;
}

/**
 * @class CSocket
 * @brief �\�P�b�g�N���X
 */
class CSocket
{

public:

	/**
		* @brief �R���X�g���N�^
		*/
	CSocket();

	/**
		* @brief �f�X�g���N�^
		*/
	~CSocket();

private:

	// �����C���^�t�F�[�X
	Behaviour::ISocketBehaviour *pBehaviour;

};

}
}

#endif		// #ifndef __SOCKET_H__
