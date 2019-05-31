#ifndef __MEMORYSTREAMWRITER_H__
#define __MEMORYSTREAMWRITER_H__

#include "MemoryStream.h"
#include "../Serializable.h"

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
	 * @fn virtual bool Serialize(ISerializable *pData) override
	 * @brief �V���A���C�Y�\�ȃI�u�W�F�N�g�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(ISerializable *pData) override { return pData->Serialize(this); }

	/**
	 * @fn virtual bool Serialize(void *pData, unsigned int DataSize) override
	 * @brief �C�ӂ̃f�[�^���V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @param[in] DataSize �f�[�^��
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(void *pData, unsigned int DataSize) override { return Write(pData, DataSize); }

	/**
	 * @fn virtual bool IsError() const override
	 * @brief �G���[���������Ă��邩�H
	 * @return �G���[���������Ă�����true��Ԃ��B
	 */
	virtual bool IsError() const override { return bIsError; }

	/**
	 * @fn virtual EStreamType GetType() const override
	 * @brief �X�g���[���^�C�v���擾
	 * @return �X�g���[���^�C�v�Ԃ��B
	 */
	virtual EStreamType GetType() const override { return EStreamType::Write; }

	/**
	 * @fn const char *GetBuffer() const
	 * @brief �o�b�t�@���擾�B
	 * @detail �o�b�t�@�̐擪�ʒu��Ԃ��B
	 * @return �o�b�t�@
	 */
	const char *GetBuffer() const { return pBuffer; }

	/**
	 * @fn unsigned int GetSize() const
	 * @brief �T�C�Y���擾
	 * @return �T�C�Y
	 */
	unsigned int GetSize() const { return CurrentPosition; }

private:

	// �o�b�t�@
	char *pBuffer;

	// �o�b�t�@�T�C�Y
	unsigned int BufferSize;

	// ���݂̈ʒu.
	unsigned int CurrentPosition;

	// �G���[���N���Ă��邩�H
	bool bIsError;


	// ��������
	bool Write(const void *pData, unsigned int Size);

};

}
}
}

#endif		// #ifndef __MEMORYSTREAMWRITER_H__
