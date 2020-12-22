#if !defined(AFX_IMAGEBUTTON_H__869AAB88_789F_11D3_AA96_006097AD7A5B__INCLUDED_)
#define AFX_IMAGEBUTTON_H__869AAB88_789F_11D3_AA96_006097AD7A5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageButton.h : header file
//

typedef struct _tagStaticPorperty
{
	_tagStaticPorperty()
	{
		colBack = GetSysColor(COLOR_BTNFACE);
		colText = GetSysColor(COLOR_BTNTEXT);
		colShadowText = GetSysColor(COLOR_BTNTEXT);
		colBorder = GetSysColor(COLOR_BTNTEXT);

		strFont = "±¼¸²";
		nFontSize = 14;
		bFrame = FALSE;
		bBold = FALSE;
		dwTextType = DT_LEFT | DT_VCENTER | DT_SINGLELINE;
		b3D = FALSE;
	};

	COLORREF	colBack;
	COLORREF	colText;
	COLORREF	colShadowText;
	COLORREF	colBorder;

	CString		strFont;
	int			nFontSize;
	BOOL		bFrame;
	BOOL		bBold;
	DWORD		dwTextType;
	BOOL		b3D;

} _STATIC_PROPERTY, *_LPSTATIC_PROPERTY;

/////////////////////////////////////////////////////////////////////////////
// XImageButton window

class XImageButton : public CButton
{
// Construction
public:
	XImageButton();
	virtual ~XImageButton();

// Attributes
public:
	// ¸â¹ö ÇÔ¼ö
	BOOL LoadBitmaps(UINT nIDBitmapResource);
	BOOL LoadBitmaps(HBITMAP hBitmap);
	BOOL LoadBitmapFile(CString strPath);

	virtual void SizeToContent();
	virtual void OnMouseExit(UINT nFlags, CPoint point);
	virtual void OnMouseEnter(UINT nFlags, CPoint point);

	void InitToolTip();
	void SetTooltipText(CString* spText, BOOL bActivate = TRUE);
	void SetTooltipText(int nId, BOOL bActivate = TRUE);
	void ActivateTooltip(BOOL bEnable = TRUE);

	BOOL LoadBMPImage( LPCTSTR sBMPFile, CBitmap& bitmap, CPalette *pPal = NULL );
	
	void SetCheck(BOOL bCheck = TRUE);
	BOOL GetCheck();

	void SetDrawText(BOOL bText = FALSE);
	BOOL GetDrawText();

	void	SetText(CString strText);
	CString	GetText();

	void	SetCanFocus(BOOL bFocus);
	BOOL	GetCanFocus();

	void SetStaticProperty(_STATIC_PROPERTY *pProperty);
	_STATIC_PROPERTY* GetStaticPorperty();

// Operations
protected:
	// ¸â¹ö º¯¼ö
	int			m_nHeight;
	int			m_nWidth;
	BOOL		m_bMouseCaptured;
	CBitmap		m_bitmap;
	CToolTipCtrl m_ToolTip;
	BOOL		m_bCheck;
	BOOL		m_bDrawText;
	BOOL		m_bCanFocus;

	CString		m_strText;

	_STATIC_PROPERTY	m_Property;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(XImageButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation

	// Generated message map functions
protected:
	//{{AFX_MSG(XImageButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEBUTTON_H__869AAB88_789F_11D3_AA96_006097AD7A5B__INCLUDED_)
