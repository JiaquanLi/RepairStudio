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
* Function:��ʼ������
* param[in] nComID ���ں�
* param[in] strSetting ��������
* return[BOOL] TRUE:�ɹ� FALSE:ʧ��
*****************************/
BOOL CSerialPort::fnInitCom(INT32 nComID,CString strSetting)
{
	//������ڴ򿪣��ȹر�
	if (fnIsOpen())
	{
		fnCloseCom();
		Sleep(200);
	}

	//��ʼ������
	m_gSerialPort.SetOption(0);//��ͨ������ģʽ
	
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
* Function:�رմ��ڣ�Ĭ��100ms����
* param[in] dwWaitTime ��ʱ�ȴ�ʱ�䣬Ĭ��100ms
*****************************/
void CSerialPort::fnCloseCom(DWORD dwWaitTime)
{
	m_gSerialPort.Close(dwWaitTime);
}

/**************************************** 
* FunctionName��fnIsOpen 
* 
* Function����鴮���Ƿ�򿪣�ֻ�ܼ���Ƿ�򿪹����޷���⴮�ڵ��ߣ����߱��ε����״̬
* return[BOOL ] TRUE:�� FALSE:û�д�
****************************************/
BOOL CSerialPort::fnIsOpen()
{
	//�˴�ֻ�Ǽ򵥵��ã�ֻ�ܼ���Ƿ�򿪹����޷���⴮�ڵ��ߣ����߱��ε����״̬
	return m_gSerialPort.IsOpen();
}

/***************************** 
* FunctionName: fnSendBytes 
* 
* Function:�����ֽ�����������
* param[in] pBytes ��������
* return[CString] �����ֽ���
*****************************/
int CSerialPort::fnSendBytes(const char* pBytes, int nLength, char** pOutBytes, int nBuffLen, int& nOutLen)
{
  if (!m_gSerialPort.IsOpen() || NULL == *pOutBytes)
  {
    return -1;
  }

  nOutLen = 0;

  //���ʹ�������
  int nSendByteNum = m_gSerialPort.Write(pBytes, nLength);
  if (nSendByteNum != nLength)
  {
    return -1;
  }

  Sleep(50);

  //��ȡ����ֵ
  nOutLen = m_gSerialPort.Read((void*)*pOutBytes, nBuffLen, 0);

  //����ֵ
  return nOutLen > 0 ? 0 : -1;
}

/***************************** 
* FunctionName: fnSendCommand 
* 
* Function:����ASC�봮������
* param[in] strCmd ��������
* return[CString]�����ַ���
*****************************/
CString CSerialPort::fnSendASCCommand(CString strCmd)
{
	DWORD dwszSize = 0;
	CString strRes = "";

	//���ʹ�������
	dwszSize = m_gSerialPort.Write(strCmd);

	Sleep(50);
	
	TCHAR szBuffer[256] = {0};

	//��ȡ����ֵ
	if (0 < dwszSize)
	{
		m_gSerialPort.ReadString(szBuffer,256,0);
		strRes = szBuffer;
	}
	
	//ȥ���ո���س�����
	strRes.Remove(' ');
	strRes.Remove('\r');
	strRes.Remove('\n');
	
	//����ֵ
	return strRes;
}

/***************************** 
* FunctionName: fnSendHexCommand 
* 
* Function:����ʮ�����ƴ�������
* param[in] strCmd ��������
* return[CString]�����ַ���
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

	//ת��Ϊʮ�������ַ���
	for (int i = 0; i < nLen; i = i + 2)
	{
		TCHAR cFirst = strTemp.GetAt(i);
		TCHAR cSecond = strTemp.GetAt(i + 1);		
		int ascDec = fnHexCharToDec(cFirst)*16 + fnHexCharToDec(cSecond);	

		*(szBuffer+nCharIndex) = ascDec;

		nCharIndex++;
	}

	//��������
	dwszSize = m_gSerialPort.Write(szBuffer,nCharIndex);

	Sleep(50);

	ZeroMemory(szBuffer, 256);
	//��ȡ����ֵ
	if (0 < dwszSize)
	{
		dwszSize = m_gSerialPort.ReadString(szBuffer,256,INFINITE);
	}

	for(int i=0; i<dwszSize; i++)
	{
		strTemp.Format("%02X", szBuffer[i]);
		strRes = strRes + strTemp.Mid(strTemp.GetLength()-2, 2);
	}

	//ȥ���ո���س�����
	strRes.Remove(' ');
	strRes.Remove('\r');
	strRes.Remove('\n');

	//����ֵ
	return strRes;
}

/***************************** 
* FunctionName: fnSendHexCommand 
* 
* Function:����ʮ�����ƴ�������
* param[in] strCmd ��������
* return[CString]�����ַ���
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

	//ת��Ϊʮ�������ַ���
	for (int i = 0; i < nLen; i = i + 2)
	{
		TCHAR cFirst = strTemp.GetAt(i);
		TCHAR cSecond = strTemp.GetAt(i + 1);		
		int ascDec = fnHexCharToDec(cFirst)*16 + fnHexCharToDec(cSecond);	
		
		*(szBuffer+nCharIndex) = ascDec;

		nCharIndex++;
	}
	
	//��������
	dwszSize = m_gSerialPort.Write(szBuffer,nCharIndex);

	Sleep(50);
	
	//��ȡ����ֵ
	if (0 < dwszSize)
	{
		m_gSerialPort.ReadString(szBuffer,256,0);
		strRes = szBuffer;
	}
	
	//ȥ���ո���س�����
	strRes.Remove(' ');
	strRes.Remove('\r');
	strRes.Remove('\n');
	
	//����ֵ
	return strRes;
}


/***************************** 
* FunctionName: fnGetLastErr 
* 
* Function:��ȡ������Ϣ
* return[char*]
*****************************/
CString CSerialPort::fnGetLastErr()
{
	return m_strLastErr;
}

/***************************** 
	* FunctionName: fnReadComData 
	* 
	* Function:ʵʱ��ȡ��������
	* return[char*]
	*****************************/
CString CSerialPort::fnReadComData()
{
	TCHAR szBuffer[256] = {0};
	CString strRes;

	m_gSerialPort.ReadString(szBuffer,256,0);
	strRes = szBuffer;
	

	//ȥ���ո���س�����
	strRes.Remove(' ');
	strRes.Remove('\r');
	strRes.Remove('\n');

	//����ֵ
	return strRes;
}