//Download by http://www.NewXing.com
// DeletePage.cpp : 实现文件
//

#include "stdafx.h"
#include "BankManager.h"
#include "DeletePage.h"
#include ".\deletepage.h"
#include "_StructDefine.h"
#include "AdoWorker.h"
#include "PrintDlg.h"


// CDeletePage 对话框

IMPLEMENT_DYNAMIC(CDeletePage, CDialog)
CDeletePage::CDeletePage(CWnd* pParent /*=NULL*/)
	: CDialog(CDeletePage::IDD, pParent)
{
}

CDeletePage::~CDeletePage()
{
}

void CDeletePage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CARDID_EDT, m_CardIdEdt);
	DDX_Control(pDX, IDC_PASS_EDT, m_PassWordEdt);
	DDX_Control(pDX, IDC_USER_LIST, m_DeleteList);
}


BEGIN_MESSAGE_MAP(CDeletePage, CDialog)
	ON_EN_CHANGE(IDC_CARDID_EDT, OnEnChangeCardidEdt)
	ON_EN_CHANGE(IDC_PASS_EDT, OnEnChangePassEdt)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_DELETE_BTN, OnBnClickedDeleteBtn)
END_MESSAGE_MAP()


// CDeletePage 消息处理程序
BOOL CDeletePage::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//////////////////////////////////初始化移动窗口位置
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	rc.top=rc.top+15;
	rc.left=rc.left+3;
	rc.bottom=rc.bottom-2;
	rc.right=rc.right-2;
	((CTabCtrl*)GetParent())->AdjustRect(false, &rc); 
	MoveWindow(&rc);
	/////////////////////////////////主体窗口设置结束
	m_PassWordEdt.SetLimitText(8);
	m_CardIdEdt.SetLimitText(12);
	/////////////////////////////////
	this->OnInitList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDeletePage::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
}

void CDeletePage::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
}
void  CDeletePage::OnInitList(void)
{
	m_DeleteList.InsertColumn(0,"帐号",LVCFMT_LEFT,120);
	m_DeleteList.InsertColumn(1,"姓名",LVCFMT_LEFT,80);
	m_DeleteList.InsertColumn(2,"身份证号码",LVCFMT_LEFT,130);
	m_DeleteList.InsertColumn(3,"所剩金额(元)",LVCFMT_LEFT,80);
	m_DeleteList.InsertColumn(4,"利息(元)",LVCFMT_LEFT,80);
	m_DeleteList.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_DeleteList.InsertItem(0,NULL);
}
void CDeletePage::OnEnChangeCardidEdt()
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
			this->WriteRecordToList(strName);//该帐户已经存在，将返回值写入ｌｉｓｔ中
		}
		else
			MessageBox("不存在这样的用户");
	}
}
void CDeletePage::OnEnChangePassEdt()
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
			this->WriteRecordToList(strName);//该帐户已经存在，将返回值写入ｌｉｓｔ中
		}
		else
			{
				MessageBox("不存在这样的帐号，或者帐号与密码有误!",NULL,MB_ICONERROR);
				this->SetDlgItemText(IDC_PASS_EDT,NULL);
			}
	}
}
CString CDeletePage::ReadRecord(void)
{
	CString strSqlText=_T("select * from UserInfo where CardId ='");
	CString strId=_T("");
	this->GetDlgItemText(IDC_CARDID_EDT,strId);
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
	CString strName=_T("");
	if(pUserInfo==NULL)
	{
		this->SetDlgItemText(IDC_PASS_EDT,NULL);
		delete pUserInfo;
		delete ado;
		return NULL;
	}
	else//存在这样的账号，在此设定表格中第二行的姓名
	{
		strName=pUserInfo->UserName;
		m_DeleteList.SetItemText(0,0,pUserInfo->CardId);
		m_DeleteList.SetItemText(0,1,strName);
		m_DeleteList.SetItemText(0,2,pUserInfo->UserId);
		delete pUserInfo;
	}
	return strName;
}

void CDeletePage::WriteRecordToList(CString strName)
{
	//开始判断是定期还是活期
	CString strType=_T("");
	CString strCardID=_T("");
	this->GetDlgItemText(IDC_CARDID_EDT,strCardID);
	CString strCheck=_T("");
	strCheck=(CString)strCardID[0]+(CString)strCardID[1];
	if(strCheck=="01")
		strType="活期";
	else if(strCheck=="02")
		strType="定期";
	//开始定义ado对像
	AdoWorker *ado=NULL;
	ado=new AdoWorker();
	if(strType=="活期")//开始处理活期
	{
		_CurrentInfo *pCurrntInfo=NULL;
		CString strSqlText=_T("select * from CurrentInfo where CardId='");
		CString strId=_T("");
		this->GetDlgItemText(IDC_CARDID_EDT,strId);
		strSqlText=strSqlText+strId+CString("'");
		pCurrntInfo=(_CurrentInfo *)ado->ExecuteSql(strSqlText,2);
		if(pCurrntInfo==NULL)
		{
			MessageBox("数据库中没有此帐号的存款记录！",NULL,MB_ICONQUESTION);
			return;
		}
		else
			{
			 this->WriteCurrentList(pCurrntInfo);
			 delete ado;
			 delete pCurrntInfo;
			}
	}
	else if(strType=="定期")//开始处理定期
		{
			_FixInfo *pFixInfo=NULL;
			CString strSqlText=_T("select * from FixInfo where CardId='");
			CString strId=_T("");
			this->GetDlgItemText(IDC_CARDID_EDT,strId);
			strSqlText=strSqlText+strId+CString("'");
			pFixInfo=(_FixInfo *)ado->ExecuteSql(strSqlText,3);
			if(pFixInfo==NULL)
			{
				MessageBox("数据库中没有此帐号的存款记录！",NULL,MB_ICONQUESTION);
				delete ado;
				return;
			}
			else
			{
				this->WriteFixList(pFixInfo);
				delete ado;
				delete pFixInfo;
			}
		}
		else
			{
				delete ado;
				return;
			}
	
}
int  CDeletePage::CountDay(_CurrentInfo *pCurrentInfo)
{
	CString strDate=_T("");
	CString strLastDate=_T("");
	CString strCurDate=_T("");
	strLastDate=pCurrentInfo->ExchangeDate;
	strCurDate=this->FormatTime();
	int iYear=0;
	int iMonth=0;
	int iDay=0;
	//开始处理日期数据，开始处理日
	int iLast=0;
	int iCur=0;
	int iFlag=0;//标志是否借位
	strDate=(CString)(pCurrentInfo->ExchangeDate[8])+(CString)(pCurrentInfo->ExchangeDate[9]);
	iLast=atoi(strDate.GetBuffer(strDate.GetLength()));
	strDate=_T("");
	strDate=(CString)strCurDate[8]+(CString)strCurDate[9];
	iCur=atoi(strDate.GetBuffer(strDate.GetLength()));
	strDate=_T("");
	if(iCur>=iLast)
		iDay=iCur-iLast;
	else
	{
		iDay=iCur+30-iLast;
		iFlag=1;
	}
	//日处理完毕，开始处理月
	strDate=_T("");
	strDate=(CString)(pCurrentInfo->ExchangeDate[5])+(CString)(pCurrentInfo->ExchangeDate[6]);
	iLast=atoi(strDate.GetBuffer(strDate.GetLength()));
	strDate=_T("");
	strDate=(CString)strCurDate[5]+(CString)strCurDate[6];
	iCur=atoi(strDate.GetBuffer(strDate.GetLength()));
	strDate=_T("");
	if(iCur>=(iLast+iFlag))
	{
		iMonth=iCur-iLast-iFlag;
		iFlag=0;
	}
	else
	{
		iDay=iCur+12-iLast-iFlag;
		iFlag=1;
	}
	//月处理完毕，开始处理年
	strDate=_T("");
	strDate=(CString)(pCurrentInfo->ExchangeDate[0])+(CString)(pCurrentInfo->ExchangeDate[1]+(CString)(pCurrentInfo->ExchangeDate[2])+(CString)(pCurrentInfo->ExchangeDate[3]));
	iLast=atoi(strDate.GetBuffer(strDate.GetLength()));
	strDate=_T("");
	strDate=(CString)strCurDate[0]+(CString)strCurDate[1]+(CString)strCurDate[2]+(CString)strCurDate[3];
	iCur=atoi(strDate.GetBuffer(strDate.GetLength()));
	strDate=_T("");

	iYear=iCur-iLast-iFlag;

	//年处理完毕
	int iDaySum=0;
	iDaySum=iYear*360+iMonth*30+iDay;
	return iDaySum;
}
void   CDeletePage::WriteCurrentList(_CurrentInfo * pCurrentInfo)
{
	//根据查询返回值，开始设置活期时第0行的数据
	CString strTypeChange=_T("");
	strTypeChange.Format("%f",pCurrentInfo->MoneyBalance);
	m_DeleteList.SetItemText(0,3,strTypeChange);
	//开始读取最近的结算日期，算出天数，然后算出先前一笔交易到现在能拥有的利息数
	//设置到第1行的利息栏中
	int iDaySum=0;
	iDaySum=this->CountDay(pCurrentInfo);
	double dRate=0.0;
	dRate=this->GetRate();
	double dAccrualMomey=0.0;
	dAccrualMomey=(double)iDaySum*dRate*(pCurrentInfo->MoneyBalance)+pCurrentInfo->AccrualBalance;//先前到现在的存款能获利息计算完毕
	strTypeChange.Format("%f",dAccrualMomey);
	m_DeleteList.SetItemText(0,4,strTypeChange);
	return ;
}

void   CDeletePage::WriteFixList(_FixInfo * pFixInfo)
{
	CString strTypeChange=_T("");
	strTypeChange.Format("%f",pFixInfo->MoneyBalance);
	m_DeleteList.SetItemText(0,3,strTypeChange);
	//判断是否到期
	if(this->CheckMatured(pFixInfo))
	{
		double dAccrualBalance=0.0;
		dAccrualBalance=pFixInfo->MoneyBalance*pFixInfo->AccrualRate;
		strTypeChange.Format("%f",dAccrualBalance);
		m_DeleteList.SetItemText(0,4,strTypeChange);
	}
	else
	{
		_CurrentInfo *pCurrentInfo=NULL;
		pCurrentInfo=new _CurrentInfo;
		pCurrentInfo->ExchangeDate=pFixInfo->ExchangeDate;
		int iDay=0;
		iDay=this->CountDay(pCurrentInfo);
		delete pCurrentInfo;
		double dAccrualBalance=0.0;
		double dAccrualRate=0.0;
		dAccrualRate=this->GetRate();
		dAccrualBalance=pFixInfo->MoneyBalance*dAccrualRate*iDay;
		strTypeChange.Format("%f",dAccrualBalance);
		m_DeleteList.SetItemText(0,4,strTypeChange);
	}
}
double   CDeletePage::GetRate(void)
{
	double dAccrualMomery=0.00005;
	return dAccrualMomery;
}
BOOL  CDeletePage::CheckMatured(_FixInfo * pFixInfo)
{
	return 0;
}
CString CDeletePage::FormatTime()
{
	CString strTPDate =_T("");
	CString TempDate =_T("") ;
	COleDateTime CurTime;
	CurTime = COleDateTime::GetCurrentTime();
	int Cur_Year = 0;
	int Cur_Month = 0;
	int Cur_Day  = 0 ;
	Cur_Year = CurTime.GetYear();
	Cur_Month = CurTime.GetMonth();
	Cur_Day = CurTime.GetDay();
	TempDate.Format("%d",Cur_Year);
	strTPDate = TempDate;
	strTPDate +="-";
	TempDate.Format("%d",Cur_Month);
	if(Cur_Month<10)
		strTPDate +="0";
	strTPDate += TempDate;
	strTPDate +="-";
	TempDate.Format("%d",Cur_Day);
	if(Cur_Day<10)
		strTPDate +="0";
	strTPDate += TempDate;
	return strTPDate;
}
void CDeletePage::EmptyTable()
{
	this->SetDlgItemText(IDC_CARDID_EDT,NULL);
	this->SetDlgItemText(IDC_PASS_EDT,NULL);
	m_DeleteList.DeleteAllItems();
	m_DeleteList.InsertItem(0,NULL);

}
void CDeletePage::OnBnClickedCancelBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	this->EmptyTable();
}

void CDeletePage::OnBnClickedDeleteBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	this->DeleteSql();
	CPrintDlg *pPrintDlg=NULL;
	pPrintDlg=new CPrintDlg();
	if(pPrintDlg->DoModal()==IDOK)
	{
		this->PrintTable();//打印数据表

	}
	delete pPrintDlg;
	MessageBox("用户注销成功！",NULL,MB_ICONINFORMATION);
	this->EmptyTable();
}
void CDeletePage::DeleteSql(void)
{
	CString strType=_T("");
	CString strCardID=_T("");
	this->GetDlgItemText(IDC_CARDID_EDT,strCardID);
	CString strCheck=_T("");
	strCheck=(CString)strCardID[0]+(CString)strCardID[1];
	if(strCheck=="01")
		strType="活期";
	else if(strCheck=="02")
		strType="定期";
	//开始定义ado对像
	AdoWorker *ado=NULL;
	ado=new AdoWorker();
	//开始处理注册信息列表
	CString strSql=_T("delete from UserInfo where CardId = '");
	strSql=strSql+strCardID+CString("'");
	ado->ExecuteSql(strSql);
	if(strType=="活期")//开始处理活期
	{
		strSql=_T("delete from CurrentInfo where CardId = '");
		strSql=strSql+strCardID+CString("'");
		ado->ExecuteSql(strSql);
	}
	if(strType=="定期")//开始处理定期
	{
		strSql=_T("delete from FixInfo where CardId = '");
		strSql=strSql+strCardID+CString("'");
		ado->ExecuteSql(strSql);
	}
	//开始处理记录表
	strSql=_T("delete from RecordInfo where CardId = '");
	strSql=strSql+strCardID+CString("'");
	ado->ExecuteSql(strSql);
	delete ado;
}
void CDeletePage::PrintTable()
{

}