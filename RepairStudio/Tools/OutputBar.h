// outputbar.h : interface of the COutputBar class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

enum OUTPUBAR_MODE
{
	OUTPUTBAR_PROCESS = 0,				//������
	OUTPUTBAR_THREADRUNNING,			//��̨��Ҫ�߳�
	OUTPUTBAR_ERROR						//������Ϣ
};

class COutputEdit : public CRichEditCtrl
{
	// ����
public:
	COutputEdit();

	// ʵ��
public:
	virtual ~COutputEdit();

	/*****************************
	* FunctionName: fnOutPutMessage
	*
	* Function:�����Ϣ����Ϣ�������
	* param[in] strMessage �������Ϣ����
	* param[in] bAppend �Ƿ���Ҫ����
	* param[in] color �����������ɫ
	* param[in] nThick ����������С
	* param[in] bErase �Ƿ����������ڵ�ԭ������
	*****************************/
	void fnOutPutMessage(CString strMessage, COLORREF color = COLOR_BLACK, BOOL bAppend = FALSE, BOOL bErase = FALSE);

	void fnSetFontSize(int nSize = 350);

private:
	int m_nSize;

protected:
	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
};

class COutputBar : public CBCGPDockingControlBar
{
public:
	COutputBar();
// Attributes
protected:
	CBCGPTabWnd	m_wndTabs;	


public:
	virtual ~COutputBar();
	COutputEdit* m_wndProcess;
	COutputEdit* m_wndThread;//ר�����������Զ����еĺ�̨�߳�
	COutputEdit* m_wndError;

	CFont m_Font;
	CFont m_FontEdit;
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL CanFloat() const { return FALSE; }
	
	//�رյ��Ϸ��Ĺرհ�ť
	virtual BOOL CanBeClosed() const { return FALSE; }
	
	DECLARE_MESSAGE_MAP()

private:
	void fnSetFont();

public:
	/*****************************
* FunctionName: fnOutPutMessage
*
* Function:�����Ϣ����Ϣ�������
* param[in] strMessage �������Ϣ����
* param[in] bAppend �Ƿ���Ҫ����
* param[in] color �����������ɫ
* param[in] nThick ����������С
* param[in] bErase �Ƿ����������ڵ�ԭ������
*****************************/
	void fnOutPutMessage(CString strMessage, COLORREF color = COLOR_BLACK, OUTPUBAR_MODE nOutPlace = OUTPUTBAR_PROCESS, BOOL bAppend = FALSE, BOOL bErase = FALSE);
};

/////////////////////////////////////////////////////////////////////////////
