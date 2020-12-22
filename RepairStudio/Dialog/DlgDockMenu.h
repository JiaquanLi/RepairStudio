#pragma once


// CDlgDockMenu 对话框

class CDlgDockMenu : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgDockMenu)

public:
	CDlgDockMenu(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgDockMenu();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MENU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton8();
};
