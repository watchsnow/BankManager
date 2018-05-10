//Download by http://www.NewXing.com
// PrintDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BankManager.h"
#include "PrintDlg.h"
#include ".\printdlg.h"


// CPrintDlg 对话框

IMPLEMENT_DYNAMIC(CPrintDlg, CDialog)
CPrintDlg::CPrintDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintDlg::IDD, pParent)
{
}

CPrintDlg::~CPrintDlg()
{
}

void CPrintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPrintDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_PRINT_BTN, OnBnClickedPrintBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPrintDlg 消息处理程序

void CPrintDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CPrintDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnCancel();
}

void CPrintDlg::OnBnClickedPrintBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

void CPrintDlg::OnBnClickedCloseBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

void CPrintDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog::OnCancel();
	CDialog::OnClose();
}
