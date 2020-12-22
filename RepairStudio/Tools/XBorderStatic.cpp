// BorderStatic.cpp : implementation file
//

#include "stdafx.h"
#include "XBorderStatic.h"
//#include "MemDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// XBorderStatic
/////////////////////////////////////////////////////////////////////////////
// XBorderStatic

XBorderStatic::XBorderStatic()
{
	m_strText = "\0";
	m_nImageIndex = -1;
}

XBorderStatic::~XBorderStatic()
{
	if(m_ImageList.GetSafeHandle())
		m_ImageList.DeleteImageList();
}


BEGIN_MESSAGE_MAP(XBorderStatic, CStatic)
	//{{AFX_MSG_MAP(XBorderStatic)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// XBorderStatic message handlers

int XBorderStatic::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	GetWindowText(m_strText);

	return 0;
}

void XBorderStatic::SetImageList(UINT nID)
{
	CBitmap resoureBitmap;
	CImageList *pImageList = new CImageList;
	pImageList->Create(16, 18, ILC_COLOR8 | ILC_MASK, 20, 10);

	resoureBitmap.LoadBitmap(nID);

	pImageList->Add(&resoureBitmap, RGB(255, 0, 255));
	m_ImageList.Create(pImageList);

	delete pImageList;
}

void XBorderStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rect, textRect, textShadowRect;
	GetClientRect(&rect);

	dc.FillRect(rect, &CBrush(m_Property.colBack));
	
	if(m_Property.bFrame)
		dc.FrameRect(rect, &CBrush(m_Property.colBorder));

	HFONT Font, oldFont;

	if(!m_Property.bBold)
		Font = CreateFont(m_Property.nFontSize, 0, 0, 0, 0, 0, 0, 0,
						  DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,
						  DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, m_Property.strFont);

	else
		Font = CreateFont(m_Property.nFontSize, 0, 0, 0, FW_BOLD, 0, 0, 0,
						  DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,
						  DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, m_Property.strFont);

	oldFont = (HFONT)dc.SelectObject(Font);	
	dc.SetBkMode(TRANSPARENT);

	CDC cdc;	
	CSize size;

	cdc.SetOutputDC(dc.m_hDC);
	size = cdc.GetOutputTextExtent(m_strText); 

	rect.DeflateRect(4, 2);

	if(m_ImageList.GetSafeHandle() && m_ImageList.GetImageCount() && m_nImageIndex != -1)
	{
		if(size.cx <= rect.Width())
		{
			m_ImageList.Draw(&dc, m_nImageIndex, CPoint(rect.left, rect.top + 5), ILD_NORMAL);
			
			textRect = rect;
			textRect.DeflateRect(16, 0, 0, 0);

			dc.SetTextColor(m_Property.colText);
			dc.DrawText(m_strText, m_strText.GetLength(), textRect, m_Property.dwTextType);
		}

		else
		{
			m_ImageList.Draw(&dc, m_nImageIndex, CPoint(rect.left, rect.top), ILD_NORMAL);
			
			textRect = rect;
			textRect.DeflateRect(16, 0, 0, 0);

			dc.SetTextColor(m_Property.colText);
			dc.DrawText(m_strText, m_strText.GetLength(), textRect, m_Property.dwTextType);
		}
	}

	else
	{
		textRect = rect;
		textShadowRect = textRect;
		textShadowRect.OffsetRect(1, 1);

		if(size.cx > rect.Width())
			m_Property.dwTextType |= DT_END_ELLIPSIS;

		if(m_Property.b3D)
		{
			dc.SetTextColor(m_Property.colShadowText);
			dc.DrawText(m_strText, m_strText.GetLength(), textShadowRect, m_Property.dwTextType);
		}

		dc.SetTextColor(m_Property.colText);
		dc.DrawText(m_strText, m_strText.GetLength(), rect, m_Property.dwTextType);
	}

	cdc.ReleaseOutputDC();

	dc.SelectObject(oldFont);
	DeleteObject(Font);

	// Do not call CStatic::OnPaint() for painting messages
}

BOOL XBorderStatic::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

void XBorderStatic::OnDestroy() 
{
	CStatic::OnDestroy();
	
	// TODO: Add your message handler code here	
}

void XBorderStatic::SetTextColor(COLORREF colText)
{
	m_Property.colText = colText;

	Invalidate(FALSE);
}

void XBorderStatic::SetBackColor(COLORREF colBack)
{
	m_Property.colBack = colBack;

	Invalidate(FALSE);
}

void XBorderStatic::SetBorderColor(COLORREF colBorder)
{
	m_Property.colBorder = colBorder;

	Invalidate(FALSE);
}

void XBorderStatic::SetFont(CString strFont)
{
	m_Property.strFont = strFont;

	Invalidate(FALSE);
}

void XBorderStatic::SetFontSize(int nSize)
{
	m_Property.nFontSize = nSize;

	Invalidate(FALSE);
}

void XBorderStatic::SetFrame(BOOL bFrame)
{
	m_Property.bFrame = bFrame;

	Invalidate(FALSE);
}

void XBorderStatic::SetBold(BOOL bBold)
{
	m_Property.bBold = bBold;

	Invalidate(FALSE);
}

void XBorderStatic::SetTextType(DWORD dwType)
{
	m_Property.dwTextType = dwType;

	Invalidate(FALSE);
}

void XBorderStatic::SetText(CString strText, int nImageIndex)
{
	m_strText = strText;
	m_nImageIndex = nImageIndex;

	Invalidate(FALSE);
}

void XBorderStatic::SetStaticProperty(_STATIC_PROPERTY *pProperty)
{
	m_Property = *pProperty;
}

_STATIC_PROPERTY* XBorderStatic::GetStaticPorperty()
{
	return (_STATIC_PROPERTY*)&m_Property;
}