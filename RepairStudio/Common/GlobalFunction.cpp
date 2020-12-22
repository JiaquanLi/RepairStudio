#include "stdafx.h"
#include "GlobalFunction.h"
#include "../MainFrm.h"

//�������ݿ�������ַ�ת��
CString fnAnsiToUtf8(CString strAnsi)
{
	char szAnsi[MAX_PATH];
	memset(szAnsi, 0, sizeof(szAnsi));
	strcpy_s(szAnsi, strAnsi.GetBuffer(strAnsi.GetLength()));

	//Ansi to Unicode
	int wcsLen = ::MultiByteToWideChar(CP_ACP, NULL, szAnsi, strlen(szAnsi), NULL, 0);
	wchar_t* strunicode = new wchar_t[wcsLen + 1];
	::MultiByteToWideChar(CP_ACP, NULL, szAnsi, strlen(szAnsi), strunicode, wcsLen);
	strunicode[wcsLen] = '\0';
	//Unicode To UTF-8
	int utf8len = ::WideCharToMultiByte(CP_UTF8, NULL, strunicode, wcslen(strunicode), NULL, 0, NULL, NULL);
	char* strutf8 = new char[utf8len + 1];
	::WideCharToMultiByte(CP_UTF8, NULL, strunicode, wcslen(strunicode), strutf8, utf8len, NULL, NULL);
	
	strutf8[utf8len] = '\0';
	delete[] strunicode;
	strunicode = NULL;

	//ת��Ϊcstring
	CString strRet(strutf8);

	return strRet;
}

CString fnUtf8ToAnsi(CString strUtf8)
{
	char szUtf8[MAX_PATH];
	memset(szUtf8, 0, sizeof(szUtf8));
	strcpy_s(szUtf8, strUtf8.GetBuffer(strUtf8.GetLength()));

	int wlen = ::MultiByteToWideChar(CP_UTF8, NULL, szUtf8, strlen(szUtf8), NULL, 0);
	wchar_t* strunicode = new wchar_t[wlen + 1];
	::MultiByteToWideChar(CP_UTF8, NULL, szUtf8, strlen(szUtf8), strunicode, wlen);
	strunicode[wlen] = '\0';

	//Unicode To Ansi
	int    ansilen = ::WideCharToMultiByte(CP_ACP, NULL, strunicode, wcslen(strunicode), NULL, 0, NULL, NULL);
	char* szAnsi = new char[ansilen + 1];
	::WideCharToMultiByte(CP_ACP, NULL, strunicode, wcslen(strunicode), szAnsi, ansilen, NULL, NULL);
	
	szAnsi[ansilen] = '\0';
	delete[] strunicode;
	strunicode = NULL;

	//ת��Ϊcstring
	CString strRet(szAnsi);

	return strRet;
}

void fnDelay(long nDlyTm, BOOL bMsgPump/* =TRUE */)
{
	LARGE_INTEGER   litmp;
	LONGLONG  lStart = 0;
	LONGLONG  lEnd = 0;
	double dbMinus, dbFreq, dbTime;
	//��ü�������ʱ��Ƶ��   
	QueryPerformanceFrequency(&litmp);
	dbFreq = (double)litmp.QuadPart;
	//��ȡ��ʼʱ��
	QueryPerformanceCounter(&litmp);
	//��ó�ʼֵ   	
	lStart = litmp.QuadPart;

	MSG   msg;
	do
	{
		//�Ƿ���Ҫ������Ϣ�������ڱ�������
		if (bMsgPump)
		{
			PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//��ȡ����ʱ��
		QueryPerformanceCounter(&litmp);
		//�����ֵֹ   
		lEnd = litmp.QuadPart;
		dbMinus = double(lEnd - lStart)*1000;
		dbTime = (dbMinus / dbFreq);
	} while (dbTime < nDlyTm);
}

//���ݷָ��ַ����ַ������зָ�
void fnSplitByString(CString strSplitString, CString strGet, CStringArray &caSplit, BOOL bEmpty)
{
	CString strTemp, strSplit;

	//������ַ�������
	caSplit.RemoveAll();

	if (strGet.IsEmpty())
	{
		return;
	}

	//����ָ��ַ���Ϊ�ա�����Ϊֻ��һ���ַ���
	if (strSplitString.IsEmpty())
	{
		caSplit.Add(strGet);
	}

	//ѭ�����ҷָ��ַ���
	strSplit = strGet;

	do
	{
		//���ҷָ��ַ�������ȡ��һ������
		int nFind = strSplit.Find(strSplitString);
		if (0 <= nFind)
		{
			strTemp = strSplit.Mid(0, nFind);
			caSplit.Add(strTemp);

			//ȥ��һ��
			strSplit = strSplit.Mid(nFind + 1, strSplit.GetLength() - nFind - 1);

			continue;
		}
		else
		{
			//���û���ҵ�������Ϊ��������һ��
			if (!strSplit.IsEmpty() || bEmpty)
			{
				caSplit.Add(strSplit);
			}

			break;
		}
	} while (TRUE);
}

//�жϸ��������뵱ǰ������������
int fnGetDays(CString strDate)
{
	CStringArray caDate;

	CTime time = CTime::GetCurrentTime();

	if (0 < strDate.Find('-'))
	{
		fnSplitByString("-", strDate, caDate);
	}
	else if (0 < strDate.Find('/'))
	{
		fnSplitByString("/", strDate, caDate);
	}
	else
	{
		//�����ʽ��20200101�ĸ�ʽ���·������ڶ���2λ���������޷��ж�
		if (8 != strDate.GetLength())
		{
			return 0;
		}
		else
		{
			caDate.Add(strDate.Mid(0, 4));
			caDate.Add(strDate.Mid(4, 2));
			caDate.Add(strDate.Mid(6, 2));
		}
	}

	//��ȡ���ڲ�
	int nYear = time.GetYear() - atoi(caDate.GetAt(0));
	int nMonth = time.GetMonth() - atoi(caDate.GetAt(1));
	int nDay = time.GetDay() - atoi(caDate.GetAt(2));

	//��ż��㣬�°�30����㣬�갲װ365�����
	int nDays = nYear * 365 + nMonth * 30 + nDay;

	return nDays;
}


BOOL fnReadMxComponentBool(int nDeviceID, BOOL &bValue)
{
	return TRUE;
}

BOOL fnWriteMxComponentBool(int nDeviceID, BOOL bValue)
{
	return TRUE;
}

//��ȡPLC��Wordֵ
BOOL fnReadMxComponentWord(int nDeviceID, WORD &nValue)
{
	return TRUE;
}
BOOL fnWriteMxComponentWord(int nDeviceID, WORD nValue)
{
	return TRUE;
}

//��PLC����д��Word����
BOOL fnWriteMxComponentMultiWord(int nDeviceID, int nSize, WORD wValue[])
{
	return TRUE;
}

//��PLC����д��Int����
BOOL fnWriteMxComponentMultiInt(int nDeviceID, int nSize, int nValue[])
{
	return TRUE;
}

//��ȡPLC��BYTEֵ
BOOL fnReadMxComponentByte(int nDeviceID, int &nValue)
{
	return TRUE;
}

BOOL fnWriteMxComponentByte(int nDeviceID, int nValue)
{
	return TRUE;
}

BOOL fnReadMxComponentInt(int nDeviceID, int &nValue)
{
	return TRUE;
}

BOOL fnWriteMxComponentInt(int nDeviceID, int nValue)
{
	return TRUE;
}

//��ȡPLC��intֵ
BOOL fnReadMxComponentInt(int nDeviceID, int* nValue)
{
	return TRUE;
}

BOOL fnWriteMxComponentInt(int nDeviceID, int* nValue)
{
	return TRUE;
}

//��ȡPLC��longֵ
BOOL fnReadMxComponentLong(int nDeviceID, long &lValue)
{
	return TRUE;
}

BOOL fnWriteMxComponentLong(int nDeviceID, long lValue)
{
	return TRUE;
}

BOOL fnReadMxComponentString(int nDeviceID, int nSize, CString &strValue)
{
	return TRUE;
}

BOOL fnWriteMxComponentString(int nDeviceID, CString strValue)
{
	return TRUE;
}


//RTC5���ƵĿ��ع�
void fnOpenLaser(BOOL bOpenLaser)
{
	//LaserOn��
	fnOpenLaserLed(bOpenLaser);
}

void fnOpenLaserLed(BOOL bOpen)
{
}

// ������Ƿ�ȫ��λ
BOOL fnAxisIsSafe(double dbPosition, int nAxis)
{
	return FALSE;
}


//�򿪹�Դ
void fnOpenLight(int nLightType, int nLightParam)
{

}


//������ʹ��
void fnLaserEnable(BOOL bOpen)
{

}

//��բ���׿���
void fnLightGateOpen(BOOL bOpen)
{
}

//������ɫ��
void fnSetColorLight(COLORREF color)
{
	switch (color)
	{
	case COLOR_RED:
		break;

	case COLOR_YELLOW:
		break;

	case COLOR_BLUE:
		break;

	case COLOR_GREEN:
		break;

	default:
		break;
	}
}
//��ȡ��Ӧ�ó���İ汾�ţ��˺������뵼��version.lib
CString fnGetAppVersion()
{
	TCHAR cFileName[MAX_PATH];
	TCHAR szVersionBuffer[8192] = _T("");
	DWORD dwVerSize;
	DWORD dwHandle;
	CString strVersion;

	//��ȡ��ǰ����ģ��������ļ����ƺ�·��
	GetModuleFileName(NULL, cFileName, MAX_PATH);
	CString strFileName = cFileName;

	//ȥ���ļ����ƣ���ȡȥ�����İ�װ·��
	strFileName = strFileName.Right(strFileName.GetLength() - strFileName.ReverseFind('\\') - 1);

	TCHAR szFile[8192];
	strcpy_s(szFile, strFileName);

	//��ȡ�汾��Ϣ��С
	dwVerSize = GetFileVersionInfoSize(szFile, &dwHandle);
	if (dwVerSize == 0)
	{
		return _T("1.000");
	}

	//��ȡ�汾��Ϣ
	if (GetFileVersionInfo(szFile, 0, dwVerSize, szVersionBuffer))
	{
		VS_FIXEDFILEINFO * pInfo;
		unsigned int nInfoLen;

		//�����汾��Ϣ
		if (VerQueryValue(szVersionBuffer, _T("\\"), (void**)&pInfo, &nInfoLen))
		{
			strVersion.Format(_T("%d.%d%d%d"),
				HIWORD(pInfo->dwFileVersionMS), LOWORD(pInfo->dwFileVersionMS),
				HIWORD(pInfo->dwFileVersionLS), LOWORD(pInfo->dwFileVersionLS));
		}
	}

	return strVersion;
}

int  fnMessageBox(const CString  strText, const DWORD nStyle, CString strCaption, CString strHeader, BOOL bCustStyle)
{
	//��ʾ����Ϣ����
	BCGP_MSGBOXPARAMS		msgParams;
	//��ʾ����
	msgParams.lpszText = strText;
	//���Ϸ��ı���
	msgParams.lpszCaption = strCaption;
	//������Ϣ
	msgParams.lpszHeader = strHeader;
	//����Ҫ�ķ��
	msgParams.dwStyle = nStyle;
	msgParams.dwStyle |= MB_TOPMOST;

	//�ⲿ��Ĭ�϶��ǱȽϴ�ŵ�����
	if (bCustStyle)
	{
		msgParams.hfontText = (HFONT)globalData.fontCaption.GetSafeHandle();
		msgParams.hfontButtons = (HFONT)globalData.fontCaption.GetSafeHandle();
	}

	return BCGPMessageBoxIndirect(&msgParams);
}

//����Ϣ������ܣ�������ܵ�����Ϣ�����̲����������߳���
void fnSendMessageBox(CString strMsg, BOOL bCaptionBar, LPVOID lpMain)
{
	//���ھ��
	HWND hWnd = NULL;

	//��ȡ�����
	CMainFrame *pFrameWnd = NULL;

	//�������
	if (NULL == lpMain)
	{
		//��ȡ�����
		pFrameWnd = (CMainFrame *)AfxGetMainWnd();
		hWnd = pFrameWnd->m_hWnd;
	}
	else
	{
		hWnd = HWND(lpMain);
	}

	//��Ϊ�ղ���ʾ
	if (NULL != hWnd)
	{
		CString *pMsg = new CString(strMsg);
		int *pCaptionBar = new int(bCaptionBar);

		::PostMessage(hWnd, WM_AFXMESSAGEBOX, WPARAM(pMsg), LPARAM(pCaptionBar));
	}
}

//�����༶Ŀ¼
BOOL fnCreateMultiDir(CString strPath)
{
	TCHAR szPath[MAX_PATH] = { 0 };
	TCHAR szbuf[MAX_PATH] = { 0 };
	BOOL bFlag = FALSE;

	_tcscpy_s(szPath, strPath);
	int nLen = _tcslen(szPath);

	//����3���ַ�
	if (3 >= nLen)
	{
		return FALSE;
	}

	//��ĩβ׷��
	if (szPath[nLen - 1] != _T('\\'))
	{
		_tcscat_s(szPath, _T("\\"));
		szPath[nLen + 1] = _T('\0');
		nLen++;
	}

	for (int i = 0; i < nLen; i++)
	{
		if (szPath[i] == _T('\\'))
		{
			if (bFlag == TRUE)
			{
				if (!PathFileExists(szbuf))
				{
					if (!CreateDirectory(szbuf, NULL))
					{
						return FALSE;
					}
				}
			}

			szbuf[i] = szPath[i];
			bFlag = TRUE;
		}
		else
		{
			szbuf[i] = szPath[i];
		}
	}

	return TRUE;
}

double fnGetAngleBetween(DPOINT ptStart1, DPOINT ptEnd1, DPOINT ptStart2, DPOINT ptEnd2)
{
	//��������ֱ����X������ļн�
	double dbAngle1, dbAngle2;
	dbAngle1 = fnGetPtsAngle(ptStart1.x, ptStart1.y, ptEnd1.x, ptEnd1.y,TRUE);
	dbAngle2 = fnGetPtsAngle(ptStart2.x, ptStart2.y, ptEnd2.x, ptEnd2.y, TRUE);

	return abs(dbAngle1 - dbAngle2);
}

int fnIsdigit(CString strData)
{
	int nDotNum = 0;
	//ȥ���ո�
	strData.Replace(_T(" "), _T(""));

	if (strData.IsEmpty())
	{
		return 0;
	}

	//�ж���ĩβ�Ƿ�Ϊ.
	if ((_T(".") == strData.Left(1)) || _T(".") == strData.Right(1))
	{
		return 0;
	}

	//�ж�.�ĸ���
	for (int i = 0; i < strData.GetLength(); i++)
	{
		if (46 == strData.GetAt(i))
		{
			nDotNum++;
		}
	}

	if (1 < nDotNum)
	{
		return 0;
	}

	BOOL bNegative = FALSE;
	//�жϵ�һλ�Ƿ��Ǹ���
	if (45 == strData.GetAt(0))
	{
		bNegative = TRUE;
		strData.Delete(0);
	}

	for (int i = 0; i < strData.GetLength(); i++)
	{
		if (46 == strData.GetAt(i))
		{
			continue;
		}

		if ((48 > strData.GetAt(i)) || (57 < strData.GetAt(i)))
		{
			return 0;
		}
	}

	if (bNegative)
	{
		return -1;
	}

	return 1;
}

//�Ƚ�ֵ��������
BOOL fnCompareLimit(double& dbValue, double dbLimitUp, double dbLimitDown)
{
	//ֵ�ж�
	if( -1 == fnCompareDouble(dbLimitUp, dbValue))
	{
		dbValue = dbLimitUp;
		return FALSE;
	}
	if (1 == fnCompareDouble(dbLimitDown, dbValue))
	{
		dbValue = dbLimitDown;
		return FALSE;
	}

	return TRUE;
}

//�Ƚ�ֵ��������
BOOL fnCompareLimit(int& nValue, int nLimitUp, int nLimitDown)
{
	//ֵ�ж�
	if (nLimitUp < nValue)
	{
		nValue = nLimitUp;
		return FALSE;
	}
	if (nLimitDown > nValue)
	{
		nValue = nLimitDown;
		return FALSE;
	}

	return TRUE;
}

//ʮ������תʮ����(��������)
UINT fnHexToDem(CString strHexToDem)
{
	UINT nDem = 0;
	for (int i = 0; i < strHexToDem.GetLength(); i++)
	{
		nDem = nDem * 16;
		if ((strHexToDem[i] <= '9') && (strHexToDem[i] >= '0'))
		{
			nDem += strHexToDem[i] - '0';
		}
		else if ((strHexToDem[i] <= 'F') && (strHexToDem[i] >= 'A'))
		{
			nDem += strHexToDem[i] - 'A' + 10;
		}
		else if ((strHexToDem[i] <= 'f') && (strHexToDem[i] >= 'a'))
		{
			nDem += strHexToDem[i] - 'a' + 10;
		}
		else
		{
			return -1;
		}
	}
	return nDem;
}

