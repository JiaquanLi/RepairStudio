#ifndef _DLL_GEOMETRY_H
#define _DLL_GEOMETRY_H

#include "CommonDefine.h"
#ifdef _cplusplus
extern "C"
{
#endif

#define _DLL_EXPORT _declspec(dllexport)

/*
1.	旋转一个点
输入: dbPtX, dbPtY 欲旋转的点坐标
输入: dbAngle 角度(角度制,逆时针为正)
输入: dbCenterX , dbCenterY 旋转中心坐标
输出: dbPtX, dbPtY 旋转后的坐标
返回 成功或者是失败
*/
_DLL_EXPORT	BOOL fnRotatePt(double &dbPtX, double &dbPtY, double dbAngle ,double dbCenterX, double dbCenterY);
	
/*
2.	矩阵变换一个点
输入: dbPtX, dbPtY 欲变换的点坐标
输入: dbM11, dbM12, dbM21, dbM22, 矩阵左上,右上,左下,右下的数据
输出: dbPtX, dbPtY 变换后的坐标
返回 成功或者是失败
*/
_DLL_EXPORT BOOL fnMatrixPt(double &dbPtX, double &dbPtY, double dbM11, double dbM12,double dbM21 ,double dbM22);

/*
3.	多点拟合为直线(最小二乘拟合)
输入 dbPtX[],dbPtY[] 拟合点数据
输入 nDataCount 拟合点个数
输出 dbK, dbB (直线形式 y=Kx+B 中的K和B)
返回 0 失败
1 垂直线段 (x=B 的形式 B值由dbB输出)
2 非垂直线段(直线形式 y=Kx+B 中的K和B)
*/
_DLL_EXPORT int fnLeastSqLine(double dbPtX[], double dbPtY[],int nDataCount,double &dbK, double &dbB);

/*
4.	多点拟合为圆(最小二乘拟合)
输入 dbPtX[],dbPtY[] 拟合点数据
输入 nDataCount 拟合点个数
输出 dbCenterX, dbCenterY圆心坐标
输出 dbRadius 半径
返回 成功或者是失败
*/
_DLL_EXPORT BOOL fnLeastSqCircle(double dbPtX[], double dbPtY[],int nDataCount,double & dbCenterX, double &dbCenterY, double &dbRadius);

/*
5.	多点拟合为圆弧(最小二乘拟合)
输入 dbPtX[],dbPtY[] 拟合点数据
输入 nDataCount 拟合点个数
输出 dbCenterX, dbCenterY圆心坐标
输出 dbRadius 半径
输出 输出 dbAngle, 圆弧角度(角度制,正值代表逆时针)
返回 成功或者是失败
*/
_DLL_EXPORT BOOL fnLeastSqArc(double dbPtX[], double dbPtY[],int nDataCount,double &dbCenterX, double &dbCenterY, double &dbRadius,double &dbAngle);


/*6-a
构造Spline
输入 dbPtX, dbPtY 输入的数据
输入 数据的个数
返回 成功或者是失败
*/

_DLL_EXPORT BOOL fnCreateCubicSpline(double *dbPtX, double *dbPtY,int nDataCount);

/*6-b
获得X对应Y的值
输入 dbPtX    X数据
输出 dbPtY    Y的数据
返回 成功,失败
*/
_DLL_EXPORT BOOL fnCubicSplineYbyX(double dbPtX, double &dbPtY);

/*
7.	求两线段交点
输入 dbLine1PtX1, dbLine1PtY1, dbLine1PtX2, dbLine1PtY2 一线段的首末点
输入 dbLine2PtX1, dbLine2PtY1, dbLine2PtX2, dbLine2PtY2 二线段的首末点
输出 dbPtX1, dbPtY1, 交点坐标1
输出 dbPtX2, dbPtY2, 交点坐标2
返回 0 无交点 
1 一个交点 交点放入交点坐标1中,
2 有重合 重合部分的首末点放入交点坐标1和交点坐标2中
*/
_DLL_EXPORT int fnLinesCross(double dbLine1PtX1, double dbLine1PtY1, 
							 double dbLine1PtX2, double dbLine1PtY2, 
							 double dbLine2PtX1, double dbLine2PtY1, 
							 double dbLine2PtX2, double dbLine2PtY2, 
							 double &dbPtX1,double &dbPtY1,
							 double &dbPtX2,double &dbPtY2);

//2条直线的表达方式不一样
_DLL_EXPORT DPOINT fnLinesCross(DPOINT pts,DPOINT pte,double a,double b,double c);
							
/*
8.	求两点距离
输入 dbX1, dbY1, dbX2, dbY2 两点坐标
返回 两点距离
*/
_DLL_EXPORT double fnGetPtsLength(double dbX1,double dbY1, double dbX2,double dbY2);

/*
9.	判读点是否在线段上
输入 dbPtX, dbPtY 判断点坐标
输入 dbLinePtX1, dbLinePtY1, dbLinePtX2, dbLinePtY2 判断线段首末点
返回 TRUE 在线段上 
	 FALSE 不在线段上
*/
_DLL_EXPORT BOOL fnPtInLine(double dbPtX, double dbPtY,double dbLinePtX1, double dbLinePtY1,
				double dbLinePtX2, double dbLinePtY2);

/*10.	求点到线段的最短距离
输入 dbPtX, dbPtY 判断点坐标
输入 dbLinePtX1, dbLinePtY1, dbLinePtX2, dbLinePtY2 线段首末点
返回 最短距离
*/
_DLL_EXPORT double fnPtToLineMinLength(double dbPtX, double dbPtY,double dbLinePtX1, double dbLinePtY1,double dbLinePtX2, double dbLinePtY2);


/*11.	根据两点求直线方程(y=kx+b形式)
输入 dbPtX1,dbPtY1, dbPtX2, dbPtY2首末点数据
输出 dbK, dbB (直线形式 y=Kx+B 中的K和B)
返回 0 失败
1 垂直线段 (x=B 的形式 B值由dbB输出)
2 非垂直线段(直线形式 y=Kx+B 中的K和B)
*/
_DLL_EXPORT int fnGetLineByTwoPts(double dbPtX1,double dbPtY1, double dbPtX2,double dbPtY2,
					  double &dbK, double &dbB);

/*
12.	根据首末两点求出两点角度 (角度制) //与X轴正向夹角 逆时针为正
输入 dbPtX1, dbPtY1 首点坐标
输入 dbPtX2, dbPtY2 末点坐标
输入 bPositive FALSE (-180—180格式) , TRUE(0--360格式)
返回 角度值
*/
_DLL_EXPORT double fnGetPtsAngle(double dbPtX1,double dbPtY1, double dbPtX2,double dbPtY2,BOOL bPositive=FALSE);

/*13.	比较double类型数据
输入 dbNum1, dbNum2 比较的两个数的数值
返回 0 相等
1 dbNum1 > dbNum2
-1 dbNum1 < dbNum2
*/
_DLL_EXPORT int fnCompareDouble(double dbNum1,double dbNum2);

/*14.	十进制,十六进制转换
a将16进制字符串显示为可读的字符串 如 "31 32 2E 35 57"(即字符串”12.5W”)

输入 strHexAsc 16进制字符串
返回 标准字符串
*/
_DLL_EXPORT LPSTR fnHexAscToString(char* strHexAsc);

/*
b 将16进制字符转化为10进制数
输入 字符(支持大小写)
返回 10进制对应值
*/
_DLL_EXPORT int fnHexCharToDec(char cHexChar);

/*
将16进制字符串转换为10进制数(支持大小写)
输入 lpcHexStr 16进制表示的字符串 如”3E” 输出为62
返回 10进制数
*/
_DLL_EXPORT int fnHexStrToDec(char* strHexAsc);

/*
17.	判读点是否多边形内部
输入 dbPtX, dbPtY 判断点坐标
输入 dbPolyX, dbPolyY 多边形点链(点链必须是按照顺序给出,可以封闭也可以不封闭,计算时都视为封闭)
输入 nPtCount		  多边形点数
返回 TRUE 在内部 
	 FALSE 在外部
*/
_DLL_EXPORT BOOL fnPtInPoly(double dbPtX, double dbPtY,double *dbPolyX, double *dbPolyY,
				int nPtCount);

//给定：直线起点，末点，偏移量(>0),偏移方向（矢量的左手边 nFlag=-1，矢量的右手边 nFlag=1）
//求出：偏移后的直线表示方程 ax+by+c=0
_DLL_EXPORT BOOL fnGetLineOffset(DPOINT pts,DPOINT pte, double dbOfsAbs,int nFlag,double& a,double& b, double& c);
_DLL_EXPORT BOOL fnGetLineOffset(DPOINT pts,DPOINT pte, double dbOfsAbs,int nFlag,DPOINT& ptStart,DPOINT& ptEnd);

//给定：一条直线，以及直线外一点
//求出：点到直线的垂足
_DLL_EXPORT DPOINT fnGetPtToLinePerpenDicularCrs(double a1,double b1, double c1, DPOINT ptC);
_DLL_EXPORT DPOINT fnGetPtToLinePerpenDicularCrs(DPOINT pts,DPOINT pte,DPOINT ptC);

//给定：一条直线，以及直线外一点
//求出：点到直线距离
_DLL_EXPORT double fnGetPtToLineDistance(double a1,double b1, double c1, DPOINT pt);
_DLL_EXPORT double fnGetPtToLineDistance(DPOINT pts,DPOINT pte, DPOINT pt);

//给定：2个圆的信息
//求出：2个圆的交点
_DLL_EXPORT int fnGetCircleCircleCrs(DPOINT ptC0,double r0, DPOINT ptC1, double r1, DPOINT& pt1,DPOINT& pt2);

//给定：一条直线，一个圆 （圆心，半径）
//求出：直线与圆的交点   返回0：无交点   1：相切   2：2个交点
_DLL_EXPORT int fnGetLineCircleCrs(DPOINT pts,DPOINT pte,DPOINT ptc, double r, DPOINT& pt1,DPOINT& pt2);
_DLL_EXPORT int fnGetLineCircleCrs(double a1,double b1,double c1, DPOINT ptc, double r, DPOINT& pt1,DPOINT& pt2);

//给定：两条直线
//求出：两条直线的交点 返回0：无交点 
_DLL_EXPORT BOOL fnGetLineLineCrs(DPOINT pt0,DPOINT pt1,DPOINT pt2,DPOINT pt3, DPOINT& ptCrs);
_DLL_EXPORT BOOL fnGetLineLineCrs(double a1,double b1,double c1, double a2,double b2,double c2,DPOINT& ptCrs);
_DLL_EXPORT BOOL fnGetLineLineCrs(DPOINT ptCenter1, double dbAngle1, DPOINT ptCenter2, double dbAngle2, DPOINT& ptCrs);
_DLL_EXPORT BOOL fnGetLineLineCrs(DPOINT pt0, DPOINT pt1, double a1, double b1, double c1, DPOINT& ptCrs);


//给定：直线的起点，末点，延伸长度（正代表延伸，负代表内缩），延伸标识（1：延伸起点 0：延伸末点)
//求出：延伸后的点的坐标
_DLL_EXPORT DPOINT fnGetLineExtPt(DPOINT pts,DPOINT pte,double dbl,BOOL bSTRExt = TRUE);

//给定：线段的起点，末点，计算线段的中点坐标
//求出：中点的坐标
_DLL_EXPORT DPOINT fnGetLineMiddlePt(DPOINT pts,DPOINT pte);

//给定：圆弧的起点，末点，圆心，延伸长度（正代表延伸，负代表内缩），延伸标识（1：延伸起点 0：延伸末点)
//求出：延伸后的点的坐标
_DLL_EXPORT DPOINT fnGetArcExtPt(DPOINT pts,DPOINT pte,DPOINT ptc,double dbl,BOOL bSTRExt  = TRUE);

//直线方程式转换
_DLL_EXPORT void fnLineEquationConvert(DPOINT pts,DPOINT pte, double& a, double& b, double& c);

//计算2条直线的内切圆，返回切点以及圆心，直线是否需要偏移
_DLL_EXPORT void fnGetLineArc(DPOINT ptLine1S,DPOINT ptLine1E,DPOINT ptLine2S,DPOINT ptLine2E,double dbRadius,BOOL bOffset1,BOOL bOffset2,DPOINT &ptCenter,DPOINT &ptCross1,DPOINT &ptCross2);

//判断点是否在直线上
_DLL_EXPORT  BOOL fnPointInLine(DPOINT ptOne,DPOINT ptLineS,DPOINT ptLineE);

//直线方程式转换,以起点作为垂足
_DLL_EXPORT void fnGetVerticalLine(DPOINT pts,DPOINT pte, double& a, double& b, double& c);

//给定一个圆弧与截取的角度大小，求截取后的终点坐标
_DLL_EXPORT DPOINT fnGetArcMidPoint(DPOINT ptCenter, double dbRadius, double dbAngle);

//计算值是否在某个范围内
_DLL_EXPORT BOOL fnBetween(double dbMiddle, double dbMin, double dbMax);

#ifdef _cplusplus
}
#endif



#endif



