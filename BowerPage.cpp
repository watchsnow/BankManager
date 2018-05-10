//Download by http://www.NewXing.com
// BowerPage.cpp : 实现文件
//

#include "stdafx.h"
#include "BankManager.h"
#include "BowerPage.h"
#include ".\bowerpage.h"
#include "_StructDefine.h"
#include "AdoWorker.h"
#include "PrintDlg.h"


// CBowerPage 对话框

IMPLEMENT_DYNAMIC(CBowerPage, CDialog)
CBowerPage::CBowerPage(CWnd* pParent /*=NULL*/)
	: CDialog(CBowerPage::IDD, pParent)
{
}

CBowerPage::~CBowerPage()
{
}

void CBowerPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USER_LIST,m_BowerList);
	DDX_Control(pDX, IDC_CARDID_EDT, m_CardIdEdt);
	DDX_Control(pDX, IDC_PASS_EDT, m_PassKeyEdt);
}


BEGIN_MESSAGE_MAP(CBowerPage, CDialog)
	ON_EN_CHANGE(IDC_CARDID_EDT, OnEnChangeCardidEdt)
	ON_EN_CHANGE(IDC_PASS_EDT, OnEnChangePassEdt)
	ON_BN_CLICKED(IDC_EMPTY_BTN, OnBnClickedEmptyBtn)
	ON_BN_CLICKED(IDC_PRINT_BTN, OnBnClickedPrintBtn)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_USER_LIST, OnLvnItemchangedUserList)
END_MESSAGE_MAP()


// CBowerPage 消息处理程序

BOOL CBowerPage::OnInitDialog()
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
	//初始化列表框
	this->OnInitList();
	/////////////////////////////////主体窗口设置结束
	/////////////////////////////////设置Ｅｄｉｔ中能容纳数据的个数
	m_CardIdEdt.SetLimitText(12);
	m_PassKeyEdt.SetLimitText(8);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CBowerPage::OnEnChangeCardidEdt()
{
	CString strCardID=_T("");
	this->GetDlgItemText(IDC_CARDID_EDT,strCardID);
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
	{
		CString strName=_T("");
		strName=this->ReadRecord();
		if(strName!="")//确定次用户存在
		{
			this->ReadExchangeRecord(strName);//该帐户已经存在，而其密码正确,开始在交易记录表中查找相关记录
		}
		else
			MessageBox("不存在这样的用户");
	}
}

void CBowerPage::OnEnChangePassEdt()
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
	{
		CString strName=_T("");
		strName=this->ReadRecord();
		if(strName!="")//确定次用户存在
		{
			this->ReadExchangeRecord(strName);//该帐户已经存在，而其密码正确,开始在交易记录表中查找相关记录
		}
		else
			MessageBox("不存在这样的帐号，或者帐号与密码有误!",NULL,MB_ICONERROR);
	}
}
CString CBowerPage::ReadRecord(void)
{
	CString strSqlText=_T("select UserName from UserInfo where CardId ='");
	CString strId=_T("");
	this->GetDlgItemText(IDC_CARDID_EDT,strId);
	strSqlText=strSqlText+strId+CString("' and UserPass ='");
	//开始添加密码查询部分
	CString strPass=_T("");
	this->GetDlgItemText(IDC_PASS_EDT,strPass);
	strSqlText=strSqlText+strPass+CString("'");
	//////////////////////////////////创建SQL语句执行类实例
	AdoWorker *ado=NULL;
	_UserNameInfo *pUserNameInfo=NULL;
	ado=new AdoWorker();
	pUserNameInfo=(_UserNameInfo *)ado->ExecuteSql(strSqlText,5);
	CString strName=_T("");
	if(pUserNameInfo==NULL)
	{
		this->SetDlgItemText(IDC_PASS_EDT,NULL);
		delete pUserNameInfo;
		delete ado;
		return NULL;
	}
	else//存在这样的账号，在此设定表格中第二行的姓名
	{
		strName=pUserNameInfo->UserName;
		delete pUserNameInfo;
	}
	return strName;
}

BOOL CBowerPage::ReadExchangeRecord(CString strName)
{
	 CString strSqlText=_T("select * from RecordInfo where CardId ='");
	 CString strCardId=_T("");
	 this->GetDlgItemText(IDC_CARDID_EDT,strCardId);
	 strSqlText=strSqlText+strCardId+CString("' order by AutoId");
	 AdoWorker *ado=NULL;
	 ado=new AdoWorker();
	 _RecordInfo *pRecordInfo=NULL;
	 pRecordInfo=(_RecordInfo *)ado->ExecuteSql(strSqlText,4);
	 if(pRecordInfo==NULL)
		{ 
			MessageBox("没有该用户的交易信息！",NULL,MB_ICONQUESTION);
			return FALSE;
		}
	 else
	 {
		 this->WriteList(strName,pRecordInfo);
		 return TRUE;
	 }
}
void CBowerPage::OnInitList(void)
{
	m_BowerList.InsertColumn(0,"银行帐号",LVCFMT_LEFT,100);
	m_BowerList.InsertColumn(1,"姓名",LVCFMT_LEFT,60);
	m_BowerList.InsertColumn(2,"金额(元)",LVCFMT_LEFT,80);
	m_BowerList.InsertColumn(3,"利息(元)",LVCFMT_LEFT,80);
	m_BowerList.InsertColumn(4,"交易时间",LVCFMT_LEFT,80);
	m_BowerList.InsertColumn(5,"存/取",LVCFMT_LEFT,50);
	m_BowerList.InsertColumn(6,"交易类型",LVCFMT_LEFT,60);
	m_BowerList.SetExtendedStyle(LVS_EX_GRIDLINES);
}

void CBowerPage::WriteList(CString strName,_RecordInfo *pRecordInfo)
{
	CString strChangeType=_T("");
	_RecordInfo *pDelete=NULL;
	pDelete=pRecordInfo;
	for(int i=0;pRecordInfo!=NULL;i++)
	{
		m_BowerList.InsertItem(i,NULL);
		m_BowerList.SetItemText(i,0,pRecordInfo->CardId);
		m_BowerList.SetItemText(i,1,strName);
		strChangeType.Format("%f",pRecordInfo->MoneryBalance);
		m_BowerList.SetItemText(i,2,strChangeType);
		strChangeType.Format("%f",pRecordInfo->AccrualBalance);
		m_BowerList.SetItemText(i,3,strChangeType);
		m_BowerList.SetItemText(i,4,pRecordInfo->ExchangeDate);
		m_BowerList.SetItemText(i,5,pRecordInfo->InOut);
		m_BowerList.SetItemText(i,6,pRecordInfo->MoneyType);
		//
		pRecordInfo=pRecordInfo->Next;
		delete pDelete;
		pDelete=pRecordInfo;
	}
}

void CBowerPage::OnBnClickedEmptyBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	this->SetDlgItemText(IDC_CARDID_EDT,NULL);
	this->SetDlgItemText(IDC_PASS_EDT,NULL);
	m_BowerList.DeleteAllItems();
}

void CBowerPage::OnBnClickedPrintBtn()
{
	// TODO: 在此添加控件通知处理程序代码

	CPrintDlg *pPrintDlg=NULL;
	pPrintDlg=new CPrintDlg();
	if(pPrintDlg->DoModal()==IDOK)
	{
		this->PrintTable();//打印数据表

	}
	delete pPrintDlg;
}

void CBowerPage::PrintTable(void)
{
}

void CBowerPage::OnLvnItemchangedUserList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
