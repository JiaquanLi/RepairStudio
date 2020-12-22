#include "StdAfx.h"
#include "MXComponent.h"

CRITICAL_SECTION g_MXCritical;

CMXComponent::CMXComponent(void)
{
	InitializeCriticalSection(&g_MXCritical);
}

CMXComponent::~CMXComponent(void)
{
	DeleteCriticalSection(&g_MXCritical);
}

//�󶨿ؼ�
void CMXComponent::fnBindMXComponent(CActutltype1 *pMXControl)
{
	::EnterCriticalSection(&g_MXCritical);
	if (NULL != pMXControl)
	{
		m_pMXControl = pMXControl;
	}
	::LeaveCriticalSection(&g_MXCritical);
}

//����PLC
BOOL CMXComponent::fnConnectToPLC(int nStationNum)
{
	::EnterCriticalSection(&g_MXCritical);
	if (m_bConnected)
	{
		fnDisconnect();
	}
	
	if (NULL == m_pMXControl)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError = "MXComponent object is null";
		m_bConnected = FALSE;
		return FALSE;
	}

	//���ö˿�
	m_pMXControl->put_ActLogicalStationNumber(nStationNum);

	//����
	long lRet = m_pMXControl->Open();

	if (0 != lRet)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_bConnected = FALSE;
		m_strLastError = "open failed";
		return FALSE;
	}
	else
	{
		m_bConnected = TRUE;
	}

	::LeaveCriticalSection(&g_MXCritical);
	return m_bConnected;
}

//�Ͽ�����
void CMXComponent::fnDisconnect()
{
	::EnterCriticalSection(&g_MXCritical);
	if (m_bConnected)
	{
		m_pMXControl->Close();
	}

	m_bConnected = FALSE;
	::LeaveCriticalSection(&g_MXCritical);
}

//�Ƿ����ӳɹ�
BOOL CMXComponent::fnIsConnected()
{
	return m_bConnected;
}

//��PLC��ȡbit����,��ȡ����Ϊ1λ
BOOL CMXComponent::fnReadBitFromPLC(CString strDevice,BOOL &bValue)
{
	::EnterCriticalSection(&g_MXCritical);
	short sValue[1];

	if (!m_bConnected)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError = "PLC is disconnected";
		return FALSE;
	}

	long lRet = m_pMXControl->ReadDeviceRandom2(strDevice,1,sValue);
	if (0 != lRet)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError.Format("Read Device %s failed",strDevice);
		return FALSE;
	}

	bValue = sValue[0] & 1;

	::LeaveCriticalSection(&g_MXCritical);
	return TRUE;
}

//��PLC��ȡbyte����,��ȡ����Ϊ1
BOOL CMXComponent::fnReadBytesFromPLC(CString strDevice,int &nValue)
{
	::EnterCriticalSection(&g_MXCritical);
	short sValue[1];

	if (!m_bConnected)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError = "PLC is disconnected";
		return FALSE;
	}

	long lRet = m_pMXControl->ReadDeviceBlock2(strDevice,1,sValue);
	if (0 != lRet)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError.Format("Read Device %s failed",strDevice);
		return FALSE;
	}

	nValue = sValue[0];

	::LeaveCriticalSection(&g_MXCritical);
	return TRUE;
}

//��PLC��ȡword����,��ȡ����Ϊ1����,2���ֽڣ��޷���
BOOL CMXComponent::fnReadWordFromPLC(CString strDevice,WORD &wValue)
{
	::EnterCriticalSection(&g_MXCritical);
	short sValue[2];

	if (!m_bConnected)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError = "PLC is disconnected";
		return FALSE;
	}

	long lRet = m_pMXControl->ReadDeviceBlock2(strDevice,2,sValue);
	if (0 != lRet)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError.Format("Read Device %s failed",strDevice);
		return FALSE;
	}
	else
	{
		CString strBinary;
		for (int i = 0; i < 2; i++)
		{
			strBinary = fnDecToBinary16(sValue[i]) + strBinary;
		}

		wValue = fnBinaryToDec(strBinary);
	}

	::LeaveCriticalSection(&g_MXCritical);
	return TRUE;
}


//��PLC��ȡint����,��ȡ����Ϊ4
BOOL CMXComponent::fnReadIntFromPLC(CString strDevice,int &nValue)
{
	::EnterCriticalSection(&g_MXCritical);
	short sValue[2];

	if (!m_bConnected)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError = "PLC is disconnected";
		return FALSE;
	}

	long lRet = m_pMXControl->ReadDeviceBlock2(strDevice,2,sValue);
	if (0 != lRet)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError.Format("Read Device %s failed",strDevice);
		return FALSE;
	}
	else
	{
		CString strBinary;
		for (int i = 0; i < 2; i++)
		{
			if (0 > sValue[i])
			{
				strBinary = fnDecToBinary16(sValue[i] - 65536) + strBinary;
			}
			else
			{
				strBinary = fnDecToBinary16(sValue[i]) + strBinary;
			}
		}

  	    nValue = fnBinaryToDec(strBinary); 
	}

	::LeaveCriticalSection(&g_MXCritical);
	return TRUE;
}

//��PLC��ȡint����,��ȡ����Ϊ4
BOOL CMXComponent::fnReadIntFromPLC(CString strDevice, int* nValue)
{
	::EnterCriticalSection(&g_MXCritical);
	short sValue[2];

	if (!m_bConnected)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError = "PLC is disconnected";
		return FALSE;
	}

	long lRet = m_pMXControl->ReadDeviceBlock2(strDevice, 2, sValue);
	if (0 != lRet)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError.Format("Read Device %s failed", strDevice);
		return FALSE;
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			nValue[i] = sValue[i];
		}
	}

	::LeaveCriticalSection(&g_MXCritical);
	return TRUE;
}

//��PLC��ȡlong����,��ȡ����Ϊ16���ֽڣ��з���
BOOL CMXComponent::fnReadLongFromPLC(CString strDevice,long &lValue)
{
	::EnterCriticalSection(&g_MXCritical);
	short sValue[4];

	if (!m_bConnected)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError = "PLC is disconnected";
		return FALSE;
	}

	long lRet = m_pMXControl->ReadDeviceBlock2(strDevice,4,sValue);
	if (0 != lRet)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError.Format("Read Device %s failed",strDevice);
		return FALSE;
	}
	else
	{
		CString strBinary;

		for (int i = 0; i < 4; i++)
		{
			strBinary = fnDecToBinary16(sValue[i]) + strBinary;
		}

		lValue = fnBinaryToDec(strBinary);

		//���λΪ1��˵��Ϊ����
		if (65535 <= sValue[3])
		{
			lValue = lValue - 4294967296;  
		}    
	}

	::LeaveCriticalSection(&g_MXCritical);
	return TRUE;
}

//��PLC��ȡFloat����,��ȡ����Ϊ8
BOOL CMXComponent::fnReadFloatFromPLC(CString strDevice,float &fValue)
{
	::EnterCriticalSection(&g_MXCritical);
	short sValue[4];

	if (!m_bConnected)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError = "PLC is disconnected";
		return FALSE;
	}

	long lRet = m_pMXControl->ReadDeviceBlock2(strDevice,8,sValue);
	if (0 != lRet)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError.Format("Read Device %s failed",strDevice);
		return FALSE;
	}
	else
	{
		CString strBinary;

		for (int i = 0; i < 4; i++)
		{
			strBinary = strBinary + fnDecToBinary8(sValue[i]);
		}

		fValue = fnBinaryToFloat(strBinary);
	}

	::LeaveCriticalSection(&g_MXCritical);
	return TRUE;
}

//��PLC��ȡstring����,��ȡ���Ȳ���
BOOL CMXComponent::fnReadStringFromPLC(CString strDevice,int nSize,CString &strValue)
{
	::EnterCriticalSection(&g_MXCritical);
	scoped_array<long> pValue(new long[nSize]);

	//�������
	strValue.Empty();

	if (!m_bConnected)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError = "PLC is disconnected";
		return FALSE;
	}

	long lRet = m_pMXControl->ReadDeviceBlock(strDevice, nSize, pValue.get());
	if (0 != lRet)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError.Format("Read Device %s failed",strDevice);
		return FALSE;
	}
	else
	{
		CString strTemp;
		for (int i = 0; i < nSize; i++)
		{
			strTemp.Format("%c%c",pValue[i]&0xFF,(pValue[i]&0xFF00) >> 8);
			strValue = strValue + strTemp;
		}
	}

	::LeaveCriticalSection(&g_MXCritical);
	return TRUE;
}

//��PLCд��bit����
BOOL CMXComponent::fnWriteBitToPLC(CString strDevice,BOOL bValue)
{
	::EnterCriticalSection(&g_MXCritical);
	short sValue[1];
	if (bValue)
	{
		sValue[0] = 1;
	}
	else
	{
		sValue[0] = 0;
	}

	if (!m_bConnected)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError = "PLC is disconnected";
		return FALSE;
	}

	long lRet = m_pMXControl->WriteDeviceRandom2(strDevice,1,sValue);
	if (0 != lRet)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError.Format("Write Device %s failed",strDevice);
		return FALSE;
	}

	::LeaveCriticalSection(&g_MXCritical);
	return TRUE;
}

//��PLCд��byte����
BOOL CMXComponent::fnWriteBytesToPLC(CString strDevice,BYTE byValue)
{
	::EnterCriticalSection(&g_MXCritical);
	short sValue[1];
	sValue[0] = byValue;

	if (!m_bConnected)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError = "PLC is disconnected";
		return FALSE;
	}

	long lRet = m_pMXControl->WriteDeviceBlock2(strDevice,1,sValue);
	if (0 != lRet)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError.Format("Write Device %s failed",strDevice);
		return FALSE;
	}
	
	::LeaveCriticalSection(&g_MXCritical);
	return TRUE;
}


//��PLCд��Word����
BOOL CMXComponent::fnWriteWordToPLC(CString strDevice,WORD wValue)
{
	::EnterCriticalSection(&g_MXCritical);
	short sValue[2];

	if (!m_bConnected)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError = "PLC is disconnected";
		return FALSE;
	}

	//��Ҫת��һ��
	CString strBinary = fnDecToBinary16(wValue);

	//ת����Ķ���������
	sValue[0] = fnBinaryToDec(strBinary.Mid(0, 16));

	long lRet = m_pMXControl->WriteDeviceBlock2(strDevice, 1, sValue);
	if (0 != lRet)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError.Format("Write Device %s failed", strDevice);
		return FALSE;
	}

	::LeaveCriticalSection(&g_MXCritical);
	return TRUE;
}

//��PLC����д��Word����
BOOL CMXComponent::fnWriteMultiWordToPLC(CString strDevice, int nSize, WORD wValue[])
{
	::EnterCriticalSection(&g_MXCritical);
	short sValue[300];
	CString strBinary;

	if (!m_bConnected)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError = "PLC is disconnected";
		return FALSE;
	}

	//��Ҫת��һ��
	for (int i = 0; i < nSize; i++)
	{
		strBinary = fnDecToBinary16(wValue[i]);
		sValue[i] = fnBinaryToDec(strBinary.Mid(0, 16));
	}

	long lRet = m_pMXControl->WriteDeviceBlock2(strDevice, nSize, sValue);
	if (0 != lRet)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError.Format("Write Device %s failed", strDevice);
		return FALSE;
	}

	::LeaveCriticalSection(&g_MXCritical);
	return TRUE;
}


BOOL CMXComponent::fnWriteMultiIntToPLC(CString strDevice, int nSize, int nValue[])
{
	::EnterCriticalSection(&g_MXCritical);
	short sValue[600];
	CString strBinary;
	int j = 0;

	if (!m_bConnected)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError = "PLC is disconnected";
		return FALSE;
	}

	//ת����Ķ���������
	for (int i = 0; i < nSize; i++)
	{
		j = i * 2;
		strBinary = fnDecToBinary32(nValue[i]);
		sValue[j] = fnBinaryToDec(strBinary.Mid(16, 16));
		sValue[j + 1] = fnBinaryToDec(strBinary.Mid(0, 16));
	}

	long lRet = m_pMXControl->WriteDeviceBlock2(strDevice, nSize * 2, sValue);
	if (0 != lRet)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError.Format("Write Device %s failed", strDevice);
		return FALSE;
	}

	::LeaveCriticalSection(&g_MXCritical);
	return TRUE;
}

//��PLCд��int����
BOOL CMXComponent::fnWriteIntToPLC(CString strDevice,int nValue)
{
	::EnterCriticalSection(&g_MXCritical);
	short sValue[2];

	if (!m_bConnected)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError = "PLC is disconnected";
		return FALSE;
	}

	//ת����Ķ���������
	CString strBinary = fnDecToBinary32(nValue);
	sValue[0] = fnBinaryToDec(strBinary.Mid(16,16));
	sValue[1] = fnBinaryToDec(strBinary.Mid(0,16));

	long lRet = m_pMXControl->WriteDeviceBlock2(strDevice,2,sValue);
	if (0 != lRet)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError.Format("Write Device %s failed",strDevice);
		return FALSE;
	}

	::LeaveCriticalSection(&g_MXCritical);
	return TRUE;
}

//��PLCд��int����
BOOL CMXComponent::fnWriteIntToPLC(CString strDevice, int* nValue)
{
	::EnterCriticalSection(&g_MXCritical);
	short sValue[2];

	if (!m_bConnected)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError = "PLC is disconnected";
		return FALSE;
	}

	//ת����Ķ���������
	for (int i =0; i < 2; i++)
	{
		sValue[i] = nValue[i];
	}
	
	long lRet = m_pMXControl->WriteDeviceBlock2(strDevice, 2, sValue);
	if (0 != lRet)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError.Format("Write Device %s failed", strDevice);
		return FALSE;
	}

	::LeaveCriticalSection(&g_MXCritical);
	return TRUE;
}

//��PLCд��long����
BOOL CMXComponent::fnWriteLongToPLC(CString strDevice,long lValue)
{
	::EnterCriticalSection(&g_MXCritical);
	short sValue[4];

	if (!m_bConnected)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError = "PLC is disconnected";
		return FALSE;
	}

	//ת����Ķ���������
	CString strBinary = fnDecToBinary64(lValue);
	for (int i = 0; i < 4; i++)
	{
		sValue[i] = fnBinaryToDec(strBinary.Mid(64 - (i + 1) * 16,16));
	}

	long lRet = m_pMXControl->WriteDeviceBlock2(strDevice,4,sValue);
	if (0 != lRet)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError.Format("Write Device %s failed",strDevice);
		return FALSE;
	}
	
	::LeaveCriticalSection(&g_MXCritical);
	return TRUE;
}

//��PLCд��float����
BOOL CMXComponent::fnWriteFloatToPLC(CString strDevice,float fValue)
{
	::EnterCriticalSection(&g_MXCritical);
	short sValue[4];

	if (!m_bConnected)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError = "PLC is disconnected";
		return FALSE;
	}

	//ת����Ķ���������
	CString strBinary = fnFloatToBinary(fValue);
	for (int i = 0; i < 4; i++)
	{
		sValue[i] = fnBinaryToDec(strBinary.Mid(i * 8,8));
	}

	long lRet = m_pMXControl->WriteDeviceBlock2(strDevice,4,sValue);
	if (0 != lRet)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError.Format("Write Device %s failed",strDevice);
		return FALSE;
	}

	::LeaveCriticalSection(&g_MXCritical);
	return TRUE;
}

//��PLCд��string����
BOOL CMXComponent::fnWriteStringToPLC(CString strDevice,CString strValue)
{
	::EnterCriticalSection(&g_MXCritical);
	int nSize = strValue.GetLength() / 2 + 1;

	scoped_array<short> pValue(new short[nSize + 1]);

	if (!m_bConnected)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError = "PLC is disconnected";
		return FALSE;
	}

	CString strTest;
	strTest = fnDecToBinary8(strValue.GetAt(1)) + fnDecToBinary8(strValue.GetAt(0));
	short nValue = fnBinaryToDec(strTest);

	for (int i = 0; i < nSize; i++)
	{
		pValue[i] = fnBinaryToDec(fnDecToBinary8(strValue.GetAt(i * 2 + 1)) + fnDecToBinary8(strValue.GetAt(i * 2)));
	}

	long lRet = m_pMXControl->WriteDeviceBlock2(strDevice, nSize, pValue.get());
	if (0 != lRet)
	{
		::LeaveCriticalSection(&g_MXCritical);
		m_strLastError.Format("Write Device %s failed", strDevice);
		return FALSE;
	}

	::LeaveCriticalSection(&g_MXCritical);
	return TRUE;
}

//��ȡ������Ϣ
CString CMXComponent::fnGetLastError()
{
	return m_strLastError;
}

double CMXComponent::fnBinaryToFloat(CString strBinary)
{
	if (strBinary.GetLength()!=32)  
	{  
		return 2;  
	}  

	//  (-1) s��ʾ����λ����s = 0��VΪ��������s = 1��VΪ������    
	//  ��2��M��ʾ��Ч���֣����ڵ���1��С��2��  
	//  ��3��2^E��ʾָ��λ��  
	//���ڵ����� ����λ 1 ָ��Ϊ8    ��Ч���� 23  
	//  ��1��E��ȫΪ0��ȫΪ1����ʱ���������Ͳ�������Ĺ����ʾ����ָ��E�ļ���ֵ��ȥ127����1023�����õ���ʵֵ���ٽ���Ч����Mǰ���ϵ�һλ��1��  
	//  ��2��EȫΪ0����ʱ����������ָ��E����1 - 127������1 - 1023������Ч����M���ټ��ϵ�һλ��1�����ǻ�ԭΪ0.xxxxxx��С������������Ϊ�˱�ʾ��0���Լ��ӽ���0�ĺ�С�����֡�  
	//  ��3��EȫΪ1����ʱ�������Ч����MȫΪ0����ʾ�����������ȡ���ڷ���λs���������Ч����M��ȫΪ0����ʾ���������һ������NaN����  
	int sign = (strBinary.GetAt(0) == '0') ? 1 : -1; 

	//�ֽ���Ч�����֣���Ϊ������E��˵�Ƚϸ��ӣ�������������ڷֽ�  
	float frac = 0.0;  
	for (int i = 9; i < strBinary.GetLength();++i)  
	{  
		frac += pow(float(2), -i + 8)*(strBinary.GetAt(i)-'0');  
	}  

	//�ֽ�ָ��λ  
	//����ȫΪ0�����  
	bool mark = true;  
	for (int i = 1; i < 9;++i)  
	{  
		if (strBinary.GetAt(i)=='1')  
		{  
			mark = false;  
			break;  
		}  
	}  
	if (mark)  
	{  
		return sign*frac*pow(float(2), 1 - 127);  
	}  
	//����ȫΪ1�����  
	mark = true;  
	for (int i = 1; i < 9;++i)  
	{  
		if (strBinary.GetAt(i)=='0')  
		{  
			mark = false;  
			break;  
		}  
	}  
	if (mark)  
	{  
		if (0.0==frac) //���MȫΪ0   
		{  
			if (1==sign)//��ô�������Ϊ1 �Ļ������ظ�����  
			{  
				return -1;  
			}  
			else //�������Ϊ0�Ļ�������������  
			{  
				return 1;  
			}  
		}  
		else         //��Ȼ�Ļ�������NAN ����һ������  
		{  
			return 2;  
		}  
	}  

	//���һ�������ָ����ȫΪ0����1  
	unsigned char p = 0;  
	for (int i = 8,Index=0; i >= 1;--i,++Index)  
	{  
		p += pow(float(2), Index)*(strBinary.GetAt(i) - '0');  
	}

	double E = pow(float(2), int(p - 127));  
	return sign*E*(1 + frac);  
}



//����λ
int CMXComponent::fnBinaryToDec(CString strBinary)
{
	//�ڴ˴������ж�һ���ַ����ж೤�ĺ���

	int size = strBinary.GetLength();

	//���ַ����Ķ���������ȡ������ȥ48��ת��Ϊint�ͣ����������µ�����binary�ڡ�

	scoped_array<int> binary(new int [size]);

	for (int i = 0; i < size; i++)
	{

		int temp = strBinary.GetAt(i) - 48;

		*(binary.get() + i) = temp;
	}

	//������������ת��Ϊʮ����

	int parseBinary = 0;

	for (int i = 0; i < size; i++)
	{
		parseBinary += pow( (*(binary.get() + i) * 2.0), (size - 1 - i) )*(*(binary.get() + i));
	}

	return parseBinary;
}

CString CMXComponent::fnFloatToBinary(float num)
{
	//  (-1) s��ʾ����λ����s = 0��VΪ��������s = 1��VΪ������    
	//  ��2��M��ʾ��Ч���֣����ڵ���1��С��2��  
	//  ��3��2^E��ʾָ��λ��  
	//���ڵ����� ����λ 1 ָ��Ϊ8    ��Ч���� 23  
	string sign = (num < 0) ? "1" : "0";  
	num = abs(num);  
	//��float�ֽ���������ֺ�С������  
	int Interger = int(num);  
	float frac = num - Interger;  
	//����ת��Ϊ�ֱ�ת��Ϊ�����Ƶ�����  
	string IntStr("");  
	string FracStr("");  
	//ת����������  
	while (Interger)  
	{  
		IntStr += (Interger % 2 + '0');  
		Interger /= 2;  
	}  
	//��ת�ַ���  
	int i = 0;  
	int j = IntStr.size() - 1;  
	while (i < j)  
	{  
		swap(IntStr[i], IntStr[j]);  
		++i;  
		--j;  
	}  
	string EStr(8, '0');             //ָ����  
	string MStr("");                //С����  
	//�ֽ�С������----����С���֣����ܻ���ַֽⲻ��ȫ�����������float�н���23λ�����Խ���ѭ��23��------���Ƕ��ڽ���С���Ĳ��֣���Ҫ�ض�һ���֣�������Ҫ����  
	for (int i = 1; i < 24+23; ++i)  
	{  
		if (frac == 0.0)       //�������0����ô�˳�ѭ��  
		{  
			break;  
		}  
		float temp = pow(float(2), -i);  
		if (frac >= temp)  
		{  
			FracStr += '1';  
			frac -= temp;  
		}  
		else  
		{  
			FracStr += '0';  
		}  
	}  
	if (num>=1.0)  
	{  
		//׼�������Ѿ�����ˣ���ʼ����ʵ�ʵĹ���
		//ƫ�� BIAS=pow(2,8-1)-1=127;  
		int Offset = IntStr.size() - 1 + 127;     
		int Index = 7;  
		//ָ����  
		while (Offset)  
		{  
			EStr[Index] = Offset % 2 + '0';  
			Offset /= 2;  
			--Index;  
		}  
		//��ôС����Ϊ;  
		MStr = IntStr.substr(1) + FracStr;  
	}  
	else  
	{  
		//�ҵ�С���ĵ�һ��1Ϊλ��  
		int Index = 0;  
		for (int i = 0; i < FracStr.size();++i)  
		{  
			if (FracStr[i]=='1')  
			{  
				Index = i + 1;  
				break;  
			}  
		}  
		unsigned char Offset = Index?(-Index + 127):0;//���С������û��1�Ļ�����ô����X.0   
		int temp = 7;  
		//ָ����  
		while (Offset)  
		{  
			EStr[temp] = Offset % 2 + '0';  
			Offset /= 2;  
			--temp;  
		}  
		//��ôС����Ϊ;  
		MStr = FracStr.substr(Index);  
	}  
	//���ַ��������  
	if (MStr.size() > 23)  
	{  
		MStr = MStr.substr(0, 23);  
	}  
	else  
	{  
		MStr.resize(23);  
		for (int i = 0; i < 23; ++i)  
		{  
			if (MStr[i] == '\0')  
			{  
				MStr[i] = '0';  
			}  
		}  
	} 

	string strRet = sign + EStr + MStr;

	return strRet.c_str();
}

CString CMXComponent::fnDecToBinary8(BYTE nValue)
{
	CString strRet,strTemp;

	if (0 <= nValue)
	{
		itoa(nValue,strRet.GetBuffer(8),2);
	}
	else
	{
		int nTemp = abs(nValue) ^ 65535;

		itoa(nTemp + 1,strRet.GetBuffer(8),2);
	}

	strTemp.Format("%08s",strRet);

	return strTemp;
}

//16λ
CString CMXComponent::fnDecToBinary16(WORD nValue)
{
	CString strRet,strTemp;

	if (0 <= nValue)
	{
		itoa(nValue,strRet.GetBuffer(16),2);
	}
	else
	{
		int nTemp = abs(nValue) ^ 65535;

		itoa(nTemp + 1,strRet.GetBuffer(16),2);
	}

	strTemp.Format("%016s",strRet);

	return strTemp;
}

//32λ
CString CMXComponent::fnDecToBinary32(int nValue)
{
	CString strRet,strTemp;

	if (0 <= nValue)
	{
		itoa(nValue,strRet.GetBuffer(32),2);
	}
	else
	{
		int nTemp = abs(nValue) ^ 65535;

		itoa(nTemp + 1,strRet.GetBuffer(32),2);
	}

	strTemp.Format("%032s",strRet);

	return strTemp;
}

//64λ
CString CMXComponent::fnDecToBinary64(INT64 nValue)
{
	CString strRet,strTemp;

	if (0 <= nValue)
	{
		itoa(nValue,strRet.GetBuffer(64),2);
	}
	else
	{
		int nTemp = (-1 * nValue) ^ 4294967295;

		itoa(nTemp + 1,strRet.GetBuffer(64),2);
	}

	strTemp.Format("%064s",strRet);

	return strTemp;
}