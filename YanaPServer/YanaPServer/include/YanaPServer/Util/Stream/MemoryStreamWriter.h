#ifndef __MEMORYSTREAMWRITER_H__
#define __MEMORYSTREAMWRITER_H__

#include "MemoryStream.h"

namespace YanaPServer
{
namespace Util
{
namespace Stream
{

/**
 * @class CMemoryStreamWriter
 * @brief �������ݗp�X�g���[��
 */
class CMemoryStreamWriter : public IMemoryStream
{

public:

	/**
	 * @brief �R���X�g���N�^
	 * @param[in] InBufferSize �o�b�t�@�T�C�Y
	 */
	CMemoryStreamWriter(unsigned int InBufferSize);

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CMemoryStreamWriter();

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
	 * @fn virtual bool Serialize(chat *pData) override
	 * @brief ������̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(char *pData) override;

	/**
	 * @fn virtual bool IsError() const override
	 * @brief �G���[���������Ă��邩�H
	 * @return �G���[���������Ă�����true��Ԃ��B
	 */
	virtual bool IsError() const override { return bIsError; }

	/**
	 * @fn unsigned char *GetBuffer() const
	 * @brief �o�b�t�@���擾�B
	 * @detail �o�b�t�@�̐擪�ʒu��Ԃ��B
	 * @return �o�b�t�@
	 */
	unsigned char *GetBuffer() const { return pBuffer; }

	/**
	 * @fn unsigned int GetSize() const
	 * @brief �T�C�Y���擾
	 * @return �T�C�Y
	 */
	unsigned int GetSize() const { return CurrentPosition; }

private:

	// �o�b�t�@
	unsigned char *pBuffer;

	// �o�b�t�@�T�C�Y
	unsigned int BufferSize;

	// ���݂̈ʒu.
	unsigned int CurrentPosition;

	// �G���[���N���Ă��邩�H
	bool bIsError;


	// ��������
	bool Write(void *pData, unsigned int Size);

};

}
}
}

#endif		// #ifndef __MEMORYSTREAMWRITER_H__