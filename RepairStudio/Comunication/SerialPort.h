#pragma once
#include "CnComm.h"

class CSerialPort
{
public:
	CSerialPort(void);
	virtual ~CSerialPort(void);

	/***************************** 
	* FunctionName: fnInitCom 
	* 
	* Function:初始化串口
	* param[in] nComID 串口号
	* param[in] strSetting 串口设置
	* return[BOOL] TRUE:成功 FALSE:失败
	*****************************/
	BOOL fnInitCom(INT32 nComID,CString strSetting);

	/***************************** 
	* FunctionName: fnCloseCom 
	* 
	* Function:关闭串口，默认100ms掩饰
	* param[in] dwWaitTime 延时等待时间，默认100ms
	*****************************/
	void fnCloseCom(DWORD dwWaitTime = 100);

	/**************************************** 
	* FunctionName：fnIsOpen 
	* 
	* Function：检查串口是否打开，只能检查是否打开过，无法检测串口掉线，或者被拔掉后的状态
	* return[BOOL ] TRUE:打开 FALSE:没有打开
	****************************************/
	BOOL fnIsOpen();

  /***************************** 
	* FunctionName: fnSendBytes 
	* 
	* Function:发送字节流串口命令
	* param[in] pBytes 串口命令
	* return[CString]返回字符串
	*****************************/
	int fnSendBytes(const char* pBytes, int nLength, char** pOutBytes, int nBuffLen, int& nOutLen);

	/***************************** 
	* FunctionName: fnSendCommand 
	* 
	* Function:发现ASC码串口命令
	* param[in] strCmd 串口命令
	* return[CString]返回字符串
	*****************************/
	CString fnSendASCCommand(CString strCmd);

	/***************************** 
	* FunctionName: fnSendHexCommand1 
	* 
	* Function:发送十六进制串口命令
	* param[in] cCmd 串口命令
	* return[CString]返回字符串  
	*****************************/
	CString fnSendHexCommand1(CString strCmd);

	/***************************** 
	* FunctionName: fnSendHexCommand 
	* 
	* Function:发送十六进制串口命令
	* param[in] cCmd 串口命令
	* return[CString]返回字符串
	*****************************/
	CString fnSendHexCommand(CString strCmd);

	/***************************** 
	* FunctionName: fnGetLastErr 
	* 
	* Function:获取错误信息
	* return[char*]
	*****************************/
	CString fnGetLastErr();

	/***************************** 
	* FunctionName: fnReadComData 
	* 
	* Function:实时读取串口数据
	* return[char*]
	*****************************/
	CString fnReadComData();

private:
	CnComm m_gSerialPort;
	//错误信息
	CString m_strLastErr;
};
