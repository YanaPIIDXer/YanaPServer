#ifndef __MEMORYSTREAMREADER_H__
#define __MEMORYSTREAMREADER_H__

#include "MemoryStream.h"

namespace YanaPServer
{
namespace Util
{
namespace Stream
{

/**
 * @class CMemoryStreamReader
 * @brief �ǂݍ��ݗp�X�g���[��
 */
class CMemoryStreamReader : public IMemoryStream
{

public:

	/**
 	 * @brief �R���X�g���N�^
	 * @param[in] pInBuffer �o�b�t�@
 	 * @param[in] InBufferSize �o�b�t�@�T�C�Y
	 */
	CMemoryStreamReader(const char *pInBuffer, unsigned int InBufferSize);

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CMemoryStreamReader();

	/**
	 * @fn virtual bool Serialize(int *pData) = 0
	 * @brief int�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(int *pData) override;

	/**
	 * @fn virtual bool Serialize(unsigned int *pData) override
	 * @brief unsigned int�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(unsigned int *pData) override;

	/**
	 * @fn virtual bool Serialize(short *pData) override
	 * @brief short�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(short *pData) override;

	/**
	 * @fn virtual bool Serialize(unsigned short *pData) override
	 * @brief unsigned short�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(unsigned short *pData) override;

	/**
	 * @fn virtual bool Serialize(char *pData) override
	 * @brief char�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(char *pData) override;

	/**
	 * @fn virtual bool Serialize(unsigned char *pData) override
	 * @brief unsigned char�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(unsigned char *pData) override;

	/**
	 * @fn virtual bool Serialize(float *pData) override
	 * @brief float�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(float *pData) override;

	/**
	 * @fn virtual bool Serialize(std::string *pData) override
	 * @brief ������̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(std::string *pData) override;

	/**
	 * @fn virtual bool IsError() const override
	 * @brief �G���[���������Ă��邩�H
	 * @return �G���[���������Ă�����true��Ԃ��B
	 */
	virtual bool IsError() const override { return bIsError; }

private:

	// �o�b�t�@
	char *pBuffer;

	//�o�b�t�@�T�C�Y
	const unsigned int BufferSize;

	// ���݂̈ʒu.
	unsigned int CurrentPosition;

	// �G���[���N���Ă��邩�H
	bool bIsError;


	// ��������
	bool Read(void *pData, unsigned int Size);

};

}
}
}

#endif		// #ifndef __MEMORYSTREAMREADER_H__
