#include "Packet/PacketHeader.h"

namespace YanaPServer
{
namespace Packet
{

const unsigned int CPacketHeader::HeaderSize = 2;

// コンストラクタ
CPacketHeader::CPacketHeader()
	: PacketId(0)
	, Size(0)
{
}

// コンストラクタ
CPacketHeader::CPacketHeader(unsigned char InPacketId, unsigned char InSize)
	: PacketId(InPacketId)
	, Size(InSize)
{
}

// シリアライズ
bool CPacketHeader::Serialize(Util::Stream::IMemoryStream *pStream)
{
	if (!pStream->Serialize(&PacketId)) { return false; }
	if (!pStream->Serialize(&Size)) { return false; }

	return true;
}

}
}
