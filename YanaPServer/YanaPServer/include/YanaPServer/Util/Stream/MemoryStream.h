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
	 * @fn virtual bool Serialize(const int *pData) = 0
	 * @brief int�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(const int *pData) = 0;

	/**
	 * @fn virtual bool Serialize(const unsigned int *pData) = 0
	 * @brief unsigned int�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(const unsigned int *pData) = 0;

	/**
	 * @fn virtual bool Serialize(const short *pData) = 0
	 * @brief short�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(const short *pData) = 0;

	/**
	 * @fn virtual bool Serialize(const unsigned short *pData) = 0
	 * @brief unsigned short�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(const unsigned short *pData) = 0;

	/**
	 * @fn virtual bool Serialize(const float *pData) = 0
	 * @brief float�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(const float *pData) = 0;

	/**
	 * @fn virtual bool Serialize(const chat *pData) = 0
	 * @brief ������̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(const char *pData) = 0;

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
