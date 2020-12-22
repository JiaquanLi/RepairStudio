#if !defined _XMotionCK3M_
#define _XMotionCK3M_

#pragma once

#include "CK3M_X64/PowerPMACcontrol.h"

using namespace PowerPMACcontrol_ns;

typedef struct  _tagDeviceConfig_CK3M
{
	CString strIP;
	CString strUser;
	CString strPsw;
	CString strPort;
}TDEVICECONFIG_CK3M;


typedef struct  _tagAxisConfig_CK3M
{
	int    nCoordNo;		// 坐标系号
	int    nDriverNo;		// 对应的驱动器号
	int    nHome_PLCNo;     // 对应的复位PLC号
	int    nMove_ProNo;     // 对应的运动程序号
		  
	int    nHomeEnd_P;		// P_variable:  home complete
	int    nMovePos_P;		// P_variable： position
	int    nMoveVel_P;		// P_variable： velocity
	int    nMoveAcc_P;		// P_variable： acceleration
	int    nMoveDec_P;		// P_variable： deceleration
	int    nMoveEnd_P;		// P_variable:  move end flag

}TAXISCONFIG_CK3M;

typedef struct  _tagSyncConfig_CK3M
{
	int    nCoordNo;		// 坐标系号
	int    nMove_ProNo;     // 对应的运动程序号
	int    nMovePos0_P;		// P_variable： position
	int    nMovePos1_P;		// P_variable： position
	int    nMoveVel_P;		// P_variable： velocity
	int    nMoveAcc_P;		// P_variable： acceleration
	int    nMoveDec_P;		// P_variable： deceleration
	int    nMoveEnd_P;		// P_variable:  move end flag

}TSYNCCONFIG_CK3M;

namespace CK3M_STATUS {
	typedef enum
	{
		ST_CK3M_TRIGGER_MOVE = 0,
		ST_CK3M_HOME_IN_PROGRESS,
		ST_CK3M_MLIMIT_HW,
		ST_CK3M_PLIMIT_HW,
		ST_CK3M_FE_WARN,
		ST_CK3M_FE_FATAL,
		ST_CK3M_LIMIT_STOP_HW,
		ST_CK3M_AMP_FAULT,
		ST_CK3M_MLIMIT_SW,
		ST_CK3M_PLIMIT_SW,
		ST_CK3M_I2T_FAULT,
		ST_CK3M_TRIGGER_NOT_FOUND,
		ST_CK3M_AMP_WARN,
		ST_CK3M_ENC_LOSS,
		ST_CK3M_RSVED_3,
		ST_CK3M_RSVED_2,
		ST_CK3M_HOME_COMPLETE,
		ST_CK3M_DES_VEL_ZERO,
		ST_CK3M_CLOSED_LOOP,
		ST_CK3M_AMP_ENA,
		ST_CK3M_IN_POS,
		ST_CK3M_RSVED_1,
		ST_CK3M_BLOCK_REQUEST,
		ST_CK3M_PHASE_FOUND,
		ST_CK3M_TRIGGER_SPEED_SEL,
		ST_CK3M_GANTRY_HOMED,
		ST_CK3M_SPINDLE_BIT1,
		ST_CK3M_SPINDLE_BIT0,
		ST_CK3M_MAX,
	}_CM3K_STATUS;
};

enum
{
	CK3M_ERROR_NONE = 0,
	CK3M_ERROR_NODEVICE,
	CK3M_ERROR_NOT_HOME,
	CK3M_ERROR_AMP_FAULT,
	CK3M_ERROR_BUSY,
	CK3M_ERROR_INVALID_AXIS,
	CK3M_ERROR_NOUSE,
	CK3M_ERROR_RATE,
};

class CMotionCK3M
{
public:
	CMotionCK3M(void);
	~CMotionCK3M(void);

	//int _getVariable(char cmd_Name[], int & value);

	//read variable int value
	BOOL fnGetVariable(CString strVariableName, int &nValue);

	//int _sendCommand(const std::string command, std::string& reply, BOOL dbgPrint = FALSE);
	//int _sendCommand(char cmd[], char reply[], int iReplyCnt, BOOL dbPrint = FALSE);
	
	//send command to controller, use one interface
	BOOL fnSendCommand(CString strCommand, BOOL dbPrint = FALSE);
	BOOL fnSendCommand(CString strCommand, CString &strReply, BOOL dbPrint = FALSE);

	//BOOL m_fnInitMotion();

	//init motion controller
	BOOL fnInitMotion();

	//void m_fnDeInint();

	//close and deinit controller
	void fnDeInint();

	//int Reset();

	//reset motion controller
	BOOL fnReset();

	//int PVarReset();

	//variables p reset
	BOOL fnPVarReset();

	//int StopSyncMove(void);

	//stop all axes sync move
	BOOL fnStopSyncMove(void);

	//int StopAllAxis(void);
	
	//stop all axes move
	BOOL fnStopAllAxis(void);

	//-->Single Axis Define
	//void m_fnMotionHome(const short & iAxis);
	
	//home one axis
	BOOL fnHomeAxis(const int &nAxis);

	//int	m_fnMovePos(const MOTION_MOVEPARAM & Param, const short & iAxis);

	//single axis abs move, absolute position
	BOOL fnSingleAbsMove(const double dbAbsPos, const int &nAxis);

	//single axis rel move, relative distance
	BOOL fnSingleRelMove(const double dbRelDistance, const int &nAxis);

	//int	m_fnMovePosXY(const MOTION_MOVEPARAM & ParamX, const MOTION_MOVEPARAM & ParamY);

	//XY Axes abs move
	BOOL fnXYAbsMove(const double dbAbsPosX, const double dbAbsPosY);
	
	//XY Axes rel move
	BOOL fnXYRelMove(const double dbRelDistanceX, const double dbRelDistanceY);

	//int	m_fnMoveJog(const MOTION_MOVEPARAM & Param, const short & iAxis);

	//jog move
	BOOL fnJogMove(const double dbSpeed,const int &nAxis);

	//BOOL m_fnIsHomeCompleted(const short & iAxis);
	//BOOL m_fnIsHomeCompleted_Param(int nHomeRtn);

	//check axis is homed
	BOOL fnIsHomeCompleted(const int &nAxis);

	//BOOL m_fnIsMoveCompleted(const short & iAxis);

	//check axis is move done
	BOOL fnIsMoveCompleted(const int &nAxis);

	//int m_fnMovePossible(int nAxis);

	//check axis move possible
	BOOL fnMovePossible(const int &nAxis);

	//double m_fnGetActualPos(const short & iAxis);
	
	//get axis actual position
	double fnGetActualPos(const int &nAxis);

	//void m_fnStopAxis(const short & iAxis);

	//stop axis
	void fnStopAxis(const int &nAxis);

	//void m_fnStopHome(const short & iAxis);
	
	//stop axis home move
	void fnStopHome(const int &nAxis);

	//void m_fnKillAxis(const short & iAxis);
	
	//kill axis move
	void fnKillAxis(const int &nAxis);

	//void m_fnStopJogAxis(const short & iAxis);

	//stop jog move
	void fnStopJog(const int &nAxis);

	//-->Multi Axis Status
	//BOOL m_fnIsMoveXYCompleted(const int & nCurStage);
	
	//check xy move done
	BOOL fnIsXYMoveCompleted();

	//void m_fnGetStatus(STAGE_MOTION_STATUS * pStatus);
	
	/************************************************************************/
	/*  how to use?????
	get all axes status
	void fnGetStatus(MOTION_STATUS *pStatus);
	BOOL m_fnIsHomePosition(int nPVariable);
	int m_fnSetTrigger(const MOTION_TRIGGERPARAM & Param);
	int m_fnCloseTrigger();
	int m_fnSetTriggerAsMM(double dRisingMM, double dFallingMM, double dPeriodeMM);
	int m_fnCloseTriggerAsMM();
	BOOL m_fnIsTiggerSetComplete();
	BOOL m_fnIsTiggerOn();
	int TriggerOnProg1(int nRising, int nFalling, int nCycle);
	int TriggerOffProg1();
	int RepeatMoveProg1();
	int RepeatMoveHomeProg1();
	int RepeatMoveStopProg1();
	*/
	/************************************************************************/

private:
	//convert controller reply to bit status
	void fnConvertResponseToBit(CString strResponse, CString &strStatusBit);

private:
	//critical 
	HANDLE m_hMutex;
	CCriticalSection m_DataCriticalSection;

	//ck3m controller
	PowerPMACcontrol	m_Control;

	//error code
	int m_nErrorCode;

	//open flag
	BOOL			m_bCK3MOpen;
	
	//axis config param
	TAXISCONFIG_CK3M m_AxisCfgParam[MAX_AXIS_NUM];

	//controller config param
	TDEVICECONFIG_CK3M	m_DeviceConfig;
};
#endif