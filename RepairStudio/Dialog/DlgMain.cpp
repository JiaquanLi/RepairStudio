// CDlgMain.cpp: 实现文件
//

#include "stdafx.h"
#include "../RepairStudio.h"
#include "DlgMain.h"


// CDlgMain 对话框

IMPLEMENT_DYNAMIC(CDlgMain, CBCGPDialog)

CDlgMain::CDlgMain(CWnd* pParent /*=nullptr*/): CBCGPDialog(IDD_DIALOG_MAIN, pParent)
{

}

CDlgMain::~CDlgMain()
{
}

void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMain, CBCGPDialog)
END_MESSAGE_MAP()


// CDlgMain 消息处理程序


BOOL CDlgMain::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	//delete dialog frame
	ModifyStyleEx(WS_EX_CLIENTEDGE, NULL, SWP_DRAWFRAME);

	//change dialog skin
	EnableVisualManagerStyle();

	return TRUE;  
}
