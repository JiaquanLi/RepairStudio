#if !defined(AFX_BORDERSTATIC_H__2E6B8BAE_D25F_4527_B765_C78594099F25__INCLUDED_)
#define AFX_BORDERSTATIC_H__2E6B8BAE_D25F_4527_B765_C78594099F25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BorderStatic.h : header file
//

#include "XImageButton.h"

/////////////////////////////////////////////////////////////////////////////
// XBorderStatic window

class XBorderStatic : public CStatic
{
// Construction
public:
	XBorderStatic();

// Attributes
public:

// Operations
public:

protected:
	_STATIC_PROPERTY	m_Property;

	CString				m_strText;
	CImageList			m_ImageList;
	int					m_nImageIndex;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(XBorderStatic)
	//}}AFX_VIRTUAL

public:
	void SetTextColor(COLORREF colText);
	void SetBackColor(COLORREF colBack);
	void SetBorderColor(COLORREF colBorder);
	void SetFont(CString strFont);
	void SetFontSize(int nSize);
	void SetFrame(BOOL bFrame);
	void SetBold(BOOL bBold);
	void SetTextType(DWORD dwType);
	void SetText(CString strText, int nImageIndex = 0);
	void SetImageList(UINT nID);

	void SetStaticProperty(_STATIC_PROPERTY *pProperty);
	_STATIC_PROPERTY* GetStaticPorperty();

// Implementation
public:
	virtual ~XBorderStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(XBorderStatic)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BORDERSTATIC_H__2E6B8BAE_D25F_4527_B765_C78594099F25__INCLUDED_)
