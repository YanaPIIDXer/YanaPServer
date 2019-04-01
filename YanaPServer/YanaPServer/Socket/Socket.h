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


	// 挙動インタフェースの生成.
	void CreateBehaviour();

	// 挙動インタフェースの解放.
	void ReleaseBehaviour();

};

}
}

#endif		// #ifndef __SOCKET_H__
