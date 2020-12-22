
#include "StdAfx.h"
#include "MotionCK3M.h"

#define MAX_CK3M_RESPONSE	16

CMotionCK3M::CMotionCK3M(void)
{
	m_bCK3MOpen = FALSE;

	m_hMutex		= CreateMutex(NULL, FALSE, NULL);

	m_DeviceConfig.strIP = "192.168.0.200";
	m_DeviceConfig.strPort = "22";
	m_DeviceConfig.strUser = "root";
	m_DeviceConfig.strPsw = "deltatau";
	m_nErrorCode = CK3M_ERROR_NONE;
}

CMotionCK3M::~CMotionCK3M(void)
{
	CloseHandle(m_hMutex);
	
	if(m_bCK3MOpen)
	{
		//CloseRuntimeLink();
	}
}

//read variable int value
BOOL CMotionCK3M::fnGetVariable(CString strVariableName, int &nValue)
{
	if (!m_bCK3MOpen)
	{
#ifdef _MACHINE_SIMUL_
		return TRUE;
#else
		m_nErrorCode = CK3M_ERROR_NODEVICE;
		return FALSE;
#endif
	}

	m_nErrorCode = m_Control.PowerPMACcontrol_getVariable(strVariableName.GetBuffer(0), nValue);
	if (CK3M_ERROR_NONE != m_nErrorCode)
	{
		return FALSE;
	}

	return TRUE;
}

//send command to controller, use one interface
BOOL CMotionCK3M::fnSendCommand(CString strCommand, CString &strReply, BOOL dbPrint)
{
	if (!m_bCK3MOpen)
	{
#ifdef _MACHINE_SIMUL_
		return TRUE;
#else
		m_nErrorCode = CK3M_ERROR_NODEVICE;
		return FALSE;
#endif
	}

	char cReplay[256] = "";

	m_nErrorCode = m_Control.PowerPMACcontrol_sendCommand(strCommand.GetBuffer(0), cReplay, 256);
	if (CK3M_ERROR_NONE != m_nErrorCode)
	{
		return FALSE;
	}

	strReply.Format("%s", cReplay);

	if (dbPrint)
	{
		TRACE("%s -> %s\n", strCommand, strReply);
	}

	return TRUE;
}

BOOL CMotionCK3M::fnSendCommand(CString strCommand, BOOL dbPrint)
{
	CString strReply;

	if (!m_bCK3MOpen)
	{
#ifdef _MACHINE_SIMUL_
		return TRUE;
#else
		m_nErrorCode = CK3M_ERROR_NODEVICE;
		return FALSE;
#endif
	}

	char cReplay[256] = "";

	m_nErrorCode = m_Control.PowerPMACcontrol_sendCommand(strCommand.GetBuffer(0), cReplay,256);
	if (CK3M_ERROR_NONE != m_nErrorCode)
	{
		return FALSE;
	}

	strReply.Format("%s", cReplay);
	if (dbPrint)
	{
		TRACE("%s -> %s\n", strCommand, strReply);
	}

	return TRUE;
}

BOOL CMotionCK3M::fnInitMotion()
{
	CString strCommand;

	if (m_bCK3MOpen)
	{
		m_Control.PowerPMACcontrol_disconnect();
		m_bCK3MOpen = FALSE;
	}

	//connect controller, make sure ip and other infor is true
	m_nErrorCode = m_Control.PowerPMACcontrol_connect(m_DeviceConfig.strIP.GetBuffer(0),
		m_DeviceConfig.strUser.GetBuffer(0), m_DeviceConfig.strPsw.GetBuffer(0), m_DeviceConfig.strPort.GetBuffer(0));
	if (CK3M_ERROR_NONE != m_nErrorCode)
	{
		return FALSE;
	}

	m_bCK3MOpen = TRUE;

	//enable motor
	strCommand = "&1 enable";
	if (!fnSendCommand(strCommand))
	{
		return FALSE;
	}

	for (int nAxis = 0; nAxis < MAX_AXIS_NUM; nAxis++)
	{
		strCommand.Format("P%d=0",m_AxisCfgParam[nAxis].nMove_ProNo);
		if (!fnSendCommand(strCommand))
		{
			return FALSE;
		}

		strCommand.Format("P%d=0", m_AxisCfgParam[nAxis].nMoveEnd_P);
		if (!fnSendCommand(strCommand))
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CMotionCK3M::fnReset()
{
	if (!m_bCK3MOpen)
	{
#ifdef _MACHINE_SIMUL_
		return TRUE;
#else
		m_nErrorCode = CK3M_ERROR_NODEVICE;
		return FALSE;
#endif
	}

	m_nErrorCode = m_Control.PowerPMACcontrol_reset();
	if (CK3M_ERROR_NONE != m_nErrorCode)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMotionCK3M::fnPVarReset()
{
	CString strCommand;

	if (!m_bCK3MOpen)
	{
#ifdef _MACHINE_SIMUL_
		return TRUE;
#else
		m_nErrorCode = CK3M_ERROR_NODEVICE;
		return FALSE;
#endif
	}

	for (int nAxis = 0; nAxis < MAX_AXIS_NUM; nAxis++)
	{
		strCommand.Format("P%d=0", m_AxisCfgParam[nAxis].nMove_ProNo);
		if (!fnSendCommand(strCommand))
		{
			return FALSE;
		}

		strCommand.Format("P%d=0", m_AxisCfgParam[nAxis].nMoveEnd_P);
		if (!fnSendCommand(strCommand))
		{
			return FALSE;
		}
	}

	return TRUE;
}

void CMotionCK3M::fnDeInint()
{
	if (m_bCK3MOpen)
	{
		fnStopSyncMove();
		fnStopAllAxis();
		m_bCK3MOpen = FALSE;
		m_Control.PowerPMACcontrol_disconnect();
	}
}

BOOL CMotionCK3M::fnStopSyncMove()
{
	if (!m_bCK3MOpen)
	{
#ifdef _MACHINE_SIMUL_
		return TRUE;
#else
		m_nErrorCode = CK3M_ERROR_NODEVICE;
		return FALSE;
#endif
	}
	
	if (!fnSendCommand("&1a"))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMotionCK3M::fnStopAllAxis(void)
{
	if (!m_bCK3MOpen)
	{
#ifdef _MACHINE_SIMUL_
		return TRUE;
#else
		m_nErrorCode = CK3M_ERROR_NODEVICE;
		return FALSE;
#endif
	}

	m_nErrorCode = m_Control.PowerPMACcontrol_stopAllAxes();
	if (CK3M_ERROR_NONE != m_nErrorCode)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMotionCK3M::fnHomeAxis(const int &nAxis)
{
	CString strCommand;

	if (!m_bCK3MOpen)
	{
#ifdef _MACHINE_SIMUL_
		return TRUE;
#else
		m_nErrorCode = CK3M_ERROR_NODEVICE;
		return FALSE;
#endif
	}

	//set p variable
	strCommand.Format("P%d=1", m_AxisCfgParam[nAxis].nHomeEnd_P);
	if (!fnSendCommand(strCommand))
	{
		return FALSE;
	}

	Sleep(10);

	m_nErrorCode = m_Control.PowerPMACcontrol_disablePlc(m_AxisCfgParam[nAxis].nHome_PLCNo);
	if (CK3M_ERROR_NONE != m_nErrorCode)
	{
		return FALSE;
	}

	Sleep(50);

	m_nErrorCode = m_Control.PowerPMACcontrol_enablePlc(m_AxisCfgParam[nAxis].nHome_PLCNo);
	if (CK3M_ERROR_NONE != m_nErrorCode)
	{
		return FALSE;
	}

	return TRUE;
}

//single axis abs move, absolute position
BOOL CMotionCK3M::fnSingleAbsMove(const double dbAbsPos, const int &nAxis)
{
	if (!m_bCK3MOpen)
	{
#ifdef _MACHINE_SIMUL_
		return TRUE;
#else
		m_nErrorCode = CK3M_ERROR_NODEVICE;
		return FALSE;
#endif
	}

	m_nErrorCode = m_Control.PowerPMACcontrol_axisMoveAbs(nAxis,dbAbsPos);
	if (CK3M_ERROR_NONE != m_nErrorCode)
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL CMotionCK3M::fnSingleRelMove(const double dbRelDistance, const int &nAxis)
{
	if (!m_bCK3MOpen)
	{
#ifdef _MACHINE_SIMUL_
		return TRUE;
#else
		m_nErrorCode = CK3M_ERROR_NODEVICE;
		return FALSE;
#endif
	}

	m_nErrorCode = m_Control.PowerPMACcontrol_axisMoveRel(nAxis, dbRelDistance);
	if (CK3M_ERROR_NONE != m_nErrorCode)
	{
		return FALSE;
	}

	return TRUE;
}


//XY Axes abs move
BOOL CMotionCK3M::fnXYAbsMove(const double dbAbsPosX, const double dbAbsPosY)
{
	if (!m_bCK3MOpen)
	{
#ifdef _MACHINE_SIMUL_
		return TRUE;
#else
		m_nErrorCode = CK3M_ERROR_NODEVICE;
		return FALSE;
#endif
	}

	//check axis is move possible
	if (!fnMovePossible(AXIAS_X_ID) || !fnMovePossible(AXIAS_Y_ID))
	{
		return FALSE;
	}

	if (!fnSingleAbsMove(dbAbsPosX,AXIAS_X_ID))
	{
		return FALSE;
	}

	if (!fnSingleAbsMove(dbAbsPosY, AXIAS_Y_ID))
	{
		return FALSE;
	}

	return TRUE;
}


//XY Axes rel move
BOOL CMotionCK3M::fnXYRelMove(const double dbRelDistanceX, const double dbRelDistanceY)
{
	if (!m_bCK3MOpen)
	{
#ifdef _MACHINE_SIMUL_
		return TRUE;
#else
		m_nErrorCode = CK3M_ERROR_NODEVICE;
		return FALSE;
#endif
	}

	//check axis is move possible
	if (!fnMovePossible(AXIAS_X_ID) || !fnMovePossible(AXIAS_Y_ID))
	{
		return FALSE;
	}

	if (!fnSingleRelMove(dbRelDistanceX, AXIAS_X_ID))
	{
		return FALSE;
	}

	if (!fnSingleRelMove(dbRelDistanceY, AXIAS_Y_ID))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMotionCK3M::fnJogMove(const double dbSpeed, const int &nAxis)
{
	if(!m_bCK3MOpen)
	{
#ifdef _MACHINE_SIMUL_
		return TRUE;
#else
		m_nErrorCode = CK3M_ERROR_NODEVICE;
		return FALSE;
#endif
	}

	//check axis is move possible
	if (!fnMovePossible(AXIAS_X_ID) || !fnMovePossible(AXIAS_Y_ID))
	{
		return FALSE;
	}

	//set speed
	m_nErrorCode = m_Control.PowerPMACcontrol_axisSetVelocity(nAxis,fabs(dbSpeed));
	if (CK3M_ERROR_NONE != m_nErrorCode)
	{
		return FALSE;
	}

	//positive or negative
	if (0 < dbSpeed)
	{
		m_nErrorCode = m_Control.PowerPMACcontrol_axisMovePositive(nAxis);
	}
	else
	{
		m_nErrorCode = m_Control.PowerPMACcontrol_axisMoveNegative(nAxis);
	}

	if (CK3M_ERROR_NONE != m_nErrorCode)
	{
		return FALSE;
	}

	return TRUE;
}	

BOOL CMotionCK3M::fnIsHomeCompleted(const int &nAxis)
{
	if (!m_bCK3MOpen)
	{
#ifdef _MACHINE_SIMUL_
		return TRUE;
#else
		m_nErrorCode = CK3M_ERROR_NODEVICE;
		return FALSE;
#endif
	}

	int nHomeVar = 0;
	CString strVarName;
	strVarName.Format("P%d", m_AxisCfgParam[nAxis].nHomeEnd_P);

	//read home variable
	if (!fnGetVariable(strVarName,nHomeVar))
	{
		return FALSE;
	}
	
	//check home done
	if (0 == nHomeVar)
	{		
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CMotionCK3M::fnIsMoveCompleted(const int &nAxis)
{	
	if (!m_bCK3MOpen)
	{
#ifdef _MACHINE_SIMUL_
		return TRUE;
#else
		m_nErrorCode = CK3M_ERROR_NODEVICE;
		return FALSE;
#endif
	}

	int nHomeVar = 0;
	CString strVarName;
	strVarName.Format("P%d", m_AxisCfgParam[nAxis].nMoveEnd_P);

	//read home variable
	if (!fnGetVariable(strVarName, nHomeVar))
	{
		return FALSE;
	}

	// 0 : Done   1 : Doing   2 : P Param Condition Error
	if (0 == nHomeVar)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CMotionCK3M::fnIsXYMoveCompleted()
{
	//two axes move done
	if (fnIsMoveCompleted(AXIAS_X_ID) && fnIsMoveCompleted(AXIAS_Y_ID))
	{
		return TRUE;
	}
	
	return FALSE;
}

BOOL CMotionCK3M::fnMovePossible(const int &nAxis)
{
	if (!m_bCK3MOpen)
	{
#ifdef _MACHINE_SIMUL_
		return TRUE;
#else
		m_nErrorCode = CK3M_ERROR_NODEVICE;
		return FALSE;
#endif
	}

	if(nAxis >= MAX_AXIS_NUM)
	{
		m_nErrorCode = CK3M_ERROR_INVALID_AXIS;
		return FALSE;
	}

	//check is move done
	if (!fnIsMoveCompleted(nAxis))
	{
		return FALSE;
	}
	
	return TRUE;
}

double CMotionCK3M::fnGetActualPos(const int &nAxis)
{	
	if (!m_bCK3MOpen)
	{
		return 0.;
	}
		
	double dbPos = 0;
	WaitForSingleObject(m_hMutex, 1000);
	m_Control.PowerPMACcontrol_axisGetCurrentPosition(nAxis, dbPos);
	ReleaseMutex(m_hMutex);

	return dbPos;
}

void CMotionCK3M::fnConvertResponseToBit(CString strResponse, CString &strStatusBit)
{
	if((MAX_CK3M_RESPONSE + 1) > strResponse.GetLength())
	{
		return;
	}

	char szTmp[256] = "";
	char szTmp2[256] = "";
	short	iTmp = 0;

	for(int nIndex = 1; nIndex < MAX_CK3M_RESPONSE + 1; nIndex++)
	{
		int nTmp = strResponse.GetAt(nIndex) - 48;

		// 'A'
		if (9 < nTmp) 
		{
			nTmp = nTmp - 7;
		}

		//'a'
		if (15 < nTmp) 
		{
			nTmp = nTmp - 32;
		}

		//'a'
		if (15 < nTmp) 
		{
			nTmp = nTmp % 16;
		}

		itoa(nTmp, szTmp, 2);
		strStatusBit.Format("%04s", szTmp);
	}
}

void CMotionCK3M::fnStopAxis(const int &nAxis)
{
	if(!m_bCK3MOpen || (nAxis >= MAX_AXIS_NUM))
	{
		return;
	}

	m_Control.PowerPMACcontrol_axisStop(nAxis);
}

void CMotionCK3M::fnStopJog(const int &nAxis)
{
	if (!m_bCK3MOpen || (nAxis >= MAX_AXIS_NUM))
	{
		return;
	}

	CString strCommand;
	strCommand.Format("#%dJ/", nAxis);
	if (fnSendCommand(strCommand))
	{
		fnSendCommand("&*a");
	}
}

void CMotionCK3M::fnStopHome(const int &nAxis)
{
	CString strCommand;

	if (!m_bCK3MOpen || (nAxis >= MAX_AXIS_NUM))
	{
		return;
	}

	strCommand.Format("#%d..2J/", nAxis);
	fnSendCommand(strCommand);

	Sleep(100);

	strCommand.Format("#%d..2J/", m_AxisCfgParam[nAxis].nHome_PLCNo);
	fnSendCommand(strCommand);
}

void CMotionCK3M::fnKillAxis(const int &nAxis)
{
	CString strCommand;

	if (!m_bCK3MOpen || (nAxis >= MAX_AXIS_NUM))
	{
		return;
	}

	strCommand.Format("#%dK", nAxis);
	fnSendCommand(strCommand);
}