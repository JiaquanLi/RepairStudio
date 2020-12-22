#pragma once

#include "actutltype1.h"

class CMXComponent
{
public:
	CMXComponent(void);
	~CMXComponent(void);

private:
	//����PLCOCX
	CActutltype1 *m_pMXControl;
	//������Ϣ
	CString m_strLastError;
	//�Ƿ�������
	BOOL m_bConnected;

public:
	//�󶨿ؼ�
	void fnBindMXComponent(CActutltype1 *pMXControl);

	//����PLC
	BOOL fnConnectToPLC(int nStationNum = 3);

	//�Ͽ�����
	void fnDisconnect();

	//�Ƿ����ӳɹ�
	BOOL fnIsConnected();

	//��PLC��ȡbit����,��ȡ����Ϊ1λ
	BOOL fnReadBitFromPLC(CString strDevice,BOOL &bValue);

	//��PLC��ȡbyte����,��ȡ����Ϊ1���ֽڣ��޷���
	BOOL fnReadBytesFromPLC(CString strDevice,int &nValue);

	//��PLC��ȡword����,��ȡ����Ϊ1����,2���ֽڣ��޷���
	BOOL fnReadWordFromPLC(CString strDevice,WORD &wValue);

	//��PLC��ȡDWORD����,��ȡ����Ϊ˫��,4���ֽڣ��޷���
	BOOL fnReadDwordFromPLC(CString strDevice,DWORD &dwValue);

	//��PLC��ȡint����,��ȡ����Ϊ4���ֽڣ��з���
	BOOL fnReadIntFromPLC(CString strDevice,int &nValue);

	//��PLC��ȡint����,��ȡ����Ϊ4���ֽڣ��з���
	BOOL fnReadIntFromPLC(CString strDevice, int* nValue);

	//��PLC��ȡLONG����,��ȡ����Ϊ8���ֽڣ��з���
	BOOL fnReadLongFromPLC(CString strDevice,long &lValue);

	//��PLC��ȡFloat����,��ȡ����Ϊ8
	BOOL fnReadFloatFromPLC(CString strDevice,float &fValue);

	//��PLC��ȡstring����,��ȡ���Ȳ���
	BOOL fnReadStringFromPLC(CString strDevice,int nSize,CString &strValue);

	//////////////////////////////////////////////////////////////////////////

	//��PLCд��bit����
	BOOL fnWriteBitToPLC(CString strDevice,BOOL bValue);

	//��PLCд��byte����
	BOOL fnWriteBytesToPLC(CString strDevice,BYTE byValue);

	//��PLCд��Word����
	BOOL fnWriteWordToPLC(CString strDevice,WORD wValue);

	BOOL fnWriteMultiWordToPLC(CString strDevice, int nSize, WORD wValue[]);

	//��PLC����д��Int����
	BOOL fnWriteMultiIntToPLC(CString strDevice, int nSize, int nValue[]);

	//��PLCд��int����
	BOOL fnWriteIntToPLC(CString strDevice,int nValue);

	//��PLCд��int����
	BOOL fnWriteIntToPLC(CString strDevice, int* nValue);

	//��PLCд��dint����
	BOOL fnWriteLongToPLC(CString strDevice,long lValue);

	//��PLCд��float����
	BOOL fnWriteFloatToPLC(CString strDevice,float fValue);

	//��PLCд��string����
	BOOL fnWriteStringToPLC(CString strDevice,CString strValue);

	//��ȡ������Ϣ
	CString fnGetLastError();

private:
	//32λ��������ת��ΪС��
	double fnBinaryToFloat(CString strBinary);

	//����λ��������ת��Ϊʮ��������
	int fnBinaryToDec(CString strBinary);

	//С��ת��Ϊ32λ����������
	CString fnFloatToBinary(float num);

	//ʮ����ת��Ϊ64λ������
	CString fnDecToBinary64(INT64 nValue);

	//ʮ����ת��Ϊ32λ������
	CString fnDecToBinary32(int nValue);

	//ʮ����ת��Ϊ16λ������
	CString fnDecToBinary16(WORD nValue);

	//ʮ����ת��Ϊ8λ������
	CString fnDecToBinary8(BYTE nValue);

};
