
#include "stdafx.h"
#include "XHitachiF202.h"
#include <stdio.h>
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
// CSerialPort

IMPLEMENT_DYNCREATE(XHitachiF202, CWinThread)


XHitachiF202::XHitachiF202()
: m_evCommRcvd( FALSE, TRUE )	// Initially Own = FALSE, Manual Reset = TRUE
{
	memset(m_cRcvBuff, 0, sizeof(m_cRcvBuff));
	memset(m_szSendData, 0, sizeof(m_szSendData));
	memset(m_szSendGetData, 0, sizeof(m_szSendGetData));

	m_dwLen = 0;
	m_nSeqNo = 0;
	m_nSeqNoGet = 0;
	m_dwTickCount = 0;
	m_nRetryNo = 0;
//	m_nCurPatternIdx = 0;
	CString strBuff;

////	if(m_DiverLog.OpenFile(PG_LOG_PATH, _T("PG")) == -1) {
////		strBuff.Format(_T("Log Path(%s) is Wrong"), PG_LOG_PATH);
//		AfxMessageBox(strBuff);
//	}
//	else {
//		m_DiverLog.SetKeepDays(30);
//		m_DiverLog.TextOut(_T("P/G Log Open Ok"));
//	}
}

XHitachiF202::~XHitachiF202()
{
}

int XHitachiF202::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(XHitachiF202, CWinThread)
	//{{AFX_MSG_MAP(CSerialPort)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerialPort message handlers

//void XSchottController::DataReceived()
//{
//	//dwLen = Read( m_cRcvBuff, 256 );
//	m_dwLen = Read( m_cRcvBuff, 1024 ); // Changed 2005.12.14
//	//Flush();
//	m_evCommRcvd.SetEvent();
//}

void XHitachiF202::OnNewRxChar()
{
	int nRcvBytes = 0;
	char szRcvBuffer[2048] = {NULL,};

	do 
	{
		if(!IsOpen())
		{
			break;
		}
		if(m_dwLen > 1023)
		{
			break;
		}
		nRcvBytes = Read( szRcvBuffer, 1024 );
		memcpy(&m_cRcvBuff[m_dwLen], szRcvBuffer, nRcvBytes);
		m_dwLen += nRcvBytes;
	} while (nRcvBytes > 0);
}

void XHitachiF202::OnNewRxFlag()
{
	m_DataCriticalSection.Lock(); // Added 2011.06.08
	{
		m_dwLen = Read( m_cRcvBuff, 1024 );
	}
	m_DataCriticalSection.Unlock();

	m_evCommRcvd.SetEvent();
}

void XHitachiF202::ResetBuffer()
{
	m_dwLen = 0;
	memset(m_cRcvBuff, 0x00, sizeof(m_cRcvBuff));
}

BOOL XHitachiF202::IsCommRcvd()
{
	BOOL bRcvd = FALSE;

	CSingleLock commRcvd( &m_evCommRcvd );

	commRcvd.Lock( 0 );
	bRcvd = commRcvd.IsLocked();
	if( bRcvd ) 
	{
		m_evCommRcvd.ResetEvent();
	}
	return bRcvd;
}

BOOL XHitachiF202::IsCommRcvdWithStealth()
{
	BOOL bRcvd = FALSE;

	CSingleLock commRcvd( &m_evCommRcvd );

	commRcvd.Lock( 0 );
	bRcvd = commRcvd.IsLocked();
	return bRcvd;
}


BOOL XHitachiF202::GetReceivedData(char* pszBuffer)
{
	m_DataCriticalSection.Lock();
	{
		memcpy(pszBuffer, m_cRcvBuff, sizeof(m_cRcvBuff));
	}
	m_DataCriticalSection.Unlock();

	return TRUE;
}
char* XHitachiF202::GetReceivedData()
{
	return m_cRcvBuff;
}

BOOL XHitachiF202::IsRcvdLength(int nLen)
{
	if(m_dwLen >= nLen)
	{
		return TRUE;
	}
	return FALSE;
}


void XHitachiF202::Purge()
{
	//PurgeComm( m_hCom, PURGE_RXCLEAR | PURGE_RXABORT );
	PurgeComm( m_hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR );	// clear all the buffer
}
BOOL XHitachiF202::GetConnect()
{
	return IsOpen();
}

char XHitachiF202::MakeBCC(char * pszInput, int nLength)
{
	char cRet = 0;
	char * pUpper = NULL;	
	pUpper = _strupr(pszInput);
	for(int i = 0; i < nLength; i++)				
	{
		cRet ^=	pUpper[i];		    //All Data make XOR
	}

	return cRet;
}

//--> 20151002.OCH.MODIFY.S
BOOL XHitachiF202::SetPortOpen(UINT uiComPort)
{
	if(uiComPort == 0)
	{
		return FALSE;
	}

	CString strCOM;
	DCB userDCB;
	userDCB.BaudRate = CBR_115200;//CBR_9600; @slc 20200411 change 
	userDCB.ByteSize  = 8;
	userDCB.Parity = NOPARITY;
	userDCB.StopBits = ONESTOPBIT;
	userDCB.EvtChar = XCommThread::CR;
	
	strCOM.Format(_T("COM%d"), uiComPort);

	SetUserDCB(userDCB);
	if(Open(strCOM, EV_RXCHAR, NULL)) 
	{
		Flush();
		return TRUE;
	}

	return FALSE;
}

/*
int XHitachiF202::SeqGetCommand(HITACHI_GETCMD nType, int& nValue)
{
	if(!IsOpen())
	{
		return _CONNECT;
	}

	char szCommand[20];
	int nRet = 0;
	int nLength = 0;
	char* pRetBuff;
	int nSeqNo = m_nSeqNo;
	int nHex1, nHex2, nHex3;
	static int nDataSize = 0;

	switch(nSeqNo)
	{
	case 0:
		ResetBuffer();
		szCommand[0] = 0x05;
		nLength = 1;
		if(Write(szCommand, nLength))
		{
			m_dwTickCount = GetTickCount();
			nSeqNo = 100;	
		}
		else 
		{
			nRet = -3;
			nSeqNo = 0;
		}
		break;		
	case 100:
		if(IsRcvdLength(1))
		{				
			pRetBuff = (char*)GetReceivedData();	

			if( pRetBuff[0] == 0x06)
			{
				nSeqNo = 150;
			}
			else
			{
				m_nRetryNo++;
				if(m_nRetryNo >= 3)
				{
					nRet = -101;
					m_nRetryNo = 0;
					nSeqNo = 0;
				}
				else
				{
					nSeqNo = 0;
				}
			}
		}
		else if(GetElapseTime(m_dwTickCount) > 1000)
		{
			m_nRetryNo++;
			if(m_nRetryNo >= 3)
			{
				nRet = -101;
				m_nRetryNo = 0;
				nSeqNo = 0;
			}
			else 
			{
				nSeqNo = 0;
			}
		}
		break;
	case 150:
		ResetBuffer();
		GetGetCommandFormat(nType, szCommand, nDataSize);
		nLength = 18;
		if(Write(szCommand, nLength))
		{
			m_dwTickCount = GetTickCount();
			nSeqNo = 200;	
		}
		else 
		{
			nRet = -3;
			nSeqNo = 0;
		}
		break;		
	case 200:
		if(IsRcvdLength(11))
		{				
			pRetBuff = (char*)GetReceivedData();	

			if( pRetBuff[0] == 0x06)
			{
				int nTempValue;
				double dPow;

				nSeqNo = 300;

				nHex1 = ConvertAsciiToHex(&(pRetBuff[2]));
				dPow = (double)nHex1;
				nTempValue = nHex1;
				
				if( nDataSize >= 2)
				{
					nTempValue = (nTempValue << 8);

					nHex2 = ConvertAsciiToHex(&(pRetBuff[4]));
					nTempValue |= nHex2;
				}

				if( nDataSize >= 3)
				{
					nTempValue = (nTempValue << 8);

					nHex3 = ConvertAsciiToHex(&(pRetBuff[6]));
					nTempValue |= nHex3;
				}


				if( nType == HTGETCMD_SHUTTER)
					nValue = (pow(10.0, dPow+1.0) * ( 1.0 + ((double)nHex2 / (double)0x100) * 9.0)) / 1000;
				else
					nValue = nTempValue;
			}
			else
			{
				m_nRetryNo++;
				if(m_nRetryNo >= 3)
				{
					nRet = -101;
					m_nRetryNo = 0;
					nSeqNo = 0;
				}
				else
				{
					nSeqNo = 0;
				}
			}
		}
		else if(GetElapseTime(m_dwTickCount) > 1000)
		{
			m_nRetryNo++;
			if(m_nRetryNo >= 3)
			{
				nRet = -251;
				m_nRetryNo = 0;
				nSeqNo = 0;
			}
			else 
			{
				nSeqNo = 0;
			}
		}
		break;
	case 300:
		ResetBuffer();
		szCommand[0] = 0x06;
		nLength = 1;
		if(Write(szCommand, nLength))
		{
			m_dwTickCount = GetTickCount();
			nSeqNo = 0;	
			nRet = 300;
		}
		else 
		{
			nRet = -301;
			nSeqNo = 0;
		}
		break;		
	}

	m_nSeqNo = nSeqNo;

	return nRet;
}
*/
int XHitachiF202::SeqGetCommand(HITACHI_GETCMD nType, int& nValue)
{
	if(!IsOpen())
	{
		return _CONNECT;
	}

	char szCommand[20];
	int nRet = 0;
	int nLength = 0;
	char* pRetBuff;
	int nSeqNo = m_nSeqNo;
	int nHex1, nHex2, nHex3;
	static int nDataSize = 0;

	ResetBuffer();
	szCommand[0] = 0x05;
	nLength = 1;
	if(Write(szCommand, nLength) == FALSE)
	{
		return -3;
	}

	m_nRetryNo = 0;
	while(TRUE)
	{
		if(IsRcvdLength(1))
			break;

		Sleep(10);

		m_nRetryNo++;
		if( m_nRetryNo > 1000)
			return -10;
	}

	pRetBuff = (char*)GetReceivedData();	

	if( pRetBuff[0] != 0x06)
	{
		return -20;
	}

	ResetBuffer();
	GetGetCommandFormat(nType, szCommand, nDataSize);
	nLength = 18;
	if(Write(szCommand, nLength) == FALSE)
	{
		return -30;
	}

	m_nRetryNo = 0;
	while(TRUE)
	{
		if(IsRcvdLength(11))
			break;

		Sleep(10);

		m_nRetryNo++;
		if( m_nRetryNo > 1000)
			return -40;
	}
			
	pRetBuff = (char*)GetReceivedData();	

	if( pRetBuff[0] != 0x06)
		return -50;

	int nTempValue;
	double dPow;

	nHex1 = ConvertAsciiToHex(&(pRetBuff[2]));
	dPow = (double)nHex1;
	nTempValue = nHex1;
	
	if( nDataSize >= 2)
	{
		nTempValue = (nTempValue << 8);

		nHex2 = ConvertAsciiToHex(&(pRetBuff[4]));
		nTempValue |= nHex2;
	}

	if( nDataSize >= 3)
	{
		nTempValue = (nTempValue << 8);

		nHex3 = ConvertAsciiToHex(&(pRetBuff[6]));
		nTempValue |= nHex3;
	}

	if( nType == HTGETCMD_SHUTTER)
		nValue = (int)((pow(10.0, dPow+1.0) * ( 1.0 + ((double)nHex2 / (double)0x100) * 9.0)) / 1000 + 1);
	else
		nValue = nTempValue;

	ResetBuffer();
	szCommand[0] = 0x06;
	nLength = 1;
	if(Write(szCommand, nLength) == FALSE)
		return -60;

	return 100;
}
/*
int XHitachiF202::SeqSetCommand(HITACHI_SETCMD nType, int nValue)
{
	if(!IsOpen())
	{
		return _CONNECT;
	}

	char szCommand[20];
	int nRet = 0;
	int nLength = 0;
	char* pRetBuff;
	int nSeqNo = m_nSeqNo;

	switch(nSeqNo)
	{
	case 0:
		ResetBuffer();
		szCommand[0] = 0x05;
		nLength = 1;
		if(Write(szCommand, nLength))
		{
			m_dwTickCount = GetTickCount();
			nSeqNo = 100;	
		}
		else 
		{
			nRet = -3;
			nSeqNo = 0;
		}
		break;		
	case 100:
		if(IsRcvdLength(1))
		{				
			pRetBuff = (char*)GetReceivedData();	

			if( pRetBuff[0] == 0x06)
			{
				nSeqNo = 150;
			}
			else
			{
				m_nRetryNo++;
				if(m_nRetryNo >= 3)
				{
					nRet = -101;
					m_nRetryNo = 0;
					nSeqNo = 0;
				}
				else
				{
					nSeqNo = 0;
				}
			}
		}
		else if(GetElapseTime(m_dwTickCount) > 1000)
		{
			m_nRetryNo++;
			if(m_nRetryNo >= 3)
			{
				nRet = -101;
				m_nRetryNo = 0;
				nSeqNo = 0;
			}
			else 
			{
				nSeqNo = 0;
			}
		}
		break;
	case 150:
		ResetBuffer();
		GetSetCommandFormat(nType, nValue, szCommand);
		nLength = 18;
		if(Write(szCommand, nLength))
		{
			m_dwTickCount = GetTickCount();
			nSeqNo = 200;	
		}
		else 
		{
			nRet = -3;
			nSeqNo = 0;
		}
		break;		
	case 200:
		if(IsRcvdLength(1))
		{				
			pRetBuff = (char*)GetReceivedData();	

			if( pRetBuff[0] == 0x06)
			{
				nSeqNo = 0;
				nRet = 250;
			}
			else
			{
				m_nRetryNo++;
				if(m_nRetryNo >= 3)
				{
					nRet = -251;
					m_nRetryNo = 0;
					nSeqNo = 0;
				}
				else
				{
					nSeqNo = 0;
				}
			}
		}
		else if(GetElapseTime(m_dwTickCount) > 1000)
		{
			m_nRetryNo++;
			if(m_nRetryNo >= 3)
			{
				nRet = -251;
				m_nRetryNo = 0;
				nSeqNo = 0;
			}
			else 
			{
				nSeqNo = 0;
			}
		}
		break;
	}

	m_nSeqNo = nSeqNo;

	return nRet;
}
*/
int XHitachiF202::SeqSetCommand(HITACHI_SETCMD nType, int nValue)
{
	if(!IsOpen())
	{
		return _CONNECT;
	}

	char szCommand[20];
	int nRet = 0;
	int nLength = 0;
	char* pRetBuff;
	int nSeqNo = m_nSeqNo;

	ResetBuffer();
	szCommand[0] = 0x05;
	nLength = 1;
	if(Write(szCommand, nLength) == FALSE)
		return -10;

	m_nRetryNo = 0;
	while(TRUE)
	{
		if(IsRcvdLength(1))
			break;

		Sleep(10);

		m_nRetryNo++;
		if( m_nRetryNo > 1000)
			return -20;
	}

	pRetBuff = (char*)GetReceivedData();	

	if( pRetBuff[0] != 0x06)
		return -30;

	ResetBuffer();
	GetSetCommandFormat(nType, nValue, szCommand);
	nLength = 18;
	if(Write(szCommand, nLength) == FALSE)
		return -40;

	m_nRetryNo = 0;
	while(TRUE)
	{
		if(IsRcvdLength(1))
			break;

		Sleep(10);

		m_nRetryNo++;
		if( m_nRetryNo > 1000)
			return -50;
	}

	pRetBuff = (char*)GetReceivedData();	

	if( pRetBuff[0] != 0x06)
		return -60;

	return 100;
}

void XHitachiF202::GetGetCommandFormat(HITACHI_GETCMD nType, char* szCommand, int &nDataSize)
{
	int nCmdHexSum = 0;

	szCommand[0] = 0x02;
	szCommand[1] = '0';
	szCommand[2] = '0';
	szCommand[3] = 'F';
	szCommand[4] = 'F';
	switch( nType)
	{
	case HTGETCMD_GAIN:
		memcpy( szCommand+5, "810C000000", 10);
		nDataSize = 2;
		break;
	case HTGETCMD_SHUTTER:
		memcpy( szCommand+5, "8111000000", 10);
		nDataSize = 2;
		break;
	case HTGETCMD_WB_MODE:
		memcpy( szCommand+5, "8129000000", 10);
		nDataSize = 1;
		break;
	case HTGETCMD_WB_RED:
		memcpy( szCommand+5, "812A000000", 10);
		nDataSize = 1;
		break;
	case HTGETCMD_WB_BLUE:
		memcpy( szCommand+5, "812B000000", 10);
		nDataSize = 1;
		break;
	case HTGETCMD_BRIGHTNESS:
		memcpy( szCommand+5, "8117000000", 10);
		nDataSize = 1;
		break;
	}
	szCommand[15] = 0x03;

	for( int i=0; i<16; i++)
	{
		nCmdHexSum += szCommand[i];
	}

	nCmdHexSum ^= 0xFF;
	nCmdHexSum &= 0xFF;

	ConvertHexToAscii(nCmdHexSum, &(szCommand[16]));
}

void XHitachiF202::GetSetCommandFormat(HITACHI_SETCMD nType, int nValue, char* szCommand)
{
	int nCmdHexSum = 0;
	int nHex;
	int nTempValue;
	int nShutterX, nShutterYY;

	memset( szCommand, 0, 18);

	szCommand[0] = 0x02;
	szCommand[1] = '0';
	szCommand[2] = '0';
	szCommand[3] = 'F';
	szCommand[4] = 'F';
	switch( nType)
	{
	case HTSETCMD_GAIN:
		szCommand[5] = '0';
		szCommand[6] = '1';
		szCommand[7] = '0';
		szCommand[8] = 'C';
		nHex = (nValue >> 8) & 0xFF;
		ConvertHexToAscii(nHex, &(szCommand[9]));
		nHex = (nValue & 0xFF);
		ConvertHexToAscii(nHex, &(szCommand[11]));
		break;
	case HTSETCMD_SHUTTER_SPEED:
		szCommand[5] = '0';
		szCommand[6] = '1';
		szCommand[7] = '1';
		szCommand[8] = '1';
		nTempValue = nValue*1000;
		nShutterX = ((int)log10((double)nTempValue))-1;
		nShutterYY = (int)(((double)nTempValue/pow(10.0, double(nShutterX+1))-1.0) * ((double)0x100/9.0));
		ConvertHexToAscii(nShutterX, &(szCommand[9]));
		ConvertHexToAscii(nShutterYY, &(szCommand[11]));
		break;
	case HTSETCMD_WB_MODE:
		szCommand[5] = '0';
		szCommand[6] = '1';
		szCommand[7] = '2';
		szCommand[8] = '9';
		nHex = (nValue & 0xFF);
		ConvertHexToAscii(nHex, &(szCommand[9]));
		break;
	case HTSETCMD_WB_RED:
		szCommand[5] = '0';
		szCommand[6] = '1';
		szCommand[7] = '2';
		szCommand[8] = 'A';
		nHex = (nValue & 0xFF);
		ConvertHexToAscii(nHex, &(szCommand[9]));
		break;
	case HTSETCMD_WB_BLUE:
		szCommand[5] = '0';
		szCommand[6] = '1';
		szCommand[7] = '2';
		szCommand[8] = 'B';
		nHex = (nValue & 0xFF);
		ConvertHexToAscii(nHex, &(szCommand[9]));
		break;
	case HTSETCMD_BRIGHTNESS:
		szCommand[5] = '0';
		szCommand[6] = '1';
		szCommand[7] = '1';
		szCommand[8] = '7';
		nHex = (nValue & 0xFF);
		ConvertHexToAscii(nHex, &(szCommand[9]));
		break;
	}
	szCommand[13] = 0x00;
	szCommand[14] = 0x00;
	szCommand[15] = 0x03;

	for( int i=0; i<16; i++)
	{
		nCmdHexSum += szCommand[i];
	}

	nCmdHexSum ^= 0xFF;
	nCmdHexSum &= 0xFF;

	ConvertHexToAscii(nCmdHexSum, &(szCommand[16]));

}

void XHitachiF202::ConvertHexToAscii(int nHex, char* szAscii)
{
	int nCh;

	nHex &= 0xFF;

	nCh = (nHex >> 4) & 0x0F;
	if( nCh <= 9)
		szAscii[0] = nCh + '0';
	else
		szAscii[0] = (nCh-10) + 'A';

	nCh = (nHex & 0x0F);
	if( nCh <= 9)
		szAscii[1] = nCh + '0';
	else
		szAscii[1] = (nCh-10) + 'A';

}

int XHitachiF202::ConvertAsciiToHex(char* szAscii)
{
	int nCh;
	int nNum = 0;
	char szNum[3];

	szNum[0] = szAscii[0];
	szNum[1] = szAscii[1];
	szNum[2] = 0;

	nCh = szAscii[0];
	if( nCh <= '9')
		nCh -= '0';
	else
	{	
		nCh -= 'A';
		nCh += 10;
	}

	nNum = nCh << 4;

	nCh = szAscii[1];
	if( nCh <= '9')
		nCh -= '0';
	else
	{	
		nCh -= 'A';
		nCh += 10;
	}

	nNum += nCh;

	return nNum;
}
