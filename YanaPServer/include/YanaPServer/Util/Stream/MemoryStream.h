#ifndef __MEMORYSTREAM_H__
#define __MEMORYSTREAM_H__

#include <string>

namespace YanaPServer
{
namespace Util
{

class ISerializable;

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
	 * @fn virtual bool Serialize(short *pData) = 0
	 * @brief short�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(short *pData) = 0;

	/**
	 * @fn virtual bool Serialize(unsigned short *pData) = 0
	 * @brief unsigned short�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(unsigned short *pData) = 0;

	/**
	 * @fn virtual bool Serialize(char *pData) = 0
	 * @brief char�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(char *pData) = 0;

	/**
	 * @fn virtual bool Serialize(unsigned char *pData) = 0
	 * @brief unsigned char�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(unsigned char *pData) = 0;

	/**
	 * @fn virtual bool Serialize(float *pData) = 0
	 * @brief float�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(float *pData) = 0;

	/**
	 * @fn virtual bool Serialize(std::string *pData) = 0
	 * @brief ������̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(std::string *pData) = 0;

	/**
	 * @fn virtual bool Serialize(ISerializable *pData) = 0
	 * @brief �V���A���C�Y�\�ȃI�u�W�F�N�g�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(ISerializable *pData) = 0;

	/**
	 * @fn virtual bool IsError() const = 0
	 * @brief �G���[���������Ă��邩�H
	 * @return �G���[���������Ă�����true��Ԃ��B
	 */
	virtual bool IsError() const = 0;

	/**
	 * @fn virtual bool IsReadMode() const = 0
	 * @brief �ǂݍ��݃��[�h���H
	 * @return �ǂݍ��݃��[�h�Ȃ�true��Ԃ��B
	 */
	virtual bool IsReadMode() const = 0;

};

}
}
}

#endif		// #ifndef __MEMORYSTRAM_H__
