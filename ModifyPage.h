//Download by http://www.NewXing.com
#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CModifyPage 对话框

class CModifyPage : public CDialog
{
	DECLARE_DYNAMIC(CModifyPage)

public:
	CModifyPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModifyPage();

// 对话框数据
	enum { IDD = IDD_MODIFY_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_CardIdEdt;
	CEdit m_PassWordEdt;
	virtual BOOL OnInitDialog();
	void OnInitList(void);
	CListCtrl m_UserList;
	CStatic m_GroupStc;
	CStatic m_NewStc;
	CEdit m_NewPassEdt;
	afx_msg void OnEnChangeCardidEdt();
	afx_msg void OnEnChangePassEdt();
	afx_msg void OnBnClickedPassbtn();
	BOOL ReadRecord(void);
protected:
	virtual void OnOK();
	virtual void OnCancel();
	void PrintTable();
	void EmptyTable();
public:
	afx_msg void OnBnClickedCancelBtn();
};
