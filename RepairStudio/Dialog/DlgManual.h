#pragma once


// CDlgManual 对话框

class CDlgManual : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgManual)

public:
	CDlgManual(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgManual();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MANUAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
};
