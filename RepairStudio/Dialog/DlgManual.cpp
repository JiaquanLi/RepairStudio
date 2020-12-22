// CDlgManual.cpp: 实现文件
//

#include "stdafx.h"
#include "../RepairStudio.h"
#include "DlgManual.h"


// CDlgManual 对话框

IMPLEMENT_DYNAMIC(CDlgManual, CBCGPDialog)

CDlgManual::CDlgManual(CWnd* pParent /*=nullptr*/)
	: CBCGPDialog(IDD_DIALOG_MANUAL, pParent)
{

}

CDlgManual::~CDlgManual()
{
}

void CDlgManual::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgManual, CBCGPDialog)
END_MESSAGE_MAP()


// CDlgManual 消息处理程序


BOOL CDlgManual::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	//delete dialog frame
	ModifyStyleEx(WS_EX_CLIENTEDGE, NULL, SWP_DRAWFRAME);

	//change dialog skin
	EnableVisualManagerStyle();

	return TRUE;
}