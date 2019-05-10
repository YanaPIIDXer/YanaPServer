#ifndef __MYSQLQUERY_H__
#define __MYSQLQUERY_H__

#ifdef _WIN32
#include <windows.h>
#include <mysql.h>
#else
#include <mysql/mysql.h>
#endif

#include "MySqlBinds.h"

namespace YanaPServer
{
namespace MySQL
{

/**
 * @class CMySqlQuery
 * @brief MySQL�N�G���N���X
 * @detail CMySqlConnection�N���X����������B
 */
class CMySqlQuery
{

public:

	/**
	 * @brief �R���X�g���N�^
	 * @param[in] pInConnection �ڑ��I�u�W�F�N�g
	 * @param[in] pInQuery �N�G��
	 */
	CMySqlQuery(MYSQL *pInConnection, const char *pInQuery);

	/**
	 * @brief �f�X�g���N�^
	 */
	~CMySqlQuery();

	/**
	 * @fn void BindInt(int *pPtr)
	 * @brief int�^�̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindInt(int *pPtr);

	/**
	 * @fn void BindInt(unsigned int *pPtr)
	 * @brief unsigned int�^�̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindInt(unsigned int *pPtr);

	/**
	 * @fn void BindShort(short *pPtr)
	 * @brief short�^�̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindShort(short *pPtr);

	/**
	 * @fn void BindShort(unsigned short *pPtr)
	 * @brief unsigned short�^�̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindShort(unsigned short *pPtr);

	/**
	 * @fn void BindChar(char *pPtr)
	 * @brief char�^�̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindChar(char *pPtr);

	/**
	 * @fn void BindChar(unsigned char *pPtr)
	 * @brief unsigned char�^�̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindChar(unsigned char *pPtr);

	/**
	 * @fn void BindFloat(float *pPtr)
	 * @brief float�^�̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindFloat(float *pPtr);

	/**
	 * @fn void BindString(char *pPtr)
	 * @brief ������̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindString(char *pPtr);

	/**
	 * @fn void BindWString(wchar_t *pPtr)
	 * @brief ���C�h������̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindWString(wchar_t *pPtr);

	/**
	 * @fn void BindTime(MYSQL_TIME *pPtr)
	 * @brief ���Ԃ̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindTime(MYSQL_TIME *pPtr);

	/**
	 * @fn void BindResultInt(int *pPtr)
	 * @brief ���ʂ�int�^�̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindResultInt(int *pPtr);

	/**
	 * @fn void BindResultInt(unsigned int *pPtr)
	 * @brief ���ʂ�unsigned int�^�̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindResultInt(unsigned int *pPtr);

	/**
	 * @fn void BindResultShort(short *pPtr)
	 * @brief ���ʂ�short�^�̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindResultShort(short *pPtr);

	/**
	 * @fn void BindResultShort(unsigned short *pPtr)
	 * @brief ���ʂ�unsigned short�^�̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindResultShort(unsigned short *pPtr);

	/**
	 * @fn void BindResultChar(char *pPtr)
	 * @brief ���ʂ�char�^�̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindResultChar(char *pPtr);

	/**
	 * @fn void BindResultChar(unsigned char *pPtr)
	 * @brief ���ʂ�unsigned char�^�̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindResultChar(unsigned char *pPtr);

	/**
	 * @fn void BindResultFloat(float *pPtr)
	 * @brief ���ʂ�float�^�̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindResultFloat(float *pPtr);

	/**
	 * @fn void BindResultString(char *pPtr)
	 * @brief ���ʂ̕�����̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindResultString(char *pPtr);

	/**
	 * @fn void BindResultWString(wchar_t *pPtr)
	 * @brief ���ʂ̃��C�h������̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindResultWString(wchar_t *pPtr);

	/**
	 * @fn void BindResultTime(MYSQL_TIME *pPtr)
	 * @brief ���ʂ̎��Ԃ̃o�C���h
	 * @param[in] pPtr �ϐ��ւ̃|�C���^
	 */
	void BindResultTime(MYSQL_TIME *pPtr);

	/**
	 * @fn bool ExecuteQuery()
	 * @brief �N�G�����s
	 * @return ����������true��Ԃ�
	 */
	bool ExecuteQuery();

	/**
	 * @fn bool Fetch()
	 * @brief �t�F�b�`
	 * @return ���̌��ʂ��c���Ă����true��Ԃ�
	 */
	bool Fetch();

	// ����
	void Close();

private:

	// MYSQL�ւ̐ڑ�.
	MYSQL *pConnection;

	// �N�G��
	const char *pQuery;

	// �X�e�[�g�����g
	MYSQL_STMT *pStatement;

	// �o�C���h
	CMySqlBinds Binds;

	// ���ʃo�C���h
	CMySqlBinds Results;

};

}
}

#endif		// #ifndef __MYSQLQUERY_H__
