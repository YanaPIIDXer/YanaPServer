#ifndef __STRINGSTREAM_H__
#define __STRINGSTREAM_H__

namespace YanaPServer
{
namespace Util
{
namespace Stream
{

/**
 * @class CStringStream
 * @brief ������X�g���[��
 * @detail Append���邽�тɓ�����new��delete������̂Œ��ӁB
 */
class CStringStream
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CStringStream();

	/**
	 * @brief �f�X�g���N�^
	 */
	~CStringStream();

	/**
	 * @fn void Append(const char *pStr)
	 * @brief �ǉ�
	 * @param[in] pStr �ǉ����镶����
	 */
	void Append(const char *pStr);

	/**
	 * @fn void AppendLine(const char *pStr)
	 * @brief �����ɉ��s�R�[�h��t�����Ēǉ�
	 * @param[in] pStr �ǉ����镶����
	 */
	void AppendLine(const char *pStr);

	/**
	 * @fn const char *GetBuffer() const
	 * @brief ������擾
	 * @return ������
	 */
	const char *Get() const { return pBuffer; }

	/**
	 * @fn unsigned int GetLength() const
	 * @brief �����񒷎擾
	 * @return ������
	 */
	unsigned int GetLength() const { return Length; }

private:

	// �o�b�t�@
	char *pBuffer;

	// ������.
	unsigned int Length;

};

}
}
}

#endif		// #ifndef __STRINGSTREAM_H__
