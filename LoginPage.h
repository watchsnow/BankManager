//Download by http://www.NewXing.com
#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CLoginPage �Ի���

class CLoginPage : public CDialog
{
	DECLARE_DYNAMIC(CLoginPage)

public:
	CLoginPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoginPage();

// �Ի�������
	enum { IDD = IDD_LOGIN_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCantonComb();
	afx_msg void OnCbnSelchangeSectionComb();
	// //�Զ������ʺŵ�ǰ������
	CString AutoCreateID(CString canton, CString section,CString type);
	CListCtrl m_LoginList;
	void OnInitList(void);
	afx_msg void OnEnChangeNameEdt();
	afx_msg void OnEnChangeIdentityEdt();
	afx_msg void OnCbnSelchangeSexComb();
	afx_msg void OnEnChangePhoneEdt();
	afx_msg void OnBnClickedLoginbtn();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CComboBox m_TypeComb;
	afx_msg void OnCbnSelchangeTypeComb();
	CEdit m_PassKeyEdt;
	CEdit m_IndentityIdEdt;
	long ReadHistory(void);
private:
	CString IntFormat(long iRecord);
	bool CheckNeed(void);
public:
	CEdit m_Phone;
	CEdit m_Name;
	void PrintTable(void);
	void EmptyTable(void);
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnEnChangePassEit();
};
