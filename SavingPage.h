//Download by http://www.NewXing.com
#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "_StructDefine.h"

// CSavingPage �Ի���

class CSavingPage : public CDialog
{
	DECLARE_DYNAMIC(CSavingPage)

public:
	CSavingPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSavingPage();

// �Ի�������
	enum { IDD = IDD_SAVING_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_SavingList;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeCardidEdt();
	afx_msg void OnCbnSelchangeTypeComb();
	afx_msg void OnEnChangeMoneyEdt();
	afx_msg void OnCbnSelchangeTimeComb();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSavingBtn();
	CComboBox m_TypeComb;
	CStatic m_DingStc;
	CEdit m_TimeEdt;
	CComboBox m_TimeComB;
	CEdit m_CardIdEdt;
	CEdit m_RateEdt;
private:
	// �����ϴν��׵�������������������ÿ�°�30����㣬ÿ��12����
	int CountDay(_CurrentInfo *pCurrentInfo);
	void WriteCurrentList(_CurrentInfo * pCurrentInfo);
	void WriteFixList(_FixInfo * pFixInfo);
	double GetRate(void);	
	void OnInitList(void);
	void SureIdExist(void);
	CString FormatTime(int);
	bool CheckCurrent(void);
	BOOL WriteCurrentSql(void);
	bool CheckFix(void);
	BOOL WriteFixSql(void);
	void EmptyTable(void);
	void PrintTable(void);
};
