/************************************************************************/
/* 用于包含所有的头文件                                                 */
/************************************************************************/
#ifndef CONTROLLER_INCLUDE_H
#define CONTROLLER_INCLUDE_H

//全局变量和函数
#include "CommonDefine.h"
#include "Sequence.h"
#include "AlarmDef.h"

//文件管理

//运动控制
#include "../Motion/MotionCK3M.h"

//外部设备
#include "Camera.h"

//内存泄露相关
#include "../Tools/byteorder.h"
#include "../Tools/scoped_ptr.h"
#include "../Tools/criticalsection.h"
#include "../Tools/basictypes.h"
#include "../Tools/bytebuffer.h"
using namespace _base;

//工具相关
#include "../Tools/ChartCtrl/ChartCtrl.h"
#include "../Tools/ChartCtrl/ChartLineSerie.h"
#include "../Tools/ChartCtrl/ChartAxisLabel.h"
#include "../Tools/ChartCtrl/ChartPointsSerie.h"
#include "../Tools/GridCtrl/GridCtrl.h"
#include "../Tools/GridCtrl/GridCellDateTime.h"
#include "../Tools/GridCtrl/GridCellCheck.h"
#include "../Tools/GridCtrl/GridCellCombo.h"
#include "../Tools/GridCtrl/GridCellNumeric.h"
#include "../Tools/XBorderStatic.h"
#include "../Tools/ColorBox.h"


#include "../Tools/MemDC.h"
#include "../Tools/MiniDump.h"
#include "../Tools/PosCorrect.h"

//database
#include "../include/DataBaseDll.h"
#include "../include/Geometry.h"

//串口和网口
#include "../Comunication/SerialPort.h"
#include "../Comunication/SocketManager.h"
#include "../Comunication/ModbusClient.h"

//振镜相关
#include "../include/ScannerDll.h"

//全局函数
#include "GlobalFunction.h"

#endif

