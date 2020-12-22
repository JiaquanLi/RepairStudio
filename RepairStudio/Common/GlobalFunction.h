#pragma once

//全局函数
#ifndef _GLOBAL_FUNCTION_H
#define  _GLOBAL_FUNCTION_H

//写历史数据
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

//全局的一些函数接口
void fnDelay(long nDlyTm, BOOL bMsgPump = TRUE);

//判断给定日期与当前日期相差多少天
int fnGetDays(CString strDate);

//宽字节转换为unicode
CString fnAnsiToUtf8(CString strAnsi);
CString fnUtf8ToAnsi(CStringW strUtf8);

//RTC5控制的开关关
void fnOpenLaser(BOOL bOpen = TRUE);

//Laser Led 开关
void fnOpenLaserLed(BOOL bOpen = TRUE);

//激光器使能
void fnLaserEnable(BOOL bOpen);

//控制四色灯
void fnSetColorLight(COLORREF color = COLOR_BLACK);

//读取PLC的IO状态
BOOL fnReadMxComponentBool(int nDeviceID, BOOL &bValue);
BOOL fnWriteMxComponentBool(int nDeviceID, BOOL bValue);

//读取PLC的Word值
BOOL fnReadMxComponentWord(int nDeviceID, WORD &nValue);
BOOL fnWriteMxComponentWord(int nDeviceID, WORD nValue);

//向PLC连续写入Word数据
BOOL fnWriteMxComponentMultiWord(int nDeviceID, int nSize, WORD wValue[]);

//向PLC连续写入Int数据
BOOL fnWriteMxComponentMultiInt(int nDeviceID, int nSize, int nValue[]);

//读取PLC的BYTE值
BOOL fnReadMxComponentByte(int nDeviceID, int &nValue);
BOOL fnWriteMxComponentByte(int nDeviceID, int nValue);

//读取PLC的int值
BOOL fnReadMxComponentInt(int nDeviceID, int &nValue);
BOOL fnWriteMxComponentInt(int nDeviceID, int nValue);

//读取PLC的int值
BOOL fnReadMxComponentInt(int nDeviceID, int* nValue);
BOOL fnWriteMxComponentInt(int nDeviceID, int* nValue);

//读取PLC的long值
BOOL fnReadMxComponentLong(int nDeviceID, long &lValue);
BOOL fnWriteMxComponentLong(int nDeviceID, long lValue);

//读取PLC的cstring值
BOOL fnReadMxComponentString(int nDeviceID, int nSize, CString &strValue);
BOOL fnWriteMxComponentString(int nDeviceID, CString strValue);

//根据分割字符对字符串进行分割
void fnSplitByString(CString strSplitString, CString strGet, CStringArray &caSplit, BOOL bEmpty = FALSE);

//获取当前的版本号
CString fnGetAppVersion();

//定义弹出框
int  fnMessageBox(const CString  strText, DWORD nStyle = MB_OKCANCEL | MB_ICONWARNING, CString strCaption = _T("科韵激光"), CString strHeader = _T(""), BOOL bCustStyle = TRUE);

//发消息给主框架，由主框架弹出消息框，流程不挂起，用于线程中
void fnSendMessageBox(CString strMsg,BOOL bCaptionBar = FALSE,LPVOID lpMain = NULL);

//创建多级目录
BOOL fnCreateMultiDir(CString strPath);

//计算直线的夹角
double fnGetAngleBetween(DPOINT ptStart1, DPOINT ptEnd1, DPOINT ptStart2, DPOINT ptEnd2);

//判断输入的是否为数字//返回-1为负数，1为正数，0不为数字
int fnIsdigit(CString strData);

//比较值的上下限
BOOL fnCompareLimit(double& dbValue, double dbLimitUp, double dbLimitDown);
BOOL fnCompareLimit(double& dbValue,CString strSegment,CString strLimitUp, CString strLimitDown, CString& strErr);

//比较值的上下限
BOOL fnCompareLimit(int& nValue, int nLimitUp, int nLimitDown);
BOOL fnCompareLimit(int& nValue, CString strSegment, CString strLimitUp, CString strLimitDown, CString& strErr);

//十六进制转十进制(不带符号)
UINT fnHexToDem(CString strHexToDem);

// 充许误差位置比较, 0 位置在充许偏差，-1 位置超过指定偏差，dbAllowDevia 允许偏差单元数
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
