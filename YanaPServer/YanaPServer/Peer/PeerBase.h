#ifndef __PEERBASE_H__
#define __PEERBASE_H__

#include "YanaPServer/Socket/Socket.h"
using namespace YanaPServer::Socket;

namespace YanaPServer
{
namespace Peer
{

/**
 * @class PeerBase
 * @brief ピア基底クラス
 */
class PeerBase
{

public:
	
	/**
	 * @brief コンストラクタ
	 * @param[in] pInSocket ソケット
	 */
	PeerBase(ISocket *pInSocket);

	/**
	 * @brief デストラクタ
	 */
	virtual ~PeerBase();

	/**
	 * @fn bool IsValid() const
	 * @brief 有効か？
	 * @return 有効ならtrueを返す。
	 */
	bool IsValid() const { return (pSocket != nullptr); }

private:

	// ソケット
	ISocket *pSocket;
	

	// ソケット解放.
	void ReleaseSocket();

};

}
}

#endif		// #ifndef __PEERBASE_H__
