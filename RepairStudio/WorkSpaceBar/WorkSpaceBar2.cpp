// workspace2.cpp : implementation of the CWorkSpaceBar2 class
//

#include "stdafx.h"
#include "../RepairStudio.h"
#include "WorkSpaceBar2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar2

BEGIN_MESSAGE_MAP(CWorkSpaceBar2, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar2 construction/destruction

CWorkSpaceBar2::CWorkSpaceBar2()
{
	//create dialog
	m_pDlgMain = new CDlgMain;
	m_pDlgManual = new CDlgManual;
	m_pDlgProcess = new CDlgProcess;
}

CWorkSpaceBar2::~CWorkSpaceBar2()
{
}

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar2 message handlers

int CWorkSpaceBar2::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create tabs window:
	if (!m_wndTabs.Create(CBCGPTabWnd::STYLE_3D, rectDummy, this, 1))
	{
		TRACE0("Failed to create workspace tab window\n");
		return -1;      // fail to create
	}

	m_wndTabs.SetImageAutoScale();
	m_wndTabs.SetImageList(IDB_WORKSPACE, 16, RGB(255, 0, 255));

	if (!m_pDlgManual->Create(IDD_DIALOG_MANUAL, &m_wndTabs))
	{
		TRACE0("Failed to create Manual view\n");
		return -1;
	}

	// Create Ö÷½çÃæ
	if (!m_pDlgMain->Create(IDD_DIALOG_MAIN, &m_wndTabs))
	{
		TRACE0("Failed to create Main view\n");
		return -1;
	}

	if (!m_pDlgProcess->Create(IDD_DIALOG_PROCESS, &m_wndTabs))
	{
		TRACE0("Failed to create Process view\n");
		return -1;
	}

	m_wndTabs.AddTab(m_pDlgMain, _T("Main"), 0 );
	m_wndTabs.AddTab(m_pDlgManual, _T("Manual"),1);
	m_wndTabs.AddTab(m_pDlgProcess, _T("Process"),1);

	return 0;
}

void CWorkSpaceBar2::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	// Tree control should cover a whole client area:
	m_wndTabs.SetWindowPos(NULL, -1, -1, cx, cy,
		SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}
