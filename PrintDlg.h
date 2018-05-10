//Download by http://www.NewXing.com
#pragma once


// CPrintDlg 对话框

class CPrintDlg : public CDialog
{
	DECLARE_DYNAMIC(CPrintDlg)

public:
	CPrintDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPrintDlg();

// 对话框数据
	enum { IDD = IDD_CHECKPRINT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedPrintBtn();
	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnClose();
};
