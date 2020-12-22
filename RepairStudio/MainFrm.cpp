// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "RepairStudio.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CBCGPFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CBCGPFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_AFXMESSAGEBOX, OnAfxMessageBox)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

//create dock windows
BOOL CMainFrame::fnCreateDockWindows()
{
	// Load control bar icons:
	CBCGPToolBarImages imagesWorkspace;
	imagesWorkspace.SetImageSize(CSize(16, 16));
	imagesWorkspace.Load(IDB_WORKSPACE);
	globalUtils.ScaleByDPI(imagesWorkspace);
	const int nPaneSize1 = globalUtils.ScaleByDPI(80);
	const int nPaneSize2 = globalUtils.ScaleByDPI(600);
	const int nOutputPaneSize = globalUtils.ScaleByDPI(150);

	//create right dock menu
	if (!m_wndWorkSpace.Create(_T(""), this, CRect(0, 0, nPaneSize1, nPaneSize1),
		TRUE, ID_VIEW_WORKSPACE,WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create right dock window\n");
		return FALSE;   
	}

	//show work space
	m_wndWorkSpace.EnableDocking(CBRS_ALIGN_RIGHT);

	//create left dock menu
	if (!m_wndWorkSpace2.Create(_T("Main"), this, CRect(0, 0, nPaneSize2, nPaneSize2),
		TRUE, ID_VIEW_WORKSPACE2, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create left dock window\n");
		return FALSE;     
	}

	//show work space
	m_wndWorkSpace2.EnableDocking(CBRS_ALIGN_LEFT);

	//create defect/output dock window
	if (!m_wndOutput.Create(_T("---Defect List---"), this, CSize(nOutputPaneSize, nOutputPaneSize),
		TRUE, ID_VIEW_OUTPUT, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM))
	{
		TRACE0("Failed to create defect/output bar\n");
		return FALSE;      // fail to create
	}

	//输出的output部分显示
	//m_wndOutput.SetIcon(imagesWorkspace.ExtractIcon(2), FALSE);
	m_wndOutput.EnableDocking(CBRS_ALIGN_BOTTOM);

	//定义停靠属性
	EnableDocking(CBRS_ALIGN_ANY);
	EnableAutoHideBars(CBRS_ALIGN_ANY);

	//bar的dock属性
	DockControlBar(&m_wndWorkSpace);
	DockControlBar(&m_wndWorkSpace2);
	DockControlBar(&m_wndOutput);

	return TRUE;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (-1 == CBCGPFrameWnd::OnCreate(lpCreateStruct))
	{
		return -1;
	}
	
	if (!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)))		
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Load dock windows
	if (!fnCreateDockWindows())
	{
		fnMessageBox("create dock windows failed");
		return -1;
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CBCGPFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	
	cs.hMenu = NULL;

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CBCGPFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CBCGPFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnClose()
{
	CBCGPFrameWnd::OnClose();
}


LRESULT CMainFrame::OnAfxMessageBox(WPARAM wParam, LPARAM lParam)
{
	//消息内容
	CString *pMsg = (CString *)wParam;

	//显示消息框
	fnMessageBox(*pMsg);

	//释放参数
	delete pMsg;

	return 1;
}

