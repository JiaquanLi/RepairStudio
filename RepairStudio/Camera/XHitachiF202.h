#if !defined _XHitachiF202_
#define _XHitachiF202_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SerialPort.h : header file
//
#include "XCommThread.h"
#include "XLog.h"
/////////////////////////////////////////////////////////////////////////////
// CSerialPort thread

#define _MAX_HITACHI_GAIN_VALUE_	341

enum HITACHI_SETCMD
{
	HTSETCMD_NONE = 0,
	HTSETCMD_MODE,
	HTSETCMD_GAIN,
	HTSETCMD_SHUTTER_SPEED,
	HTSETCMD_WB_MODE,
	HTSETCMD_WB_RED,
	HTSETCMD_WB_BLUE,
	HTSETCMD_BRIGHTNESS,
};

enum HITACHI_GETCMD
{
	HTGETCMD_NONE = 0,
	HTGETCMD_MODE,
	HTGETCMD_GAIN,
	HTGETCMD_SHUTTER,
	HTGETCMD_WB_MODE,
	HTGETCMD_WB_RED,
	HTGETCMD_WB_BLUE,
	HTGETCMD_BRIGHTNESS
};

class XHitachiF202 : public XCommThread //CWinThread
{
	DECLARE_DYNCREATE(XHitachiF202)
protected:
	CEvent m_evCommRcvd;
	//void DataReceived();
	void OnNewRxChar();
	void OnNewRxFlag();
	void ResetBuffer();

	// Attributes
public:
	char MakeBCC(char * pszInput, int nLength);
	BOOL GetConnect();
	BOOL SetPortOpen(UINT uiComPort = 1);

	int SeqSetCommand(HITACHI_SETCMD nType, int nValue);
	int SeqGetCommand(HITACHI_GETCMD nType, int& nValue);

	void GetSetCommandFormat(HITACHI_SETCMD nType, int nValue, char* szCommand);
	void GetGetCommandFormat(HITACHI_GETCMD nType, char* szCommand, int &nDataSize);

	void ConvertHexToAscii(int nHex, char* szAscii);
	int ConvertAsciiToHex(char* szAscii);
	// Operations
public:
	BOOL IsCommRcvd();
	XHitachiF202();           // protected constructor used by dynamic creation
	virtual ~XHitachiF202();
	BOOL GetReceivedData(char* pBuff);
	char* GetReceivedData();
	BOOL IsRcvdLength(int nLen);
	void Purge();
	DWORD m_dwLen;
	BOOL IsCommRcvdWithStealth(); // Added 2005.12.15

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialPort)
public:
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

private:
	//	BYTE m_cRcvBuff[256];
	int m_nMaxPattern;
	CCriticalSection m_DataCriticalSection;

	char m_cRcvBuff[1024]; // changed 2005.12.14
	DWORD m_dwTickCount;
	CString m_strSend;
	int m_nRetryNo;
	int m_nSeqNo;
	int m_nSeqNoGet;
	char m_szSendData[1024];
	char m_szSendGetData[1024];
	XLog m_DiverLog;
	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSerialPort)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif
