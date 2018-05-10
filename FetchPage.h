//Download by http://www.NewXing.com
#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "_StructDefine.h"

// CFetchPage �Ի���

class CFetchPage : public CDialog
{
	DECLARE_DYNAMIC(CFetchPage)

public:
	CFetchPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFetchPage();

// �Ի�������
	enum { IDD = IDD_FETCH_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_FetchStc;
	CEdit m_MoneyEdt;
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeCardidEdt();
	afx_msg void OnEnChangeMoneyEdt();
	afx_msg void OnEnChangePassEdt();
	CListCtrl m_FetchList;
	CEdit m_CardIdEdt;
	CEdit m_PassKeyEdt;
private:
	// �����ϴν��׵�������������������ÿ�°�30����㣬ÿ��12����
	int CountDay(_CurrentInfo *pCurrentInfo);
	void WriteCurrentList(_CurrentInfo * pCurrentInfo);
	void WriteFixList(_FixInfo * pFixInfo);
	double GetRate(void);	
	void OnInitList(void);
	void ReadRecord(void);;
	CString FormatTime();
	bool CheckCurrent(void);
	BOOL WriteCurrentSql(void);
	bool CheckFix(void);
	BOOL WriteFixSql(void);
	void EmptyTable(void);
	void PrintTable(void);
	BOOL CheckMatured(_FixInfo * pFixInfo);
public:
	afx_msg void OnBnClickedFetchBtn();	
	afx_msg void OnBnClickedCancelBtn();
};
