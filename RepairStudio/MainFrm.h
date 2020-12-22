// MainFrm.h : interface of the CMainFrame class
//


#pragma once
#include "WorkSpaceBar/WorkSpaceBar.h"
#include "WorkSpaceBar/WorkSpaceBar2.h"
#include "OutputBar.h"

class CMainFrame : public CBCGPFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CCamera m_Camera;

protected:  // control bar embedded members
	CBCGPStatusBar			m_wndStatusBar;
	CWorkSpaceBar			m_wndWorkSpace;
	CWorkSpaceBar2			m_wndWorkSpace2;
	COutputBar				m_wndOutput;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();

	//显示消息框和标题栏
	afx_msg LRESULT OnAfxMessageBox(WPARAM wParam, LPARAM lParam);


	DECLARE_MESSAGE_MAP()

private:
	//create dock windows
	BOOL fnCreateDockWindows();

};
