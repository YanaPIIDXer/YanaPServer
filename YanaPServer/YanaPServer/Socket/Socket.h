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
 * @brief ソケットクラス
 */
class CSocket
{

public:

	/**
		* @brief コンストラクタ
		*/
	CSocket();

	/**
		* @brief デストラクタ
		*/
	~CSocket();

private:

	// 挙動インタフェース
	Behaviour::ISocketBehaviour *pBehaviour;

};

}
}

#endif		// #ifndef __SOCKET_H__
