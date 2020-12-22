#ifndef _DLL_GEOMETRY_H
#define _DLL_GEOMETRY_H

#include "CommonDefine.h"
#ifdef _cplusplus
extern "C"
{
#endif

#define _DLL_EXPORT _declspec(dllexport)

/*
1.	��תһ����
����: dbPtX, dbPtY ����ת�ĵ�����
����: dbAngle �Ƕ�(�Ƕ���,��ʱ��Ϊ��)
����: dbCenterX , dbCenterY ��ת��������
���: dbPtX, dbPtY ��ת�������
���� �ɹ�������ʧ��
*/
_DLL_EXPORT	BOOL fnRotatePt(double &dbPtX, double &dbPtY, double dbAngle ,double dbCenterX, double dbCenterY);
	
/*
2.	����任һ����
����: dbPtX, dbPtY ���任�ĵ�����
����: dbM11, dbM12, dbM21, dbM22, ��������,����,����,���µ�����
���: dbPtX, dbPtY �任�������
���� �ɹ�������ʧ��
*/
_DLL_EXPORT BOOL fnMatrixPt(double &dbPtX, double &dbPtY, double dbM11, double dbM12,double dbM21 ,double dbM22);

/*
3.	������Ϊֱ��(��С�������)
���� dbPtX[],dbPtY[] ��ϵ�����
���� nDataCount ��ϵ����
��� dbK, dbB (ֱ����ʽ y=Kx+B �е�K��B)
���� 0 ʧ��
1 ��ֱ�߶� (x=B ����ʽ Bֵ��dbB���)
2 �Ǵ�ֱ�߶�(ֱ����ʽ y=Kx+B �е�K��B)
*/
_DLL_EXPORT int fnLeastSqLine(double dbPtX[], double dbPtY[],int nDataCount,double &dbK, double &dbB);

/*
4.	������ΪԲ(��С�������)
���� dbPtX[],dbPtY[] ��ϵ�����
���� nDataCount ��ϵ����
��� dbCenterX, dbCenterYԲ������
��� dbRadius �뾶
���� �ɹ�������ʧ��
*/
_DLL_EXPORT BOOL fnLeastSqCircle(double dbPtX[], double dbPtY[],int nDataCount,double & dbCenterX, double &dbCenterY, double &dbRadius);

/*
5.	������ΪԲ��(��С�������)
���� dbPtX[],dbPtY[] ��ϵ�����
���� nDataCount ��ϵ����
��� dbCenterX, dbCenterYԲ������
��� dbRadius �뾶
��� ��� dbAngle, Բ���Ƕ�(�Ƕ���,��ֵ������ʱ��)
���� �ɹ�������ʧ��
*/
_DLL_EXPORT BOOL fnLeastSqArc(double dbPtX[], double dbPtY[],int nDataCount,double &dbCenterX, double &dbCenterY, double &dbRadius,double &dbAngle);


/*6-a
����Spline
���� dbPtX, dbPtY ���������
���� ���ݵĸ���
���� �ɹ�������ʧ��
*/

_DLL_EXPORT BOOL fnCreateCubicSpline(double *dbPtX, double *dbPtY,int nDataCount);

/*6-b
���X��ӦY��ֵ
���� dbPtX    X����
��� dbPtY    Y������
���� �ɹ�,ʧ��
*/
_DLL_EXPORT BOOL fnCubicSplineYbyX(double dbPtX, double &dbPtY);

/*
7.	�����߶ν���
���� dbLine1PtX1, dbLine1PtY1, dbLine1PtX2, dbLine1PtY2 һ�߶ε���ĩ��
���� dbLine2PtX1, dbLine2PtY1, dbLine2PtX2, dbLine2PtY2 ���߶ε���ĩ��
��� dbPtX1, dbPtY1, ��������1
��� dbPtX2, dbPtY2, ��������2
���� 0 �޽��� 
1 һ������ ������뽻������1��,
2 ���غ� �غϲ��ֵ���ĩ����뽻������1�ͽ�������2��
*/
_DLL_EXPORT int fnLinesCross(double dbLine1PtX1, double dbLine1PtY1, 
							 double dbLine1PtX2, double dbLine1PtY2, 
							 double dbLine2PtX1, double dbLine2PtY1, 
							 double dbLine2PtX2, double dbLine2PtY2, 
							 double &dbPtX1,double &dbPtY1,
							 double &dbPtX2,double &dbPtY2);

//2��ֱ�ߵı�﷽ʽ��һ��
_DLL_EXPORT DPOINT fnLinesCross(DPOINT pts,DPOINT pte,double a,double b,double c);
							
/*
8.	���������
���� dbX1, dbY1, dbX2, dbY2 ��������
���� �������
*/
_DLL_EXPORT double fnGetPtsLength(double dbX1,double dbY1, double dbX2,double dbY2);

/*
9.	�ж����Ƿ����߶���
���� dbPtX, dbPtY �жϵ�����
���� dbLinePtX1, dbLinePtY1, dbLinePtX2, dbLinePtY2 �ж��߶���ĩ��
���� TRUE ���߶��� 
	 FALSE �����߶���
*/
_DLL_EXPORT BOOL fnPtInLine(double dbPtX, double dbPtY,double dbLinePtX1, double dbLinePtY1,
				double dbLinePtX2, double dbLinePtY2);

/*10.	��㵽�߶ε���̾���
���� dbPtX, dbPtY �жϵ�����
���� dbLinePtX1, dbLinePtY1, dbLinePtX2, dbLinePtY2 �߶���ĩ��
���� ��̾���
*/
_DLL_EXPORT double fnPtToLineMinLength(double dbPtX, double dbPtY,double dbLinePtX1, double dbLinePtY1,double dbLinePtX2, double dbLinePtY2);


/*11.	����������ֱ�߷���(y=kx+b��ʽ)
���� dbPtX1,dbPtY1, dbPtX2, dbPtY2��ĩ������
��� dbK, dbB (ֱ����ʽ y=Kx+B �е�K��B)
���� 0 ʧ��
1 ��ֱ�߶� (x=B ����ʽ Bֵ��dbB���)
2 �Ǵ�ֱ�߶�(ֱ����ʽ y=Kx+B �е�K��B)
*/
_DLL_EXPORT int fnGetLineByTwoPts(double dbPtX1,double dbPtY1, double dbPtX2,double dbPtY2,
					  double &dbK, double &dbB);

/*
12.	������ĩ�����������Ƕ� (�Ƕ���) //��X������н� ��ʱ��Ϊ��
���� dbPtX1, dbPtY1 �׵�����
���� dbPtX2, dbPtY2 ĩ������
���� bPositive FALSE (-180��180��ʽ) , TRUE(0--360��ʽ)
���� �Ƕ�ֵ
*/
_DLL_EXPORT double fnGetPtsAngle(double dbPtX1,double dbPtY1, double dbPtX2,double dbPtY2,BOOL bPositive=FALSE);

/*13.	�Ƚ�double��������
���� dbNum1, dbNum2 �Ƚϵ�����������ֵ
���� 0 ���
1 dbNum1 > dbNum2
-1 dbNum1 < dbNum2
*/
_DLL_EXPORT int fnCompareDouble(double dbNum1,double dbNum2);

/*14.	ʮ����,ʮ������ת��
a��16�����ַ�����ʾΪ�ɶ����ַ��� �� "31 32 2E 35 57"(���ַ�����12.5W��)

���� strHexAsc 16�����ַ���
���� ��׼�ַ���
*/
_DLL_EXPORT LPSTR fnHexAscToString(char* strHexAsc);

/*
b ��16�����ַ�ת��Ϊ10������
���� �ַ�(֧�ִ�Сд)
���� 10���ƶ�Ӧֵ
*/
_DLL_EXPORT int fnHexCharToDec(char cHexChar);

/*
��16�����ַ���ת��Ϊ10������(֧�ִ�Сд)
���� lpcHexStr 16���Ʊ�ʾ���ַ��� �硱3E�� ���Ϊ62
���� 10������
*/
_DLL_EXPORT int fnHexStrToDec(char* strHexAsc);

/*
17.	�ж����Ƿ������ڲ�
���� dbPtX, dbPtY �жϵ�����
���� dbPolyX, dbPolyY ����ε���(���������ǰ���˳�����,���Է��Ҳ���Բ����,����ʱ����Ϊ���)
���� nPtCount		  ����ε���
���� TRUE ���ڲ� 
	 FALSE ���ⲿ
*/
_DLL_EXPORT BOOL fnPtInPoly(double dbPtX, double dbPtY,double *dbPolyX, double *dbPolyY,
				int nPtCount);

//������ֱ����㣬ĩ�㣬ƫ����(>0),ƫ�Ʒ���ʸ�������ֱ� nFlag=-1��ʸ�������ֱ� nFlag=1��
//�����ƫ�ƺ��ֱ�߱�ʾ���� ax+by+c=0
_DLL_EXPORT BOOL fnGetLineOffset(DPOINT pts,DPOINT pte, double dbOfsAbs,int nFlag,double& a,double& b, double& c);
_DLL_EXPORT BOOL fnGetLineOffset(DPOINT pts,DPOINT pte, double dbOfsAbs,int nFlag,DPOINT& ptStart,DPOINT& ptEnd);

//������һ��ֱ�ߣ��Լ�ֱ����һ��
//������㵽ֱ�ߵĴ���
_DLL_EXPORT DPOINT fnGetPtToLinePerpenDicularCrs(double a1,double b1, double c1, DPOINT ptC);
_DLL_EXPORT DPOINT fnGetPtToLinePerpenDicularCrs(DPOINT pts,DPOINT pte,DPOINT ptC);

//������һ��ֱ�ߣ��Լ�ֱ����һ��
//������㵽ֱ�߾���
_DLL_EXPORT double fnGetPtToLineDistance(double a1,double b1, double c1, DPOINT pt);
_DLL_EXPORT double fnGetPtToLineDistance(DPOINT pts,DPOINT pte, DPOINT pt);

//������2��Բ����Ϣ
//�����2��Բ�Ľ���
_DLL_EXPORT int fnGetCircleCircleCrs(DPOINT ptC0,double r0, DPOINT ptC1, double r1, DPOINT& pt1,DPOINT& pt2);

//������һ��ֱ�ߣ�һ��Բ ��Բ�ģ��뾶��
//�����ֱ����Բ�Ľ���   ����0���޽���   1������   2��2������
_DLL_EXPORT int fnGetLineCircleCrs(DPOINT pts,DPOINT pte,DPOINT ptc, double r, DPOINT& pt1,DPOINT& pt2);
_DLL_EXPORT int fnGetLineCircleCrs(double a1,double b1,double c1, DPOINT ptc, double r, DPOINT& pt1,DPOINT& pt2);

//����������ֱ��
//���������ֱ�ߵĽ��� ����0���޽��� 
_DLL_EXPORT BOOL fnGetLineLineCrs(DPOINT pt0,DPOINT pt1,DPOINT pt2,DPOINT pt3, DPOINT& ptCrs);
_DLL_EXPORT BOOL fnGetLineLineCrs(double a1,double b1,double c1, double a2,double b2,double c2,DPOINT& ptCrs);
_DLL_EXPORT BOOL fnGetLineLineCrs(DPOINT ptCenter1, double dbAngle1, DPOINT ptCenter2, double dbAngle2, DPOINT& ptCrs);
_DLL_EXPORT BOOL fnGetLineLineCrs(DPOINT pt0, DPOINT pt1, double a1, double b1, double c1, DPOINT& ptCrs);


//������ֱ�ߵ���㣬ĩ�㣬���쳤�ȣ����������죬�������������������ʶ��1��������� 0������ĩ��)
//����������ĵ������
_DLL_EXPORT DPOINT fnGetLineExtPt(DPOINT pts,DPOINT pte,double dbl,BOOL bSTRExt = TRUE);

//�������߶ε���㣬ĩ�㣬�����߶ε��е�����
//������е������
_DLL_EXPORT DPOINT fnGetLineMiddlePt(DPOINT pts,DPOINT pte);

//������Բ������㣬ĩ�㣬Բ�ģ����쳤�ȣ����������죬�������������������ʶ��1��������� 0������ĩ��)
//����������ĵ������
_DLL_EXPORT DPOINT fnGetArcExtPt(DPOINT pts,DPOINT pte,DPOINT ptc,double dbl,BOOL bSTRExt  = TRUE);

//ֱ�߷���ʽת��
_DLL_EXPORT void fnLineEquationConvert(DPOINT pts,DPOINT pte, double& a, double& b, double& c);

//����2��ֱ�ߵ�����Բ�������е��Լ�Բ�ģ�ֱ���Ƿ���Ҫƫ��
_DLL_EXPORT void fnGetLineArc(DPOINT ptLine1S,DPOINT ptLine1E,DPOINT ptLine2S,DPOINT ptLine2E,double dbRadius,BOOL bOffset1,BOOL bOffset2,DPOINT &ptCenter,DPOINT &ptCross1,DPOINT &ptCross2);

//�жϵ��Ƿ���ֱ����
_DLL_EXPORT  BOOL fnPointInLine(DPOINT ptOne,DPOINT ptLineS,DPOINT ptLineE);

//ֱ�߷���ʽת��,�������Ϊ����
_DLL_EXPORT void fnGetVerticalLine(DPOINT pts,DPOINT pte, double& a, double& b, double& c);

//����һ��Բ�����ȡ�ĽǶȴ�С�����ȡ����յ�����
_DLL_EXPORT DPOINT fnGetArcMidPoint(DPOINT ptCenter, double dbRadius, double dbAngle);

//����ֵ�Ƿ���ĳ����Χ��
_DLL_EXPORT BOOL fnBetween(double dbMiddle, double dbMin, double dbMax);

#ifdef _cplusplus
}
#endif



#endif



