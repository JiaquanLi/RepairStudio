#pragma once


// CDlgMatch 对话框

class CDlgMatch : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgMatch)

public:
	CDlgMatch(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgMatch();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MATCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

private:
	CFont m_Font;

private:
	//设置控件字体和颜色
	void fnSetFontAndColor();
};
