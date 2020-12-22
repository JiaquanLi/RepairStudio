// ImageButton.cpp : implementation file
//

#include "stdafx.h"
#include "XImageButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// 비트맵 파일로부터 CBitmap 객체를 생성하는 함수
BOOL XImageButton::LoadBMPImage( LPCTSTR sBMPFile, CBitmap& bitmap, CPalette *pPal )
{
	CFile file;
	if( !file.Open( sBMPFile, CFile::modeRead) )
		return FALSE;

	if( bitmap.GetSafeHandle() != NULL )
		bitmap.DeleteObject();

	BITMAPFILEHEADER bmfHeader;

	// Read file header
	if (file.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) != sizeof(bmfHeader))
		return FALSE;

	// File type should be 'BM'
	if (bmfHeader.bfType != ((WORD) ('M' << 8) | 'B'))
		return FALSE;

	// Get length of the remainder of the file and allocate memory
	DWORD nPackedDIBLen = (DWORD)(file.GetLength() - sizeof(BITMAPFILEHEADER));
	HGLOBAL hDIB = ::GlobalAlloc(GMEM_FIXED, nPackedDIBLen);
	if (hDIB == 0)
		return FALSE;

	// Read the remainder of the bitmap file.
	if (file.Read((LPSTR)hDIB, nPackedDIBLen) != nPackedDIBLen )
	{
		::GlobalFree(hDIB);
		return FALSE;
	}

	BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)hDIB ;
	BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ;

	// If bmiHeader.biClrUsed is zero we have to infer the number
	// of colors from the number of bits used to specify it.
	int nColors = bmiHeader.biClrUsed ? bmiHeader.biClrUsed : 
										   1 << bmiHeader.biBitCount;

	LPVOID lpDIBBits;
	if( bmInfo.bmiHeader.biBitCount > 8 )
		lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors + bmInfo.bmiHeader.biClrUsed) + 
				   ((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
	else
		lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors);

	// Create the logical palette
	if( pPal != NULL )
	{
		// Create the palette
		if( nColors <= 256 )
		{
			UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
			LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];

			pLP->palVersion = 0x300;
			pLP->palNumEntries = nColors;

			for( int i=0; i < nColors; i++)
			{
				pLP->palPalEntry[i].peRed = bmInfo.bmiColors[i].rgbRed;
				pLP->palPalEntry[i].peGreen = bmInfo.bmiColors[i].rgbGreen;
				pLP->palPalEntry[i].peBlue = bmInfo.bmiColors[i].rgbBlue;
				pLP->palPalEntry[i].peFlags = 0;
			}

			pPal->CreatePalette( pLP );

			delete[] pLP;
		}
	}

	CClientDC dc(NULL);
	CPalette* pOldPalette = NULL;
	if( pPal )
	{
		pOldPalette = dc.SelectPalette( pPal, FALSE );
		dc.RealizePalette();
	}

	HBITMAP hBmp = CreateDIBitmap( dc.m_hDC,                // handle to device context 
						&bmiHeader,     // pointer to bitmap size and format data 
						CBM_INIT,       // initialization flag 
						lpDIBBits,      // pointer to initialization data 
						&bmInfo,        // pointer to bitmap color-format data 
						DIB_RGB_COLORS);                // color-data usage 
	bitmap.Attach( hBmp );

	if( pOldPalette )
		   dc.SelectPalette( pOldPalette, FALSE );

	::GlobalFree(hDIB);
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// XImageButton

XImageButton::XImageButton()
{
	m_bMouseCaptured = FALSE;
	m_nWidth = 0;
	m_nHeight = 0;
	m_bCheck = FALSE;
	m_bDrawText = FALSE;
	m_strText = _T("");
	m_bCanFocus = FALSE;

	// No tooltip created
	m_ToolTip.m_hWnd = NULL;
}

XImageButton::~XImageButton()
{
}


BEGIN_MESSAGE_MAP(XImageButton, CButton)
	//{{AFX_MSG_MAP(XImageButton)
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// XImageButton message handlers

BOOL XImageButton::LoadBitmaps(UINT nIDBitmapResource)
{
	m_bitmap.DeleteObject();

	if( !m_bitmap.LoadBitmap(nIDBitmapResource) )
	{
		TRACE0("Failed to load bitmap for normal image.\n");
		return FALSE;   // need this one image
	}

	// Member variable setting
	BITMAP bm;
	m_bitmap.GetBitmap( &bm );
	ASSERT(bm.bmWidth%4 == 0);
	m_nWidth = (int)(bm.bmWidth / 4);
	m_nHeight = bm.bmHeight;

	return TRUE;
}

BOOL XImageButton::LoadBitmaps(HBITMAP hBitmap)
{
	m_bitmap.DeleteObject();
	
	if(!m_bitmap.Attach(hBitmap))
	{
		TRACE0("Failed to load bitmap for normal image.\n");
		return FALSE;   // need this one image
	}

	// Member variable setting
	BITMAP bm;
	m_bitmap.GetBitmap( &bm );
	ASSERT(bm.bmWidth%4 == 0);
	m_nWidth = (int)(bm.bmWidth / 4);
	m_nHeight = bm.bmHeight;

	return TRUE;
}

BOOL XImageButton::LoadBitmapFile(CString strPath)
{
	CFileFind find;
	if( !find.FindFile( strPath ) )
	{
		return FALSE;
	}

	m_bitmap.DeleteObject();
	if(!LoadBMPImage( strPath, m_bitmap ) )
	{
		TRACE0("Failed to load bitmap for normal image.\n");
		return FALSE;   // need this one image
	}

	// Member variable setting
	BITMAP bm;
	m_bitmap.GetBitmap( &bm );
	ASSERT(bm.bmWidth%4 == 0);
	m_nWidth = (int)(bm.bmWidth / 4);
	m_nHeight = bm.bmHeight;

	return TRUE;
}

BOOL XImageButton::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= WM_PARENTNOTIFY ;

	return CButton::PreCreateWindow(cs);
}

BOOL XImageButton::PreTranslateMessage(MSG* pMsg) 
{
	CWnd *pParent = (CWnd*)GetParent();

	InitToolTip();
	m_ToolTip.RelayEvent(pMsg);
	
	return CButton::PreTranslateMessage(pMsg);
}

void XImageButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( !m_bMouseCaptured || GetCapture() != this )
	{
		SetCapture();
		m_bMouseCaptured = TRUE;
		OnMouseEnter(nFlags, point);
	}
	else
	{
		CRect rect;
		GetClientRect( &rect );

		if( !rect.PtInRect(point) )
		{
			ReleaseCapture();
			m_bMouseCaptured = FALSE;
			OnMouseExit(nFlags, point);
		}
	}
	
	CButton::OnMouseMove(nFlags, point);
}

void XImageButton::OnMouseEnter(UINT nFlags, CPoint point)
{
	// To save a time
	//Invalidate(FALSE);
	//UpdateWindow();
}

void XImageButton::OnMouseExit(UINT nFlags, CPoint point)
{
	Invalidate(FALSE);
	UpdateWindow();
}

// SizeToContent will resize the button to the size of the bitmap
void XImageButton::SizeToContent()
{
	ASSERT(m_bitmap.m_hObject != NULL);
	ASSERT(m_nWidth != 0);
	ASSERT(m_nHeight != 0);
	VERIFY(SetWindowPos(NULL, -1, -1, m_nWidth, m_nHeight,
			SWP_NOMOVE|SWP_NOZORDER|SWP_NOREDRAW|SWP_NOACTIVATE));
}

void XImageButton::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	ASSERT(lpDIS != NULL);
	// must have at least the first bitmap loaded before calling DrawItem
	ASSERT(m_bitmap.m_hObject != NULL);     // required

	if(lpDIS->hDC == NULL) {
		AfxMessageBox(_T("kkkkk Bottom Bar Error"));
	}


	CDC* pDC = CDC::FromHandle( lpDIS->hDC );
	CDC memDC;
	if(!memDC.CreateCompatibleDC( pDC )) {
		AfxMessageBox(_T("Error"));
		return;
	}
	CBitmap* pOld = memDC.SelectObject( &m_bitmap );
	if( pOld == NULL )
		return;     // destructors will clean up

	CRect rect;
	rect.CopyRect(&lpDIS->rcItem);

	UINT state = lpDIS->itemState;

	if (m_bCheck)
	{
		pDC->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(),
			&memDC, m_nWidth*2, 0, m_nWidth, m_nHeight, SRCCOPY);
	}

	else
	{
		if( !m_bMouseCaptured )
		{
			pDC->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(),
				&memDC, 0, 0, m_nWidth, m_nHeight, SRCCOPY);
		}

		if( m_bMouseCaptured )
		{
			if(m_bCanFocus)
			{
				pDC->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(),
					&memDC, m_nWidth, 0, m_nWidth, m_nHeight, SRCCOPY);
			}
		}

		if ( state & ODS_SELECTED )
		{
			pDC->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(),
				&memDC, m_nWidth*2, 0, m_nWidth, m_nHeight, SRCCOPY);
		}

		if ( state & ODS_DISABLED )
		{
			pDC->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(),
				&memDC, m_nWidth*3, 0, m_nWidth, m_nHeight, SRCCOPY);
		}
	}

	if(m_bDrawText)
	{
		HFONT Font, oldFont;

		if(!m_Property.bBold)
			Font = CreateFont(m_Property.nFontSize, 0, 0, 0, 0, 0, 0, 0,
							  DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,
							  DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, m_Property.strFont);

		else
			Font = CreateFont(m_Property.nFontSize, 0, 0, 0, FW_BOLD, 0, 0, 0,
							  DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,
							  DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, m_Property.strFont);

		oldFont = (HFONT)pDC->SelectObject(Font);	
		pDC->SetBkMode(TRANSPARENT);

		CRect shadowRect(rect);
		shadowRect.OffsetRect(1, 1);

		if(m_Property.b3D)
		{
			pDC->SetTextColor(m_Property.colShadowText);
			pDC->DrawText(m_strText, m_strText.GetLength(), shadowRect, m_Property.dwTextType);
		}

		pDC->SetTextColor(m_Property.colText);
		pDC->DrawText(m_strText, m_strText.GetLength(), rect, m_Property.dwTextType);

		pDC->SelectObject(oldFont);
		DeleteObject(Font);
	}

	// draw the whole button
	memDC.SelectObject(pOld);
}

BOOL XImageButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	HCURSOR hCursor;

	CString strWndDir;
	GetWindowsDirectory(strWndDir.GetBuffer(MAX_PATH), MAX_PATH);
	strWndDir.ReleaseBuffer();

	strWndDir += _T("\\winhlp32.exe");
	// This retrieves cursor #106 from winhlp32.exe, which is a hand pointer
	HMODULE hModule = LoadLibrary(strWndDir);
	if(hModule) 
	{
		HCURSOR hHandCursor = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
		if(hHandCursor) hCursor = CopyCursor(hHandCursor);
		::SetCursor(hCursor);
	}
	
	FreeLibrary(hModule);

	return TRUE;
}

void XImageButton::OnSetFocus(CWnd* pOldWnd) 
{
	CButton::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
}

void XImageButton::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	m_bMouseCaptured = FALSE;
}

void XImageButton::InitToolTip()
{
	if (m_ToolTip.m_hWnd == NULL)
	{
		// Create ToolTip control
		m_ToolTip.Create(this);
		// Create inactive
		m_ToolTip.Activate(FALSE);
	}
} // End of InitToolTip

void XImageButton::SetTooltipText(CString* spText, BOOL bActivate)
{
	// We cannot accept NULL pointer
	if (spText == NULL) return;

	// Initialize ToolTip
	InitToolTip();

	// If there is no tooltip defined then add it
	if (m_ToolTip.GetToolCount() == 0)
	{
		CRect rectBtn; 
		GetClientRect(rectBtn);
		m_ToolTip.AddTool(this, (LPCTSTR)*spText, rectBtn, 1);
	}

	// Set text for tooltip
	m_ToolTip.UpdateTipText((LPCTSTR)*spText, this, 1);
	m_ToolTip.Activate(bActivate);
} // End of SetTooltipText

void XImageButton::SetTooltipText(int nId, BOOL bActivate)
{
	CString sText;

	// load string resource
	sText.LoadString(nId);
	// If string resource is not empty
	if (sText.IsEmpty() == FALSE) SetTooltipText(&sText, bActivate);
} // End of SetTooltipText


void XImageButton::ActivateTooltip(BOOL bActivate)
{
	// If there is no tooltip then do nothing
	if (m_ToolTip.GetToolCount() == 0) return;

	// Activate tooltip
	m_ToolTip.Activate(bActivate);
} // End of EnableTooltip


int XImageButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;

	InitToolTip();
	
	return 0;
}

void XImageButton::SetCheck(BOOL bCheck)
{
	if(!IsWindowEnabled())
		m_bMouseCaptured = FALSE;

	m_bCheck = bCheck;

	Invalidate(FALSE);
	UpdateWindow();
}

BOOL XImageButton::GetCheck()
{
	return m_bCheck;
}

void XImageButton::SetDrawText(BOOL bText)
{
	m_bDrawText = bText;

	Invalidate(FALSE);
	UpdateWindow();
}

BOOL XImageButton::GetDrawText()
{
	return m_bDrawText;
}

void XImageButton::SetText(CString strText)
{
	m_strText = strText;

	Invalidate(FALSE);
	UpdateWindow();
}

CString XImageButton::GetText()
{
	return m_strText;
}
	
void XImageButton::SetCanFocus(BOOL bFocus)
{
	m_bCanFocus = bFocus;
}

BOOL XImageButton::GetCanFocus()
{
	return m_bCanFocus;
}

void XImageButton::SetStaticProperty(_STATIC_PROPERTY *pProperty)
{
	m_Property = *pProperty;
}

_STATIC_PROPERTY* XImageButton::GetStaticPorperty()
{
	return (_STATIC_PROPERTY*)&m_Property;
}


void XImageButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd *pParent = (CWnd*)GetParent();
	if(pParent)
	{
		MSG msg;
		msg.hwnd = pParent->GetSafeHwnd();
		msg.message = WM_LBUTTONDOWN;
		msg.wParam = nFlags;
		msg.lParam = GetDlgCtrlID();
		msg.pt = point;

		pParent->SendMessage(WM_NOTIFY, pParent->GetDlgCtrlID(), (LPARAM)&msg);
	}

	CButton::OnLButtonDown(nFlags, point);
}

void XImageButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd *pParent = (CWnd*)GetParent();
	if(pParent)
	{
		MSG msg;
		msg.hwnd = pParent->GetSafeHwnd();
		msg.message = WM_LBUTTONUP;
		msg.wParam = nFlags;
		msg.lParam = GetDlgCtrlID();
		msg.pt = point;

		pParent->SendMessage(WM_NOTIFY, pParent->GetDlgCtrlID(), (LPARAM)&msg);
	}

	CButton::OnLButtonUp(nFlags, point);
}
