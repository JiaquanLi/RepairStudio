#include "stdafx.h"
#include "GlobalFunction.h"
#include "../MainFrm.h"

//进行数据库的中文字符转换
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

	//转换为cstring
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

	//转换为cstring
	CString strRet(szAnsi);

	return strRet;
}

void fnDelay(long nDlyTm, BOOL bMsgPump/* =TRUE */)
{
	LARGE_INTEGER   litmp;
	LONGLONG  lStart = 0;
	LONGLONG  lEnd = 0;
	double dbMinus, dbFreq, dbTime;
	//获得计数器的时钟频率   
	QueryPerformanceFrequency(&litmp);
	dbFreq = (double)litmp.QuadPart;
	//获取起始时间
	QueryPerformanceCounter(&litmp);
	//获得初始值   	
	lStart = litmp.QuadPart;

	MSG   msg;
	do
	{
		//是否需要传递消息，不至于被阻塞。
		if (bMsgPump)
		{
			PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//获取结束时间
		QueryPerformanceCounter(&litmp);
		//获得终止值   
		lEnd = litmp.QuadPart;
		dbMinus = double(lEnd - lStart)*1000;
		dbTime = (dbMinus / dbFreq);
	} while (dbTime < nDlyTm);
}

//根据分割字符对字符串进行分割
void fnSplitByString(CString strSplitString, CString strGet, CStringArray &caSplit, BOOL bEmpty)
{
	CString strTemp, strSplit;

	//先清空字符串数组
	caSplit.RemoveAll();

	if (strGet.IsEmpty())
	{
		return;
	}

	//如果分割字符串为空。则认为只有一个字符串
	if (strSplitString.IsEmpty())
	{
		caSplit.Add(strGet);
	}

	//循环查找分割字符串
	strSplit = strGet;

	do
	{
		//查找分割字符串，获取第一个数据
		int nFind = strSplit.Find(strSplitString);
		if (0 <= nFind)
		{
			strTemp = strSplit.Mid(0, nFind);
			caSplit.Add(strTemp);

			//去掉一个
			strSplit = strSplit.Mid(nFind + 1, strSplit.GetLength() - nFind - 1);

			continue;
		}
		else
		{
			//如果没有找到，则认为这个是最后一个
			if (!strSplit.IsEmpty() || bEmpty)
			{
				caSplit.Add(strSplit);
			}

			break;
		}
	} while (TRUE);
}

//判断给定日期与当前日期相差多少天
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
		//必须格式是20200101的格式，月份与日期都是2位数，否则无法判断
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

	//获取日期差
	int nYear = time.GetYear() - atoi(caDate.GetAt(0));
	int nMonth = time.GetMonth() - atoi(caDate.GetAt(1));
	int nDay = time.GetDay() - atoi(caDate.GetAt(2));

	//大概计算，月按30天计算，年安装365天计算
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

//读取PLC的Word值
BOOL fnReadMxComponentWord(int nDeviceID, WORD &nValue)
{
	return TRUE;
}
BOOL fnWriteMxComponentWord(int nDeviceID, WORD nValue)
{
	return TRUE;
}

//向PLC连续写入Word数据
BOOL fnWriteMxComponentMultiWord(int nDeviceID, int nSize, WORD wValue[])
{
	return TRUE;
}

//向PLC连续写入Int数据
BOOL fnWriteMxComponentMultiInt(int nDeviceID, int nSize, int nValue[])
{
	return TRUE;
}

//读取PLC的BYTE值
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

//读取PLC的int值
BOOL fnReadMxComponentInt(int nDeviceID, int* nValue)
{
	return TRUE;
}

BOOL fnWriteMxComponentInt(int nDeviceID, int* nValue)
{
	return TRUE;
}

//读取PLC的long值
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


//RTC5控制的开关关
void fnOpenLaser(BOOL bOpenLaser)
{
	//LaserOn灯
	fnOpenLaserLed(bOpenLaser);
}

void fnOpenLaserLed(BOOL bOpen)
{
}

// 检测轴是否安全到位
BOOL fnAxisIsSafe(double dbPosition, int nAxis)
{
	return FALSE;
}


//打开光源
void fnOpenLight(int nLightType, int nLightParam)
{

}


//激光器使能
void fnLaserEnable(BOOL bOpen)
{

}

//光闸气缸控制
void fnLightGateOpen(BOOL bOpen)
{
}

//控制四色灯
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
//获取本应用程序的版本号，此函数必须导入version.lib
CString fnGetAppVersion()
{
	TCHAR cFileName[MAX_PATH];
	TCHAR szVersionBuffer[8192] = _T("");
	DWORD dwVerSize;
	DWORD dwHandle;
	CString strVersion;

	//获取当前工作模块的完整文件名称和路径
	GetModuleFileName(NULL, cFileName, MAX_PATH);
	CString strFileName = cFileName;

	//去掉文件名称，获取去完整的安装路径
	strFileName = strFileName.Right(strFileName.GetLength() - strFileName.ReverseFind('\\') - 1);

	TCHAR szFile[8192];
	strcpy_s(szFile, strFileName);

	//获取版本信息大小
	dwVerSize = GetFileVersionInfoSize(szFile, &dwHandle);
	if (dwVerSize == 0)
	{
		return _T("1.000");
	}

	//获取版本信息
	if (GetFileVersionInfo(szFile, 0, dwVerSize, szVersionBuffer))
	{
		VS_FIXEDFILEINFO * pInfo;
		unsigned int nInfoLen;

		//解析版本信息
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
	//提示框信息变量
	BCGP_MSGBOXPARAMS		msgParams;
	//显示内容
	msgParams.lpszText = strText;
	//最上方的标题
	msgParams.lpszCaption = strCaption;
	//主题信息
	msgParams.lpszHeader = strHeader;
	//最重要的风格
	msgParams.dwStyle = nStyle;
	msgParams.dwStyle |= MB_TOPMOST;

	//这部分默认都是比较大号的字体
	if (bCustStyle)
	{
		msgParams.hfontText = (HFONT)globalData.fontCaption.GetSafeHandle();
		msgParams.hfontButtons = (HFONT)globalData.fontCaption.GetSafeHandle();
	}

	return BCGPMessageBoxIndirect(&msgParams);
}

//发消息给主框架，由主框架弹出消息框，流程不挂起，用于线程中
void fnSendMessageBox(CString strMsg, BOOL bCaptionBar, LPVOID lpMain)
{
	//窗口句柄
	HWND hWnd = NULL;

	//获取主框架
	CMainFrame *pFrameWnd = NULL;

	//非主框架
	if (NULL == lpMain)
	{
		//获取主框架
		pFrameWnd = (CMainFrame *)AfxGetMainWnd();
		hWnd = pFrameWnd->m_hWnd;
	}
	else
	{
		hWnd = HWND(lpMain);
	}

	//不为空才显示
	if (NULL != hWnd)
	{
		CString *pMsg = new CString(strMsg);
		int *pCaptionBar = new int(bCaptionBar);

		::PostMessage(hWnd, WM_AFXMESSAGEBOX, WPARAM(pMsg), LPARAM(pCaptionBar));
	}
}

//创建多级目录
BOOL fnCreateMultiDir(CString strPath)
{
	TCHAR szPath[MAX_PATH] = { 0 };
	TCHAR szbuf[MAX_PATH] = { 0 };
	BOOL bFlag = FALSE;

	_tcscpy_s(szPath, strPath);
	int nLen = _tcslen(szPath);

	//至少3个字符
	if (3 >= nLen)
	{
		return FALSE;
	}

	//在末尾追加
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
	//计算两条直线与X正方向的夹角
	double dbAngle1, dbAngle2;
	dbAngle1 = fnGetPtsAngle(ptStart1.x, ptStart1.y, ptEnd1.x, ptEnd1.y,TRUE);
	dbAngle2 = fnGetPtsAngle(ptStart2.x, ptStart2.y, ptEnd2.x, ptEnd2.y, TRUE);

	return abs(dbAngle1 - dbAngle2);
}

int fnIsdigit(CString strData)
{
	int nDotNum = 0;
	//去除空格
	strData.Replace(_T(" "), _T(""));

	if (strData.IsEmpty())
	{
		return 0;
	}

	//判断首末尾是否为.
	if ((_T(".") == strData.Left(1)) || _T(".") == strData.Right(1))
	{
		return 0;
	}

	//判断.的个数
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
	//判断第一位是否是负号
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

//比较值的上下限
BOOL fnCompareLimit(double& dbValue, double dbLimitUp, double dbLimitDown)
{
	//值判断
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

//比较值的上下限
BOOL fnCompareLimit(int& nValue, int nLimitUp, int nLimitDown)
{
	//值判断
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

//十六进制转十进制(不带符号)
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

