//Download by http://www.NewXing.com
#pragma once


// CPrintDlg �Ի���

class CPrintDlg : public CDialog
{
	DECLARE_DYNAMIC(CPrintDlg)

public:
	CPrintDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPrintDlg();

// �Ի�������
	enum { IDD = IDD_CHECKPRINT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedPrintBtn();
	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnClose();
};
