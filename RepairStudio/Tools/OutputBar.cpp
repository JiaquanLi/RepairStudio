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
	lstrcpynA(cf.szFaceName, T2A((LPTSTR)(LPCTSTR)"΢���ź�"), LF_FACESIZE);
	m_wndProcess->SetDefaultCharFormat(cf);
	m_wndThread->SetDefaultCharFormat(cf);
	m_wndError->SetDefaultCharFormat(cf);
	//������ɫ
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

	// �����������:
	const DWORD dwStyle = WS_VISIBLE | WS_CHILD | ES_READONLY | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE;

	//�����ؼ�
	m_wndProcess = new COutputEdit;
	m_wndProcess->Create(dwStyle, rectDummy, &m_wndTabs, 1);
	m_wndThread = new COutputEdit;
	m_wndThread->Create(dwStyle, rectDummy, &m_wndTabs, 1);
	m_wndError = new COutputEdit;
	m_wndError->Create(dwStyle, rectDummy, &m_wndTabs, 1);

	//��������
	fnSetFont();

	// Attach list windows to tab:
	m_wndTabs.AddTab(m_wndProcess, _T("������Ϣ"), -1);
	m_wndTabs.AddTab(m_wndThread, _T("�ӹ���Ϣ"), -1);
	m_wndTabs.AddTab(m_wndError, _T("������Ϣ"), -1);

	//����tab����
	m_Font.CreatePointFont(80, "΢���ź�", NULL);
	m_wndTabs.SetFont(&m_Font);

	return 0;
}

void COutputBar::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	// ѡ��ؼ�Ӧ��������������:
	m_wndTabs.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndProcess->SetWindowPos(NULL, -1, -1, cx, cy - 32, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndThread->SetWindowPos(NULL, -1, -1, cx, cy - 32, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndError->SetWindowPos(NULL, -1, -1, cx, cy - 32, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void COutputBar::fnOutPutMessage(CString strMessage, COLORREF color, OUTPUBAR_MODE nOutPlace, BOOL bAppend, BOOL bErase)
{
	COutputEdit *pEdit = NULL;

	//�˳�ʱ��
	CString strTime;
	CTime time = CTime::GetCurrentTime();
	strTime = time.Format(_T("#%H:%M:%S-->"));
	strMessage = strTime + strMessage;

	//�Ƿ���Ҫ������������
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

	//����ӡ���ַ�
	if (strMessage.IsEmpty())
	{
		return;
	}
	
	//���������������ɫ
	CHARFORMAT cf;
	memset(&cf, 0, sizeof(cf));
	cf.crTextColor = color;
	cf.dwMask = CFM_COLOR | CFM_SIZE;
	cf.yHeight = 250;
	pEdit->SetSelectionCharFormat(cf);

	//��ÿһ��֮ǰ����2���ո�
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

	//���ı���ĩβ����һ��
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
// COutputEdit ��Ϣ�������

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
* Function:�����Ϣ����Ϣ�������
* param[in] strMessage �������Ϣ����
* param[in] bAppend �Ƿ���Ҫ����
* param[in] color �����������ɫ
* param[in] nThick ����������С
* param[in] bErase �Ƿ����������ڵ�ԭ������
*****************************/
void COutputEdit::fnOutPutMessage(CString strMessage, COLORREF color, BOOL bAppend, BOOL bErase)
{
	if (m_hWnd == NULL)
	{
		return;
	}
	//�Ƿ���Ҫ������������
	if (bErase)
	{
		SetWindowText(_T(""));
	}

	//����ӡ���ַ�
	if (strMessage.IsEmpty())
	{
		return;
	}

	//���������������ɫ
	CHARFORMAT cf;
	memset(&cf, 0, sizeof(cf));
	cf.crTextColor = color;
	cf.dwMask = CFM_COLOR | CFM_SIZE;
	cf.yHeight = m_nSize;
	SetSelectionCharFormat(cf);

	//��ÿһ��֮ǰ����2���ո�
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

	//���ı���ĩβ����һ��
	SetSel(-1, -1);
	ReplaceSel((LPCTSTR)strNew);
}
