#ifndef __PACKET_H__
#define __PACKET_H__

#include "Util/Serializable.h"
#include "Util/Stream/MemoryStream.h"

namespace YanaPServer
{
namespace Packet
{

/**
 * @class CPacket
 * @brief パケット基底クラス
 */
class CPacket : public Util::ISerializable
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CPacket() {}

	/**
	 * @brief デストラクタ
	 */
	virtual ~CPacket() {}

	/**
	 * @fn virtual unsigned char GetPacketId() const = 0
	 * @brief パケットＩＤ取得
	 * @return パケットＩＤ
	 */
	virtual unsigned char GetPacketId() const = 0;

};

}
}

#endif		// #ifndef __PACKET_H__
