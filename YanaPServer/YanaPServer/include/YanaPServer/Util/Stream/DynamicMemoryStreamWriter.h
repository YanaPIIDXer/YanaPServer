#ifndef __DYNAMICMEMORYSTREAMWRITER_H__
#define __DYNAMICMEMORYSTREAMWRITER_H__

#include "MemoryStream.h"

namespace YanaPServer
{
namespace Util
{
namespace Stream
{

/**
 * @class CDynamicMemoryStreamWriter
 * @brief ���I�Ƀ��������m�ۂ��Ȃ��珑�����ރX�g���[���N���X
 * @detail �ʏ��SizeCaliculator �� StreamWriter�̗���ŏ������ނ��A
 *         �X�g���[���ɏ�������ł���Œ��ɓ��I�ȏ�����g�񂾂肷��P�[�X�ł�
 *         ������̃N���X���g�����B
 *         ��Serialize�����s���邽�тɁA�����I��new��delete���J��Ԃ��̂Œ��ӁB
 */
class CDynamicMemoryStreamWriter : public IMemoryStream
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CDynamicMemoryStreamWriter();

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CDynamicMemoryStreamWriter();

	/**
	 * @fn virtual bool Serialize(const int *pData) = 0
	 * @brief int�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(const int *pData) override;

	/**
	 * @fn virtual bool Serialize(const unsigned int *pData) override
	 * @brief unsigned int�̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(const unsigned int *pData) override;

	/**
	 * @fn virtual bool Serialize(const chat *pData) override
	 * @brief ������̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(const char *pData) override;

	/**
	 * @fn virtual bool IsError() const override
	 * @brief �G���[���������Ă��邩�H
	 * @return �G���[�͋N���Ȃ��̂ŏ��false��Ԃ��B
	 */
	virtual bool IsError() const override { return false; }

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

	// ���݂̈ʒu.
	unsigned int CurrentPosition;


	// ��������
	bool Write(const void *pData, unsigned int Size);

};

}
}
}

#endif		// #ifndef __DYNAMICMEMORYSTREAMWRITER_H__
