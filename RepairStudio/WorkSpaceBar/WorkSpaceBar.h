// workspacebar.h : interface of the CWorkSpaceBar class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../Dialog/DlgDockMenu.h"

class CWorkSpaceBar : public CBCGPDockingControlBar
{
public:
	CWorkSpaceBar();

// Attributes
protected:
	CDlgDockMenu *m_pDockMenu;

// Operations
public:

// Overrides

// Implementation
public:
	virtual ~CWorkSpaceBar();

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
