#pragma once

#include "atf_lib.h"

#define WDI_RESOLUTION 8
class XWDIAutoFocus
{
protected:

	// Attributes
public:
	BOOL SetPortOpen(UINT uiComPort);
	BOOL Open(char* pszCom, int nBaudrate);
	void Close();
	BOOL IsOpen();
	DWORD GetElapseTime(DWORD dwTime);
	void ReSetSeqNo();
	int SeqSetHome();
	int SeqSetJogMove(BOOL bDir);
	int SeqSetABSMove(int iPos);
	int SeqSetRelMove(BOOL bDir, UINT uiPos);
	int SeqSetStop();
	int SeqSetAFStop();
	int SeqAutoSearchRange(UINT uiPort, UINT uiCW, UINT uiCCW);
	int SeqAutoFocusPortSet(UINT uiPort); 
	int SeqAutoFocusSurface(short sSurfaceNum);
	int SeqAutoFocus(BOOL bTraceMode = FALSE);
	int SeqAutoFocusInitialize();
	int SeqGetCurPos(int & nCurPos);
	//int SeqGetLastPos(int& nCurPos);
	int SeqMakeZeroSet();
	int SeqReadHwStat(int & nHWFault, int & nNLimit, int & nPLimit);
	int SeqReadSensStat(int & nState);
	int SeqAFLaserOn(BOOL bOn);
	// Operations
public:
	XWDIAutoFocus();           // protected constructor used by dynamic creation
	virtual ~XWDIAutoFocus();

public:

private:
	BOOL m_bInit;
	UINT m_nCurPos;
	DWORD m_dwTickCount;
	int m_nRetryNo;
	int m_nSeqNo;

	short m_sStatus;
	// Implementation
protected:
};
