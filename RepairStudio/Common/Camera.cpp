#include "stdafx.h"
#include "Camera.h"



MIL_ID CCamera::m_milApplication = M_NULL;
MIL_ID CCamera::m_milSystem = M_NULL;

CCamera::CCamera(void)
{
	m_milDigitizer = M_NULL;
	m_milDisplay = M_NULL;

	m_BoardType = 0;
	m_nLastGrabBufferIndex = 0;
	m_nCurrentGrabBufferIndex = 0;

	m_byteGrab = NULL;

	m_MilWBCoeff = NULL;
	m_milXX = M_NULL;
	m_milBayer = M_BAYER_GB;
}

CCamera::~CCamera(void)
{
}

void CCamera::fnSetApplication(MIL_ID nApp)
{
	m_milApplication = nApp;
}

MIL_ID CCamera::fnGetApplication()
{
	return m_milApplication;
}

void CCamera::fnGetImageData(BYTE* pData)
{
	memcpy(pData, m_byteGrab, sizeof(m_byteGrab));
}

BOOL CCamera::Initialize_Solios(int nBoardNo, int nWidth, int nHeight, int nBand, CString strDCF)
{
#ifdef _MIL_SIMUL_
	return 0;
#else
	m_byteGrab = new BYTE[nWidth * nHeight * nBand];

	m_BoardType = nBoardNo;

	CFileFind ff;
	BOOL bFind = ff.FindFile(strDCF);
	ff.Close();
	if (!bFind)
	{
		return FALSE;
	}
	if (!m_milApplication)
	{
		MappAlloc(M_DEFAULT, &m_milApplication);
		MappControl(M_ERROR, M_PRINT_DISABLE);
	}

	{
		MsysAlloc(M_SYSTEM_RADIENTEVCL, nBoardNo, M_DEFAULT, &m_milSystem);//M_SYSTEM_SOLIOS
	}
	MdispAlloc(m_milSystem, M_DEFAULT, _T("M_DEFAULT"), M_WINDOWED + M_GDI_OVERLAY, &m_milDisplay);
	MdigAlloc(m_milSystem, 0, strDCF, M_DEFAULT, &m_milDigitizer);
    
	MdigControl(m_milDigitizer, M_GRAB_MODE, M_ASYNCHRONOUS);
	MdigControl(m_milDigitizer, M_GRAB_TIMEOUT, 2000);


	MbufAllocColor(m_milSystem, nBand, nWidth, nHeight, 8 + M_UNSIGNED, M_IMAGE + M_GRAB + M_PROC + M_DISP, &m_milLiveImageResultBuffer);
	for (int n = 0; n < 2; n++)
	{
		MbufAlloc2d(m_milSystem, nWidth, nHeight, 8 + M_UNSIGNED, M_IMAGE + M_GRAB + M_PROC + M_DISP, &(m_milGrabBuffers[n]));
	}

	return TRUE;
#endif
}

void CCamera::Finalize()
{
	if (m_byteGrab != NULL)
	{
		delete[] m_byteGrab;
	}
#ifndef _MIL_SIMUL_
	MdigControl(m_milDigitizer, M_GRAB_ABORT, M_DEFAULT);

	for (int i = 0; i < 2; i++)
	{
		if (m_milGrabBuffers[i] != M_NULL)
		{
			MbufFree(m_milGrabBuffers[i]);
			m_milGrabBuffers[i] = M_NULL;
		}
	}

	if (!m_milLiveImageResultBuffer)
	{
		MbufFree(m_milLiveImageResultBuffer);
	}

	if (m_milDisplay != M_NULL)
	{
		MdispFree(m_milDisplay);
		m_milDisplay = M_NULL;
	}

	if (m_milSystem != M_NULL)
	{
		MsysFree(m_milSystem);
		m_milSystem = M_NULL;
	}

	if (m_milApplication != M_NULL)
	{
		MappFree(m_milApplication);
		m_milApplication = M_NULL;
	}
#endif

}

int CCamera::Sequence()
{

#ifdef _MIL_SIMUL_
	return 0;
#else
	int nRet = 0;
	m_DataCriticalSection.Lock();
	MappTimer(M_TIMER_RESET, M_NULL);
	MdigGrab(m_milDigitizer, m_milGrabBuffers[m_nCurrentGrabBufferIndex]);

	MIL_ID milCurrentProcBuffer = m_milGrabBuffers[m_nLastGrabBufferIndex];
	
	MbufBayer(milCurrentProcBuffer, m_milLiveImageResultBuffer, m_MilWBCoeff, m_milBayer);
	MbufGetColor(m_milLiveImageResultBuffer, M_PACKED | M_RGB24, M_ALL_BANDS, m_byteGrab);

	m_nLastGrabBufferIndex = m_nCurrentGrabBufferIndex;

	if (m_nLastGrabBufferIndex == 0) m_nCurrentGrabBufferIndex = 1;
	else m_nCurrentGrabBufferIndex = 0;

	Sleep(50);
	m_DataCriticalSection.Unlock();

	return nRet;
#endif
}

void CCamera::fnSetWhiteBalance(const float & fR, const float & fG, const float & fB)
{
#ifndef _MIL_SIMUL_
	MbufAlloc1d(m_milSystem, 3, 32 + M_FLOAT, M_ARRAY, &m_MilWBCoeff);
	m_fCoeff[0] = fR;	// RED
	m_fCoeff[1] = fG;	// GREEN
	m_fCoeff[2] = fB;	// BLUE

	MbufPut1d(m_MilWBCoeff, 0, 3, m_fCoeff);
#endif
}
void CCamera::fnSetBayer(MIL_ID milVal)
{
	m_milBayer = milVal;
}
