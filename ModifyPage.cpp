//Download by http://www.NewXing.com
// ModifyPage.cpp : 实现文件
//

#include "stdafx.h"
#include "BankManager.h"
#include "ModifyPage.h"
#include ".\modifypage.h"
#include "AdoWorker.h"
#include "_StructDefine.h"
#include "PrintDlg.h"


// CModifyPage 对话框

IMPLEMENT_DYNAMIC(CModifyPage, CDialog)
CModifyPage::CModifyPage(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyPage::IDD, pParent)
{
}

CModifyPage::~CModifyPage()
{
}

void CModifyPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CARDID_EDT, m_CardIdEdt);
	DDX_Control(pDX, IDC_PASS_EDT, m_PassWordEdt);
	DDX_Control(pDX, IDC_USER_LIST, m_UserList);
	DDX_Control(pDX, IDC_NEW_STC, m_GroupStc);
	DDX_Control(pDX, IDC_NEWP_STC, m_NewStc);
	DDX_Control(pDX, IDC_NEWPASS_EDT, m_NewPassEdt);
}


BEGIN_MESSAGE_MAP(CModifyPage, CDialog)
	ON_EN_CHANGE(IDC_CARDID_EDT, OnEnChangeCardidEdt)
	ON_EN_CHANGE(IDC_PASS_EDT, OnEnChangePassEdt)
	ON_BN_CLICKED(IDC_PASS_BTN, OnBnClickedPassbtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
END_MESSAGE_MAP()


// CModifyPage 消息处理程序

BOOL CModifyPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	rc.top=rc.top+15;
	rc.left=rc.left+3;
	rc.bottom=rc.bottom-2;
	rc.right=rc.right-2;
	((CTabCtrl*)GetParent())->AdjustRect(false, &rc); 
	MoveWindow(&rc);
	/////////////////////////////////主体窗口设置结束
	/////////////////////////////////开始设置Edit框中容纳数据的个数
	m_PassWordEdt.SetLimitText(8);
	m_CardIdEdt.SetLimitText(12);
	m_NewPassEdt.SetLimitText(8);
	/////////////////////////////////隐藏新密码输入窗口
	m_GroupStc.ShowWindow(SW_HIDE);
	m_NewStc.ShowWindow(SW_HIDE);
	m_NewPassEdt.ShowWindow(SW_HIDE);
	//初始化列表框
	this->OnInitList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CModifyPage::OnInitList(void)
{
	m_UserList.InsertColumn(0,"帐号",LVCFMT_LEFT,120);
	m_UserList.InsertColumn(1,"姓名",LVCFMT_LEFT,80);
	m_UserList.InsertColumn(2,"性别",LVCFMT_LEFT,60);
	m_UserList.InsertColumn(3,"身份证号码",LVCFMT_LEFT,130);
	m_UserList.InsertColumn(4,"移动电话",LVCFMT_LEFT,100);
	m_UserList.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_UserList.InsertItem(0,NULL);
}

void CModifyPage::OnEnChangeCardidEdt()
{
	CString strCardID=_T("");
	this->GetDlgItemText(IDC_CARDID_EDT,strCardID);
	m_UserList.SetItemText(0,0,strCardID);//设置帐号栏
	////在此中要判断输入数据的位数，若数据已满则自动连接数据库，查询此人帐号和以前的余额，显示在表格中
	////定活期选择和此两者控制何时要自动连接数据库查询
	int iStr=0;
	iStr=strCardID.GetLength();
	if(iStr==2)//自动检查帐号是定期还是活期
	{
		if(!(strCardID=="01"||strCardID=="02"))//活期
			{
				MessageBox("不存在这样类型的账号,请重新输入！",NULL,MB_ICONERROR);
			    this->SetDlgItemText(IDC_CARDID_EDT,NULL);
			}
	}
	int iStrID=0;
	iStrID=strCardID.GetLength();
	CString strPass=_T("");
	this->GetDlgItemText(IDC_PASS_EDT,strPass);
	int iStrPass=0;
	iStrPass=strPass.GetLength();
	if(iStrID==12&&iStrPass==8)
		if(this->ReadRecord())//用户存在
		{
			m_GroupStc.ShowWindow(SW_SHOW);
			m_NewStc.ShowWindow(SW_SHOW);
			m_NewPassEdt.ShowWindow(SW_SHOW);
		}
}

void CModifyPage::OnEnChangePassEdt()
{
	CString strCardID=_T("");
	this->GetDlgItemText(IDC_CARDID_EDT,strCardID);
	int iStrID=0;
	iStrID=strCardID.GetLength();
	CString strPass=_T("");
	this->GetDlgItemText(IDC_PASS_EDT,strPass);
	int iStrPass=0;
	iStrPass=strPass.GetLength();
	if(iStrID==12&&iStrPass==8)
		if(this->ReadRecord())//此用户存在
		{
			m_GroupStc.ShowWindow(SW_SHOW);
			m_NewStc.ShowWindow(SW_SHOW);
			m_NewPassEdt.ShowWindow(SW_SHOW);
		}
}

void CModifyPage::OnOK()
{
}

void CModifyPage::OnCancel()
{
}

BOOL CModifyPage::ReadRecord(void)//根据输入的账号和密码查询数据库，判断该帐号是否存在，且密码是否正确
{
	CString strSqlText=_T("select * from UserInfo where CardId ='");
	CString strId=_T("");
	strId=m_UserList.GetItemText(0,0);
	strSqlText=strSqlText+strId+CString("' and UserPass ='");
	//开始添加密码查询部分
	CString strPass=_T("");
	this->GetDlgItemText(IDC_PASS_EDT,strPass);
	strSqlText=strSqlText+strPass+CString("'");
	//////////////////////////////////创建SQL语句执行类实例
	AdoWorker *ado=NULL;
	_UserInfo *pUserInfo=NULL;
	ado=new AdoWorker();
	pUserInfo=(_UserInfo *)ado->ExecuteSql(strSqlText,1);
	CString strUserInfo=_T("");
	if(pUserInfo==NULL)
	{
		MessageBox(" 不存在该帐号或者请您检查帐号和密码的正确性！",NULL,MB_ICONERROR);
		delete pUserInfo;
		delete ado;
		return FALSE;
	}
	else//存在这样的账号，在此设定表格中第一行的其他数据
	{
		strUserInfo=pUserInfo->UserName;
		m_UserList.SetItemText(0,1,strUserInfo);
		strUserInfo=pUserInfo->UserSex;
		m_UserList.SetItemText(0,2,strUserInfo);
		strUserInfo=pUserInfo->UserId;
		m_UserList.SetItemText(0,3,strUserInfo);
		strUserInfo=pUserInfo->UserPhone;
		m_UserList.SetItemText(0,4,strUserInfo);
		delete pUserInfo;
	}
	return TRUE;
}
void CModifyPage::OnBnClickedPassbtn()
{
	//检查输入密码的位数
	CString strCheck=_T("");
	this->GetDlgItemText(IDC_NEWPASS_EDT,strCheck);
	int iSum=0;
	iSum=strCheck.GetLength();
	if(iSum!=8)
	{
		MessageBox("新密码的位数应为8位,输入有误！",NULL,MB_ICONERROR);
		return;
	}
	//密码检查正确，开始组织SQL语句，写数据库
	CString strSqlText=_T("update UserInfo set UserPass ='");
	strSqlText=strSqlText+strCheck+(CString)("'where CardId='");
	this->GetDlgItemText(IDC_CARDID_EDT,strCheck);
	strSqlText=strSqlText+strCheck+(CString)("'");
	AdoWorker *ado=NULL;
	ado=new AdoWorker();
	if(ado->ExecuteSql(strSqlText))
	{
		CPrintDlg *pPrintDlg=NULL;
		pPrintDlg=new CPrintDlg();
		if(pPrintDlg->DoModal()==IDOK)
		{
			this->PrintTable();//打印数据表

		}
		delete pPrintDlg;
		MessageBox("修改密码成功！",NULL,MB_ICONASTERISK);
		this->EmptyTable();
	}
	else
		MessageBox("修改密码不成功！",NULL,MB_ICONERROR);

}
void CModifyPage::EmptyTable()
{
	this->SetDlgItemText(IDC_CARDID_EDT,NULL);
	this->SetDlgItemText(IDC_PASS_EDT,NULL);
	this->SetDlgItemText(IDC_NEWPASS_EDT,NULL);
	m_GroupStc.ShowWindow(SW_HIDE);
	m_NewStc.ShowWindow(SW_HIDE);
	m_NewPassEdt.ShowWindow(SW_HIDE);
	m_UserList.DeleteAllItems();
	m_UserList.InsertItem(0,NULL);

}
void CModifyPage::OnBnClickedCancelBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	this->EmptyTable();
}
void CModifyPage::PrintTable()
{
}