//Download by http://www.NewXing.com
#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "_StructDefine.h"

// CBowerPage 对话框

class CBowerPage : public CDialog
{
	DECLARE_DYNAMIC(CBowerPage)

public:
	CBowerPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBowerPage();

// 对话框数据
	enum { IDD = IDD_BOWER_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_BowerList;
	afx_msg void OnEnChangeCardidEdt();
	afx_msg void OnEnChangePassEdt();
	virtual BOOL OnInitDialog();
	CString ReadRecord(void);
	BOOL ReadExchangeRecord(CString strName);
	CEdit m_CardIdEdt;
	CEdit m_PassKeyEdt;
	void OnInitList(void);
	void WriteList(CString strName,_RecordInfo *pRecordInfo);
	afx_msg void OnBnClickedEmptyBtn();
	afx_msg void OnBnClickedPrintBtn();
	void PrintTable(void);
	afx_msg void OnLvnItemchangedUserList(NMHDR *pNMHDR, LRESULT *pResult);
};
