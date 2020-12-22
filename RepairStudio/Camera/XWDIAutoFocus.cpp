
#include "stdafx.h"
#include "XWDIAutoFocus.h"

XWDIAutoFocus::XWDIAutoFocus()
{
	m_nSeqNo = 0;
	m_dwTickCount = 0;
	m_nRetryNo = 0;
	m_bInit = FALSE;
	m_nCurPos = 0;
	m_sStatus = 0;
}

XWDIAutoFocus::~XWDIAutoFocus()
{
}

DWORD XWDIAutoFocus::GetElapseTime(DWORD dwTime)
{
	return (GetTickCount() - dwTime);
}

BOOL XWDIAutoFocus::SetPortOpen(UINT uiComPort)
{
	if(uiComPort == 0)
	{
		return FALSE;
	}
	char szCOM[255] = {NULL,};
	sprintf(szCOM, "COM%d", uiComPort);


	if(atf_OpenConnection(szCOM, CBR_9600))
	{
		return FALSE;
	}

	if(atf_PingAck())
	{
		return FALSE;
	}

	if(atf_WriteBaud(CBR_9600))
	{
		return FALSE;
	}

	if(atf_ChangeCommBaudrate(CBR_9600))
	{
		return FALSE;
	}

	//if(atf_PingAck())
	//{
	//	return FALSE;
	//}

	m_bInit = TRUE;

	return TRUE;
}
BOOL XWDIAutoFocus::Open(char* pszCom, int nBaudrate)
{
	if(atf_OpenConnection(pszCom, nBaudrate))
	{
		return FALSE;
	}

	if(atf_PingAck())
	{
		return FALSE;
	}

	if(atf_WriteBaud(nBaudrate))
	{
		return FALSE;
	}

	if(atf_ChangeCommBaudrate(nBaudrate))
	{
		return FALSE;
	}

	//if(atf_PingAck())
	//{
	//	return FALSE;
	//}

	m_bInit = TRUE;

	return TRUE;
}

void XWDIAutoFocus::Close()
{
	atf_CloseConnection();
	m_bInit = FALSE;
}

BOOL XWDIAutoFocus::IsOpen()
{
	return m_bInit;
}


void XWDIAutoFocus::ReSetSeqNo()
{
	m_nRetryNo = 0;
	m_nSeqNo = 0;
}

int XWDIAutoFocus::SeqSetHome()
{
	if(!IsOpen())
	{
		return 1;
	}
	char szllcCmd[128] = {'\0'};
	int nStatus = 0;

	int nRet = 0;
	int	nSeqNo = m_nSeqNo;
	int nCmdRet = 0;
	int nIsHomeRet = 0;
	bool bHome = false;

	switch(nSeqNo)
	{
	case 0:
		atf_AfStop();
		nCmdRet = atf_RunHomingZ(NULL);
		if(nCmdRet == ErrOK)
		{
			nSeqNo = 100;
			m_dwTickCount = GetTickCount();
		}		
		else if(nCmdRet == ErrNoresources)
		{
			nRet = -8;
			nSeqNo = 0;
		}
		else if(nCmdRet == ErrOperFailed)
		{
			nRet = -10;
			nSeqNo = 0;
		}
		else if(nCmdRet == ErrTimeout)
		{
			nRet = -11;
			nSeqNo = 0;
		}
		else
		{
			nRet = -2;
			nSeqNo = 0;
		}
		break;
	case 100:
		nIsHomeRet = atf_IsInHomePosition(&bHome);
		if(nIsHomeRet == ErrOK)
		{
			if(bHome == true)
			{
				nRet = 100;
				nSeqNo = 0;
			}
			//else	//doing
			//{
			//	nRet = -101;
			//	nSeqNo = 0;
			//}
		}
		else if(nIsHomeRet == ErrNoresources)
		{
			nRet = -108;
			nSeqNo = 0;
		}
		else if(nIsHomeRet == ErrOperFailed)
		{
			nRet = -110;
			nSeqNo = 0;
		}
		else if(nIsHomeRet == ErrTimeout)
		{
			nRet = -111;
			nSeqNo = 0;
		}
		else
		{
			nRet = -102;
			nSeqNo = 0;
		}
		break;
	default:
		nRet = -1;
		nSeqNo = 0;
		break;
	}
	m_nSeqNo = nSeqNo;

	return nRet;
}
int XWDIAutoFocus::SeqSetJogMove(BOOL bDir)
{

	return 1;
}

int XWDIAutoFocus::SeqSetABSMove(int iPos)
{
	if(!IsOpen())
	{
		return 1;
	}

	int nRet = 0;
	int	nSeqNo = m_nSeqNo;
	static int nABSCurPos = 0;
	int nTargetPos = 0;

	switch(nSeqNo)
	{
	case 0:
		atf_AfStop();
		if(atf_ReadAbsZPos(&nABSCurPos) == 0)
		{
			nSeqNo = 50;
		}
		else
		{
			nRet = -10;
			nSeqNo = 0;
		}
		break;
	case 50:
		nTargetPos = iPos - (nABSCurPos / WDI_RESOLUTION);
		if(atf_MoveZum(nTargetPos) != 0)
		{
			nRet = 50;
			nSeqNo = 0;
		}
		else
		{
			nSeqNo = 100;
			m_dwTickCount = GetTickCount();
		}
		break;	
	case 100:
		if(atf_ReadStatus(&m_sStatus) != 0)
		{
			nRet = -2;
			nSeqNo = 0;
		}
		else
		{
			if((m_sStatus & MsZMotion) == 0)
			{
				nRet = 100;
				nSeqNo = 0;
			}
			//else if(m_sStatus & MsHwOK)	// Remove ??
			//{
			//	nRet = -101;
			//	nSeqNo = 0;
			//}
			else if(GetElapseTime(m_dwTickCount) > 5000)
			{
				nRet = -102;
				nSeqNo = 0;
			}
		}
		break;
	default:
		nRet = -1;
		nSeqNo = 0;
		break;
	}
	m_nSeqNo = nSeqNo; 
	return nRet;
}

int XWDIAutoFocus::SeqSetRelMove(BOOL bDir, UINT uiPos)
{
	if(!IsOpen())
	{
		return 1;
	}

	int nRet = 0;
	int	nSeqNo = m_nSeqNo;
	switch(nSeqNo)
	{
	case 0:
		atf_AfStop();
		if(bDir)
		{
			uiPos *= -1;
		}
		if(atf_MoveZum(uiPos) != 0)
		{
			nRet = -10;
			nSeqNo = 0;
		}
		else
		{			
			nSeqNo = 100;
			m_dwTickCount = GetTickCount();
		}
		break;	
	case 100:
		if(atf_ReadStatus(&m_sStatus) != 0)
		{
			nRet = -2;
			nSeqNo = 0;
		}
		else 
		{
			if((m_sStatus & MsZMotion) == 0)
			{
				nRet = 100;
				nSeqNo = 0;
			}
			//else if(m_sStatus & MsHwOK)
			//{
			//	nRet = -101;
			//	nSeqNo = 0;
			//}
			else
			{
				if(GetElapseTime(m_dwTickCount) > 10000)
				{
					nRet = -102;
					nSeqNo = 0;
				}
			}
		}
		break;
	default:
		nRet = -1;
		nSeqNo = 0;
		break;
	}
	m_nSeqNo = nSeqNo; 
	return nRet;
}

int XWDIAutoFocus::SeqSetStop()
{
	if(!IsOpen())
	{
		return 1;
	}
	int nRet = 0;
	int nSubRet = 0;

	int	nSeqNo = m_nSeqNo;
	switch(nSeqNo)
	{
	case 0:
		nSubRet = atf_DisableLaser();
		if(nSubRet == ErrOK)
		{
			//nRet = 1;
			nSeqNo = 100;
		}
		else
		{
			//nRet = -2;
			nSeqNo = 100;
		}
		break;
	case 100:
		nSubRet = atf_StopZMotor();
		if(nSubRet == ErrOK)
		{
			nRet = 100;
			nSeqNo = 0;
		}
		else
		{
			nRet = -100;
			nSeqNo = 0;
		}
		break;
	default:
		nRet = -1;
		nSeqNo = 0;
		break;
	}
	m_nSeqNo = nSeqNo;
	return nRet;
}

int XWDIAutoFocus::SeqSetAFStop()
{
	if(!IsOpen())
	{
		return 1;
	}
	int nRet = 0;
	int nSubRet = 0;

	int	nSeqNo = m_nSeqNo;
	switch(nSeqNo)
	{
	case 0:
		nSubRet = atf_AfStop();
		if(nSubRet == ErrOK)
		{
			//nRet = 1;
			nSeqNo = 100;
		}
		else
		{
			//nRet = -2;
			nSeqNo = 100;
		}
		break;
	case 100:
		nSubRet = atf_DisableLaser();
		if(nSubRet == ErrOK)
		{
			nRet = 100;
			nSeqNo = 0;
		}
		else
		{
			nRet = -100;
			nSeqNo = 0;
		}
		break;
	default:
		nRet = -1;
		nSeqNo = 0;
		break;
	}
	m_nSeqNo = nSeqNo;
	return nRet;

}

int XWDIAutoFocus::SeqAutoSearchRange(UINT uiPort, UINT uiCW, UINT uiCCW)
{
	if(!IsOpen())
	{
		return 1;
	}
	int nRet = 1;

	return nRet;
}

int XWDIAutoFocus::SeqAutoFocusPortSet(UINT uiPort)
{
	if(!IsOpen())
	{
		return 1;
	}
	static DWORD dwTime = 0;
	static int nRetry = 0;
	int nRet = 0;
	int nSubRet = 0;
	int nData[100] = {NULL,}	;
	//nRet = atf_ReadObjNum(nData);
	int nProt = 0;
	int	nSeqNo = m_nSeqNo;
	switch(nSeqNo)
	{
	case 0:
		nSeqNo = 50;
		atf_AfStop();

		break;
	case 50:
		nSubRet = atf_WriteObjNum(uiPort);
		if(nSubRet == ErrOK)
		{
			nSeqNo = 0;
			nRet = 1;
			nRetry = 0;
		}
		else
		{
			if(nRetry > 3)
			{
				nSeqNo = 0;
				nRetry = 0;
				nRet = -1;
			}
			else
			{
				nSeqNo = 100;
				nRetry++;
			}
		}
		break;
	case 100:		
		nSeqNo = 200;
		dwTime = GetTickCount();		
		break;
	case 200:
		if(GetElapseTime(dwTime) > 200)
		{
			nSeqNo = 50;
		}
		break;
	default:
		nRet = -2;
		nSeqNo = 0;
		nRetry = 0;
		break;
	}
	m_nSeqNo = nSeqNo;
	return nRet;
}

int XWDIAutoFocus::SeqAutoFocusSurface(short sSurfaceNum)
{
	if(!IsOpen())
	{
		return 1;
	}
	static DWORD dwTime = 0;
	static int nRetry = 0;
	int nRet = 0;
	int nSubRet = 0;
	int nData[100] = {NULL,};
	int nProt = 0;
	int	nSeqNo = m_nSeqNo;
	switch(nSeqNo)
	{
	case 0:
		nSeqNo = 50;
		atf_AfStop();
		break;
	case 50:
		nSubRet = atf_WriteSurface(sSurfaceNum);
		if(nSubRet == ErrOK)
		{
			nSeqNo = 60;
		}
		else
		{
			if(nRetry > 3)
			{
				nSeqNo = 0;
				nRetry = 0;
				nRet = -1;
			}
			else
			{
				nSeqNo = 100;
				nRetry++;
			}
		}
		break;
	case 60:
		nSubRet = atf_WriteSurface(sSurfaceNum);
		if(nSubRet == ErrOK)
		{
			nSeqNo = 0;
			nRet = 60;
			nRetry = 0;
		}
		else
		{
			if(nRetry > 3)
			{
				nSeqNo = 0;
				nRetry = 0;
				nRet = -1;
			}
			else
			{
				nSeqNo = 100;
				nRetry++;
			}
		}
		break;
	case 100:		
		nSeqNo = 200;
		dwTime = GetTickCount();		
		break;
	case 200:
		if(GetElapseTime(dwTime) > 200)
		{
			nSeqNo = 50;
		}
		break;
	default:
		nRet = -2;
		nSeqNo = 0;
		nRetry = 0;
		break;
	}
	m_nSeqNo = nSeqNo;
	return nRet;
}

int XWDIAutoFocus::SeqAutoFocus(BOOL bTraceMode)
{
	if(!IsOpen())
	{
		return 1;
	}
	static DWORD dwTime = 0;
	static int nRetry = 0;
	static int nInFocusCheck = 0;
	short nFlagStat = 0;
	int nRet = 0;
	int nCmdRet = 0;
	int	nSeqNo = m_nSeqNo;
	switch(nSeqNo)
	{		
	case 0:
		if(atf_EnableLaser() == 0)
		{
			atf_AFTrack();
			if(bTraceMode)
			{
				nRet = 1;
				nSeqNo = 0;
				nInFocusCheck = 0;

			}
			else
			{
				nSeqNo = 100;
				nInFocusCheck = 0;
				dwTime = GetTickCount();
			}
			nRetry = 0;
		}
		else
		{
			nRet = -3;
			nSeqNo = 0;
			nInFocusCheck = 0;
			nRetry = 0;
		}
		break;
	case 100:
		nCmdRet = atf_ReadStatus(&nFlagStat);
		if(nCmdRet == ErrOK)
		{
			if((nFlagStat & MsInFocus) == MsInFocus)
			{
				nInFocusCheck++;
				if(nInFocusCheck > 10)
				{
					nSeqNo = 200;
				}
			}
			else if(GetElapseTime(dwTime) > 4000)
			{
				//nRet = -100;
				nSeqNo = 200;
			}
		}
		else if(GetElapseTime(dwTime) > 5000)
		{
			//nRet = -110;
			nSeqNo = 200;
		}
		break;
	case 200:
		nCmdRet = atf_AfStop();
		if(nCmdRet == ErrOK)
		{
			//nRet = 1;
			nSeqNo = 300;
		}
		else
		{
			//nRet = -2;
			nSeqNo = 300;
		}
		break;
	case 300:
		nCmdRet = atf_DisableLaser();
		if(nCmdRet == ErrOK)
		{
			if(nInFocusCheck > 9)
			{
				nRet = 300;
				nSeqNo = 0;
				nInFocusCheck = 0;
				nRetry = 0;
			}
			else
			{
				nRet = -300;
				nSeqNo = 0;
				nInFocusCheck = 0;
				nRetry = 0;
			}
		}
		else
		{
			nRetry++;
			if(nRetry > 3)
			{
				nRet = -310;
				nSeqNo = 0;
				nInFocusCheck = 0;
				nRetry = 0;
			}
		}
		break;
	default:
		nRet = -1;
		nSeqNo = 0;
		break;
	}
	m_nSeqNo = nSeqNo;

	return nRet;
}
int XWDIAutoFocus::SeqAutoFocusInitialize()
{
	if(!IsOpen())
	{
		return 1;
	}

	int nRet = 0;

	int	nSeqNo = m_nSeqNo;
	switch(nSeqNo)
	{
	case 0:
		atf_AfStop();
		atf_DisableLaser();
		nRet = 1;
		break;	
	case 100:
		break;
	default:
		nRet = -1;
		nSeqNo = 0;
		break;
	}
	m_nSeqNo = nSeqNo;
	return nRet;
}

int XWDIAutoFocus::SeqGetCurPos(int & nCurPos)
{
	if(!IsOpen())
	{
		nCurPos = 0;
		return 1;
	}
	int nReadPos = 0;
	int nRet = 0;
	int	nSeqNo = m_nSeqNo;
	switch(nSeqNo)
	{
	case 0:
		if(atf_ReadAbsZPos(&nReadPos) == 0)
		{
			nCurPos = nReadPos / WDI_RESOLUTION;
			nRet = 1;
			nSeqNo = 0;
		}
		else
		{
			nRet = -2;
			nSeqNo = 0;
		}
		break;	
	default:
		nRet = -1;
		nSeqNo = 0;
		break;
	}
	m_nSeqNo = nSeqNo;
	return nRet;
}

int XWDIAutoFocus::SeqReadHwStat(int & nHWFault, int & nNLimit, int & nPLimit)
{
	if(!IsOpen())
	{		
		return 1;
	}

	int nRet = 0;
	int	nSeqNo = m_nSeqNo;
	int nCmdRet = 0;
	int nHwStat = 0;

	switch(nSeqNo)
	{
	case 0:
		nCmdRet = atf_ReadHwStat(&nHwStat);
		if(nCmdRet == ErrOK)
		{
			nSeqNo = 0;
			nRet = 1;
			if((nHwStat & HwOK) == HwOK)
			{
				nHWFault = FALSE;
			}
			else
			{
				nHWFault = TRUE;
			}
			
			//if((nHwStat & HwCasErr) == HwCasErr)
			//else

			//if((nHwStat & HwLaserDioDisabled) == HwLaserDioDisabled)
			//else

			//if((nHwStat & HwSyncDioAsserted) == HwSyncDioAsserted)
			//else

			//if((nHwStat & HwSyncDioLastFrame) == HwSyncDioLastFrame)
			//else

			//if((nHwStat & HwSyncEnabled) == HwSyncEnabled)
			//else

			//if((nHwStat & HwMotionZ) == HwMotionZ)
			//else

			//if((nHwStat & HwMotionX) == HwMotionX)
			//else
			//
			//if((nHwStat & HwMotionY) == HwMotionY)
			//else
			//
			if((nHwStat & HwMotionCWLimit) == HwMotionCWLimit)
			{
				nPLimit = TRUE;
			}
			else
			{
				nPLimit = FALSE;
			}
			//if((nHwStat & HwMotionCWLimitSense) == HwMotionCWLimitSense)
			//else

			if((nHwStat & HwMotionCCWLimit) == HwMotionCCWLimit)
			{
				nNLimit = TRUE;
			}
			else
			{
				nNLimit = FALSE;
			}
			//if((nHwStat & HwMotionCCWLimitSense) == HwMotionCCWLimitSense)
			//else

			//if((nHwStat & HwMotionInhibit) == HwMotionInhibit)
			//else
			//
			//if((nHwStat & HwMotionInhibitSense) == HwMotionInhibitSense)
			//else

		}
		else if(nCmdRet == ErrWrongType)
		{
			nSeqNo = 0;
			nRet = -2;
		}
		else if(nCmdRet == ErrOutOfBound)
		{
			nSeqNo = 0;
			nRet = -3;
		}
		else if(nCmdRet == ErrSntaxError)
		{
			nSeqNo = 0;
			nRet = -4;
		}
		else if(nCmdRet == ErrNoresources)
		{
			nSeqNo = 0;
			nRet = -5;

		}
		else if(nCmdRet == ErrOperFailed)
		{
			nSeqNo = 0;
			nRet = -6;
		}
		else if(nCmdRet == ErrTimeout)
		{
			nSeqNo = 0;
			nRet = -7;
		}
		else if(nCmdRet == ErrChksum)
		{
			nSeqNo = 0;
			nRet = -8;
		}
		else
		{
			nSeqNo = 0;
			nRet = -9;
		}
		break;	
	default:
		nRet = -1;
		nSeqNo = 0;
		break;
	}
	m_nSeqNo = nSeqNo;
	return nRet;
}

int XWDIAutoFocus::SeqReadSensStat(int & nState)
{
	if(!IsOpen())
	{		
		return 1;
	}

	int nRet = 0;
	int	nSeqNo = m_nSeqNo;
	int nCmdRet = 0;
	short nFlagStat = 0;

	switch(nSeqNo)
	{
	case 0:
		nCmdRet = atf_ReadStatus(&nFlagStat);
		if(nCmdRet == ErrOK)
		{
			nSeqNo = 0;
			nRet = 1;
			//if((nFlagStat & MsExecuteAf) == MsExecuteAf)
			//{
			//	nState = 1;
			//}
			//else
			//{

			//}
			//if((nFlagStat & MsLaserTracking) == MsLaserTracking)
			//{
			//	nState = 1;
			//}
			//else
			//{

			//}
			if((nFlagStat & MsInFocus) == MsInFocus)
			{
				nState = 1;
			}
			else
			{
				nState = 0;
			}
			//if((nFlagStat & MsExecuteAf))
			//{
			//	nState = 1;
			//}
			//else
			//{

			//}
		}
		else if(nCmdRet == ErrWrongType)
		{
			nSeqNo = 0;
			nRet = -2;
			nState = 0;
		}
		else if(nCmdRet == ErrOutOfBound)
		{
			nSeqNo = 0;
			nRet = -3;
			nState = 0;
		}
		else if(nCmdRet == ErrSntaxError)
		{
			nSeqNo = 0;
			nRet = -4;
			nState = 0;
		}
		else if(nCmdRet == ErrNoresources)
		{
			nSeqNo = 0;
			nRet = -5;
			nState = 0;

		}
		else if(nCmdRet == ErrOperFailed)
		{
			nSeqNo = 0;
			nRet = -6;
			nState = 0;

		}
		else if(nCmdRet == ErrTimeout)
		{
			nSeqNo = 0;
			nRet = -7;
			nState = 0;

		}
		else if(nCmdRet == ErrChksum)
		{
			nSeqNo = 0;
			nRet = -8;
			nState = 0;

		}
		else
		{
			nSeqNo = 0;
			nRet = -9;
			nState = 0;
		}
		break;	
	default:
		nRet = -1;
		nSeqNo = 0;
		break;
	}
	m_nSeqNo = nSeqNo;
	return nRet;

}
int XWDIAutoFocus::SeqAFLaserOn(BOOL bOn)
{
	if(!IsOpen())
	{		
		return 1;
	}

	int nRet = 0;
	int	nSeqNo = m_nSeqNo;
	int nCmdRet = 0;
	short nFlagStat = 0;

	switch(nSeqNo)
	{
	case 0:
		if(bOn)
		{
			nCmdRet = atf_EnableLaser();
			
		}
		else
		{
			nCmdRet = atf_DisableLaser();
		}
		if(nCmdRet == ErrOK)
		{
			nSeqNo = 0;
			nRet = 1;
		}
		else
		{
			nSeqNo = 0;
			nRet = -5;
		}
		break;	
	default:
		nRet = -1;
		nSeqNo = 0;
		break;
	}
	m_nSeqNo = nSeqNo;
	return nRet;
}

int XWDIAutoFocus::SeqMakeZeroSet()
{
	if(!IsOpen())
	{
		return 1;
	}
	static DWORD dwTime = 0;	
	int nRet = 0;
	int nSubRet = 0;
	int	nSeqNo = m_nSeqNo;
	switch(nSeqNo)
	{
	case 0:
		nSeqNo = 100;
		atf_AfStop();
		//Sleep(50);
		break;
	case 100:
		nSeqNo = 200;
		atf_EnableLaser();
		//Sleep(50);
		break;
	case 200:
		nSubRet = atf_Make0();
		if(nSubRet == 0)
		{
			nSeqNo = 300;
			dwTime = GetTickCount();
		}
		else
		{
			nRet = -200;
			nSeqNo = 0;
		}
		break;
	case 300:
		if(GetElapseTime(dwTime) > 5000)
		{
			nRet = 300;
			nSeqNo = 0;
			atf_DisableLaser();
		}
		break;
	default:
		nRet = -1;
		nSeqNo = 0;
		break;
	}
	m_nSeqNo = nSeqNo;
	return nRet;
}
