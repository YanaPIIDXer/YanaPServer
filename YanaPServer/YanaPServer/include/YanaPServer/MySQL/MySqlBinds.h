#ifndef __MYSQLBINDS_H__
#define __MYSQLBINDS_H__

#ifdef _WIN32
#include <windows.h>
#include <mysql.h>
#else
#include <mysql/mysql.h>
#endif

#include <vector>

namespace YanaPServer
{
namespace MySQL
{

/**
 * @class CMySqlBinds
 * @brief �o�C���h
 * @detail ���p�҂����̃N���X�𒼐ڑ��삷�鎖�͂Ȃ��B
 *         �iCMySqlQuery�N���X���g�p����B�j
 */
class CMySqlBinds
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CMySqlBinds();

	/**
	 * @brief �f�X�g���N�^
	 */
	~CMySqlBinds();

	/**
	 * @fn void AddInt(int *pPtr)
	 * @brief int�ǉ�
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void AddInt(int *pPtr);

	/**
	 * @fn void AddInt(unsigned int *pPtr)
	 * @brief unsigned int�ǉ�
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void AddInt(unsigned int *pPtr);

	/**
	 * @fn void AddShort(short *pPtr)
	 * @brief short�ǉ�
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void AddShort(short *pPtr);

	/**
	 * @fn void AddShort(unsigned short *pPtr)
	 * @brief unsigned short�ǉ�
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void AddShort(unsigned short *pPtr);

	/**
	 * @fn void AddChar(char *pPtr)
	 * @brief char�ǉ�
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void AddChar(char *pPtr);

	/**
	 * @fn void AddChar(unsigned char *pPtr)
	 * @brief unsigned char�ǉ�
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void AddChar(unsigned char *pPtr);

	/**
	 * @fn void AddFloat(float *pPtr)
	 * @brief float�ǉ�
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void AddFloat(float *pPtr);

	/**
	 * @fn void AddString(char *pPtr)
	 * @brief ������ǉ�
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 * @param[in] bForResult ���ʂւ̃o�C���h���H
	 */
	void AddString(char *pPtr, bool bForResult);

	/**
	 * @fn void AddWString(wchar_t *pPtr)
	 * @brief ���C�h������ǉ�
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 * @param[in] bForResult ���ʂւ̃o�C���h���H
	 */
	void AddWString(wchar_t *pPtr, bool bForResult);

	/**
	 * @fn void AddTime(MYSQL_TIME *pPtr)
	 * @brief ���Ԓǉ�
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void AddTime(MYSQL_TIME *pPtr);

	/**
	 * @fn MYSQL_BIND *Get() 
	 * @brief �擾
	 * @return �o�C���h�I�u�W�F�N�g
	 */
	MYSQL_BIND *Get() { return pBinds; }

private:

	// String�^�̃o�b�t�@��.
	static const int StringBufferLength;

	// �o�C���h
	MYSQL_BIND *pBinds;

	// �z��.
	int Length;

	// �̈�g��.
	void Reallocate();

};

}
}

#endif		// #ifndef __MYSQLBINDS_H__
