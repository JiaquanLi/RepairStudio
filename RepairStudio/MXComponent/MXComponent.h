#pragma once

#include "actutltype1.h"

class CMXComponent
{
public:
	CMXComponent(void);
	~CMXComponent(void);

private:
	//三菱PLCOCX
	CActutltype1 *m_pMXControl;
	//错误信息
	CString m_strLastError;
	//是否连接上
	BOOL m_bConnected;

public:
	//绑定控件
	void fnBindMXComponent(CActutltype1 *pMXControl);

	//连接PLC
	BOOL fnConnectToPLC(int nStationNum = 3);

	//断开连接
	void fnDisconnect();

	//是否连接成功
	BOOL fnIsConnected();

	//从PLC读取bit数据,读取长度为1位
	BOOL fnReadBitFromPLC(CString strDevice,BOOL &bValue);

	//从PLC读取byte数据,读取长度为1个字节，无符号
	BOOL fnReadBytesFromPLC(CString strDevice,int &nValue);

	//从PLC读取word数据,读取长度为1个字,2个字节，无符号
	BOOL fnReadWordFromPLC(CString strDevice,WORD &wValue);

	//从PLC读取DWORD数据,读取长度为双字,4个字节，无符号
	BOOL fnReadDwordFromPLC(CString strDevice,DWORD &dwValue);

	//从PLC读取int数据,读取长度为4个字节，有符号
	BOOL fnReadIntFromPLC(CString strDevice,int &nValue);

	//从PLC读取int数据,读取长度为4个字节，有符号
	BOOL fnReadIntFromPLC(CString strDevice, int* nValue);

	//从PLC读取LONG数据,读取长度为8个字节，有符号
	BOOL fnReadLongFromPLC(CString strDevice,long &lValue);

	//从PLC读取Float数据,读取长度为8
	BOOL fnReadFloatFromPLC(CString strDevice,float &fValue);

	//从PLC读取string数据,读取长度不定
	BOOL fnReadStringFromPLC(CString strDevice,int nSize,CString &strValue);

	//////////////////////////////////////////////////////////////////////////

	//向PLC写入bit数据
	BOOL fnWriteBitToPLC(CString strDevice,BOOL bValue);

	//向PLC写入byte数据
	BOOL fnWriteBytesToPLC(CString strDevice,BYTE byValue);

	//向PLC写入Word数据
	BOOL fnWriteWordToPLC(CString strDevice,WORD wValue);

	BOOL fnWriteMultiWordToPLC(CString strDevice, int nSize, WORD wValue[]);

	//向PLC连续写入Int数据
	BOOL fnWriteMultiIntToPLC(CString strDevice, int nSize, int nValue[]);

	//向PLC写入int数据
	BOOL fnWriteIntToPLC(CString strDevice,int nValue);

	//向PLC写入int数据
	BOOL fnWriteIntToPLC(CString strDevice, int* nValue);

	//向PLC写入dint数据
	BOOL fnWriteLongToPLC(CString strDevice,long lValue);

	//向PLC写入float数据
	BOOL fnWriteFloatToPLC(CString strDevice,float fValue);

	//向PLC写入string数据
	BOOL fnWriteStringToPLC(CString strDevice,CString strValue);

	//获取错误信息
	CString fnGetLastError();

private:
	//32位二进制数转换为小数
	double fnBinaryToFloat(CString strBinary);

	//任意位二进制数转换为十进制数字
	int fnBinaryToDec(CString strBinary);

	//小数转换为32位二进制数据
	CString fnFloatToBinary(float num);

	//十进制转换为64位二进制
	CString fnDecToBinary64(INT64 nValue);

	//十进制转换为32位二进制
	CString fnDecToBinary32(int nValue);

	//十进制转换为16位二进制
	CString fnDecToBinary16(WORD nValue);

	//十进制转换为8位二进制
	CString fnDecToBinary8(BYTE nValue);

};
