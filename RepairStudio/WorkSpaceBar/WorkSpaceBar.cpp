// workspace.cpp : implementation of the CWorkSpaceBar class
//

#include "stdafx.h"
#include "../RepairStudio.h"
#include "WorkSpaceBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar

BEGIN_MESSAGE_MAP(CWorkSpaceBar, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar construction/destruction

CWorkSpaceBar::CWorkSpaceBar()
{
	//create dialog
	m_pDockMenu = new CDlgDockMenu;
}

CWorkSpaceBar::~CWorkSpaceBar()
{
}

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar message handlers

int CWorkSpaceBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create Ö÷½çÃæ
	if (!m_pDockMenu->Create(IDD_DIALOG_MENU, this))
	{
		TRACE0("Failed to create Menu view\n");
		return -1;
	}

	m_pDockMenu->ShowWindow(SW_MAXIMIZE);

	return 0;
}

void CWorkSpaceBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	// Tree control should cover a whole client area:
	m_pDockMenu->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);
}

