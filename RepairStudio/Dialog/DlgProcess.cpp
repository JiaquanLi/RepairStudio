// DlgProcess.cpp: 实现文件
//

#include "stdafx.h"
#include "../RepairStudio.h"
#include "DlgProcess.h"


// CDlgProcess 对话框

IMPLEMENT_DYNAMIC(CDlgProcess, CBCGPDialog)

CDlgProcess::CDlgProcess(CWnd* pParent /*=nullptr*/)
	: CBCGPDialog(IDD_DIALOG_PROCESS, pParent)
{

}

CDlgProcess::~CDlgProcess()
{
}

void CDlgProcess::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgProcess, CBCGPDialog)
END_MESSAGE_MAP()


// CDlgProcess 消息处理程序

BOOL CDlgProcess::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	//delete dialog frame
	ModifyStyleEx(WS_EX_CLIENTEDGE, NULL, SWP_DRAWFRAME);

	//change dialog skin
	EnableVisualManagerStyle();

	return TRUE;
}