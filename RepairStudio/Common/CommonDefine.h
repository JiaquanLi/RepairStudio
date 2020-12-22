/************************************************************************/
/* ���ڶ���һЩ���õ�ȫ�ֱ������궨�壬�ṹ���                                                                     */
/************************************************************************/
#ifndef CONTROLLER_DEFINE_H
#define CONTROLLER_DEFINE_H

#define WM_UPDATE_POWER		  WM_USER + 0x101
#define WP_UPDATE_POWER		  WM_USER + 0x102
#define WM_UPDATE_AMMETER		WM_USER + 0x501
//��Ϣ��
#define WM_AFXMESSAGEBOX	WM_USER + 0x103
//�Ի���ˢ�³�ʼ������
#define WM_DIALOG_INITIAL_UPDATE	WM_USER + 0x105
//����ʮ��У��������Ϣ
#define  WM_DESTROY_CROSSCALIBRATION   WM_USER + 0x107
//�������У��������Ϣ
#define  WM_DESTROY_DLGMATCH   WM_USER + 0x108
//������У��������Ϣ
#define  WM_DESTROY_SCANCALIBRATION  WM_USER + 0x109
//�����Զ�Ѱ��������Ϣ
#define  WM_DESTROY_SCANFOCUS  WM_USER + 0x110
//��У��������У���ļ�
#define  WM_OPEN_FILE WM_USER + 0x111
//ˢ������״̬��Ϣ
#define  WM_REFRESH_CIM_INFO WM_USER + 0x112
//ѭ����ʱ
#define LOOP_DELAY  50
#define SHORT_DELAY 200
#define LONG_DELAY  500
#define BEFF_DELAY  500
#define WATER_DELAY 1000
#define VOLTMETER_DELAY 1000
#define DUST_DELAY  1000
#define HEART_DELAY 1000
#define PLC_DELAY   2000

#define MAXCAMERACOUNT		8	
#define MAX_AXIS_NUM		3

//�Ի�������ƫ�ƶ���
#define DIALOG_TOP_OFFSET  5

#define ARRAY_SIZE(x) (static_cast<int>((sizeof(x)/sizeof(x[0]))))
#define PATH_FOLDER_NAME "D:\\Cowin_Repair"
#define RESULT_OK	0
#define RESULT_PROC	-2
#define IN_POSITION_VALUE_UMAC	1
#define	JOG_MOVE_NEGATIVE	0
#define JOG_MOVE_POSITIVE	1
//PIֵ
const double PI = 3.1415926535897932;
const double PIx2 = 6.283185307179586;

//Arc to Angle
const double ARC_ANGEL = 57.29577951308232;
const double ANGEL_ARC = 0.0174532925199433;

//�û��ȼ�
#define USER_NULL		-1
#define OPERATOR		0
#define ADMINISTATOR	1
#define SUPER			2

//������ɫ
#define  COLOR_UI			(RGB(236,233,216))		//������ɫ
#define	 COLOR_BLACK		(RGB(0,0,0))			//��ɫ
#define  COLOR_GREY			(RGB(152,152,152))		//��ɫ
#define  COLOR_GREY_SYSTEM	(RGB(236,233,216))
#define  COLOR_MAGENTA		(RGB(255, 0, 255))		//��ɫ
#define  COLOR_WHITE		(RGB(255, 255, 255))	//��ɫ
#define  COLOR_HIGHTGREY	(RGB(192, 192, 192))	//�߻�ɫ
#define	 COLOR_BTN_BG  		(RGB(230, 220, 140))		//��ť����ɫ
#define  COLOR_GRID_BACK	(RGB(0xFF, 0xFF, 0xE0)) //gridͼ�ı���ɫ������ɫ
#define  COLOR_HIGHTLIGHT   (RGB(248, 147, 29))		//��ťѡ������ɫ
#define  COLOR_BTN			(RGB(213,228,242))		//��ť��ɫ
#define  COLOR_RED			(RGB(255,66,93))		//��ɫ
#define  COLOR_PLUM			(RGB(189,49,187))		//÷��ɫ
#define  COLOR_CYAN			(RGB( 167, 220, 224))	//��ɫ
#define	 COLOR_GREEN		(RGB(179, 214, 110))	//��ɫ
#define	 COLOR_YELLOW		(RGB(248, 147, 29))		//��ɫ	
#define  COLOR_BLUE			(RGB( 92, 167, 186))	//��ɫ
#define  COLOR_PURPLE		(RGB(181, 84, 184))		//��ɫ
#define  COLOR_BLUE2	(RGB(207,221, 238))	
#define  COLOR_GRID_HEAD   (RGB(134,164,197))		//���ͷ��ɫ
#define  COLOR_GRID_ROW1   (RGB(185,205,229))		//�����ɫ1
#define  COLOR_GRID_ROW2   (RGB(221,231,243))		//�����ɫ2


//����ֱ���
#define REVIEW_PIXEL_COUNT_X_CAM           4096
#define REVIEW_PIXEL_COUNT_Y_CAM           3000
#define REVIEW_PIXEL_COUNT_MONITOR_X        800
#define REVIEW_PIXEL_COUNT_MONITOR_Y        600
#define PATH_MIL_REVIEW_DCF                _T("4096_300.dcf")
//�ֶ�����״̬
enum CAMERA_MESSURE
{
	MESSURE_END = 0,		//������������û�п�ʼ����
	MESSURE_READY = 1,		//��ʼ׼�������У���û�����
	MESSURE_DISPLAY = 2		//һ�ֲ�����ɣ�������ʾ���Խ��	
};

//�������ID
enum
{
	AXIAS_X_ID = 0,                         //X��
	AXIAS_Y_ID = 1,							//Y��
	AXIAS_Z_ID = 2,						    //Z��
};

//�ƶ���ʽ
enum MOVE_MODE
{
	MOVE_JOG = 0,
	MOVE_INC = 1,
	MOVE_P2T = 1,
	MOVE_ABS = 2,
	MOVE_TRAP = 2
};				

//double���͵������
struct DPOINT
{
	double x;
	double y;
	double z;
	
	DPOINT::DPOINT()
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}
	
	DPOINT::DPOINT(double dbx,double dby,double dbz)
	{
		x = dbx;
		y = dby;
		z = dbz;
	}
	
	const DPOINT& operator=(const DPOINT& point)
	{
		if (this == &point)
		{
			return *this;
		}
		else
		{
			x = point.x;
			y = point.y;
			z = point.z;
			return point;
		}
	}
	
	const DPOINT& operator-(const DPOINT& point)
	{
		x = x - point.x;
		y = y - point.y;
		z = z - point.z;
		
		return *this;
	}
	
	const DPOINT& operator+(const DPOINT& point)
	{
		x = x + point.x;
		y = y + point.y;
		z = z + point.z;
		
		return *this;
	}
};
typedef CArray<DPOINT,DPOINT&> POINTARRAY;

struct USER_INFO
{
    CString strName;	//�û���
    CString strPsw;		//�û�����
    CString strLimit;	//�û�Ȩ�ޣ�0����������Ա��1����ͨ����Ա��2����ͨ����Ա
    int nLimit;			//�û�Ȩ�ޣ�0����������Ա��1����ͨ����Ա��2����ͨ����Ա
    CString strChinaName;//������
    CString strCompanyCode;//��˾����
    CString strLogInTime;	//���һ�ε�¼ʱ��
    CString strLogOutTime;		//���һ���˳�ʱ��
    BOOL bSave;			//��¼ʱ�Ƿ񱣴��û���������
    BOOL bLastLog;	//�Ƿ������µ�¼�û�
	BOOL bManualLogin; //�ֶ���¼��  ������CIM�û�Ȩ�޿���

	//�˳�
	void fnLogOut()
	{
		strName.Empty();
		strPsw.Empty();
		strLimit.Empty();
		nLimit = USER_NULL;
		strChinaName.Empty();
		strCompanyCode.Empty();
		bSave = FALSE;
		bLastLog = FALSE;
		bManualLogin = FALSE;
	}

    int fnGetUserLimit()
    {
        if ("Super" == strLimit)
        {
			nLimit = SUPER;
        }
        else if ("Admin" == strLimit)
        {
            nLimit = ADMINISTATOR;
        }
        else if ("Operator" == strLimit)
        {
            nLimit = OPERATOR;
        }
		else
		{
			nLimit = USER_NULL;
		}

		return nLimit;
    };

	CString fnSetUserLimit(int nLimit)
	{
		if (SUPER == nLimit)
		{
			strLimit = "Super";
		}
		else if (ADMINISTATOR == nLimit)
		{
			strLimit = "Admin";
		}
		else if (OPERATOR == nLimit)
		{
			strLimit = "Operator";
		}
		else
		{
			strLimit.Empty();
		}

		return strLimit;
	};

    USER_INFO::USER_INFO()
    {
        strName.Empty();
        strPsw.Empty();
        strLimit = "";
        strChinaName.Empty();
        strCompanyCode.Empty();
        strLogOutTime.Empty();
        strLogInTime.Empty();
        bSave = FALSE;
        bLastLog = FALSE;
		bManualLogin = FALSE;
		nLimit = USER_NULL;
    }

    const USER_INFO& operator=(const USER_INFO& user)
    {
        if (this == &user)
        {
            return *this;
        }
        else
        {
            strName = user.strName;
            strPsw = user.strPsw;
            strLimit = user.strLimit;
            strChinaName = user.strChinaName;
            strCompanyCode = user.strCompanyCode;
            strLogOutTime = user.strLogOutTime;
            strLogInTime = user.strLogInTime;
            bSave = user.bSave;	
            bLastLog = user.bLastLog;
			nLimit = user.nLimit;
            return user;
        }
    }
};
typedef CArray<USER_INFO,USER_INFO&> USERARRAY;

//�񾵲�������
struct SCAN_PARAM
{
	double dbJumpSpd;//��ת�ٶ�	
	double dbMarkSpd;//ɨ���ٶ�
	int nJumpDly;//��ת��ʱ
	int nMarkDly;//ɨ����ʱ	
	int nOnDly;//������ʱ	
	int nOffDly;//�ع���ʱ	
	int nCrossDly;//�ս���ʱ

	double dbXRatio;//X�������ű���	
	double dbYRatio;//Y�������ű���	
	double dbXOfset;//X��������ƫ��	
	double dbYOfset;//Y��������ƫ��	
	double dbAngle;	//������ת�Ƕ�	

	BOOL bMirrorX, bMirrorY;//xy���Ƿ���	
	BOOL bExchangeXY;//�Ƿ�X/Y�ύ��

	int nBitmm;//bit/mm����ϵ��	
	CString	strCalFile;//У���ļ�
	double dbFovX;//�񾵵�ɨ����Ұ��С
	double dbFovY;

	SCAN_PARAM()
	{
		dbJumpSpd = 1000;
		nJumpDly = 10;
		dbMarkSpd = 100;
		nMarkDly = 10;
		nOnDly = 10;
		nOffDly = 20;
		nCrossDly = 10;
		dbXRatio = 1;
		dbYRatio = 1;
		dbXOfset = 0;
		dbYOfset = 0;
		dbAngle = 0;
		nBitmm = 1092;
		bMirrorX = FALSE;
		bMirrorY = FALSE;
		bExchangeXY = FALSE;
		strCalFile.Empty();
		dbFovX = 30;
		dbFovY = 30;
	}

	//���ƹ���
	SCAN_PARAM(const SCAN_PARAM& param)
	{
		dbJumpSpd = param.dbJumpSpd;
		nJumpDly = param.nJumpDly;
		dbMarkSpd = param.dbMarkSpd;
		nMarkDly = param.nMarkDly;
		nOnDly = param.nOnDly;
		nOffDly = param.nOffDly;
		nCrossDly = param.nCrossDly;
		dbXRatio = param.dbXRatio;
		dbYRatio = param.dbYRatio;
		dbXOfset = param.dbXOfset;
		dbYOfset = param.dbYOfset;
		dbAngle = param.dbAngle;
		nBitmm = param.nBitmm;
		bMirrorX = param.bMirrorX;
		bMirrorY = param.bMirrorY;
		bExchangeXY = param.bExchangeXY;
		strCalFile = param.strCalFile;

		dbFovX = param.dbFovX;
		dbFovY = param.dbFovY;
	}

	//��ֵ����
	SCAN_PARAM& operator=(const SCAN_PARAM& param)
	{
		if (this != &param)
		{
			dbJumpSpd = param.dbJumpSpd;
			nJumpDly = param.nJumpDly;
			dbMarkSpd = param.dbMarkSpd;
			nMarkDly = param.nMarkDly;
			nOnDly = param.nOnDly;
			nOffDly = param.nOffDly;
			nCrossDly = param.nCrossDly;
			dbXRatio = param.dbXRatio;
			dbYRatio = param.dbYRatio;
			dbXOfset = param.dbXOfset;
			dbYOfset = param.dbYOfset;
			dbAngle = param.dbAngle;
			nBitmm = param.nBitmm;
			bMirrorX = param.bMirrorX;
			bMirrorY = param.bMirrorY;
			bExchangeXY = param.bExchangeXY;
			strCalFile = param.strCalFile;

			dbFovX = param.dbFovX;
			dbFovY = param.dbFovY;
		}
		return *this;
	}
};

struct SCAN_CRAFT
{
	double dbJumpSpd;//��ת�ٶ�
	double dbMarkSpd;//ɨ���ٶ�

	int nJumpDly;//��ת��ʱ
	int nMarkDly;//ɨ����ʱ
	int nOnDly;//������ʱ
	int nOffDly;//�ع���ʱ
	int nCrossDly;//�ս���ʱ

	SCAN_CRAFT()
	{
		dbJumpSpd = 1000;
		dbMarkSpd = 100;
		nJumpDly = 20;
		nMarkDly = 20;
		nOnDly = 30;
		nOffDly = 50;
		nCrossDly = 10;
	}

	SCAN_CRAFT(const SCAN_CRAFT& param)
	{
		dbJumpSpd = param.dbJumpSpd;
		dbMarkSpd = param.dbMarkSpd;
		nJumpDly = param.nJumpDly;
		nMarkDly = param.nMarkDly;
		nOnDly = param.nOnDly;
		nOffDly = param.nOffDly;
		nCrossDly = param.nCrossDly;

	}
	SCAN_CRAFT& operator= (const SCAN_CRAFT& param)
	{
		if (this != &param)
		{
			dbJumpSpd = param.dbJumpSpd;
			dbMarkSpd = param.dbMarkSpd;
			nJumpDly = param.nJumpDly;
			nMarkDly = param.nMarkDly;
			nOnDly = param.nOnDly;
			nOffDly = param.nOffDly;
			nCrossDly = param.nCrossDly;
		}
		return *this;
	}
};

//�������
struct CAMERA_PARAM
{
	//Ӱ�񿨣ɣ�
	int			nChannelIndex;
	//Ӱ�񿨼�������ļ�
	CString		strCamFile;
	//Ӱ�������ַ�
	CString		strConnect;
	//IMI SN
	CString strSN;
	//Ӱ���СX
	UINT		nImageSizeX;
	//Ӱ���СY
	UINT		nImageSizeY;
	//Ӱ������λ��
	int			nVisionCenterX;
	//Ӱ������λ��
	int			nVisionCenterY;
	//���ر�x
	double 		dbPixelSizeX;
	//���ر�y
	double		dbPixelSizeY;
	//ͼ����
	BOOL		bHorMirror;
	//ͼ����
	BOOL		bVerMirror;
	//������ʾ
	double		dbZoomShowX;
	//������ʾ
	double		dbZoomShowY;
	//�������ر��õľ��ο��С
	CRect		rect;
	//Ӱ��������ʾԲ�λ���������
	int nCenterShape;
	//Բ��ֱ�����������εĿ��
	double dbCenterRadius;
	//�����ʾԲ�λ��Ǿ���
	int nCursorShape;
	//���������ʾԲ�ε�ֱ�����������εĿ��
	double dbCursorRadius;
	//�ع�ʱ��
	int nExplodeTime;
	//�ع�����
	int nExplodeGain;
	//ˢ��֡��
	int nFrameRate;
	//Gamma����
	int nGammaGain;
	//��Դ������������
	int nLightSource;
	//�Ƿ���ʾֱ�����
	BOOL bShowGauge;
	BOOL bShowLineFit;
	BOOL bShowMatch;
	BOOL bShowRoi;
	//�Ƿ���Ҫ��ʾ��ɫʮ����
	BOOL bShowCross;
	//�Ƿ���ʾ����У�����ο�
	BOOL bShowCalRect;
	//�Ƿ���ʾͼ������
	BOOL bShowResult;
	//�жϽ���Ƿ�NG
	BOOL bResultNg;
	//ͼ������
	CString strResult;
	//�Ƿ��ڲ���״̬
	CAMERA_MESSURE nMessure;
	//������񾵵����Ľ�������
	DPOINT ptCalibration;
	//����
    //���ƶ�
	double dbMatchLevel;
	//���Ĵ�СX
	int	nCenterSizeX;
	//���Ĵ�СY
	int	nCenterSizeY;


	CAMERA_PARAM::CAMERA_PARAM()
	{
		dbMatchLevel = 0;
		nCenterSizeX = 0;
		nCenterSizeY = 0;
		nChannelIndex = 0;
		strCamFile.Empty();
		strConnect.Empty();
		strSN.Empty();
		nImageSizeX = 640;
		nImageSizeY = 480;
		nVisionCenterX = 0;
		nVisionCenterY = 0;
		dbPixelSizeX = 3;
		dbPixelSizeY = 4;
		bHorMirror = FALSE;
		bVerMirror = FALSE;
		bShowMatch = FALSE;
		bShowRoi = FALSE;
		dbZoomShowX = 0;
		dbZoomShowY = 0;
		dbCenterRadius = 1.00;
		nCenterShape = 0;
		nCursorShape = 0;
		dbCursorRadius = 0.5;
		rect = CRect(50, 50, 100, 100);
		nExplodeTime = 10;
		nExplodeGain = 1;
		nFrameRate = 10;
		nGammaGain = 1;
		nLightSource = 20;
		//�Ƿ���ʾֱ�����
		bShowGauge = FALSE;
		bShowLineFit = FALSE;
		//�Ƿ���Ҫ��ʾ��ɫʮ����
		bShowCross = TRUE;
		//�Ƿ���ʾ����У�����ο�
		bShowCalRect = FALSE;
		bResultNg = FALSE;
		strResult = " ";
		//�Ƿ���ʾͼ������
		bShowResult = FALSE;
		//�Ƿ��ڲ���״̬
		nMessure = MESSURE_END;
	}

	//����=������
	const CAMERA_PARAM& operator=(const CAMERA_PARAM& param)
	{
		if (this == &param)
		{
			return   *this;
		}
		else
		{
			nChannelIndex = param.nChannelIndex;
			strCamFile = param.strCamFile;
			strConnect = param.strConnect;
			strSN = param.strSN;
			nImageSizeX = param.nImageSizeX;
			nImageSizeY = param.nImageSizeY;
			nVisionCenterX = param.nVisionCenterX;
			nVisionCenterY = param.nVisionCenterY;
			dbPixelSizeX = param.dbPixelSizeX;
			dbPixelSizeY = param.dbPixelSizeY;
			bHorMirror = param.bHorMirror;
			bVerMirror = param.bVerMirror;
			bShowMatch = param.bShowMatch;
			bShowRoi = param.bShowRoi;
			bShowResult = param.bShowResult;
			bResultNg = param.bResultNg;
			strResult = param.strResult;
			dbZoomShowX = param.dbZoomShowX;
			dbZoomShowY = param.dbZoomShowY;
			nCenterShape = param.nCenterShape;
			dbCenterRadius = param.dbCenterRadius;
			nCursorShape = param.nCursorShape;
			dbCursorRadius = param.dbCursorRadius;
			rect = param.rect;
			nExplodeTime = param.nExplodeTime;
			nExplodeGain = param.nExplodeGain;
			nFrameRate = param.nFrameRate;
			nGammaGain = param.nGammaGain;
			bShowGauge = param.bShowGauge;
			bShowLineFit = param.bShowLineFit;
			bShowCross = param.bShowCross;
			bShowCalRect = param.bShowCalRect;
			nMessure = param.nMessure;
			ptCalibration = param.ptCalibration;
			dbMatchLevel = param.dbMatchLevel;
			nCenterSizeX = param.nCenterSizeX;
			nCenterSizeY = param.nCenterSizeY;
			return   param;
		}
	}
};

//�˶��������״̬��Ϣ�������߳�ˢ��
struct AXIS_STATUS
{
	//�����λ����Ϣ
	double dbAxisPos[MAX_AXIS_NUM];

	//�������λ״̬��Ϣ
	BOOL bLimitPos[MAX_AXIS_NUM];
	BOOL bLimitNeg[MAX_AXIS_NUM];

	//����ʹ��״̬��Ϣ
	BOOL bAxisEnable[MAX_AXIS_NUM];

	//�Ƿ����˶�״̬
	BOOL bMoving[MAX_AXIS_NUM];

	//�Ƿ�����˸�λ
	BOOL bHomed[MAX_AXIS_NUM];

	//��������˿�״̬
	BOOL bAxisInPut[120];

	//��������˿�״̬
	BOOL bAxisOutPut[120];

    //ϵͳ�����״̬	
    BOOL bAxisErr[120];

	//��鵱ǰ����ϵϵͳ�Ƿ��������˶�,ֻҪ��һ�������˶������ֵΪTRUE
	BOOL bAxisMoving;

	//���Ӽ����ϳ�״̬���������ʹ��
	BOOL bComposeStatus[20];

	//���캯��
	AXIS_STATUS::AXIS_STATUS()
	{
		bAxisMoving = FALSE;
	}
};

//���˶�����ģʽ
struct MOTION_MODE
{	
	//�˶�ģʽ
	int nMoveMode;
	//����
	double dbDistance;
	//�ֶ������ٶ�
	double dbManualVel;
	//��λ�˶��ٶȣ��Ǽ������ʱ����˶�
	double dbJumpVel;
	//��λ�ٶ�
	double dbHomeVel;
	//���ٶ�
	double dbJumpAcc;
	//���ٶ�
	double dbJumpDec;
	//����λ
	double dbLimitPos;
	double dbLimitNeg;
	//��ķֱ���
	double dbRatio;
	//�����ٶ�
	double dbKDec;
	//�Ӽ��ٶ�
	double dbJerk;
	//�������캯��
	MOTION_MODE()
	{
		nMoveMode = MOVE_INC;
		dbDistance = 1;
		dbManualVel = 10;
		dbJumpVel = 10;
		dbHomeVel = 10;
		dbJumpAcc = 1000;
		dbJumpDec = 1000;
		dbLimitNeg = -1000;
		dbLimitPos = 1000;
		dbRatio = 1000;
		dbJerk = 1000;
		dbKDec = 1000;
	}

	//����=������
	MOTION_MODE& operator=(const MOTION_MODE& param)   
	{   
		if (this != &param)   
		{
			nMoveMode = param.nMoveMode;
			dbDistance = param.dbDistance;
			dbManualVel = param.dbManualVel;
			dbJumpVel = param.dbJumpVel;
			dbHomeVel = param.dbHomeVel;
			dbJumpAcc = param.dbJumpAcc;
			dbLimitPos = param.dbLimitPos;
			dbLimitNeg = param.dbLimitNeg;
			dbKDec = param.dbKDec;
			dbJerk = param.dbJerk;
			dbRatio = param.dbRatio;
		}
		return *this;
	}   
};

#endif


