// CDlgMatch.cpp: 实现文件
//

#include "stdafx.h"
#include "../HLSScanner.h"
#include "CDlgMatch.h"


// CDlgMatch 对话框

IMPLEMENT_DYNAMIC(CDlgMatch, CBCGPDialog)

CDlgMatch::CDlgMatch(CWnd* pParent /*=nullptr*/)
	: CBCGPDialog(IDD_DIALOG_MATCH, pParent)
{

}

CDlgMatch::~CDlgMatch()
{
}

void CDlgMatch::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMatch, CBCGPDialog)
END_MESSAGE_MAP()


// CDlgMatch 消息处理程序

BOOL CDlgMatch::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	//delete dialog frame
	ModifyStyleEx(WS_EX_CLIENTEDGE, NULL, SWP_DRAWFRAME);

	//change dialog skin
	EnableVisualManagerStyle();

	//set color and font
	fnSetFontAndColor();

	return TRUE;
}

//设置控件字体
void CDlgMatch::fnSetFontAndColor()
{
	//按钮的字体
	m_Font.CreatePointFont(120, "隶书", NULL);

	//进行界面控件ID循环获取，然后分别进行赋值，但是static必须更改名字
	HWND subWnd = ::GetWindow(GetSafeHwnd(), GW_CHILD);
	while (subWnd)
	{
		CWnd *subCWnd = CWnd::FromHandle(subWnd);
		int  nCtrlID = subCWnd->GetDlgCtrlID();
		if (0 < nCtrlID)
		{
			//设置Static字体
			GetDlgItem(nCtrlID)->SetFont(&m_Font);
		}
		subWnd = ::GetWindow(subWnd, GW_HWNDNEXT);
	}
}