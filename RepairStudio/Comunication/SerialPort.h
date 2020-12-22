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
	* Function:��ʼ������
	* param[in] nComID ���ں�
	* param[in] strSetting ��������
	* return[BOOL] TRUE:�ɹ� FALSE:ʧ��
	*****************************/
	BOOL fnInitCom(INT32 nComID,CString strSetting);

	/***************************** 
	* FunctionName: fnCloseCom 
	* 
	* Function:�رմ��ڣ�Ĭ��100ms����
	* param[in] dwWaitTime ��ʱ�ȴ�ʱ�䣬Ĭ��100ms
	*****************************/
	void fnCloseCom(DWORD dwWaitTime = 100);

	/**************************************** 
	* FunctionName��fnIsOpen 
	* 
	* Function����鴮���Ƿ�򿪣�ֻ�ܼ���Ƿ�򿪹����޷���⴮�ڵ��ߣ����߱��ε����״̬
	* return[BOOL ] TRUE:�� FALSE:û�д�
	****************************************/
	BOOL fnIsOpen();

  /***************************** 
	* FunctionName: fnSendBytes 
	* 
	* Function:�����ֽ�����������
	* param[in] pBytes ��������
	* return[CString]�����ַ���
	*****************************/
	int fnSendBytes(const char* pBytes, int nLength, char** pOutBytes, int nBuffLen, int& nOutLen);

	/***************************** 
	* FunctionName: fnSendCommand 
	* 
	* Function:����ASC�봮������
	* param[in] strCmd ��������
	* return[CString]�����ַ���
	*****************************/
	CString fnSendASCCommand(CString strCmd);

	/***************************** 
	* FunctionName: fnSendHexCommand1 
	* 
	* Function:����ʮ�����ƴ�������
	* param[in] cCmd ��������
	* return[CString]�����ַ���  
	*****************************/
	CString fnSendHexCommand1(CString strCmd);

	/***************************** 
	* FunctionName: fnSendHexCommand 
	* 
	* Function:����ʮ�����ƴ�������
	* param[in] cCmd ��������
	* return[CString]�����ַ���
	*****************************/
	CString fnSendHexCommand(CString strCmd);

	/***************************** 
	* FunctionName: fnGetLastErr 
	* 
	* Function:��ȡ������Ϣ
	* return[char*]
	*****************************/
	CString fnGetLastErr();

	/***************************** 
	* FunctionName: fnReadComData 
	* 
	* Function:ʵʱ��ȡ��������
	* return[char*]
	*****************************/
	CString fnReadComData();

private:
	CnComm m_gSerialPort;
	//������Ϣ
	CString m_strLastErr;
};
