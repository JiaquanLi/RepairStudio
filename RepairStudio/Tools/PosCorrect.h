//interface for the CPosCorrect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCORRECTRESULT_H__9142063C_0F3F_41FA_8B6A_2FA547B11AE0__INCLUDED_)
#define AFX_CALCORRECTRESULT_H__9142063C_0F3F_41FA_8B6A_2FA547B11AE0__INCLUDED_
/*--------------------------
����Ϊͼ�����Ʊƽ��� ��������С����ԭ��

 �����Է�����ʱ �����˸�˹�任
  
��һ������ calResult 

������Ϊ:m_return[]
������ʽ AX+B=Y
AΪ[m_return0  m_return1]	A��ʾ��ת������
   [m_return2  m_return3] 

BΪ[m_return4]				B��ʾƫ��
   [m_return5]

��ת��			ƽ����
|m0	m1|			|m4|
|m2	m3|			|m5|

�÷�: ����calResult�� ʹ��m_return;
��������һ������Ϊ(a,b)
��ʵ��Ϊ
  (m_return0*a + m_return1*b + m_return4,
   m_return2*a+ m_return3*b + m_return5)
-----------------------------------*/


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXNUM 1000	//������ݸ���
#define MATRIX_N 6/*���̽���*/ 

struct CorrectData
{
	//��ת�Ƕ�
	double dbAngle;
	//ƫ����
	double dbOffsetX,dbOffsetY;
	//����
	double dbRatioX,dbRatioY;
	//ת�����ĵ�
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

	//���������DXF��λ�㣬�Լ�ʵ��ƽ̨������ʵ�ʶ�λ�㣬�������õ�ת������
	//1���λ:����ƽ��; 2���λ:����ƽ�ơ���ת������������;3���Լ�����:�����㣬������ѡ���Ƿ��������
	void GetTransforms(double objectX[], double objectY[], double realX[],double realY[],int num,BOOL bCalKxKy = TRUE);
	//��������DXF�㣬�����λ����ת����ʵ��ƽ̨�ϵĵ�
	void GetTransPoint(double dbInx,double dbIny,double &dbOutx,double &dbOuty);
	//����ͼ��ת�����ݣ������Ƕȣ�ƫ������
	void GetTransResult(CorrectData &data);
	void GetTransResult(BOOL bAlign,double &dbResult0,double &dbResult1,double &dbResult2,double &dbResult3,double &dbResult4,double &dbResult5);

//	void calcRoiPoint(double dbInx,double dbIny,double &dbOutx,double &dbOuty);


	//����һ�ֶ�λ��ʽ�������Ƚ�
	//////////////////////////////////////////////////////////////////////////	
	//�������յĽ��
	void fnCalcResult(double objectX[], double objectY[], double realX[],double realY[],int num);
	//���ݼ�����������ĵ����ת��
	void fnCalcPoint(double dbInx,double dbIny,double &dbOutx,double &dbOuty);
	void fnGetCalcResult(double &dbAngle,double &dbXRate,double &dbYRate);

	//////////////////////////////////////////////////////////////////////////
private:
	void myprintf(double a[][MATRIX_N],double *b);/*��ӡ�������a,b*/ 
	void hdai(double a[][MATRIX_N],double *b);/*�ش����*/ 
	void lzyxq(double a[][MATRIX_N],double *b);/*��˹�任*/ 
	void lzy(double a[][MATRIX_N],double *b,int k);/*�б任*/ 

	//////////////////////////////////////////////////////////////////////////

	//����������ģ������ȵ��øýӿں���ܽ��м���
	void fnCalcRef(double objectX[], double objectY[], double realX[],double realY[],int num);

	//�������ű���
	void fnCalcRatio();
	
	//������ת�Ƕ�
	void fnCalcAngle(double dbXRate,double dbYRate);

	//////////////////////////////////////////////////////////////////////////

private:	
	double matrixA[MATRIX_N][MATRIX_N];
	double matrixB[MATRIX_N];

	//����ת���� 
	double m_return[MATRIX_N];
	//����ת����
	double m_returnRoi[MATRIX_N];

	//ʵ�ʵ������ԭ��ͼ���ϵĵ�����
	POINTARRAY m_caRefPoint;
	POINTARRAY m_caRealPint;

	DPOINT m_ptRefCenter;
	DPOINT m_ptRealCenter;

	//������
	DPOINT m_ptRatio;
	double m_dbAngle;

	//��ת����
	DPOINT m_pRoi;

	//�Ƿ��������
	BOOL m_bCalKxKy;
	int m_nPoint;//��λ��ĸ���

};

#endif // !defined(AFX_CALCORRECTRESULT_H__9142063C_0F3F_41FA_8B6A_2FA547B11AE0__INCLUDED_)
