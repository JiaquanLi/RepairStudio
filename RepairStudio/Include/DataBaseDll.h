
#pragma once

#include "sqlite3.h"

//内部错误
#define CPPSQLITE_ERROR 1000

class AFX_EXT_CLASS CDataBaseDll : public CObject  
{
public:
	CDataBaseDll();
	virtual ~CDataBaseDll();

	/***************************** 
	* FunctionName: fnOpenDataBase 
	* 
	* Function:打开数据库
	* param[in] cFileName 数据库绝对路径 
	* return[BOOL] TRUE:成功 FALSE:失败
	*****************************/
	BOOL fnOpenDataBase(const char* cFileName);

	/***************************** 
	* FunctionName: fnCloseDataBase 
	* 
	* Function:关闭数据库
	*****************************/
	void fnCloseDataBase();

	/***************************** 
	* FunctionName: fnDataBaseIsOpen 
	* 
	* Function:检查数据库是否已经打开
	* return[BOOL] TRUE:成功 FALSE:失败
	*****************************/
	BOOL fnDataBaseIsOpen();

	/***************************** 
	* FunctionName: fnTableIsExist 
	* 
	* Function:根据表名字，检查该表是否存在
	* param[in] cTableName 表名称
	* return[BOOL] TRUE:成功 FALSE:失败
	*****************************/
	BOOL fnTableIsExist(const char* cTableName);

	/***************************** 
	* FunctionName: fnExcuteQuery 
	* 
	* Function:根据sql语句查询，为后续操作做准备
	* param[in] cQuery sql语句
	* return[sqlite3_stmt] 准备语句
	*****************************/
	sqlite3_stmt* fnExcuteQuery(const char* cQuery);

	/***************************** 
	* FunctionName: fnEOFRecord 
	* 
	* Function:判断当前记录是否到达最后一条
	* param[in] pStatement 准备语句
	* return[BOOL] TRUE:是 FALSE:否
	*****************************/
	BOOL fnEOFRecord(sqlite3_stmt *pStatement);

	/***************************** 
	* FunctionName: fnGetNextRecord 
	* 
	* param[in] pStatement 准备语句
	* Function:获取下一条记录
	*****************************/
	void fnGetNextRecord(sqlite3_stmt *pStatement);

	/***************************** 
	* FunctionName: fnGetFieldDataType 
	* 
	* Function:获取指定列的数据类型
	* param[in] pStatement 准备语句
	* param[in] nColum 列数，从0开始
	* return[int] 数据类型 SQLITE_NULL表示无数据类型
	*****************************/
	int fnGetFieldDataType(sqlite3_stmt *pStatement,int nColum);

	/***************************** 
	* FunctionName: fnGetFieldIndexFromName 
	* 
	* Function:根据字段名称获取该字段所在的列序号
	* param[in] pStatement 准备语句
	* param[in] cFileName 字段名称
	* return[int]列序号
	*****************************/
	int fnGetFieldIndexFromFieldName(sqlite3_stmt *pStatement,const char* cFileName);

	/***************************** 
	* FunctionName: fnGetFieldNameFromIndex 
	* 
	* Function:根据字段序号获取字段名称
	* param[in] pStatement 准备语句
	* param[in] nFieldIndex 字段序号
	* return[char*]字段名称
	*****************************/
	const char* fnGetFieldNameFromIndex(sqlite3_stmt *pStatement,int nFieldIndex);

	/***************************** 
	* FunctionName: fnCheckFieldIsNull 
	* 
	* Function:检查指定字段是否为空
	* param[in] pStatement 准备语句
	* param[in] nFieldIndex 字段序号
	* return[BOOL] TRUE:成功 FALSE:失败
	*****************************/
	BOOL fnCheckFieldIsNullFromIndex(sqlite3_stmt *pStatement,int nFieldIndex);

	/***************************** 
	* FunctionName: fnCheckFieldIsNullFromName 
	* 
	* Function:检查指定字段是否为空
	* param[in] pStatement 准备语句
	* param[in] cFieldName 字段名称 
	* return[BOOL] TRUE:成功 FALSE:失败
	*****************************/
	BOOL fnCheckFieldIsNullFromName(sqlite3_stmt *pStatement,const char* cFieldName);


	/***************************** 
	* FunctionName: fnGetFieldIntValue 
	* 
	* Function:根据字段序列号获取字段的整数值
	* param[in] pStatement 准备语句
	* param[in] nFieldIndex 字段序号
	* param[in] nDefaultValue 字段为空时，返回该默认值
	* return[int]该字段的整数值
	*****************************/
	int fnGetFieldIntValue(sqlite3_stmt *pStatement,int nFieldIndex,int nDefaultValue = 0);

	/***************************** 
	* FunctionName: fnGetFieldIntValue 
	* 
	* Function:根据字段名称获取字段的整数值
	* param[in] pStatement 准备语句
	* param[in] cFieldName 字段名称
	* param[in] nDefaultValue 字段为空时，返回该默认值
	* return[int]该字段的整数值
	*****************************/
	int fnGetFieldIntValue(sqlite3_stmt *pStatement,const char* cFieldName,int nDefaultValue = 0);

	/***************************** 
	* FunctionName: fnSetFieldIntValue 
	* 
	* Function:根据字段名称设置字段的整型值
	* param[in] cTableName 表的名称
	* param[in] cFieldName 字段名称
	* param[in] nValue 字段的值
	* return[BOOL]成功、失败
	*****************************/
	BOOL fnSetFieldIntValue(const char* cTableName,const char* cFieldName,int nValue);

	/***************************** 
	* FunctionName: fnSetFieldIntValue 
	* 
	* Function:根据字段名称设置字段的整型值
	* param[in] cTableName 表的名称
	* param[in] cFieldName 字段名称
	* param[in] cKeyName 关键字
	* param[in] nValue 字段的值
	* param[in] cKeyValue 关键字值
	* return[BOOL]成功、失败
	*****************************/
	BOOL fnSetFieldIntValue(const char* cTableName,const char* cFieldName,int nValue,const char* cKeyName,const char* cKeyValue);

	/***************************** 
	* FunctionName: fnGetFieldStringValue 
	* 
	* Function:根据字段序号获取字段的字符值
	* param[in] pStatement 准备语句
	* param[in] nFieldIndex 字段序号
	* param[in] cDefault 字段为空时，返回该默认值
	* return[const char*]字符串值
	*****************************/
	CString fnGetFieldStringValue(sqlite3_stmt *pStatement,int nFieldIndex,const char* cDefault = "");

	/***************************** 
	* FunctionName: fnGetFieldStringValue 
	* 
	* Function:根据字段名称获取字段的字符值
	* param[in] pStatement 准备语句
	* param[in] cFieldName 字段名称
	* param[in] cDefault 字段为空时，返回该默认值
	* return[const char*]字符串值
	*****************************/
	CString fnGetFieldStringValue(sqlite3_stmt *pStatement,const char* cFieldName,const char* cDefault = "");

	/***************************** 
	* FunctionName: fnSetFieldStringValue 
	* 
	* Function:根据字段名称设置字段的字符串值
	* param[in] cTableName 表的名称
	* param[in] cFieldName 字段名称
	* param[in] cValue 字段的值
	* return[BOOL]成功、失败
	*****************************/
	BOOL fnSetFieldStringValue(const char* cTableName,const char* cFieldName,const char* cValue);

	/***************************** 
	* FunctionName: fnSetFieldStringValue 
	* 
	* Function:根据字段名称设置字段的字符串值
	* param[in] cTableName 表的名称
	* param[in] cFieldName 字段名称
	* param[in] cValue 字段的值
	* param[in] cKeyName 关键字
	* param[in] cKeyValue 关键字值
	* return[BOOL]成功、失败
	*****************************/
	BOOL fnSetFieldStringValue(const char* cTableName,const char* cFieldName,const char* cValue,const char* cKeyName,const char* cKeyValue);

	/***************************** 
	* FunctionName: fnGetFieldDoubleValue 
	* 
	* Function:根据字段序号获取字段的浮点数值
	* param[in] pStatement 准备语句
	* param[in] nFieldIndex 字段序号
	* param[in] dbDefaultValue 字段为空时，返回该默认值
	* return[float]浮点数值
	*****************************/
	double fnGetFieldDoubleValue(sqlite3_stmt *pStatement,int nFieldIndex,double dbDefaultValue = 0.0);

	/***************************** 
	* FunctionName: fnGetFieldFloatValue 
	* 
	* Function:根据字段名称获取字段的浮点数
	* param[in] pStatement 准备语句
	* param[in] cFieldName 字段名称
	* param[in] dbDefaultValue 字段为空时，返回该默认值
	* return[double]浮点数值
	*****************************/
	double fnGetFieldDoubleValue(sqlite3_stmt *pStatement,const char* cFieldName,double dbDefaultValue = 0.0);

	/***************************** 
	* FunctionName: fnSetFieldDoubleValue 
	* 
	* Function:根据字段名称设置字段的浮点数
	* param[in] cTableName 表的名称
	* param[in] cFieldName 字段名称
	* param[in] dbValue 字段的值
	* return[BOOL]成功、失败
	*****************************/
	BOOL fnSetFieldDoubleValue(const char* cTableName,const char* cFieldName,double dbValue);

	/***************************** 
	* FunctionName: fnSetFieldDoubleValue 
	* 
	* Function:根据字段名称设置字段的浮点数
	* param[in] cTableName 表的名称
	* param[in] cFieldName 字段名称
	* param[in] dbValue 字段的值
	* param[in] cKeyName 关键字名称
	* param[in] cKeyValue 关键字的值
	* return[BOOL]成功、失败
	*****************************/
	BOOL fnSetFieldDoubleValue(const char* cTableName,const char* cFieldName,double dbValue,const char* cKeyName,const char* cKeyValue);

	/***************************** 
	* FunctionName: fnGetFieldByteValue 
	* 
	* Function:根据字段序号获取字段的二进制值
	* param[in] pStatement 准备语句
	* param[in] nFieldIndex 字段序号
	* param[in] nLength 文本长度
	* return[const unsigned char*] 二进制文本
	*****************************/
	const char* fnGetFieldByteValue(sqlite3_stmt *pStatement,int nFieldIndex,int& nLength);

	/***************************** 
	* FunctionName: fnGetFieldByteValue 
	* 
	* Function:根据字段名称获取字段的二进制值
	* param[in] pStatement 准备语句
	* param[in] cFieldName 字段名称
	* param[in] nLength 文本长度
	* return[const unsigned char*] 二进制文本
	*****************************/
    const char* fnGetFieldByteValue(sqlite3_stmt *pStatement,const char* cFieldName,int& nLength);

	/***************************** 
	* FunctionName: fnGetRecordsCount 
	* 
	* Function:获取当前查询语句查询到的记录数
	* param[in] pStatement 查询语句
	* return[int] 记录个数
	*****************************/
	int fnGetRecordsCount(sqlite3_stmt *pStatement);

	/***************************** 
	* FunctionName: fnGetRecordsCount 
	* 
	* Function:获取当前记录表的所有记录
	* param[in] cSQL 根据查询语句获得查询后的记录个数
	* return[int]记录个数
	*****************************/
	int fnGetRecordsCount(const char* cSQL);

	/***************************** 
	* FunctionName: fnSetBusyTimeOut 
	* 
	* Function:设置数据库操作超时时间，单位毫秒
	* param[in] nTimeOut 超时时间
	*****************************/
	void fnSetBusyTimeOut(int nTimeOut);

	/***************************** 
	* FunctionName: fnExcuteSQL 
	* 
	* Function:执行一条SQL语句，返回此操作影响的记录个数
	* param[in] cSQL	sql语句
	* param[in] Callback Defaults to NULL.回调函数，默认为空
	* return[int]记录个数
	*****************************/
	int fnExcuteSQL(const char* cSQL,sqlite3_callback Callback = NULL);

	/***************************** 
	* FunctionName: fnQueryDataBase 
	* 
	* Function:根据SQL查询语句获取所有查询结果
	* param[in] cSQL sql语句
	* param[in] *strResult 查询结果
	* param[out] nColums 列数
	* param[out] nRows 行数
	* return[BOOL] TRUE:成功 FALSE:失败
	*****************************/
	BOOL fnQueryDataBase(const char* cSQL,char** pResult,int &nColums,int &nRows);

    //准备
    BOOL  fnQuickInsert(const char* cSQL,CString *pData,int nRow,int nCol);

    //单纯插入指令
    BOOL fnExcuteInsert(const char* cSQL);

	//插入一条数据
	BOOL fnInsertNewData(const char* cTableName);


	/***************************** 
	* FunctionName: fnGetLastErr
	* 
	* Function:获取数据库操作的错误信息
	* return[char*] 错误信息
	*****************************/
	char * fnGetLastErr();

	/***************************** 
	* FunctionName: fnFinalize 
	* 
	* Function:销毁准备语句
	* param[in] pStatement 
	*****************************/
	void fnFinalize(sqlite3_stmt* pStatement);

	/***************************** 
	* FunctionName: fnUpdateTable 
	* 
	* Function:刷新数据表，得到准备语句
	* param[in] cTableName 数据表名称
	* return[sqlite3_stmt*]准备语句
	*****************************/
	sqlite3_stmt* fnUpdateTable(const char* cTableName);
	
	//获取当前数据库中所有表的名称,只能获取当前打开的数据库
	BOOL fnGetTablesName(CStringArray &caTableNames);

	//获取列的个数
	int fnGetColumCount(sqlite3_stmt *pStatement);

	//获取表指定列的名称
	const char * fnGetColumName(sqlite3_stmt *pStatement,int nColumIndex = 0);

	//获取表指定列的类型
	const char * fnGetColumType(sqlite3_stmt *pStatement,int nColumIndex = 0);

private:
	/***************************** 
	* FunctionName: fnErrorParase 
	* 
	* Function根据错误ID解析成具体的错误信息
	* param[in] nErrorCode 错误ID号
	* param[in] cErrMsg 错误信息，默认通过SQLITE3自身获取
	*****************************/
	void fnErrorParase(int nErrorCode,const char* cErrMsg = NULL);

private:
	//数据库对象
	sqlite3* m_pDataBase;
	//是否最后一行
    BOOL m_bEof;
	//超时时间
	int m_nBusyTimeoutMs;
	//错误信息
	CString  m_strLastErr;
	//SQL语句
	CString	 m_strSQL;
};
