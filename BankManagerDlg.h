//Download by http://www.NewXing.com
// BankManagerDlg.h : 头文件
//

#pragma once
#include "btnst.h"
#include "afxwin.h"
#include "LoginPage.h"
#include "SavingPage.h"
#include "FetchPage.h"
#include "ModifyPage.h"
#include "BowerPage.h"
#include "DeletePage.h"


// CBankManagerDlg 对话框
class CBankManagerDlg : public CDialog
{
// 构造
public:
	CBankManagerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BANKMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
	afx_msg void OnBnClickedLoginchk();
	afx_msg void OnBnClickedSavingchk();
	afx_msg void OnBnClickedFetchchk();
	afx_msg void OnBnClickedChangepwchk();
	afx_msg void OnBnClickedExchangechk();
	afx_msg void OnBnClickedDeleteuserchk();
	afx_msg void OnBnClickedCancelbtn();
public:
	CButtonST m_LoginChk;
	CButtonST m_SavingChk;
	CButtonST m_FetchChk;
	CButtonST m_ChangePwChk;
	CButtonST m_ExchangeChk;
	CButtonST m_DeleteLoginChk;
	CStatic m_ChooseStc;
	CStatic m_WorkStc;
	CButtonST m_CancelBtn;
	CLoginPage m_LoginPage;
	CSavingPage m_SavingPage;
	CFetchPage m_FetchPage;
	CModifyPage m_ModifyPage;
	CBowerPage m_BowerPage;
	CDeletePage m_DeletePage;
	
private:
	int OnInitChk(void);
	
public:
	// //用来初始化６个工作区页面
	int OnInitPage(void);
};
