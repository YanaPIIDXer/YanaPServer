#ifndef __PEERBASE_H__
#define __PEERBASE_H__

#include "YanaPServer/Socket/Socket.h"
using namespace YanaPServer::Socket;

namespace YanaPServer
{
namespace Peer
{

/**
 * @class CPeerBase
 * @brief ピア基底クラス
 */
class CPeerBase
{

public:
	
	/**
	 * @brief コンストラクタ
	 * @param[in] pInSocket ソケット
	 */
	CPeerBase(ISocket *pInSocket);

	/**
	 * @brief デストラクタ
	 */
	virtual ~CPeerBase() = 0;

	/**
	 * @fn bool IsValid() const
	 * @brief 有効か？
	 * @return 有効ならtrueを返す。
	 */
	bool IsValid() const { return (pSocket != nullptr && pSocket->IsValid()); }

private:

	// ソケット
	ISocket *pSocket;
	

	// ソケット解放.
	void ReleaseSocket();

};

}
}

#endif		// #ifndef __PEERBASE_H__
