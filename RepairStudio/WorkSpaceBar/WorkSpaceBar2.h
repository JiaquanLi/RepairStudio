// workspace2.h : interface of the CWorkSpaceBar2 class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../Dialog/DlgMain.h"
#include "../Dialog/DlgManual.h"
#include "../Dialog/DlgProcess.h"

class CWorkSpaceBar2 : public CBCGPDockingControlBar
{
public:
	CWorkSpaceBar2();

// Attributes
protected:
	CBCGPTabWnd	m_wndTabs;
	CDlgMain *m_pDlgMain;
	CDlgManual *m_pDlgManual;
	CDlgProcess *m_pDlgProcess;

// Operations
public:

// Overrides

// Implementation
public:
	virtual ~CWorkSpaceBar2();

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL CanBeClosed() const { return FALSE; }
	virtual BOOL CanBeResized() const { return FALSE; }
	virtual BOOL IsResizable()  const { return FALSE; }
	virtual BOOL IsHorizontal() const { return FALSE; }
	virtual BOOL CanFloat() const { return FALSE; }
	virtual int GetCaptionHeight() const { return 0; }
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
