#ifndef __MEMORYSTREAM_H__
#define __MEMORYSTREAM_H__

namespace YanaPServer
{
namespace Util
{
namespace Stream
{

/**
 * @class IMemoryStream
 * @brief �������X�g���[��
 */
class IMemoryStream
{

public:

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~IMemoryStream() {}

	/**
	 * @fn virtual bool Serialize(int *pData) = 0
	 * @brief int�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(int *pData) = 0;

	/**
	 * @fn virtual bool Serialize(unsigned int *pData) = 0
	 * @brief unsigned int�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(unsigned int *pData) = 0;

	/**
	 * @fn virtual bool Serialize(chat *pData) = 0
	 * @brief ������̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(char *pData) = 0;

	/**
	 * @fn virtual bool IsError() const = 0
	 * @brief �G���[���������Ă��邩�H
	 * @return �G���[���������Ă�����true��Ԃ��B
	 */
	virtual bool IsError() const = 0;

};

}
}
}

#endif		// #ifndef __MEMORYSTRAM_H__
