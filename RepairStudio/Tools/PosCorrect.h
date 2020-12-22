//interface for the CPosCorrect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCORRECTRESULT_H__9142063C_0F3F_41FA_8B6A_2FA547B11AE0__INCLUDED_)
#define AFX_CALCORRECTRESULT_H__9142063C_0F3F_41FA_8B6A_2FA547B11AE0__INCLUDED_
/*--------------------------
此类为图形相似逼近类 运用了最小二乘原理

 解线性方程组时 运用了高斯变换
  
就一个方法 calResult 

计算结果为:m_return[]
如下形式 AX+B=Y
A为[m_return0  m_return1]	A表示旋转和涨缩
   [m_return2  m_return3] 

B为[m_return4]				B表示偏移
   [m_return5]

旋转阵			平移阵
|m0	m1|			|m4|
|m2	m3|			|m5|

用法: 调用calResult后 使用m_return;
如理论上一个坐标为(a,b)
则实际为
  (m_return0*a + m_return1*b + m_return4,
   m_return2*a+ m_return3*b + m_return5)
-----------------------------------*/


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXNUM 1000	//最大数据个数
#define MATRIX_N 6/*方程阶数*/ 

struct CorrectData
{
	//旋转角度
	double dbAngle;
	//偏移量
	double dbOffsetX,dbOffsetY;
	//缩放
	double dbRatioX,dbRatioY;
	//转换中心点
	DPOINT ptCenter;

	CorrectData::CorrectData()
	{
		dbAngle = 0;
		dbOffsetY = 0;
		dbOffsetX = 0;
		dbRatioX = 1;
		dbRatioY = 1;
	}

	const CorrectData& operator=(const CorrectData& data)   
	{   
		if (this != &data)   
		{ 
			dbAngle = data.dbAngle;
			dbOffsetX = data.dbOffsetX;
			dbOffsetY = data.dbOffsetY;
			dbRatioX = data.dbRatioX;
			dbRatioY = data.dbRatioY;
			ptCenter = data.ptCenter;
			return   data;   
		}	
		return  *this; 
	}   
};

class CPosCorrect  
{
public:
	CPosCorrect();
	virtual ~CPosCorrect();

	void ClearTransforms();

	//根据输入的DXF对位点，以及实际平台读到的实际对位点，计算结果得到转换矩阵
	//1点对位:计算平移; 2点对位:计算平移、旋转，不计算缩放;3点以及以上:都计算，但可以选择是否计算缩放
	void GetTransforms(double objectX[], double objectY[], double realX[],double realY[],int num,BOOL bCalKxKy = TRUE);
	//根据输入DXF点，计算对位坐标转换到实际平台上的点
	void GetTransPoint(double dbInx,double dbIny,double &dbOutx,double &dbOuty);
	//计算图形转换数据，包括角度，偏移量等
	void GetTransResult(CorrectData &data);
	void GetTransResult(BOOL bAlign,double &dbResult0,double &dbResult1,double &dbResult2,double &dbResult3,double &dbResult4,double &dbResult5);

//	void calcRoiPoint(double dbInx,double dbIny,double &dbOutx,double &dbOuty);


	//另外一种对位方式，以作比较
	//////////////////////////////////////////////////////////////////////////	
	//计算最终的结果
	void fnCalcResult(double objectX[], double objectY[], double realX[],double realY[],int num);
	//根据计算结果对输入的点进行转换
	void fnCalcPoint(double dbInx,double dbIny,double &dbOutx,double &dbOuty);
	void fnGetCalcResult(double &dbAngle,double &dbXRate,double &dbYRate);

	//////////////////////////////////////////////////////////////////////////
private:
	void myprintf(double a[][MATRIX_N],double *b);/*打印运算矩阵a,b*/ 
	void hdai(double a[][MATRIX_N],double *b);/*回代求解*/ 
	void lzyxq(double a[][MATRIX_N],double *b);/*高斯变换*/ 
	void lzy(double a[][MATRIX_N],double *b,int k);/*行变换*/ 

	//////////////////////////////////////////////////////////////////////////

	//计算相对中心，必须先调用该接口后才能进行计算
	void fnCalcRef(double objectX[], double objectY[], double realX[],double realY[],int num);

	//计算缩放比例
	void fnCalcRatio();
	
	//计算旋转角度
	void fnCalcAngle(double dbXRate,double dbYRate);

	//////////////////////////////////////////////////////////////////////////

private:	
	double matrixA[MATRIX_N][MATRIX_N];
	double matrixB[MATRIX_N];

	//无旋转中心 
	double m_return[MATRIX_N];
	//有旋转中心
	double m_returnRoi[MATRIX_N];

	//实际点坐标和原来图形上的点坐标
	POINTARRAY m_caRefPoint;
	POINTARRAY m_caRealPint;

	DPOINT m_ptRefCenter;
	DPOINT m_ptRealCenter;

	//计算结果
	DPOINT m_ptRatio;
	double m_dbAngle;

	//旋转中心
	DPOINT m_pRoi;

	//是否计算缩放
	BOOL m_bCalKxKy;
	int m_nPoint;//对位点的个数

};

#endif // !defined(AFX_CALCORRECTRESULT_H__9142063C_0F3F_41FA_8B6A_2FA547B11AE0__INCLUDED_)
