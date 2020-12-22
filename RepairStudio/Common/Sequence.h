#if !defined(AFX_XSEQUENCE_H__64789601_61BF_11D4_917F_000086500CF9__INCLUDED_)
#define AFX_XSEQUENCE_H__64789601_61BF_11D4_917F_000086500CF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// sequence.h : header file
//

// COMMUNICATION MACRO
#define EVENT(X)				( WaitForSingleObject( X, 0 ) == WAIT_OBJECT_0 )
#define MSG(M,A,B)				if( m_hWnd ) PostMessage( m_hWnd, M, (UINT)A, (LONG)B );

/////////////////////////////////////////////////////////////////////////////
// CSequence thread

class CSequence : public CWinThread
{
	DECLARE_DYNCREATE(CSequence)
protected:

// Attributes
public:

// Operations
public:
	// protected constructor used by dynamic creation
	CSequence();
	virtual ~CSequence();

	//param initilize, child class do it
	virtual BOOL fnInitializeSeq();

	//finalize sequence,child class do it
	virtual void fnFinalizeSeq();

	//kill sequence,child class do it
	virtual void fnKillSeq();

	//stop current sequence
	void fnSetSeqStop();

	//run current sequence
	void fnSetSeqRun();

	//pause current sequence
	void fnSetSeqPause();

	//set sequence from pause to release
	void fnSetSeqPauseRelease();

	//start sequence
	BOOL fnSeqStart(HWND hWnd = NULL);

	//set current sequence owner window
	void fnSetSeqOwner(CWnd *pOwner);

	//send message to owner window
	void fnSeqMessage(UINT uMsg, WPARAM wParam, LPARAM lParam = 0);

	//get elapse time than dwTime
	DWORD fnGetSeqElapseTime(DWORD dwTime);

	//check is elapsed than nMSec ∫¡√Î
	BOOL fnIsSeqElapseMMSec(DWORD dwTime, int nMSec);

	//check is elapsed than nSec  √Î
	BOOL fnIsSeqElapseSec(DWORD dwTime, double dbSec);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSequence)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

protected:
	//check sequence is sleep done with defaut time 
	BOOL fnIsSeqSleepDone();
	
	//check sequence is sleep done than dwCurSleepTime
	BOOL fnIsSeqSleepDone(DWORD & dwCurSleepTime);
	
	//set sequence sleep time
	void fnSetSeqSleepTime(DWORD dwSleepTime);

	//none done with child class
	virtual BOOL fnSequence();

// Implementation
protected:
	//message owner window
	CWnd*  m_pOwnerWnd;

	//event handle
	HANDLE m_hDead;
	HANDLE m_hKill;
	HANDLE m_hRun;
	HANDLE m_hPause;
	HWND   m_hWnd;

	//sequence number
	DWORD m_dwSeqNo;

	//recorver sequence number
	DWORD m_dwRecoverSeqNo;	

	// sequence sleep timer variable
	DWORD m_dwSleepStartTick;	

	// sequence sleep time
	DWORD m_dwSleepTime;

	// Generated message map functions
	//{{AFX_MSG(XSequence)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XSEQUENCE_H__64789601_61BF_11D4_917F_000086500CF9__INCLUDED_)
