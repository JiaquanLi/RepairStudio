// RepairStudioView.h : interface of the CRepairStudioView class
//


#pragma once
#include "Common/Include.h"

class CRepairStudioView : public CBCGPFormView
{
protected: // create from serialization only
	CRepairStudioView();
	DECLARE_DYNCREATE(CRepairStudioView)

public:
	enum{ IDD = IDD_REPAIRSTUDIO_FORM };

// Attributes
public:
	CRepairStudioDoc* GetDocument() const;

// Operations
public:
	CCamera m_Camera;

// Overrides
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CRepairStudioView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void fnInitDialog();
// Generated message map functions
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg void OnFilePrintPreview();
	afx_msg LRESULT OnChangeVisualManager(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	CFont m_Font;
	UINT m_uiPixel_CAM_X;
	UINT m_uiPixel_CAM_Y;
	UINT m_uiPixel_Monitor_X;
	UINT m_uiPixel_Monitor_Y;
	BYTE * m_pByteData;
	BITMAPINFO		*m_pBmpInfo;

private:
	//设置控件字体和颜色
	void fnSetFontAndColor();


	virtual void OnDraw(CDC* /*pDC*/);
	void fnInitBitmapInfo();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // debug version in RepairStudioView.cpp
inline CRepairStudioDoc* CRepairStudioView::GetDocument() const
   { return reinterpret_cast<CRepairStudioDoc*>(m_pDocument); }
#endif

