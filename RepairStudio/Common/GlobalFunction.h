#pragma once

//ȫ�ֺ���
#ifndef _GLOBAL_FUNCTION_H
#define  _GLOBAL_FUNCTION_H

//д��ʷ����
enum LOG_DATABASE
{
	DATABASE_CONFIG = 0,
	DATABASE_PRODUCT,
	DATABASE_LIGHT,
	DATABASE_ABSORB,
	DATABASE_CRAFTPOSITION,
	DATABASE_MOTIONPARAM,
	DATABASE_CAM,
	DATABASE_DELAY,
	DATABASE_SCAN,
	DATABASE_POWERTEST,	
};

//ȫ�ֵ�һЩ�����ӿ�
void fnDelay(long nDlyTm, BOOL bMsgPump = TRUE);

//�жϸ��������뵱ǰ������������
int fnGetDays(CString strDate);

//���ֽ�ת��Ϊunicode
CString fnAnsiToUtf8(CString strAnsi);
CString fnUtf8ToAnsi(CStringW strUtf8);

//RTC5���ƵĿ��ع�
void fnOpenLaser(BOOL bOpen = TRUE);

//Laser Led ����
void fnOpenLaserLed(BOOL bOpen = TRUE);

//������ʹ��
void fnLaserEnable(BOOL bOpen);

//������ɫ��
void fnSetColorLight(COLORREF color = COLOR_BLACK);

//��ȡPLC��IO״̬
BOOL fnReadMxComponentBool(int nDeviceID, BOOL &bValue);
BOOL fnWriteMxComponentBool(int nDeviceID, BOOL bValue);

//��ȡPLC��Wordֵ
BOOL fnReadMxComponentWord(int nDeviceID, WORD &nValue);
BOOL fnWriteMxComponentWord(int nDeviceID, WORD nValue);

//��PLC����д��Word����
BOOL fnWriteMxComponentMultiWord(int nDeviceID, int nSize, WORD wValue[]);

//��PLC����д��Int����
BOOL fnWriteMxComponentMultiInt(int nDeviceID, int nSize, int nValue[]);

//��ȡPLC��BYTEֵ
BOOL fnReadMxComponentByte(int nDeviceID, int &nValue);
BOOL fnWriteMxComponentByte(int nDeviceID, int nValue);

//��ȡPLC��intֵ
BOOL fnReadMxComponentInt(int nDeviceID, int &nValue);
BOOL fnWriteMxComponentInt(int nDeviceID, int nValue);

//��ȡPLC��intֵ
BOOL fnReadMxComponentInt(int nDeviceID, int* nValue);
BOOL fnWriteMxComponentInt(int nDeviceID, int* nValue);

//��ȡPLC��longֵ
BOOL fnReadMxComponentLong(int nDeviceID, long &lValue);
BOOL fnWriteMxComponentLong(int nDeviceID, long lValue);

//��ȡPLC��cstringֵ
BOOL fnReadMxComponentString(int nDeviceID, int nSize, CString &strValue);
BOOL fnWriteMxComponentString(int nDeviceID, CString strValue);

//���ݷָ��ַ����ַ������зָ�
void fnSplitByString(CString strSplitString, CString strGet, CStringArray &caSplit, BOOL bEmpty = FALSE);

//��ȡ��ǰ�İ汾��
CString fnGetAppVersion();

//���嵯����
int  fnMessageBox(const CString  strText, DWORD nStyle = MB_OKCANCEL | MB_ICONWARNING, CString strCaption = _T("���ϼ���"), CString strHeader = _T(""), BOOL bCustStyle = TRUE);

//����Ϣ������ܣ�������ܵ�����Ϣ�����̲����������߳���
void fnSendMessageBox(CString strMsg,BOOL bCaptionBar = FALSE,LPVOID lpMain = NULL);

//�����༶Ŀ¼
BOOL fnCreateMultiDir(CString strPath);

//����ֱ�ߵļн�
double fnGetAngleBetween(DPOINT ptStart1, DPOINT ptEnd1, DPOINT ptStart2, DPOINT ptEnd2);

//�ж�������Ƿ�Ϊ����//����-1Ϊ������1Ϊ������0��Ϊ����
int fnIsdigit(CString strData);

//�Ƚ�ֵ��������
BOOL fnCompareLimit(double& dbValue, double dbLimitUp, double dbLimitDown);
BOOL fnCompareLimit(double& dbValue,CString strSegment,CString strLimitUp, CString strLimitDown, CString& strErr);

//�Ƚ�ֵ��������
BOOL fnCompareLimit(int& nValue, int nLimitUp, int nLimitDown);
BOOL fnCompareLimit(int& nValue, CString strSegment, CString strLimitUp, CString strLimitDown, CString& strErr);

//ʮ������תʮ����(��������)
UINT fnHexToDem(CString strHexToDem);

// �������λ�ñȽ�, 0 λ���ڳ���ƫ�-1 λ�ó���ָ��ƫ�dbAllowDevia ����ƫ�Ԫ��
inline int fnComparePos(double dbPos1, double dbPos2, double dbAllowDevia = 3)
{
	if ((-1 * dbAllowDevia < dbPos1 - dbPos2) &&
		(dbAllowDevia > dbPos1 - dbPos2))
	{
		return 0;
	}

	return -1;
}

#define	EnumToString(X) CString(#X)

#endif
