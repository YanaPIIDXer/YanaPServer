#ifndef __MEMORYSIZECALICULATOR_H__
#define __MEMORYSIZECALICULATOR_H__

#include "MemoryStream.h"

namespace YanaPServer
{
namespace Util
{
namespace Stream
{

/**
 * @class CMemorySizeCaliculator
 * @brief �T�C�Y�v�Z�X�g���[��
 */
class CMemorySizeCaliculator : public IMemoryStream
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CMemorySizeCaliculator();

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CMemorySizeCaliculator() {}

	/**
	 * @fn virtual bool Serialize(const int *pData) override
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
	 * @fn virtual bool Serialize(cconst chat *pData) override
	 * @brief ������̃V���A���C�Y
	 * @param[in] pData �f�[�^
	 * @return ����������true��Ԃ��B
	 */
	virtual bool Serialize(const char *pData) override;

	/**
	 * @fn virtual bool IsError() const override
	 * @brief �G���[���������Ă��邩�H
	 * @return �G���[�Ȃ�Ė����̂ŏ��false��Ԃ��B
	 */
	virtual bool IsError() const override { return false; }

	/**
	 * @fn unsigned int GetSize() const
	 * @brief �T�C�Y�擾
	 * @return �T�C�Y
	 */
	unsigned int GetSize() const { return Size; }

private:

	// �T�C�Y
	unsigned int Size;

};

}
}
}

#endif		// #ifndef __MEMORYSIZECALICULATOR_H__
