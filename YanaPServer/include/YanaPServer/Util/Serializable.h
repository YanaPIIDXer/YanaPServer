#ifndef __SERIALIZABLE_H__
#define __SERIALIZABLE_H__

#include "Stream/MemoryStream.h"

namespace YanaPServer
{
namespace Util
{

/**
 * @class ISerializable
 * @brief �V���A���C�Y�p�C���^�t�F�[�X
 */
class ISerializable
{

public:

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~ISerializable() {}

	/**
	 * @fn virtual bool Serialize(Stream::IMemoryStream *pStream) = 0
	 * @brief �V���A���C�Y
	 * @param[in] pStream �X�g���[��
	 * @return ����������true��Ԃ�
	 */
	virtual bool Serialize(Stream::IMemoryStream *pStream) = 0;

};

}
}

#endif		// #ifndef __SERIALIZABLE_H__
