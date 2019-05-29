#ifndef __SSLHANDSHAKE_H__
#define __SSLHANDSHAKE_H__

#include "Util/Stream/MemoryStream.h"

namespace YanaPServer
{
namespace Servlet
{

class CServletPeer;

namespace Secure
{

/**
 * @class CSSLHandshake
 * @brief SSLハンドシェイク
 */
class CSSLHandshake
{

public:

	/**
	 * @brief コンストラクタ
	 * @param[in] pInPeer Peer
	 */
	CSSLHandshake(CServletPeer *pInPeer);

	/**
	 * @brief デストラクタ
	 */
	~CSSLHandshake();

	/**
	 * @fn void OnRecv(const char *pData, unsigned int Size)
	 * @brief 受信した
	 * @param[in] pData データ
	 * @param[in] Size データ長
	 */
	void OnRecv(const char *pData, unsigned int Size);

private:

	// メッセージタイプ
	enum EMessageType
	{
		ClientHello = 0x01,
	};

	// Peer
	CServletPeer *pPeer;


	// ClientHelloを受信した。
	void OnRecvClientHello(YanaPServer::Util::Stream::IMemoryStream *pStream);

};

}
}
}

#endif		// #ifndef __SSLHANDSHAKE_H__
