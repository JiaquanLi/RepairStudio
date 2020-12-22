#include "StdAfx.h"
#include "SerialPort.h"

CSerialPort::CSerialPort(void)
{
}

CSerialPort::~CSerialPort(void)
{
	fnCloseCom();
}
/***************************** 
* FunctionName: fnInitCom 
* 
* Function:初始化串口
* param[in] nComID 串口号
* param[in] strSetting 串口设置
* return[BOOL] TRUE:成功 FALSE:失败
*****************************/
BOOL CSerialPort::fnInitCom(INT32 nComID,CString strSetting)
{
	//如果串口打开，先关闭
	if (fnIsOpen())
	{
		fnCloseCom();
		Sleep(200);
	}

	//初始化串口
	m_gSerialPort.SetOption(0);//普通的阻塞模式
	
	try
	{
		if(m_gSerialPort.Open(nComID,strSetting))
		{
			return TRUE;
		}
		else
		{
			m_strLastErr.Format(_T("Open serial port%dfailed"),nComID);
			return FALSE;
		}
	}
	catch (...)
	{
		m_strLastErr.Format(_T("Open serial port%dfailed"),nComID);
		return FALSE;
	}
}

/***************************** 
* FunctionName: fnCloseCom 
* 
* Function:关闭串口，默认100ms掩饰
* param[in] dwWaitTime 延时等待时间，默认100ms
*****************************/
void CSerialPort::fnCloseCom(DWORD dwWaitTime)
{
	m_gSerialPort.Close(dwWaitTime);
}

/**************************************** 
* FunctionName：fnIsOpen 
* 
* Function：检查串口是否打开，只能检查是否打开过，无法检测串口掉线，或者被拔掉后的状态
* return[BOOL ] TRUE:打开 FALSE:没有打开
****************************************/
BOOL CSerialPort::fnIsOpen()
{
	//此处只是简单调用，只能检查是否打开过，无法检测串口掉线，或者被拔掉后的状态
	return m_gSerialPort.IsOpen();
}

/***************************** 
* FunctionName: fnSendBytes 
* 
* Function:发送字节流串口命令
* param[in] pBytes 串口命令
* return[CString] 返回字节流
*****************************/
int CSerialPort::fnSendBytes(const char* pBytes, int nLength, char** pOutBytes, int nBuffLen, int& nOutLen)
{
  if (!m_gSerialPort.IsOpen() || NULL == *pOutBytes)
  {
    return -1;
  }

  nOutLen = 0;

  //发送串口命令
  int nSendByteNum = m_gSerialPort.Write(pBytes, nLength);
  if (nSendByteNum != nLength)
  {
    return -1;
  }

  Sleep(50);

  //读取返回值
  nOutLen = m_gSerialPort.Read((void*)*pOutBytes, nBuffLen, 0);

  //返回值
  return nOutLen > 0 ? 0 : -1;
}

/***************************** 
* FunctionName: fnSendCommand 
* 
* Function:发现ASC码串口命令
* param[in] strCmd 串口命令
* return[CString]返回字符串
*****************************/
CString CSerialPort::fnSendASCCommand(CString strCmd)
{
	DWORD dwszSize = 0;
	CString strRes = "";

	//发送串口命令
	dwszSize = m_gSerialPort.Write(strCmd);

	Sleep(50);
	
	TCHAR szBuffer[256] = {0};

	//读取返回值
	if (0 < dwszSize)
	{
		m_gSerialPort.ReadString(szBuffer,256,0);
		strRes = szBuffer;
	}
	
	//去掉空格与回车换行
	strRes.Remove(' ');
	strRes.Remove('\r');
	strRes.Remove('\n');
	
	//返回值
	return strRes;
}

/***************************** 
* FunctionName: fnSendHexCommand 
* 
* Function:发送十六进制串口命令
* param[in] strCmd 串口命令
* return[CString]返回字符串
*****************************/

CString CSerialPort::fnSendHexCommand1(CString strCmd)
{
	DWORD dwszSize = 0;
	int nCharIndex = 0;
	TCHAR szBuffer[256] = {0};
	CString strTemp = strCmd;
	CString strRes;
	strTemp.Remove(' ');
	int nLen = strTemp.GetLength();

	//转换为十六进制字符串
	for (int i = 0; i < nLen; i = i + 2)
	{
		TCHAR cFirst = strTemp.GetAt(i);
		TCHAR cSecond = strTemp.GetAt(i + 1);		
		int ascDec = fnHexCharToDec(cFirst)*16 + fnHexCharToDec(cSecond);	

		*(szBuffer+nCharIndex) = ascDec;

		nCharIndex++;
	}

	//发送命令
	dwszSize = m_gSerialPort.Write(szBuffer,nCharIndex);

	Sleep(50);

	ZeroMemory(szBuffer, 256);
	//读取返回值
	if (0 < dwszSize)
	{
		dwszSize = m_gSerialPort.ReadString(szBuffer,256,INFINITE);
	}

	for(int i=0; i<dwszSize; i++)
	{
		strTemp.Format("%02X", szBuffer[i]);
		strRes = strRes + strTemp.Mid(strTemp.GetLength()-2, 2);
	}

	//去掉空格与回车换行
	strRes.Remove(' ');
	strRes.Remove('\r');
	strRes.Remove('\n');

	//返回值
	return strRes;
}

/***************************** 
* FunctionName: fnSendHexCommand 
* 
* Function:发送十六进制串口命令
* param[in] strCmd 串口命令
* return[CString]返回字符串
*****************************/
CString CSerialPort::fnSendHexCommand(CString strCmd)
{
	DWORD dwszSize = 0;
	int nCharIndex = 0;
	TCHAR szBuffer[256] = {0};
	CString strTemp = strCmd;
	CString strRes;
	strTemp.Remove(' ');
	int nLen = strTemp.GetLength();

	//转换为十六进制字符串
	for (int i = 0; i < nLen; i = i + 2)
	{
		TCHAR cFirst = strTemp.GetAt(i);
		TCHAR cSecond = strTemp.GetAt(i + 1);		
		int ascDec = fnHexCharToDec(cFirst)*16 + fnHexCharToDec(cSecond);	
		
		*(szBuffer+nCharIndex) = ascDec;

		nCharIndex++;
	}
	
	//发送命令
	dwszSize = m_gSerialPort.Write(szBuffer,nCharIndex);

	Sleep(50);
	
	//读取返回值
	if (0 < dwszSize)
	{
		m_gSerialPort.ReadString(szBuffer,256,0);
		strRes = szBuffer;
	}
	
	//去掉空格与回车换行
	strRes.Remove(' ');
	strRes.Remove('\r');
	strRes.Remove('\n');
	
	//返回值
	return strRes;
}


/***************************** 
* FunctionName: fnGetLastErr 
* 
* Function:获取错误信息
* return[char*]
*****************************/
CString CSerialPort::fnGetLastErr()
{
	return m_strLastErr;
}

/***************************** 
	* FunctionName: fnReadComData 
	* 
	* Function:实时读取串口数据
	* return[char*]
	*****************************/
CString CSerialPort::fnReadComData()
{
	TCHAR szBuffer[256] = {0};
	CString strRes;

	m_gSerialPort.ReadString(szBuffer,256,0);
	strRes = szBuffer;
	

	//去掉空格与回车换行
	strRes.Remove(' ');
	strRes.Remove('\r');
	strRes.Remove('\n');

	//返回值
	return strRes;
}