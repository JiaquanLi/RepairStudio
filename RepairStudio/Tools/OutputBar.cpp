// outputbar.cpp : implementation of the COutputBar class
//

#include<afxcmn.h>
#include "stdafx.h"
#include "../PadCut.h"
#include "outputbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

BEGIN_MESSAGE_MAP(COutputBar, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputBar construction/destruction

COutputBar::COutputBar()
{
	
}

COutputBar::~COutputBar()
{
}

/////////////////////////////////////////////////////////////////////////////
// COutputBar message handlers

void COutputBar::fnSetFont()
{
	CHARFORMAT cf;
	cf.dwMask = CFM_FACE | CFM_SIZE | CFM_BOLD;
	cf.yHeight = 200;
	cf.dwEffects = ~CFE_BOLD;
	cf.crTextColor = COLOR_YELLOW;
	lstrcpynA(cf.szFaceName, T2A((LPTSTR)(LPCTSTR)"微软雅黑"), LF_FACESIZE);
	m_wndProcess->SetDefaultCharFormat(cf);
	m_wndThread->SetDefaultCharFormat(cf);
	m_wndError->SetDefaultCharFormat(cf);
	//设置颜色
	m_wndProcess->SetBackgroundColor(FALSE, RGB(242, 248, 255));
	m_wndThread->SetBackgroundColor(FALSE, RGB(221, 255, 221));
	m_wndError->SetBackgroundColor(FALSE, RGB(255, 234, 225));
}

int COutputBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create tabs window:
	if (!m_wndTabs.Create(CBCGPTabWnd::STYLE_3D, rectDummy, this, 1))
	{
		TRACE0("Failed to create output tab window\n");
		return -1;      // fail to create
	}

	// 创建输出窗格:
	const DWORD dwStyle = WS_VISIBLE | WS_CHILD | ES_READONLY | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE;

	//创建控件
	m_wndProcess = new COutputEdit;
	m_wndProcess->Create(dwStyle, rectDummy, &m_wndTabs, 1);
	m_wndThread = new COutputEdit;
	m_wndThread->Create(dwStyle, rectDummy, &m_wndTabs, 1);
	m_wndError = new COutputEdit;
	m_wndError->Create(dwStyle, rectDummy, &m_wndTabs, 1);

	//设置字体
	fnSetFont();

	// Attach list windows to tab:
	m_wndTabs.AddTab(m_wndProcess, _T("运行信息"), -1);
	m_wndTabs.AddTab(m_wndThread, _T("加工信息"), -1);
	m_wndTabs.AddTab(m_wndError, _T("报警信息"), -1);

	//设置tab字体
	m_Font.CreatePointFont(80, "微软雅黑", NULL);
	m_wndTabs.SetFont(&m_Font);

	return 0;
}

void COutputBar::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	// 选项卡控件应覆盖整个工作区:
	m_wndTabs.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndProcess->SetWindowPos(NULL, -1, -1, cx, cy - 32, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndThread->SetWindowPos(NULL, -1, -1, cx, cy - 32, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndError->SetWindowPos(NULL, -1, -1, cx, cy - 32, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void COutputBar::fnOutPutMessage(CString strMessage, COLORREF color, OUTPUBAR_MODE nOutPlace, BOOL bAppend, BOOL bErase)
{
	COutputEdit *pEdit = NULL;

	//退出时间
	CString strTime;
	CTime time = CTime::GetCurrentTime();
	strTime = time.Format(_T("#%H:%M:%S-->"));
	strMessage = strTime + strMessage;

	//是否需要清除输出框内容
	if (OUTPUTBAR_PROCESS == nOutPlace)
	{
		pEdit = m_wndProcess;
	}
	else if (OUTPUTBAR_THREADRUNNING == nOutPlace)
	{
		pEdit = m_wndThread;
	}
	else
	{
		pEdit = m_wndError;
	}

	if (bErase)
	{
		pEdit->SetWindowText(_T(""));
	}

	//不打印空字符
	if (strMessage.IsEmpty())
	{
		return;
	}
	
	//设置输入字体的颜色
	CHARFORMAT cf;
	memset(&cf, 0, sizeof(cf));
	cf.crTextColor = color;
	cf.dwMask = CFM_COLOR | CFM_SIZE;
	cf.yHeight = 250;
	pEdit->SetSelectionCharFormat(cf);

	//在每一行之前增加2个空格
	strMessage.TrimLeft();
	strMessage.TrimRight();

	CString strNew;
	if (!bAppend)
	{
		strNew.Format(_T("\r\n%s"), strMessage);
	}
	else
	{
		strNew.Format(_T("%s"), strMessage);
	}

	//在文本框末尾增加一行
	pEdit->SetSel(-1, -1);
	pEdit->ReplaceSel((LPCTSTR)strNew);
	pEdit->LineScroll(pEdit->GetLineCount());
}

/////////////////////////////////////////////////////////////////////////////
// COutputEdit

COutputEdit::COutputEdit()
{
	m_nSize = 350;
}

COutputEdit::~COutputEdit()
{
}

BEGIN_MESSAGE_MAP(COutputEdit, CRichEditCtrl)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_OUTPUTWND, OnViewOutput)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// COutputEdit 消息处理程序

void COutputEdit::OnViewOutput()
{
	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
	CFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CFrameWndEx, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus();
		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout();
	}
}

void COutputEdit::fnSetFontSize(int nSize)
{
	m_nSize = nSize;
}

/*****************************
* FunctionName: fnOutPutMessage
*
* Function:输出信息到信息输出框内
* param[in] strMessage 输出的信息内容
* param[in] bAppend 是否需要换行
* param[in] color 输出的字体颜色
* param[in] nThick 输出的字体大小
* param[in] bErase 是否清除输出框内的原有内容
*****************************/
void COutputEdit::fnOutPutMessage(CString strMessage, COLORREF color, BOOL bAppend, BOOL bErase)
{
	if (m_hWnd == NULL)
	{
		return;
	}
	//是否需要清除输出框内容
	if (bErase)
	{
		SetWindowText(_T(""));
	}

	//不打印空字符
	if (strMessage.IsEmpty())
	{
		return;
	}

	//设置输入字体的颜色
	CHARFORMAT cf;
	memset(&cf, 0, sizeof(cf));
	cf.crTextColor = color;
	cf.dwMask = CFM_COLOR | CFM_SIZE;
	cf.yHeight = m_nSize;
	SetSelectionCharFormat(cf);

	//在每一行之前增加2个空格
	strMessage.TrimLeft();
	strMessage.TrimRight();

	CString strNew;
	if (!bAppend)
	{
		strNew.Format(_T("\r\n%s"), strMessage);
	}
	else
	{
		strNew.Format(_T("%s"), strMessage);
	}

	//在文本框末尾增加一行
	SetSel(-1, -1);
	ReplaceSel((LPCTSTR)strNew);
}
