
#pragma once

#include "sqlite3.h"

//�ڲ�����
#define CPPSQLITE_ERROR 1000

class AFX_EXT_CLASS CDataBaseDll : public CObject  
{
public:
	CDataBaseDll();
	virtual ~CDataBaseDll();

	/***************************** 
	* FunctionName: fnOpenDataBase 
	* 
	* Function:�����ݿ�
	* param[in] cFileName ���ݿ����·�� 
	* return[BOOL] TRUE:�ɹ� FALSE:ʧ��
	*****************************/
	BOOL fnOpenDataBase(const char* cFileName);

	/***************************** 
	* FunctionName: fnCloseDataBase 
	* 
	* Function:�ر����ݿ�
	*****************************/
	void fnCloseDataBase();

	/***************************** 
	* FunctionName: fnDataBaseIsOpen 
	* 
	* Function:������ݿ��Ƿ��Ѿ���
	* return[BOOL] TRUE:�ɹ� FALSE:ʧ��
	*****************************/
	BOOL fnDataBaseIsOpen();

	/***************************** 
	* FunctionName: fnTableIsExist 
	* 
	* Function:���ݱ����֣����ñ��Ƿ����
	* param[in] cTableName ������
	* return[BOOL] TRUE:�ɹ� FALSE:ʧ��
	*****************************/
	BOOL fnTableIsExist(const char* cTableName);

	/***************************** 
	* FunctionName: fnExcuteQuery 
	* 
	* Function:����sql����ѯ��Ϊ����������׼��
	* param[in] cQuery sql���
	* return[sqlite3_stmt] ׼�����
	*****************************/
	sqlite3_stmt* fnExcuteQuery(const char* cQuery);

	/***************************** 
	* FunctionName: fnEOFRecord 
	* 
	* Function:�жϵ�ǰ��¼�Ƿ񵽴����һ��
	* param[in] pStatement ׼�����
	* return[BOOL] TRUE:�� FALSE:��
	*****************************/
	BOOL fnEOFRecord(sqlite3_stmt *pStatement);

	/***************************** 
	* FunctionName: fnGetNextRecord 
	* 
	* param[in] pStatement ׼�����
	* Function:��ȡ��һ����¼
	*****************************/
	void fnGetNextRecord(sqlite3_stmt *pStatement);

	/***************************** 
	* FunctionName: fnGetFieldDataType 
	* 
	* Function:��ȡָ���е���������
	* param[in] pStatement ׼�����
	* param[in] nColum ��������0��ʼ
	* return[int] �������� SQLITE_NULL��ʾ����������
	*****************************/
	int fnGetFieldDataType(sqlite3_stmt *pStatement,int nColum);

	/***************************** 
	* FunctionName: fnGetFieldIndexFromName 
	* 
	* Function:�����ֶ����ƻ�ȡ���ֶ����ڵ������
	* param[in] pStatement ׼�����
	* param[in] cFileName �ֶ�����
	* return[int]�����
	*****************************/
	int fnGetFieldIndexFromFieldName(sqlite3_stmt *pStatement,const char* cFileName);

	/***************************** 
	* FunctionName: fnGetFieldNameFromIndex 
	* 
	* Function:�����ֶ���Ż�ȡ�ֶ�����
	* param[in] pStatement ׼�����
	* param[in] nFieldIndex �ֶ����
	* return[char*]�ֶ�����
	*****************************/
	const char* fnGetFieldNameFromIndex(sqlite3_stmt *pStatement,int nFieldIndex);

	/***************************** 
	* FunctionName: fnCheckFieldIsNull 
	* 
	* Function:���ָ���ֶ��Ƿ�Ϊ��
	* param[in] pStatement ׼�����
	* param[in] nFieldIndex �ֶ����
	* return[BOOL] TRUE:�ɹ� FALSE:ʧ��
	*****************************/
	BOOL fnCheckFieldIsNullFromIndex(sqlite3_stmt *pStatement,int nFieldIndex);

	/***************************** 
	* FunctionName: fnCheckFieldIsNullFromName 
	* 
	* Function:���ָ���ֶ��Ƿ�Ϊ��
	* param[in] pStatement ׼�����
	* param[in] cFieldName �ֶ����� 
	* return[BOOL] TRUE:�ɹ� FALSE:ʧ��
	*****************************/
	BOOL fnCheckFieldIsNullFromName(sqlite3_stmt *pStatement,const char* cFieldName);


	/***************************** 
	* FunctionName: fnGetFieldIntValue 
	* 
	* Function:�����ֶ����кŻ�ȡ�ֶε�����ֵ
	* param[in] pStatement ׼�����
	* param[in] nFieldIndex �ֶ����
	* param[in] nDefaultValue �ֶ�Ϊ��ʱ�����ظ�Ĭ��ֵ
	* return[int]���ֶε�����ֵ
	*****************************/
	int fnGetFieldIntValue(sqlite3_stmt *pStatement,int nFieldIndex,int nDefaultValue = 0);

	/***************************** 
	* FunctionName: fnGetFieldIntValue 
	* 
	* Function:�����ֶ����ƻ�ȡ�ֶε�����ֵ
	* param[in] pStatement ׼�����
	* param[in] cFieldName �ֶ�����
	* param[in] nDefaultValue �ֶ�Ϊ��ʱ�����ظ�Ĭ��ֵ
	* return[int]���ֶε�����ֵ
	*****************************/
	int fnGetFieldIntValue(sqlite3_stmt *pStatement,const char* cFieldName,int nDefaultValue = 0);

	/***************************** 
	* FunctionName: fnSetFieldIntValue 
	* 
	* Function:�����ֶ����������ֶε�����ֵ
	* param[in] cTableName �������
	* param[in] cFieldName �ֶ�����
	* param[in] nValue �ֶε�ֵ
	* return[BOOL]�ɹ���ʧ��
	*****************************/
	BOOL fnSetFieldIntValue(const char* cTableName,const char* cFieldName,int nValue);

	/***************************** 
	* FunctionName: fnSetFieldIntValue 
	* 
	* Function:�����ֶ����������ֶε�����ֵ
	* param[in] cTableName �������
	* param[in] cFieldName �ֶ�����
	* param[in] cKeyName �ؼ���
	* param[in] nValue �ֶε�ֵ
	* param[in] cKeyValue �ؼ���ֵ
	* return[BOOL]�ɹ���ʧ��
	*****************************/
	BOOL fnSetFieldIntValue(const char* cTableName,const char* cFieldName,int nValue,const char* cKeyName,const char* cKeyValue);

	/***************************** 
	* FunctionName: fnGetFieldStringValue 
	* 
	* Function:�����ֶ���Ż�ȡ�ֶε��ַ�ֵ
	* param[in] pStatement ׼�����
	* param[in] nFieldIndex �ֶ����
	* param[in] cDefault �ֶ�Ϊ��ʱ�����ظ�Ĭ��ֵ
	* return[const char*]�ַ���ֵ
	*****************************/
	CString fnGetFieldStringValue(sqlite3_stmt *pStatement,int nFieldIndex,const char* cDefault = "");

	/***************************** 
	* FunctionName: fnGetFieldStringValue 
	* 
	* Function:�����ֶ����ƻ�ȡ�ֶε��ַ�ֵ
	* param[in] pStatement ׼�����
	* param[in] cFieldName �ֶ�����
	* param[in] cDefault �ֶ�Ϊ��ʱ�����ظ�Ĭ��ֵ
	* return[const char*]�ַ���ֵ
	*****************************/
	CString fnGetFieldStringValue(sqlite3_stmt *pStatement,const char* cFieldName,const char* cDefault = "");

	/***************************** 
	* FunctionName: fnSetFieldStringValue 
	* 
	* Function:�����ֶ����������ֶε��ַ���ֵ
	* param[in] cTableName �������
	* param[in] cFieldName �ֶ�����
	* param[in] cValue �ֶε�ֵ
	* return[BOOL]�ɹ���ʧ��
	*****************************/
	BOOL fnSetFieldStringValue(const char* cTableName,const char* cFieldName,const char* cValue);

	/***************************** 
	* FunctionName: fnSetFieldStringValue 
	* 
	* Function:�����ֶ����������ֶε��ַ���ֵ
	* param[in] cTableName �������
	* param[in] cFieldName �ֶ�����
	* param[in] cValue �ֶε�ֵ
	* param[in] cKeyName �ؼ���
	* param[in] cKeyValue �ؼ���ֵ
	* return[BOOL]�ɹ���ʧ��
	*****************************/
	BOOL fnSetFieldStringValue(const char* cTableName,const char* cFieldName,const char* cValue,const char* cKeyName,const char* cKeyValue);

	/***************************** 
	* FunctionName: fnGetFieldDoubleValue 
	* 
	* Function:�����ֶ���Ż�ȡ�ֶεĸ�����ֵ
	* param[in] pStatement ׼�����
	* param[in] nFieldIndex �ֶ����
	* param[in] dbDefaultValue �ֶ�Ϊ��ʱ�����ظ�Ĭ��ֵ
	* return[float]������ֵ
	*****************************/
	double fnGetFieldDoubleValue(sqlite3_stmt *pStatement,int nFieldIndex,double dbDefaultValue = 0.0);

	/***************************** 
	* FunctionName: fnGetFieldFloatValue 
	* 
	* Function:�����ֶ����ƻ�ȡ�ֶεĸ�����
	* param[in] pStatement ׼�����
	* param[in] cFieldName �ֶ�����
	* param[in] dbDefaultValue �ֶ�Ϊ��ʱ�����ظ�Ĭ��ֵ
	* return[double]������ֵ
	*****************************/
	double fnGetFieldDoubleValue(sqlite3_stmt *pStatement,const char* cFieldName,double dbDefaultValue = 0.0);

	/***************************** 
	* FunctionName: fnSetFieldDoubleValue 
	* 
	* Function:�����ֶ����������ֶεĸ�����
	* param[in] cTableName �������
	* param[in] cFieldName �ֶ�����
	* param[in] dbValue �ֶε�ֵ
	* return[BOOL]�ɹ���ʧ��
	*****************************/
	BOOL fnSetFieldDoubleValue(const char* cTableName,const char* cFieldName,double dbValue);

	/***************************** 
	* FunctionName: fnSetFieldDoubleValue 
	* 
	* Function:�����ֶ����������ֶεĸ�����
	* param[in] cTableName �������
	* param[in] cFieldName �ֶ�����
	* param[in] dbValue �ֶε�ֵ
	* param[in] cKeyName �ؼ�������
	* param[in] cKeyValue �ؼ��ֵ�ֵ
	* return[BOOL]�ɹ���ʧ��
	*****************************/
	BOOL fnSetFieldDoubleValue(const char* cTableName,const char* cFieldName,double dbValue,const char* cKeyName,const char* cKeyValue);

	/***************************** 
	* FunctionName: fnGetFieldByteValue 
	* 
	* Function:�����ֶ���Ż�ȡ�ֶεĶ�����ֵ
	* param[in] pStatement ׼�����
	* param[in] nFieldIndex �ֶ����
	* param[in] nLength �ı�����
	* return[const unsigned char*] �������ı�
	*****************************/
	const char* fnGetFieldByteValue(sqlite3_stmt *pStatement,int nFieldIndex,int& nLength);

	/***************************** 
	* FunctionName: fnGetFieldByteValue 
	* 
	* Function:�����ֶ����ƻ�ȡ�ֶεĶ�����ֵ
	* param[in] pStatement ׼�����
	* param[in] cFieldName �ֶ�����
	* param[in] nLength �ı�����
	* return[const unsigned char*] �������ı�
	*****************************/
    const char* fnGetFieldByteValue(sqlite3_stmt *pStatement,const char* cFieldName,int& nLength);

	/***************************** 
	* FunctionName: fnGetRecordsCount 
	* 
	* Function:��ȡ��ǰ��ѯ����ѯ���ļ�¼��
	* param[in] pStatement ��ѯ���
	* return[int] ��¼����
	*****************************/
	int fnGetRecordsCount(sqlite3_stmt *pStatement);

	/***************************** 
	* FunctionName: fnGetRecordsCount 
	* 
	* Function:��ȡ��ǰ��¼������м�¼
	* param[in] cSQL ���ݲ�ѯ����ò�ѯ��ļ�¼����
	* return[int]��¼����
	*****************************/
	int fnGetRecordsCount(const char* cSQL);

	/***************************** 
	* FunctionName: fnSetBusyTimeOut 
	* 
	* Function:�������ݿ������ʱʱ�䣬��λ����
	* param[in] nTimeOut ��ʱʱ��
	*****************************/
	void fnSetBusyTimeOut(int nTimeOut);

	/***************************** 
	* FunctionName: fnExcuteSQL 
	* 
	* Function:ִ��һ��SQL��䣬���ش˲���Ӱ��ļ�¼����
	* param[in] cSQL	sql���
	* param[in] Callback Defaults to NULL.�ص�������Ĭ��Ϊ��
	* return[int]��¼����
	*****************************/
	int fnExcuteSQL(const char* cSQL,sqlite3_callback Callback = NULL);

	/***************************** 
	* FunctionName: fnQueryDataBase 
	* 
	* Function:����SQL��ѯ����ȡ���в�ѯ���
	* param[in] cSQL sql���
	* param[in] *strResult ��ѯ���
	* param[out] nColums ����
	* param[out] nRows ����
	* return[BOOL] TRUE:�ɹ� FALSE:ʧ��
	*****************************/
	BOOL fnQueryDataBase(const char* cSQL,char** pResult,int &nColums,int &nRows);

    //׼��
    BOOL  fnQuickInsert(const char* cSQL,CString *pData,int nRow,int nCol);

    //��������ָ��
    BOOL fnExcuteInsert(const char* cSQL);

	//����һ������
	BOOL fnInsertNewData(const char* cTableName);


	/***************************** 
	* FunctionName: fnGetLastErr
	* 
	* Function:��ȡ���ݿ�����Ĵ�����Ϣ
	* return[char*] ������Ϣ
	*****************************/
	char * fnGetLastErr();

	/***************************** 
	* FunctionName: fnFinalize 
	* 
	* Function:����׼�����
	* param[in] pStatement 
	*****************************/
	void fnFinalize(sqlite3_stmt* pStatement);

	/***************************** 
	* FunctionName: fnUpdateTable 
	* 
	* Function:ˢ�����ݱ��õ�׼�����
	* param[in] cTableName ���ݱ�����
	* return[sqlite3_stmt*]׼�����
	*****************************/
	sqlite3_stmt* fnUpdateTable(const char* cTableName);
	
	//��ȡ��ǰ���ݿ������б������,ֻ�ܻ�ȡ��ǰ�򿪵����ݿ�
	BOOL fnGetTablesName(CStringArray &caTableNames);

	//��ȡ�еĸ���
	int fnGetColumCount(sqlite3_stmt *pStatement);

	//��ȡ��ָ���е�����
	const char * fnGetColumName(sqlite3_stmt *pStatement,int nColumIndex = 0);

	//��ȡ��ָ���е�����
	const char * fnGetColumType(sqlite3_stmt *pStatement,int nColumIndex = 0);

private:
	/***************************** 
	* FunctionName: fnErrorParase 
	* 
	* Function���ݴ���ID�����ɾ���Ĵ�����Ϣ
	* param[in] nErrorCode ����ID��
	* param[in] cErrMsg ������Ϣ��Ĭ��ͨ��SQLITE3�����ȡ
	*****************************/
	void fnErrorParase(int nErrorCode,const char* cErrMsg = NULL);

private:
	//���ݿ����
	sqlite3* m_pDataBase;
	//�Ƿ����һ��
    BOOL m_bEof;
	//��ʱʱ��
	int m_nBusyTimeoutMs;
	//������Ϣ
	CString  m_strLastErr;
	//SQL���
	CString	 m_strSQL;
};
