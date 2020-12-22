// outputbar.h : interface of the COutputBar class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

enum OUTPUBAR_MODE
{
	OUTPUTBAR_PROCESS = 0,				//主进程
	OUTPUTBAR_THREADRUNNING,			//后台主要线程
	OUTPUTBAR_ERROR						//报错信息
};

class COutputEdit : public CRichEditCtrl
{
	// 构造
public:
	COutputEdit();

	// 实现
public:
	virtual ~COutputEdit();

	/*****************************
	* FunctionName: fnOutPutMessage
	*
	* Function:输出信息到信息输出框内
	* param[in] strMessage 输出的信息内容
	* param[in] bAppend 是否需要换行
	* param[in] color 输出的字体颜色
	* param[in] nThick 输出的字体大小
	* param[in] bErase 是否清除输出框内的原有内容
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
	COutputEdit* m_wndThread;//专门用来运行自动运行的后台线程
	COutputEdit* m_wndError;

	CFont m_Font;
	CFont m_FontEdit;
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL CanFloat() const { return FALSE; }
	
	//关闭掉上方的关闭按钮
	virtual BOOL CanBeClosed() const { return FALSE; }
	
	DECLARE_MESSAGE_MAP()

private:
	void fnSetFont();

public:
	/*****************************
* FunctionName: fnOutPutMessage
*
* Function:输出信息到信息输出框内
* param[in] strMessage 输出的信息内容
* param[in] bAppend 是否需要换行
* param[in] color 输出的字体颜色
* param[in] nThick 输出的字体大小
* param[in] bErase 是否清除输出框内的原有内容
*****************************/
	void fnOutPutMessage(CString strMessage, COLORREF color = COLOR_BLACK, OUTPUBAR_MODE nOutPlace = OUTPUTBAR_PROCESS, BOOL bAppend = FALSE, BOOL bErase = FALSE);
};

/////////////////////////////////////////////////////////////////////////////
