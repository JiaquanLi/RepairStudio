// CalCorrectResult.cpp: implementation of the CPosCorrect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PosCorrect.h"
#include <math.h>
#include <conio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPosCorrect::CPosCorrect()
{
//初始化
	int i,j;

	for (i=0;i<MATRIX_N;i++)
	{
		for (j=0;j<MATRIX_N;j++)
		{
			matrixA[i][j] = 0.0;
		}
		matrixB[i] = 0;
		m_returnRoi[i] = 0;
	}

	m_return[0] = 1;
	m_return[1] = 0;
	m_return[2] = 0;
	m_return[3] = 1;
	m_return[4] = 0;
	m_return[5] = 0;

	m_dbAngle = 0;

	m_bCalKxKy = FALSE;
	m_nPoint = 0;
}

CPosCorrect::~CPosCorrect()
{

}

void CPosCorrect::ClearTransforms()
{
	//初始化
	int i,j;
	
	for (i=0;i<MATRIX_N;i++)
	{
		for (j=0;j<MATRIX_N;j++)
		{
			matrixA[i][j] = 0.0;
		}
		matrixB[i] = 0;
		m_returnRoi[i] = 0;
	}

	m_return[0] = 1;
	m_return[1] = 0;
	m_return[2] = 0;
	m_return[3] = 1;
	m_return[4] = 0;
	m_return[5] = 0;
	
	m_dbAngle = 0;

}
//object 理论值,DXF数据信息
//real 实际值，实际平台取得数值
void CPosCorrect::GetTransforms(double objectX[], double objectY[], double realX[],double realY[],int num,BOOL bCalKxKy)
{
	m_bCalKxKy = bCalKxKy;
	m_nPoint = num;
	//一些矩阵项
	double SumX2=0.0,SumXY=0.0,
			SumY2=0.0,SumX=0.0,
			SumY=0.0,SumXXb=0.0,
			SumYXb=0.0,SumXYb=0.0,
			SumYYb=0.0,SumXb=0.0,
			SumYb=0.0;

	//开始计算一些数值
	for (int i=0;i<num;i++)
	{	
		SumX2 = SumX2 + objectX[i] * objectX[i];
		SumXY = SumXY + objectX[i] * objectY[i];
		SumY2 = SumY2 + objectY[i] * objectY[i];
		SumX = SumX + objectX[i];
		SumY = SumY + objectY[i];
		
		SumXXb = SumXXb + objectX[i] * realX[i];
		SumYXb = SumYXb + objectY[i] * realX[i];
		SumXYb = SumXYb + objectX[i] * realY[i];
		SumYYb = SumYYb + objectY[i] * realY[i];

		SumXb = SumXb + realX[i];
		SumYb = SumYb + realY[i];
	}
	
	//构造6*6阶方阵	A
	matrixA[0][0] =	SumX2;
	matrixA[0][1] = SumXY;
	matrixA[0][4] = SumX;

	matrixA[1][0] = SumXY;
	matrixA[1][1] = SumY2;
	matrixA[1][4] = SumY;

	matrixA[2][2] = SumX2;
	matrixA[2][3] = SumXY;
	matrixA[2][5] = SumX;

	matrixA[3][2] = SumXY;
	matrixA[3][3] = SumY2;
	matrixA[3][5] = SumY;

	matrixA[4][0] = SumX;
	matrixA[4][1] = SumY;
	matrixA[4][4] = num;

	matrixA[5][2] = SumX;
	matrixA[5][3] = SumY;
	matrixA[5][5] = num;


	//构造6*1阶方阵	B
	matrixB[0] = SumXXb;
	matrixB[1] = SumYXb;
	matrixB[2] = SumXYb;
	matrixB[3] = SumYYb;
	matrixB[4] = SumXb;
	matrixB[5] = SumYb;

	//计算结果
	m_ptRefCenter.x = SumX / num;
	m_ptRefCenter.y = SumY / num;
	m_ptRealCenter.x = SumXb / num;
	m_ptRealCenter.y = SumYb / num;
	
	lzyxq(matrixA,matrixB);	
	hdai(matrixA,matrixB); 
	//1个，2个对位点的单独计算。。。。。。	
	if (1 == num)
	{
		//直接计算出转换阵
		
		m_return[0] = 1;
		m_return[1] = 0;
		m_return[2] = 0;
		m_return[3] = 1;
		m_return[4] = realX[0] - objectX[0];
		m_return[5] = realY[0] - objectY[0];

		return;//1个对位点，只代表平移变换，无旋转，无缩放
	}
	//2个对位点
	if (2 == num)
	{
		double costheat = 0;
		double sintheat = 0;
		double sincos = 0;

		sincos = (objectX[1]-objectX[0])*(objectX[1]-objectX[0])+(objectY[1]-objectY[0])*(objectY[1]-objectY[0]);
		costheat = ((realX[1]-realX[0])*(objectX[1]-objectX[0])+(realY[1]-realY[0])*(objectY[1]-objectY[0])) / sincos;
		sintheat = ((realY[1]-realY[0])*(objectX[1]-objectX[0])-(realX[1]-realX[0])*(objectY[1]-objectY[0])) / sincos;
		m_return[0] = costheat;
		m_return[1] = -1*sintheat;
		m_return[2] = sintheat;
		m_return[3] = costheat;
		m_return[4] = realX[0] - objectX[0]*costheat + objectY[0]*sintheat;
		m_return[5] = realY[0] - objectX[0]*sintheat - objectY[0]*costheat;

		return;//2个对位点，只代表平移、旋转，不计算缩放
	}

	//大于等于3个点时，可以计算是否缩放，小于3点，是没有缩放的
	
	if (!m_bCalKxKy)//如果不计算缩放，则需要把矩阵分解后在重新组合起来
	{
		//分别计算出来旋转角度，缩放比率，以及平移量
		double kx = sqrt(m_return[0] * m_return[0] + m_return[2] * m_return[2]);
		double ky = sqrt(m_return[1] * m_return[1] + m_return[3] * m_return[3]);
		//计算出旋转角度
		double dbAngle = 0;
		if (fnCompareDouble(fabs(m_return[0]),0))
		{
			dbAngle = atan(m_return[2]/m_return[0]);
		}

		//修正矩阵的值
 		m_return[0] = cos(dbAngle);
 		m_return[1] = -1*sin(dbAngle);
 		m_return[2] = -1*m_return[1];
 		m_return[3] = m_return[0];

		//以对位中心点为参考点旋转		
		m_return[4] = m_ptRealCenter.x;
		m_return[5] = m_ptRealCenter.y;
	}

	return;
}

void CPosCorrect::hdai(double a[][MATRIX_N],double *b) 
{ 
	double x[MATRIX_N]; 
	int i,j; 
	double sum; 
	x[MATRIX_N-1]=b[MATRIX_N-1]/a[MATRIX_N-1][MATRIX_N-1]; 
	for(i=MATRIX_N-2;i>=0;i--) 
	{ 
		sum=0; 
		for(j=i+1;j<MATRIX_N;j++) 
			sum+=a[i][j]*x[j]; 
		x[i]=(b[i]-sum)/a[i][i]; 
	} 

    //得到最终结果	
	for(i=0;i<MATRIX_N;i++) 
	{ 
		m_return[i] = x[i];
	} 
} 

void CPosCorrect::lzy(double a[][MATRIX_N],double *b,int k) 
{ 
	int i,j,t; 
	double tempa,tempb; 
	t=k; 
	tempa=a[t][k]; 
	
	for(i=k+1;i<MATRIX_N;i++) 
	{ 
		if(fabs(tempa)<fabs(a[i][k])) 
		{ 
			tempa=a[i][k]; 
			t=i; 
		} 
	} 
	
	if(t!=k) 
	{ 
		for(j=0;j<MATRIX_N;j++) 
		{ 
			tempa=a[k][j]; 
			a[k][j]=a[t][j]; 
			a[t][j]=tempa; 
		} 
		
		tempb=b[k]; 
		b[k]=b[t]; 
		b[t]=tempb; 
	} 
} 

void CPosCorrect::lzyxq(double a[][MATRIX_N],double *b) 
{ 
	int i,j,k; 
	
	double l; 
	for(k=0;k<MATRIX_N-1;k++) 
	{ 
		
		lzy(a,b,k); 
		for(i=k+1;i<MATRIX_N;i++) 
		{ 
			l=a[i][k]/a[k][k]; 
			b[i]-=l*b[k]; 
			for(j=k;j<MATRIX_N;j++) 
			{ 
				a[i][j]-=l*a[k][j]; 
				
			} 
		} 
	} 
} 

void CPosCorrect::myprintf(double a[][MATRIX_N],double *b) 
{ 
	int i,j; 
	printf("a is:\n"); 
	for(i=0;i<MATRIX_N;i++) 
	{ 
		for(j=0;j<MATRIX_N;j++) 
		{ 
			printf("%4.6f ",a[i][j]); 
		} 
		printf("\n"); 
	} 
	printf("b is:\n"); 
	for(i=0;i<MATRIX_N;i++) 
	{ 
		printf("%4.6f\n",b[i]); 
	} 
} 

void CPosCorrect::GetTransResult(CorrectData &data)
{	
	//如果之前没有计算过初始矩阵
	if (fabs(m_return[0]) < 0.00001)
	{
		return ;
	}

	//旋转角度 逆时针 弧度制
	m_returnRoi[0] = atan(-1.0 * m_return[1] / m_return[0] );
//	m_returnRoi[0] = atan(m_return[2] / m_return[0] );
	
	//kx x轴缩放
	m_returnRoi[1] = sqrt(m_return[0]*m_return[0] + m_return[1]*m_return[1]);	
	//ky y轴缩放
	m_returnRoi[2] = sqrt(m_return[2]*m_return[2] + m_return[3]*m_return[3]);	
	//x偏移
	m_returnRoi[3] = m_ptRealCenter.x - m_ptRefCenter.x;
	//y偏移
	m_returnRoi[4] = m_ptRealCenter.y - m_ptRefCenter.y;
	//0
	m_returnRoi[5] = 0;
	//赋值
	data.dbAngle = m_returnRoi[0];
	data.dbOffsetX = m_returnRoi[3];
	data.dbOffsetY = m_returnRoi[4];
	data.dbRatioX = m_returnRoi[1];
	data.dbRatioY = m_returnRoi[2];
	data.ptCenter = m_ptRefCenter;
}

void CPosCorrect::GetTransResult(BOOL bAlign,double &dbResult0,double &dbResult1,double &dbResult2,double &dbResult3,double &dbResult4,double &dbResult5)
{
	if (bAlign)
	{
		dbResult0 = m_return[0];
		dbResult1 = m_return[1];
		dbResult2 = m_return[2];
		dbResult3 = m_return[3];
		dbResult4 = m_return[4];
		dbResult5 = m_return[5];
	}
	else
	{
		dbResult0 = 1;
		dbResult1 = 0;
		dbResult2 = 0;
		dbResult3 = 1;
		dbResult4 = 0;
		dbResult5 = 0;
	}
}

void CPosCorrect::GetTransPoint(double dbInx,double dbIny,double &dbOutx,double &dbOuty)
{
	if (m_bCalKxKy || m_nPoint < 3)//计算缩放,或者对位点数小于3个，用这个矩阵
	{
		dbOutx = m_return[0] * dbInx + m_return[1] * dbIny + m_return[4];
		dbOuty = m_return[2] * dbInx + m_return[3] * dbIny + m_return[5];
	}

	if(!m_bCalKxKy && m_nPoint > 2)//不计算缩放，并且点数大于等于3,用这个矩阵
	{
		dbOutx = m_return[0] * (dbInx-m_ptRefCenter.x) + m_return[1] * (dbIny-m_ptRefCenter.y) + m_return[4];
		dbOuty = m_return[2] * (dbInx-m_ptRefCenter.x) + m_return[3] * (dbIny-m_ptRefCenter.y) + m_return[5];
	}
}

/*
void CPosCorrect::GetTransPointRoi(double dbInx,double dbIny,double &dbOutx,double &dbOuty)
{
	dbOutx = m_pRoi.x + (dbInx - m_pRoi.x) * cos(m_returnRoi[0]) - (dbIny - m_pRoi.y) * sin(m_returnRoi[0]) + m_returnRoi[3];
	dbOuty = m_pRoi.y + (dbIny - m_pRoi.y) * cos(m_returnRoi[0]) + (dbInx - m_pRoi.x) * sin(m_returnRoi[0]) + m_returnRoi[4];
}
*/
//////////////////////////////////////////////////////////////////////////

//计算相对中心，必须先调用该接口后才能进行计算
void CPosCorrect::fnCalcRef(double objectX[], double objectY[], double realX[],double realY[],int num)
{ 
	double dbRefx = 0;
	double dbRefy = 0;
	double dbRealx = 0;
	double dbRealy = 0;

	m_caRefPoint.RemoveAll();
	m_caRealPint.RemoveAll();

	for (int i = 0; i < num; i++)
	{
		DPOINT ptRef,ptReal;
		ptRef.x = objectX[i];
		ptRef.y = objectY[i];
		m_caRefPoint.Add(ptRef);

		ptReal.x = realX[i];
		ptReal.y = realY[i];
		m_caRealPint.Add(ptReal);

		dbRefx = dbRefx + objectX[i];
		dbRefy = dbRefy + objectY[i];
		dbRealx = dbRealx + realX[i];
		dbRealy = dbRealy + realY[i];
	}

	//计算中心点
	m_ptRefCenter.x = dbRefx / num;
	m_ptRefCenter.y = dbRefy / num;
	m_ptRealCenter.x = dbRealx / num;
	m_ptRealCenter.y = dbRealy / num;
}

//计算缩放比例
void CPosCorrect::fnCalcRatio()
{	
	double dbMatrix1 = 0;
	double dbMatrix2 = 0;
	double dbMatrix3 = 0;
	double dbMatrix4 = 0;

    for( int i = 0; i < m_caRefPoint.GetSize(); i++)
	{
		dbMatrix1 = dbMatrix1 + (m_caRefPoint.GetAt(i).x - m_ptRefCenter.x) * ((m_caRealPint.GetAt(i).x - m_ptRealCenter.x) * cos(m_dbAngle / ARC_ANGEL) - (m_caRealPint.GetAt(i).y - m_ptRealCenter.y) * sin( m_dbAngle / ARC_ANGEL)); 
	
		dbMatrix2 = dbMatrix2 + (m_caRefPoint.GetAt(i).x - m_ptRefCenter.x) * (m_caRefPoint.GetAt(i).x - m_ptRefCenter.x);
			
		dbMatrix3 = dbMatrix3 + (m_caRefPoint.GetAt(i).y - m_ptRefCenter.y) * ((m_caRealPint.GetAt(i).x - m_ptRealCenter.x) * sin( m_dbAngle / ARC_ANGEL) + (m_caRealPint.GetAt(i).y - m_ptRealCenter.y) * cos( m_dbAngle / ARC_ANGEL));
		
		dbMatrix4 = dbMatrix4 + (m_caRefPoint.GetAt(i).y - m_ptRefCenter.y) * (m_caRefPoint.GetAt(i).y - m_ptRefCenter.y);		
    }

	//计算偏移量
	m_ptRatio.x = dbMatrix1 / dbMatrix2;
	m_ptRatio.y = dbMatrix3 / dbMatrix4;	
}

//计算旋转角度
void CPosCorrect::fnCalcAngle(double dbXRate,double dbYRate)
{
	double dbMatrix1 = 0;
	double dbMatrix2 = 0;
	double dbMatrix3 = 0;
	double dbMatrix4 = 0;
    
    for( int i = 0; i < m_caRefPoint.GetSize(); i++)
	{
		dbMatrix1 = dbMatrix1 + (m_caRefPoint.GetAt(i).x - m_ptRefCenter.x) * (m_caRealPint.GetAt(i).y - m_ptRealCenter.y);

		dbMatrix2 = dbMatrix2 + (m_caRefPoint.GetAt(i).y - m_ptRefCenter.y) * (m_caRealPint.GetAt(i).x - m_ptRealCenter.x);

		dbMatrix3 = dbMatrix3 + (m_caRefPoint.GetAt(i).x - m_ptRefCenter.x) * (m_caRealPint.GetAt(i).x - m_ptRealCenter.x);

		dbMatrix4 = dbMatrix4 + (m_caRefPoint.GetAt(i).y - m_ptRefCenter.y) * (m_caRealPint.GetAt(i).y - m_ptRealCenter.y);		
    }
	
	//计算旋转角度
	m_dbAngle = atan((-1 * dbXRate * dbMatrix1 + dbYRate * dbMatrix2) / (dbXRate * dbMatrix3 + dbYRate * dbMatrix4))  * ARC_ANGEL;
}

//计算最终的结果
void CPosCorrect::fnCalcResult(double objectX[], double objectY[], double realX[],double realY[],int num)
{
	int nCount = 0;
	double dbOldRatiox = 0;
	double dbOldRatioy = 0;
	double dbOldAngle = 0;

    m_ptRatio.x = 1;
    m_ptRatio.y = 1;
    m_dbAngle = 91;

	//计算中心点坐标
	fnCalcRef(objectX,objectY,realX,realY,num);
	
    do 
    {
		dbOldRatiox = m_ptRatio.x;
		dbOldRatioy = m_ptRatio.y;
		dbOldAngle = m_dbAngle;		
		//计算角度
		fnCalcAngle(dbOldRatiox,dbOldRatioy);
		//计算缩放
		fnCalcRatio();
		nCount++;
		
    } while( (fabs(dbOldRatiox - m_ptRatio.x) > 0.00001 || fabs(dbOldRatioy - m_ptRatio.y) > 0.00001 || fabs(dbOldAngle - m_dbAngle) > 0.0001) && (nCount <= 1000) );
}

//根据计算结果对输入的点进行转换
void CPosCorrect::fnCalcPoint(double dbInx,double dbIny,double &dbOutx,double &dbOuty)
{
	double dbRefx = dbInx - m_ptRefCenter.x;
	double dbRefy = dbIny - m_ptRefCenter.y;
	dbOutx = m_ptRealCenter.x + m_ptRatio.x * dbRefx * cos(m_dbAngle / ARC_ANGEL) + m_ptRatio.y * dbRefy * sin( m_dbAngle / ARC_ANGEL);
	dbOuty = m_ptRealCenter.y + m_ptRatio.y * dbRefy * cos(m_dbAngle / ARC_ANGEL) - m_ptRatio.x * dbRefx * sin( m_dbAngle / ARC_ANGEL);
}

void CPosCorrect::fnGetCalcResult(double &dbAngle,double &dbXRate,double &dbYRate)
{
	dbAngle = m_dbAngle;
	dbXRate = m_ptRatio.x;
	dbYRate = m_ptRatio.y;
}
