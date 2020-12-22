// sequence.cpp : implementation file
//

#include "stdafx.h"
#include "sequence.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Sequence

IMPLEMENT_DYNCREATE(CSequence, CWinThread)

CSequence::CSequence()	
{
	m_bAutoDelete = FALSE;
	m_pOwnerWnd = NULL;

	m_dwSeqNo = 0;
	m_dwRecoverSeqNo = 0;
	m_hWnd = NULL;

	// MANUAL Reset, Initial state = non-signal
	m_hDead     = CreateEvent( NULL, TRUE, FALSE, NULL );	
	m_hKill     = CreateEvent( NULL, TRUE, FALSE, NULL );
	m_hRun		 = CreateEvent( NULL, TRUE, FALSE, NULL );	
	m_hPause    = CreateEvent( NULL, TRUE, FALSE, NULL );
}

CSequence::~CSequence()
{
	CloseHandle(m_hDead);
	CloseHandle(m_hKill);
	CloseHandle(m_hRun);
	CloseHandle(m_hPause);
}

BEGIN_MESSAGE_MAP(CSequence, CWinThread)
	//{{AFX_MSG_MAP(CSequence)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSequence message handlers

BOOL CSequence::InitInstance()
{
	static DWORD oldSeqNo = -1;

	if (!fnInitializeSeq())
	{
		VERIFY(SetEvent(m_hDead));
		fnFinalizeSeq();
		return FALSE;
	}

	while (!EVENT(m_hKill))
	{
		VERIFY(WaitForSingleObject(m_hRun, INFINITE) == WAIT_OBJECT_0);
		fnSequence();
	}

	VERIFY(SetEvent(m_hDead));

	//finish it
	fnFinalizeSeq();

	return FALSE;
}

int CSequence::ExitInstance()
{
	return CWinThread::ExitInstance();
}

BOOL CSequence::fnInitializeSeq()
{
	return TRUE;
}

void CSequence::fnFinalizeSeq()
{

}

void CSequence::fnKillSeq()
{
	if(m_hThread)
	{
		ResumeThread();
		VERIFY(SetEvent(m_hPause));
		VERIFY(SetEvent(m_hRun));
		VERIFY(SetEvent(m_hKill));

		Sleep( 100 );
		VERIFY( WaitForSingleObject( m_hDead, INFINITE ) == WAIT_OBJECT_0 );
		Sleep( 100 );
		VERIFY( WaitForSingleObject( m_hThread, INFINITE ) == WAIT_OBJECT_0 );
		Sleep( 100 );
	}

	DWORD exitCode;
	if( !GetExitCodeThread(m_hThread, &exitCode))
	{
		if(STILL_ACTIVE == GetLastError())
		{
			TerminateThread(m_hThread, -1);
			Sleep( 200 );

			if (!GetExitCodeThread(m_hThread, &exitCode))
			{
				fnSendMessageBox("kill sequence and get exit code thread failed" , MB_ICONSTOP | MB_SYSTEMMODAL | MB_OK);
			}
		}
	}
}

void CSequence::fnSetSeqStop()
{
	ResetEvent(m_hRun);
}

void CSequence::fnSetSeqRun()
{
	SetEvent(m_hRun);
}

void CSequence::fnSetSeqPause()
{
	SetEvent(m_hPause);
}

void CSequence::fnSetSeqPauseRelease()
{
	ResetEvent(m_hPause);
}

BOOL CSequence::fnSeqStart(HWND hWnd)
{
	if (NULL == hWnd)
	{
		return FALSE;
	}

	m_pOwnerWnd = CWnd::FromHandle(hWnd);

	if (!CWinThread::CreateThread())
	{
		return FALSE;
	}

	return TRUE;
}

void CSequence::fnSetSeqOwner(CWnd *pOwner)
{
	m_pOwnerWnd = pOwner;
}

void CSequence::fnSeqMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (NULL == m_pOwnerWnd)
	{
		m_pOwnerWnd->PostMessage(uMsg, wParam, lParam);
	}
}

DWORD CSequence::fnGetSeqElapseTime(DWORD dwTime)
{
	return (GetTickCount() - dwTime);
}

BOOL CSequence::fnIsSeqElapseMMSec(DWORD dwTime, int nMSec)
{
	if ((GetTickCount() - dwTime) > nMSec)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CSequence::fnIsSeqElapseSec(DWORD dwTime, double dbSec)
{
	int nSec = (int)(dbSec * 1000);

	if ((GetTickCount() - dwTime) > nSec)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CSequence::fnIsSeqSleepDone()
{
	if ((GetTickCount() - m_dwSleepStartTick) > m_dwSleepTime)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CSequence::fnIsSeqSleepDone(DWORD &dwCurSleepTime)
{
	dwCurSleepTime = GetTickCount() - m_dwSleepStartTick;
	if (dwCurSleepTime > m_dwSleepTime)
	{
		return TRUE;
	}

	return FALSE;
}

void CSequence::fnSetSeqSleepTime(DWORD dwSleepTime)
{
	m_dwSleepTime = dwSleepTime;
	m_dwSleepStartTick = GetTickCount();
}

BOOL CSequence::fnSequence()
{
	return TRUE;
}














