/************************************************************************/
/* ���ڰ������е�ͷ�ļ�                                                 */
/************************************************************************/
#ifndef CONTROLLER_INCLUDE_H
#define CONTROLLER_INCLUDE_H

//ȫ�ֱ����ͺ���
#include "CommonDefine.h"
#include "Sequence.h"
#include "AlarmDef.h"

//�ļ�����

//�˶�����
#include "../Motion/MotionCK3M.h"

//�ⲿ�豸
#include "Camera.h"

//�ڴ�й¶���
#include "../Tools/byteorder.h"
#include "../Tools/scoped_ptr.h"
#include "../Tools/criticalsection.h"
#include "../Tools/basictypes.h"
#include "../Tools/bytebuffer.h"
using namespace _base;

//�������
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

//���ں�����
#include "../Comunication/SerialPort.h"
#include "../Comunication/SocketManager.h"
#include "../Comunication/ModbusClient.h"

//�����
#include "../include/ScannerDll.h"

//ȫ�ֺ���
#include "GlobalFunction.h"

#endif

