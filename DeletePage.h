//Download by http://www.NewXing.com
#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "_StructDefine.h"


// CDeletePage 对话框

class CDeletePage : public CDialog
{
	DECLARE_DYNAMIC(CDeletePage)

public:
	CDeletePage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeletePage();

// 对话框数据
	enum { IDD = IDD_DELETE_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	CEdit m_CardIdEdt;
	CEdit m_PassWordEdt;
	CListCtrl m_DeleteList;
	void OnInitList(void);
	afx_msg void OnEnChangeCardidEdt();
	CString ReadRecord(void);
	afx_msg void OnEnChangePassEdt();
private:
	int CountDay(_CurrentInfo *pCurrentInfo);
	void WriteRecordToList(CString strName);
	void WriteCurrentList(_CurrentInfo * pCurrentInfo);
	void WriteFixList(_FixInfo * pFixInfo);
	double GetRate(void);	
	CString FormatTime();
	void EmptyTable(void);
	void PrintTable(void);
	BOOL CheckMatured(_FixInfo * pFixInfo);
	//CString FormatTime();
public:
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedDeleteBtn();
	void DeleteSql(void);
};
