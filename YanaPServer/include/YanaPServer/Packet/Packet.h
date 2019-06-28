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
 * @brief �p�P�b�g���N���X
 */
class CPacket : public Util::ISerializable
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CPacket() {}

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CPacket() {}

	/**
	 * @fn virtual unsigned char GetPacketId() const = 0
	 * @brief �p�P�b�g�h�c�擾
	 * @return �p�P�b�g�h�c
	 */
	virtual unsigned char GetPacketId() const = 0;

};

}
}

#endif		// #ifndef __PACKET_H__
