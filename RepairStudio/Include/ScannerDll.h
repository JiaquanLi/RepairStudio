//�������mmΪ��λ


#pragma once
#include "CommonDefine.h"

class CScannerDll  
{
public:
	virtual ~CScannerDll(){};	

	virtual void fnGetVersion(CString &strName,CString &strVersion) = 0;
	virtual BOOL fnInitDevice(const SCAN_PARAM& param,UINT nLaserCtrMode = 0,int nCardIndex=0,BOOL bMode3d = FALSE,BOOL bMaster = FALSE) = 0;
	virtual BOOL fnCloseDevice(int nCardIndex=0) = 0;	
	//�������ò���
	virtual BOOL fnSetParam(const SCAN_PARAM& param,int nCardIndex=0) = 0;
	virtual BOOL fnSetCraftParam(const SCAN_CRAFT& craft,int nCardIndex=0) = 0;
	virtual BOOL fnSetCraftParamToList(const SCAN_CRAFT& craft,int nCardIndex=0) = 0;
	//������������
	virtual BOOL fnSetMarkSpeed(double dbSpeed = 1000,int nCardIndex=0) = 0;
	virtual BOOL fnSetJumpSpeed(double dbSpeed = 1000,int nCardIndex=0) = 0;
	//�б���Ʋ���
	virtual BOOL fnOpenList(int nListNo = 1,int nCardIndex=0) = 0;
	virtual BOOL fnCloseList(int nCardIndex=0) = 0;
	virtual BOOL fnExecuteListEx(INT& bWorkFlag,BOOL bWait = TRUE,int nCardIndex=0) = 0;
	virtual BOOL fnExecuteList(BOOL bWait=TRUE,int nCardIndex=0,BOOL bMasterMode=FALSE) = 0;
	virtual BOOL fnJustWaitScanDone(INT& bWorkFlag,int nCardIndex=0) = 0;
	virtual BOOL fnAutoChangeList(int nCardIndex=0) = 0;
	virtual BOOL fnStopMarking(int nCardIndex=0,BOOL bMasterMode=FALSE) = 0;
	//�񾵿��Ʋ���
	virtual BOOL fnFastJump(const DPOINT& pt,int nCardIndex=0) = 0;
	virtual BOOL fnAbsJump(const DPOINT& pt,int nCardIndex=0) = 0;
	virtual BOOL fnScanPoint(const DPOINT& pt,double dbTime,int nCardIndex=0) = 0;
	virtual BOOL fnScanLine(const DPOINT& ptEnd,int nCardIndex=0) = 0;
	virtual BOOL fnScanLine(const DPOINT& ptStr,const DPOINT& ptEnd,int nCardIndex=0) = 0;	
	virtual BOOL fnScanArc(const DPOINT& ptC,double dbAngle,int nCardIndex=0) = 0;
	virtual BOOL fnScanArc(const DPOINT& ptC,const DPOINT& ptStr,double dbAngle,int nCardIndex=0) = 0;
	virtual BOOL fnScanCirFilledLN(const DPOINT &center, double dbRadius,double dbFilledStep,int nCardIndex=0) = 0;//Բ����ֱ�����
	virtual BOOL fnScanCirFilledLX(const DPOINT &center, double dbRadius,double dbFilledStep,double dbRatio,int nCardIndex=0) = 0;//Բ�����������
	//�񾵿̻�ʮ��
	virtual BOOL fnScanCross(const DPOINT& ptC,double dbWidth,double dbSpeed,int nCardIndex=0) = 0;
	//�񾵼�����Ʋ���
	virtual BOOL fnOpenLaser(BOOL bOpen=TRUE,int nCardIndex=0) = 0;

	//IO����
	//ģ����� 0~10V
	virtual BOOL fnSetAnalogOut(double dbValue,int nCardIndex=0,int nPort = 0,BOOL bInList = FALSE) = 0;
	virtual BOOL fnSetDigitalOutputBit(int bValue,int nBit = 0,int nCardIndex=0) = 0;
	virtual BOOL fnSetDigitalOutputPort(int nValue,int nCardIndex=0) = 0;
	virtual BOOL fnGetDigitalOutputPort(int& nValue,int nCardIndex=0) = 0;
	virtual BOOL fnGetDigitalInputPort(int& nValue,int nCardIndex=0) = 0;

	//Laser1 Laser2 PWM Setting
	virtual BOOL fnSetLaserPwm(double dbFreq,double dbDuty,int nCardIndex=0) = 0;
	virtual BOOL fnSetLaserPwmStandby(double dbFreq,double dbDuty,int nCardIndex=0) = 0;//set_laser_mode 4,6
	virtual BOOL fnSetFirstPulseKiller(double dbValue,int nCardIndex=0) = 0;//us

	//3d opreration
	virtual BOOL fnSetScaleZ(double dbScaleZ,int nCardIndex=0) = 0;
	virtual BOOL fnSetZposList(double dbZposition,int nCardIndex=0) = 0;
	virtual BOOL fnSetZpos(double dbZposition,int nCardIndex=0) = 0;

	virtual CString fnGetLastErr() = 0;	
	
	/*
	virtual BOOL fnSetRotate(double dbRotate,int nCardIndex=0) = 0;
	virtual BOOL fnSetScale(double dbScale,int nCardIndex=0) = 0;    

	virtual BOOL fnSetMarkSpeed(double dbMarkSpeed,int nCardIndex=0) = 0;
	virtual BOOL fnSetJumpSpeed(double dbJumpSpeed,int nCardIndex=0) = 0;
	virtual BOOL fnExecuteList(BOOL bWait=TRUE,int nListNo = 1,int nCardIndex=0) = 0;
	virtual BOOL fnGetListStatus(BOOL &bBusy,int nListNo = 1,int nCardIndex=0) = 0;
	virtual BOOL fnGetHeadStatus(UINT &nStatus,int nCardIndex=0) = 0;

	virtual BOOL fnOpenLaser(int nCardIndex=0) = 0;
	virtual BOOL fnCloseLaser(int nCardIndex=0) = 0;
	virtual BOOL fnZero(int nCardIndex=0) = 0;	

	virtual BOOL fnScanPoint(double dbX,double dbY,double dbTime,int nCardIndex=0) = 0;
	virtual BOOL fnScanLine(double dbX, double dbY,int nCardIndex=0 ,SEG_TYPE nLineType=SEG_TYPE_SINGLE) = 0;
	virtual BOOL fnScanArc(double dbCenterX, double dbCenterY, double dbAngle,
		int nCardIndex=0,SEG_TYPE nArcType=SEG_TYPE_SINGLE,double dbEndX=0,double dbEndY=0) = 0;
	virtual BOOL fnAbsJump(double dbX,double dbY,int nCardIndex=0) = 0;			

	
	virtual BOOL fnSetSkyWriting(double dbTimeLag,int iLsrOnSft,int nCardIndex=0) = 0;
	virtual BOOL fnSetWobble(int nPrf,double dbAmp1,double dbAmp2,int nCardIndex=0) = 0;
	virtual BOOL fnSetAnalogOut(double dbIDI,int nCardIndex=0) = 0;
	virtual BOOL fnSetPWM(double dbTrigHz,double dbPwm,int nCardIndex=0) = 0;
	virtual BOOL fnSetFirstPulseKill(int nKillTime,int nCardIndex=0) = 0;

	virtual BOOL fnSetOutputBit(int nBitIndex,BOOL bOpen,int nCardIndex=0) = 0;
	virtual BOOL fnGetOutputBit(int nBitIndex,BOOL &bOpen,int nCardIndex=0) = 0;
	virtual BOOL fnGetOutput( UINT &nReturnValue, int nCardIndex=0) = 0;


	virtual BOOL fnGetInputBit(int nBitIndex,BOOL &bOpen,int nCardIndex=0) = 0;
	virtual BOOL fnGetInput( UINT &nReturnValue, int nCardIndex=0) = 0;
	virtual CString fnGetLastErr() = 0;	

	
	//for 3d use------------------
	virtual BOOL fnSetScaleZ(double dbScaleZ,int nCardIndex=0) = 0;
	virtual BOOL fnSetZposList(double dbZposition,int nCardIndex=0) = 0;
	virtual BOOL fnSetZpos(double dbZposition,int nCardIndex=0) = 0;
	virtual BOOL fnScanArc3d(double dbCenterX, double dbCenterY, double dbCenterZ,double dbAngle,int nCardIndex=0,
		SEG_TYPE nArcType=SEG_TYPE_SINGLE,double dbEndX=0, double dbEndY=0, double dbEndZ=0) = 0;
	virtual BOOL fnScanLine3d(double dbX, double dbY,double dbZ,int nCardIndex=0) = 0;	
	virtual BOOL fnAbsJump3d(double dbX,double dbY,double dbZ,int nCardIndex=0) = 0;	
	virtual BOOL fnScanPoint3d(double dbX,double dbY,double dbZ,double dbTime,int nCardIndex=0) = 0;
	*/


protected:
	SCAN_PARAM m_caParam[8];		//�������
	CString m_strLastErr;		//���������Ϣ
	/*
	double	m_dbScale[8];			//�������ֵ
	double	m_dbScaleZ[8];			//����Zƽ�����ֵ	
	double  m_dbRotate[8];			//�񾵰�װ�Ƕ�
	*/

	
};
/***************************** 
* FunctionName: _declspec 
* 
* Function:��õ�ǰ����ģ�����ָ��,�ýӿ���ҪΪDLL����ӿ�
* return[CScannerDll *]���ض���ָ��
*****************************/
extern "C" _declspec(dllexport) CScannerDll* fnCreateScanDLLPtr();

/***************************** 
* FunctionName: _declspec 
* 
* Function:ɾ������ģ��ָ�����,�ýӿ���ҪΪDLL����ӿ�
* param[in] pScanner����ģ��ָ�� 
*****************************/
extern "C" _declspec(dllexport) void fnDeleteScanDLLPtr(CScannerDll* pScanner);

