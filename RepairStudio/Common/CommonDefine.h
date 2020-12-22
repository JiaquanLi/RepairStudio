/************************************************************************/
/* 用于定于一些常用的全局变量，宏定义，结构体等                                                                     */
/************************************************************************/
#ifndef CONTROLLER_DEFINE_H
#define CONTROLLER_DEFINE_H

#define WM_UPDATE_POWER		  WM_USER + 0x101
#define WP_UPDATE_POWER		  WM_USER + 0x102
#define WM_UPDATE_AMMETER		WM_USER + 0x501
//消息框
#define WM_AFXMESSAGEBOX	WM_USER + 0x103
//对话框刷新初始化界面
#define WM_DIALOG_INITIAL_UPDATE	WM_USER + 0x105
//销毁十字校正窗体消息
#define  WM_DESTROY_CROSSCALIBRATION   WM_USER + 0x107
//销毁相机校正窗体消息
#define  WM_DESTROY_DLGMATCH   WM_USER + 0x108
//销毁振镜校正窗体消息
#define  WM_DESTROY_SCANCALIBRATION  WM_USER + 0x109
//销毁自动寻焦窗体消息
#define  WM_DESTROY_SCANFOCUS  WM_USER + 0x110
//振镜校正参数打开校正文件
#define  WM_OPEN_FILE WM_USER + 0x111
//刷新帐料状态信息
#define  WM_REFRESH_CIM_INFO WM_USER + 0x112
//循环延时
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

//对话框向下偏移多少
#define DIALOG_TOP_OFFSET  5

#define ARRAY_SIZE(x) (static_cast<int>((sizeof(x)/sizeof(x[0]))))
#define PATH_FOLDER_NAME "D:\\Cowin_Repair"
#define RESULT_OK	0
#define RESULT_PROC	-2
#define IN_POSITION_VALUE_UMAC	1
#define	JOG_MOVE_NEGATIVE	0
#define JOG_MOVE_POSITIVE	1
//PI值
const double PI = 3.1415926535897932;
const double PIx2 = 6.283185307179586;

//Arc to Angle
const double ARC_ANGEL = 57.29577951308232;
const double ANGEL_ARC = 0.0174532925199433;

//用户等级
#define USER_NULL		-1
#define OPERATOR		0
#define ADMINISTATOR	1
#define SUPER			2

//字体颜色
#define  COLOR_UI			(RGB(236,233,216))		//界面颜色
#define	 COLOR_BLACK		(RGB(0,0,0))			//黑色
#define  COLOR_GREY			(RGB(152,152,152))		//灰色
#define  COLOR_GREY_SYSTEM	(RGB(236,233,216))
#define  COLOR_MAGENTA		(RGB(255, 0, 255))		//紫色
#define  COLOR_WHITE		(RGB(255, 255, 255))	//白色
#define  COLOR_HIGHTGREY	(RGB(192, 192, 192))	//高灰色
#define	 COLOR_BTN_BG  		(RGB(230, 220, 140))		//按钮背景色
#define  COLOR_GRID_BACK	(RGB(0xFF, 0xFF, 0xE0)) //grid图的背景色，淡黄色
#define  COLOR_HIGHTLIGHT   (RGB(248, 147, 29))		//按钮选中是颜色
#define  COLOR_BTN			(RGB(213,228,242))		//按钮颜色
#define  COLOR_RED			(RGB(255,66,93))		//红色
#define  COLOR_PLUM			(RGB(189,49,187))		//梅红色
#define  COLOR_CYAN			(RGB( 167, 220, 224))	//青色
#define	 COLOR_GREEN		(RGB(179, 214, 110))	//绿色
#define	 COLOR_YELLOW		(RGB(248, 147, 29))		//黄色	
#define  COLOR_BLUE			(RGB( 92, 167, 186))	//蓝色
#define  COLOR_PURPLE		(RGB(181, 84, 184))		//紫色
#define  COLOR_BLUE2	(RGB(207,221, 238))	
#define  COLOR_GRID_HEAD   (RGB(134,164,197))		//表格头颜色
#define  COLOR_GRID_ROW1   (RGB(185,205,229))		//表格颜色1
#define  COLOR_GRID_ROW2   (RGB(221,231,243))		//表格颜色2


//相机分辨率
#define REVIEW_PIXEL_COUNT_X_CAM           4096
#define REVIEW_PIXEL_COUNT_Y_CAM           3000
#define REVIEW_PIXEL_COUNT_MONITOR_X        800
#define REVIEW_PIXEL_COUNT_MONITOR_Y        600
#define PATH_MIL_REVIEW_DCF                _T("4096_300.dcf")
//手动测量状态
enum CAMERA_MESSURE
{
	MESSURE_END = 0,		//测量结束或者没有开始测量
	MESSURE_READY = 1,		//开始准备测试中，还没有完成
	MESSURE_DISPLAY = 2		//一轮测量完成，可以显示测试结果	
};

//定义各轴ID
enum
{
	AXIAS_X_ID = 0,                         //X轴
	AXIAS_Y_ID = 1,							//Y轴
	AXIAS_Z_ID = 2,						    //Z轴
};

//移动方式
enum MOVE_MODE
{
	MOVE_JOG = 0,
	MOVE_INC = 1,
	MOVE_P2T = 1,
	MOVE_ABS = 2,
	MOVE_TRAP = 2
};				

//double类型的坐标点
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
    CString strName;	//用户名
    CString strPsw;		//用户密码
    CString strLimit;	//用户权限，0：超级管理员，1：普通管理员，2：普通操作员
    int nLimit;			//用户权限，0：超级管理员，1：普通管理员，2：普通操作员
    CString strChinaName;//中文名
    CString strCompanyCode;//公司工号
    CString strLogInTime;	//最近一次登录时间
    CString strLogOutTime;		//最近一次退出时间
    BOOL bSave;			//登录时是否保存用户名和密码
    BOOL bLastLog;	//是否是最新登录用户
	BOOL bManualLogin; //手动登录后  不接受CIM用户权限控制

	//退出
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

//振镜参数集合
struct SCAN_PARAM
{
	double dbJumpSpd;//跳转速度	
	double dbMarkSpd;//扫描速度
	int nJumpDly;//跳转延时
	int nMarkDly;//扫描延时	
	int nOnDly;//开光延时	
	int nOffDly;//关光延时	
	int nCrossDly;//拐角延时

	double dbXRatio;//X方向缩放比率	
	double dbYRatio;//Y方向缩放比率	
	double dbXOfset;//X方向中心偏移	
	double dbYOfset;//Y方向中心偏移	
	double dbAngle;	//中心旋转角度	

	BOOL bMirrorX, bMirrorY;//xy轴是否镜像	
	BOOL bExchangeXY;//是否X/Y轴交换

	int nBitmm;//bit/mm比例系数	
	CString	strCalFile;//校正文件
	double dbFovX;//振镜的扫描视野大小
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

	//复制构造
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

	//赋值构造
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
	double dbJumpSpd;//跳转速度
	double dbMarkSpd;//扫描速度

	int nJumpDly;//跳转延时
	int nMarkDly;//扫描延时
	int nOnDly;//开光延时
	int nOffDly;//关光延时
	int nCrossDly;//拐角延时

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

//相机参数
struct CAMERA_PARAM
{
	//影像卡ＩＤ
	int			nChannelIndex;
	//影像卡加载相机文件
	CString		strCamFile;
	//影像链接字符
	CString		strConnect;
	//IMI SN
	CString strSN;
	//影像大小X
	UINT		nImageSizeX;
	//影像大小Y
	UINT		nImageSizeY;
	//影像中心位置
	int			nVisionCenterX;
	//影像中心位置
	int			nVisionCenterY;
	//像素比x
	double 		dbPixelSizeX;
	//像素比y
	double		dbPixelSizeY;
	//图像镜像
	BOOL		bHorMirror;
	//图像镜像
	BOOL		bVerMirror;
	//缩放显示
	double		dbZoomShowX;
	//缩放显示
	double		dbZoomShowY;
	//计算像素比用的矩形框大小
	CRect		rect;
	//影像中心显示圆形还是正方形
	int nCenterShape;
	//圆形直径或者正方形的宽度
	double dbCenterRadius;
	//鼠标显示圆形还是矩形
	int nCursorShape;
	//鼠标中心显示圆形的直径或者正方形的宽度
	double dbCursorRadius;
	//曝光时间
	int nExplodeTime;
	//曝光增益
	int nExplodeGain;
	//刷新帧率
	int nFrameRate;
	//Gamma增益
	int nGammaGain;
	//光源控制器的亮度
	int nLightSource;
	//是否显示直线拟合
	BOOL bShowGauge;
	BOOL bShowLineFit;
	BOOL bShowMatch;
	BOOL bShowRoi;
	//是否需要显示黄色十字线
	BOOL bShowCross;
	//是否显示像素校正矩形框
	BOOL bShowCalRect;
	//是否显示图像处理结果
	BOOL bShowResult;
	//判断结果是否NG
	BOOL bResultNg;
	//图像处理结果
	CString strResult;
	//是否处于测量状态
	CAMERA_MESSURE nMessure;
	//相机与振镜的中心矫正数据
	DPOINT ptCalibration;
	//新增
    //相似度
	double dbMatchLevel;
	//中心大小X
	int	nCenterSizeX;
	//中心大小Y
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
		//是否显示直线拟合
		bShowGauge = FALSE;
		bShowLineFit = FALSE;
		//是否需要显示黄色十字线
		bShowCross = TRUE;
		//是否显示像素校正矩形框
		bShowCalRect = FALSE;
		bResultNg = FALSE;
		strResult = " ";
		//是否显示图像处理结果
		bShowResult = FALSE;
		//是否处于测量状态
		nMessure = MESSURE_END;
	}

	//重载=操作符
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

//运动轴的所有状态信息，用于线程刷新
struct AXIS_STATUS
{
	//各轴的位置信息
	double dbAxisPos[MAX_AXIS_NUM];

	//各轴的限位状态信息
	BOOL bLimitPos[MAX_AXIS_NUM];
	BOOL bLimitNeg[MAX_AXIS_NUM];

	//各轴使能状态信息
	BOOL bAxisEnable[MAX_AXIS_NUM];

	//是否在运动状态
	BOOL bMoving[MAX_AXIS_NUM];

	//是否完成了复位
	BOOL bHomed[MAX_AXIS_NUM];

	//所有输入端口状态
	BOOL bAxisInPut[120];

	//所有输出端口状态
	BOOL bAxisOutPut[120];

    //系统错误的状态	
    BOOL bAxisErr[120];

	//检查当前坐标系系统是否有轴在运动,只要有一个轴在运动，则该值为TRUE
	BOOL bAxisMoving;

	//增加几个合成状态，方便后面使用
	BOOL bComposeStatus[20];

	//构造函数
	AXIS_STATUS::AXIS_STATUS()
	{
		bAxisMoving = FALSE;
	}
};

//轴运动控制模式
struct MOTION_MODE
{	
	//运动模式
	int nMoveMode;
	//距离
	double dbDistance;
	//手动控制速度
	double dbManualVel;
	//点位运动速度，非激光出光时候的运动
	double dbJumpVel;
	//复位速度
	double dbHomeVel;
	//加速度
	double dbJumpAcc;
	//减速度
	double dbJumpDec;
	//轴限位
	double dbLimitPos;
	double dbLimitNeg;
	//轴的分辨率
	double dbRatio;
	//减减速度
	double dbKDec;
	//加加速度
	double dbJerk;
	//拷贝构造函数
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

	//重载=操作符
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


