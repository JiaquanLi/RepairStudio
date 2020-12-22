// RepairStudioView.cpp : implementation of the CRepairStudioView class
//

#include "stdafx.h"
#include "RepairStudio.h"

#include "RepairStudioDoc.h"
#include "RepairStudioView.h"
using namespace Gdiplus;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRepairStudioView

IMPLEMENT_DYNCREATE(CRepairStudioView, CBCGPFormView)

BEGIN_MESSAGE_MAP(CRepairStudioView, CBCGPFormView)
	ON_WM_CONTEXTMENU()
	ON_REGISTERED_MESSAGE(BCGM_CHANGEVISUALMANAGER, OnChangeVisualManager)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CRepairStudioView construction/destruction

CRepairStudioView::CRepairStudioView()
	: CBCGPFormView(CRepairStudioView::IDD)
{
	EnableVisualManagerStyle();
	m_pBmpInfo = new BITMAPINFO[sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD)];
	m_pByteData = new BYTE[REVIEW_PIXEL_COUNT_X_CAM*REVIEW_PIXEL_COUNT_Y_CAM * 3];
	memset(m_pByteData, 0x0, sizeof(BYTE)*REVIEW_PIXEL_COUNT_X_CAM*REVIEW_PIXEL_COUNT_Y_CAM*3);
	fnInitBitmapInfo();
}

CRepairStudioView::~CRepairStudioView()
{
}

void CRepairStudioView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
}

BOOL CRepairStudioView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CBCGPFormView::PreCreateWindow(cs);
}

void CRepairStudioView::OnInitialUpdate()
{
	CBCGPFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();

	//delete dialog frame
	ModifyStyleEx(WS_EX_CLIENTEDGE, NULL, SWP_DRAWFRAME);

	//set color and font
	fnSetFontAndColor();

	fnInitDialog();
}


// CRepairStudioView diagnostics

#ifdef _DEBUG
void CRepairStudioView::AssertValid() const
{
	CBCGPFormView::AssertValid();
}

void CRepairStudioView::Dump(CDumpContext& dc) const
{
	CBCGPFormView::Dump(dc);
}

CRepairStudioDoc* CRepairStudioView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRepairStudioDoc)));
	return (CRepairStudioDoc*)m_pDocument;
}
#endif //_DEBUG


// CRepairStudioView message handlers
LRESULT CRepairStudioView::OnChangeVisualManager(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	return 0;
}

void CRepairStudioView::fnInitDialog()
{
	//Link Type Mil board Camera
	m_Camera.Initialize_Solios(0, REVIEW_PIXEL_COUNT_X_CAM, REVIEW_PIXEL_COUNT_Y_CAM, 3, PATH_MIL_REVIEW_DCF);
	m_Camera.fnSetBayer(M_BAYER_RG);
	//m_Camera.fnSetSeqRun();
}

void CRepairStudioView::OnContextMenu(CWnd*, CPoint point)
{
	if (CBCGPPopupMenu::GetSafeActivePopupMenu() != NULL)
	{
		return;
	}

	theApp.ShowPopupMenu(IDR_CONTEXT_MENU, point, this);
}

//���ÿؼ�����
void CRepairStudioView::fnSetFontAndColor()
{
	//��ť������
	m_Font.CreatePointFont(120, "����", NULL);

	//���н���ؼ�IDѭ����ȡ��Ȼ��ֱ���и�ֵ������static�����������
	HWND subWnd = ::GetWindow(GetSafeHwnd(), GW_CHILD);
	while (subWnd)
	{
		CWnd *subCWnd = CWnd::FromHandle(subWnd);
		int  nCtrlID = subCWnd->GetDlgCtrlID();
		if (0 < nCtrlID)
		{
			//����Static����
			GetDlgItem(nCtrlID)->SetFont(&m_Font);
		}
		subWnd = ::GetWindow(subWnd, GW_HWNDNEXT);
	}
}


void CRepairStudioView::OnDraw(CDC* pDC)
{
	// TODO: �ڴ����ר�ô����/����û���
	CDC			memDCGrab;
	CBitmap		cBitmap;
	HBITMAP		hOldBitmap;

	memDCGrab.CreateCompatibleDC(pDC);
	memDCGrab.SetMapMode(pDC->GetMapMode());

	cBitmap.CreateCompatibleBitmap(pDC, REVIEW_PIXEL_COUNT_X_CAM, REVIEW_PIXEL_COUNT_Y_CAM);

	hOldBitmap = (HBITMAP)SelectObject(memDCGrab.m_hDC, cBitmap.m_hObject);

	::SetStretchBltMode(memDCGrab.m_hDC, COLORONCOLOR);
	double dScal = REVIEW_PIXEL_COUNT_Y_CAM / (double)REVIEW_PIXEL_COUNT_X_CAM;
	StretchDIBits(memDCGrab.m_hDC,
		0,
		0,
		REVIEW_PIXEL_COUNT_X_CAM,
		REVIEW_PIXEL_COUNT_Y_CAM,
		0,
		0,
		REVIEW_PIXEL_COUNT_X_CAM,
		REVIEW_PIXEL_COUNT_Y_CAM,
		m_pByteData,
		m_pBmpInfo,
		DIB_RGB_COLORS, SRCCOPY);

	Graphics* MemGraphic = Graphics::FromHDC(memDCGrab.m_hDC);


	pDC->BitBlt(0, 0, m_uiPixel_Monitor_X, m_uiPixel_Monitor_Y, &memDCGrab, 0, 0, SRCCOPY);

	delete MemGraphic;

	memDCGrab.SelectObject(hOldBitmap);

	cBitmap.DeleteObject();
	memDCGrab.DeleteDC();
}

void CRepairStudioView::fnInitBitmapInfo()
{
	for (int i = 0; i < 256; i++)
	{
		m_pBmpInfo->bmiColors[i].rgbRed = m_pBmpInfo->bmiColors[i].rgbGreen = m_pBmpInfo->bmiColors[i].rgbBlue = i;
		m_pBmpInfo->bmiColors[i].rgbReserved = 0;
	}

	m_pBmpInfo->bmiHeader.biBitCount = 24;
	m_pBmpInfo->bmiHeader.biWidth = m_uiPixel_CAM_X;
	m_pBmpInfo->bmiHeader.biHeight = m_uiPixel_CAM_Y;
	m_pBmpInfo->bmiHeader.biSizeImage = m_uiPixel_CAM_X * m_uiPixel_CAM_Y * 24;

	m_pBmpInfo->bmiHeader.biClrUsed = 0;
	m_pBmpInfo->bmiHeader.biClrImportant = 0;
	m_pBmpInfo->bmiHeader.biCompression = BI_RGB;
	m_pBmpInfo->bmiHeader.biPlanes = 1;
	m_pBmpInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBmpInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBmpInfo->bmiHeader.biYPelsPerMeter = 0;
}


void CRepairStudioView::OnSize(UINT nType, int cx, int cy)
{
	CBCGPFormView::OnSize(nType, cx, cy);

	m_uiPixel_Monitor_X = cx;
	m_uiPixel_Monitor_Y = cy;
	// TODO: �ڴ˴������Ϣ����������
}
