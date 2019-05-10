#ifndef __MYSQLCONNECTION_H__
#define __MYSQLCONNECTION_H__

#ifdef _WIN32
#include <windows.h>
#include <mysql.h>
#else
#include <mysql/mysql.h>
#endif

#include "MySqlQuery.h"

namespace YanaPServer
{
namespace MySQL
{

/**
 * @class CMySqlConnection
 * @brief MySQL�ڑ��N���X
 */
class CMySqlConnection
{

public:

	/**
	 * @brief �R���X�g���N�^
	 */
	CMySqlConnection();

	/**
	 * @brief �f�X�g���N�^
	 */
	~CMySqlConnection();

	/**
	 * @fn bool Connect(const char *pHost, const char *pUserName, const char *pPassword, const char *pDBName)
	 * @brief �ڑ�
	 * @param[in] pHost �z�X�g
	 * @param[in] pUserName ���[�U��
	 * @param[in] pPassword �p�X���[�h
	 * @param[in] pDBName �c�a��
	 * @return ����������true��Ԃ�
	 */
	bool Connect(const char *pHost, const char *pUserName, const char *pPassword, const char *pDBName);

	/**
	 * @fn bool SimpleQuery(const char *pQuery) const
	 * @brief �P���ȃN�G�����s
	 * @param[in] pQuery �N�G��
	 * @return ����������true��Ԃ�
	 */
	bool SimpleQuery(const char *pQuery) const;

	/**
	 * @fn CMySqlQuery CreateQuery(const char *pQuery) const
	 * @brief �N�G������
	 * @param[in] pQuery �N�G��
	 * @return �N�G���I�u�W�F�N�g
	 */
	CMySqlQuery CreateQuery(const char *pQuery) const;

	/**
	 * @fn void Disconnect()
	 * @brief �ؒf
	 */
	void Disconnect();

private:

	// MySQL�ւ̐ڑ�.
	MYSQL *pConnection;

};

}
}

#endif		// #ifndef __MYSQLCONNECTION_H__
