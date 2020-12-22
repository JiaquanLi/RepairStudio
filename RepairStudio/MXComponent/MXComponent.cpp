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

//绑定控件
void CMXComponent::fnBindMXComponent(CActutltype1 *pMXControl)
{
	::EnterCriticalSection(&g_MXCritical);
	if (NULL != pMXControl)
	{
		m_pMXControl = pMXControl;
	}
	::LeaveCriticalSection(&g_MXCritical);
}

//连接PLC
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

	//设置端口
	m_pMXControl->put_ActLogicalStationNumber(nStationNum);

	//连接
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

//断开连接
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

//是否连接成功
BOOL CMXComponent::fnIsConnected()
{
	return m_bConnected;
}

//从PLC读取bit数据,读取长度为1位
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

//从PLC读取byte数据,读取长度为1
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

//从PLC读取word数据,读取长度为1个字,2个字节，无符号
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


//从PLC读取int数据,读取长度为4
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

//从PLC读取int数据,读取长度为4
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

//从PLC读取long数据,读取长度为16个字节，有符号
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

		//最高位为1，说明为负数
		if (65535 <= sValue[3])
		{
			lValue = lValue - 4294967296;  
		}    
	}

	::LeaveCriticalSection(&g_MXCritical);
	return TRUE;
}

//从PLC读取Float数据,读取长度为8
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

//从PLC读取string数据,读取长度不定
BOOL CMXComponent::fnReadStringFromPLC(CString strDevice,int nSize,CString &strValue)
{
	::EnterCriticalSection(&g_MXCritical);
	scoped_array<long> pValue(new long[nSize]);

	//清除数据
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

//向PLC写入bit数据
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

//向PLC写入byte数据
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


//向PLC写入Word数据
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

	//需要转换一下
	CString strBinary = fnDecToBinary16(wValue);

	//转换后的二进制数据
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

//向PLC连续写入Word数据
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

	//需要转换一下
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

	//转换后的二进制数据
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

//向PLC写入int数据
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

	//转换后的二进制数据
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

//向PLC写入int数据
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

	//转换后的二进制数据
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

//向PLC写入long数据
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

	//转换后的二进制数据
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

//向PLC写入float数据
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

	//转换后的二进制数据
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

//向PLC写入string数据
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

//获取错误信息
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

	//  (-1) s表示符号位，当s = 0，V为正数；当s = 1，V为负数。    
	//  （2）M表示有效数字，大于等于1，小于2。  
	//  （3）2^E表示指数位。  
	//对于单精度 符号位 1 指数为8    有效数字 23  
	//  （1）E不全为0或不全为1。这时，浮点数就采用上面的规则表示，即指数E的计算值减去127（或1023），得到真实值，再将有效数字M前加上第一位的1。  
	//  （2）E全为0。这时，浮点数的指数E等于1 - 127（或者1 - 1023），有效数字M不再加上第一位的1，而是还原为0.xxxxxx的小数。这样做是为了表示±0，以及接近于0的很小的数字。  
	//  （3）E全为1。这时，如果有效数字M全为0，表示±无穷大（正负取决于符号位s）；如果有效数字M不全为0，表示这个数不是一个数（NaN）。  
	int sign = (strBinary.GetAt(0) == '0') ? 1 : -1; 

	//分解有效数数字，因为，对于E来说比较复杂，所以我们最后在分解  
	float frac = 0.0;  
	for (int i = 9; i < strBinary.GetLength();++i)  
	{  
		frac += pow(float(2), -i + 8)*(strBinary.GetAt(i)-'0');  
	}  

	//分解指数位  
	//假如全为0的情况  
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
	//假如全为1的情况  
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
		if (0.0==frac) //如果M全为0   
		{  
			if (1==sign)//那么如果符号为1 的话，返回负无穷  
			{  
				return -1;  
			}  
			else //如果符号为0的话，返回正无穷  
			{  
				return 1;  
			}  
		}  
		else         //不然的话，返回NAN 不是一个数字  
		{  
			return 2;  
		}  
	}  

	//最后一种情况，指数不全为0或者1  
	unsigned char p = 0;  
	for (int i = 8,Index=0; i >= 1;--i,++Index)  
	{  
		p += pow(float(2), Index)*(strBinary.GetAt(i) - '0');  
	}

	double E = pow(float(2), int(p - 127));  
	return sign*E*(1 + frac);  
}



//任意位
int CMXComponent::fnBinaryToDec(CString strBinary)
{
	//在此处调用判断一个字符串有多长的函数

	int size = strBinary.GetLength();

	//将字符串的二进制数字取出，减去48，转换为int型，并保存在新的数组binary内。

	scoped_array<int> binary(new int [size]);

	for (int i = 0; i < size; i++)
	{

		int temp = strBinary.GetAt(i) - 48;

		*(binary.get() + i) = temp;
	}

	//将二进制数字转换为十进制

	int parseBinary = 0;

	for (int i = 0; i < size; i++)
	{
		parseBinary += pow( (*(binary.get() + i) * 2.0), (size - 1 - i) )*(*(binary.get() + i));
	}

	return parseBinary;
}

CString CMXComponent::fnFloatToBinary(float num)
{
	//  (-1) s表示符号位，当s = 0，V为正数；当s = 1，V为负数。    
	//  （2）M表示有效数字，大于等于1，小于2。  
	//  （3）2^E表示指数位。  
	//对于单精度 符号位 1 指数为8    有效数字 23  
	string sign = (num < 0) ? "1" : "0";  
	num = abs(num);  
	//将float分解成正数部分和小数部分  
	int Interger = int(num);  
	float frac = num - Interger;  
	//将其转换为分别转换为二进制的数字  
	string IntStr("");  
	string FracStr("");  
	//转换正数部分  
	while (Interger)  
	{  
		IntStr += (Interger % 2 + '0');  
		Interger /= 2;  
	}  
	//翻转字符串  
	int i = 0;  
	int j = IntStr.size() - 1;  
	while (i < j)  
	{  
		swap(IntStr[i], IntStr[j]);  
		++i;  
		--j;  
	}  
	string EStr(8, '0');             //指数域  
	string MStr("");                //小数域  
	//分解小数部分----由于小部分，可能会出现分解不完全的情况，并且float中仅有23位，所以仅仅循环23次------但是对于仅有小数的部分，还要截断一部分，所以需要补充  
	for (int i = 1; i < 24+23; ++i)  
	{  
		if (frac == 0.0)       //如果等于0，那么退出循环  
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
		//准备工作已经完成了，开始进行实际的工作
		//偏置 BIAS=pow(2,8-1)-1=127;  
		int Offset = IntStr.size() - 1 + 127;     
		int Index = 7;  
		//指数域  
		while (Offset)  
		{  
			EStr[Index] = Offset % 2 + '0';  
			Offset /= 2;  
			--Index;  
		}  
		//那么小数域为;  
		MStr = IntStr.substr(1) + FracStr;  
	}  
	else  
	{  
		//找到小数的第一个1为位置  
		int Index = 0;  
		for (int i = 0; i < FracStr.size();++i)  
		{  
			if (FracStr[i]=='1')  
			{  
				Index = i + 1;  
				break;  
			}  
		}  
		unsigned char Offset = Index?(-Index + 127):0;//如果小数部分没有1的话，那么就是X.0   
		int temp = 7;  
		//指数域  
		while (Offset)  
		{  
			EStr[temp] = Offset % 2 + '0';  
			Offset /= 2;  
			--temp;  
		}  
		//那么小数域为;  
		MStr = FracStr.substr(Index);  
	}  
	//对字符进行填充  
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

//16位
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

//32位
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

//64位
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