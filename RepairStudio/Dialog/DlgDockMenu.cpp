// CDlgDockMenu.cpp: 实现文件
//

#include "stdAfx.h"
#include "../RepairStudio.h"
#include "DlgDockMenu.h"


// CDlgDockMenu 对话框

IMPLEMENT_DYNAMIC(CDlgDockMenu, CBCGPDialog)

CDlgDockMenu::CDlgDockMenu(CWnd* pParent /*=nullptr*/)
	: CBCGPDialog(IDD_DIALOG_MENU, pParent)
{

}

CDlgDockMenu::~CDlgDockMenu()
{
}

void CDlgDockMenu::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDockMenu, CBCGPDialog)
	ON_BN_CLICKED(IDC_BUTTON8, &CDlgDockMenu::OnBnClickedButton8)
END_MESSAGE_MAP()


// CDlgDockMenu 消息处理程序

BOOL CDlgDockMenu::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	//delete dialog frame
	ModifyStyleEx(WS_EX_CLIENTEDGE, NULL, SWP_DRAWFRAME);

	//change dialog skin
	EnableVisualManagerStyle();
	
	return TRUE;
}

void CDlgDockMenu::OnBnClickedButton8()
{
	fnSendMessageBox("BUTTON8");
}
