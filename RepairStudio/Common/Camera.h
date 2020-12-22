#ifndef _CAMERA_H
#define _CAMERA_H 
#include "../include/MIL_x64/mil.h"
#include "../include/MIL_x64/MILDyn/milim.h"
#include "../Common/Sequence.h"

class CCriticalSection;
class CCamera : public CSequence
{
public:
	CCamera(void);
	~CCamera(void);

	BOOL Initialize_Solios(int nBoardNo, int nWidth, int nHeight, int nBand, CString strDCF);
	void fnSetApplication(MIL_ID nApp);
	int Sequence();
	void Finalize();

	MIL_ID fnGetApplication();
	void fnGetImageData(BYTE* pData);
	void fnSetWhiteBalance(const float & fR, const float & fG, const float & fB);
	void fnSetBayer(MIL_ID milVal = M_BAYER_GR);

private:
	static MIL_ID m_milApplication;
	static MIL_ID m_milSystem;

	MIL_ID m_milDigitizer;
	MIL_ID m_milDisplay;
	MIL_ID m_milGrabBuffers[2];
	MIL_ID m_milLiveImageResultBuffer;
	MIL_ID m_MilWBCoeff;
	MIL_ID m_milXX;

	int m_nLastGrabBufferIndex;
	int m_nCurrentGrabBufferIndex;
	float m_fCoeff[3];
	BYTE*m_byteGrab;
	int	m_BoardType;
	MIL_ID m_milBayer;
	CCriticalSection m_DataCriticalSection;
};



#endif // !CAMERA_H
