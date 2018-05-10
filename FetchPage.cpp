//Download by http://www.NewXing.com
// FetchPage.cpp : 实现文件
//

#include "stdafx.h"
#include "BankManager.h"
#include "FetchPage.h"
#include ".\fetchpage.h"
#include "_StructDefine.h"
#include "AdoWorker.h"
#include "PrintDlg.h"

// CFetchPage 对话框

IMPLEMENT_DYNAMIC(CFetchPage, CDialog)
CFetchPage::CFetchPage(CWnd* pParent /*=NULL*/)
	: CDialog(CFetchPage::IDD, pParent)
{
}

CFetchPage::~CFetchPage()
{
}

void CFetchPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FETCH_STC, m_FetchStc);
	DDX_Control(pDX, IDC_MONEY_EDT, m_MoneyEdt);
	DDX_Control(pDX, IDC_FETCH_LIST, m_FetchList);
	DDX_Control(pDX, IDC_CARDID_EDT, m_CardIdEdt);
	DDX_Control(pDX, IDC_PASS_EDT, m_PassKeyEdt);
}


BEGIN_MESSAGE_MAP(CFetchPage, CDialog)
	ON_EN_CHANGE(IDC_CARDID_EDT, OnEnChangeCardidEdt)
	ON_EN_CHANGE(IDC_MONEY_EDT, OnEnChangeMoneyEdt)
	ON_EN_CHANGE(IDC_PASS_EDT, OnEnChangePassEdt)
	ON_BN_CLICKED(IDC_FETCH_BTN, OnBnClickedFetchBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
END_MESSAGE_MAP()


// CFetchPage 消息处理程序

void CFetchPage::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
}

void CFetchPage::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
}

BOOL CFetchPage::OnInitDialog()
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
	//////////////////////////////////////////主窗口设置完毕
	m_CardIdEdt.SetLimitText(12);
	m_PassKeyEdt.SetLimitText(8);
	m_MoneyEdt.ShowWindow(SW_HIDE);
	//初始化列表框
	this->OnInitList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CFetchPage::OnInitList(void)
{
	m_FetchList.InsertColumn(0,"银行帐号",LVCFMT_LEFT,100);
	m_FetchList.InsertColumn(1,"姓名",LVCFMT_LEFT,60);
	m_FetchList.InsertColumn(2,"金额(元)",LVCFMT_LEFT,60);
	m_FetchList.InsertColumn(3,"利息(元)",LVCFMT_LEFT,60);
	m_FetchList.InsertColumn(4,"取款类型",LVCFMT_LEFT,60);
	m_FetchList.InsertColumn(5,"交易时间",LVCFMT_LEFT,75);
	m_FetchList.InsertColumn(6,"到期时间",LVCFMT_LEFT,75);
	m_FetchList.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_FetchList.InsertItem(0,NULL);
	m_FetchList.InsertItem(1,NULL);
	CString strCurTime=_T("");
	strCurTime=this->FormatTime();
	//m_FetchList.SetItemText(0,4,strCurTime);
	m_FetchList.SetItemText(1,5,strCurTime);
}
CString CFetchPage::FormatTime()
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
void CFetchPage::OnEnChangeCardidEdt()
{
	CString strCardID=_T("");
	this->GetDlgItemText(IDC_CARDID_EDT,strCardID);
    m_FetchList.SetItemText(1,0,strCardID);//设置帐号栏
	////在此中要判断输入数据的位数，若数据已满则自动连接数据库，查询此人帐号和以前的余额，显示在表格中
	////定活期选择和此两者控制何时要自动连接数据库查询
	int iStr=0;
	iStr=strCardID.GetLength();
	if(iStr==2)//自动检查帐号是定期还是活期
	{
		if(strCardID=="01")//活期
		{
			m_FetchList.SetItemText(1,4,"活期");
			m_MoneyEdt.ShowWindow(SW_SHOW);
		}
		else if(strCardID=="02")//定期
		{
			m_FetchList.SetItemText(1,4,"定期");
			m_MoneyEdt.ShowWindow(SW_HIDE);
		}
		else
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
		this->ReadRecord();
		
}

void CFetchPage::OnEnChangeMoneyEdt()
{
	CString strMoney=_T("");
	this->GetDlgItemText(IDC_MONEY_EDT,strMoney);
	m_FetchList.SetItemText(1,2,strMoney);//设置帐号栏
}


void CFetchPage::OnEnChangePassEdt()
{
	CString strCardID=_T("");
	this->GetDlgItemText(IDC_CARDID_EDT,strCardID);
	m_FetchList.SetItemText(1,0,strCardID);//设置帐号栏
	////在此中要判断输入数据的位数，若数据已满则自动连接数据库，查询此人帐号和以前的余额，显示在表格中
	////定活期选择和此两者控制何时要自动连接数据库查询
	int iStr=0;
	iStr=strCardID.GetLength();
	if(iStr==2)//自动检查帐号是定期还是活期
	{
		if(strCardID=="01")//活期
		{
			m_FetchList.SetItemText(1,3,"活期");
		}
		else if(strCardID=="02")//定期
		{
			m_FetchList.SetItemText(1,3,"定期");
		}
		else
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
		this->ReadRecord();
}

void CFetchPage::ReadRecord(void)//根据输入的账号和密码查询数据库，得到姓名，判断该帐号是否存在
{
	CString strSqlText=_T("select UserName from UserInfo where CardId ='");
	CString strId=_T("");
	strId=m_FetchList.GetItemText(1,0);
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
		MessageBox(" 不存在该帐号或者请您检查帐号和密码的正确性！",NULL,MB_ICONERROR);
		this->SetDlgItemText(IDC_CARDID_EDT,NULL);
		this->SetDlgItemText(IDC_MONEY_EDT,NULL);
		this->SetDlgItemText(IDC_PASS_EDT,NULL);
		delete pUserNameInfo;
		delete ado;
		return ;
	}
	else//存在这样的账号，在此设定表格中第二行的姓名
	{
		strName=pUserNameInfo->UserName;
		m_FetchList.SetItemText(1,1,strName);
		delete pUserNameInfo;
	}
	//到此此账号已经注册，检查是活期还是定期
	//如果是活期，查找到最后一次交易的记录，若是定期，
	//在定期记录表中查找，如果是返回为NULL才能继续办理，
	//如果不是，表明该账号已经有存款，不能再继续存放定期存款
	CString strCheckType=_T("");
	//this->GetDlgItemText(IDC_TYPE_COMB,strCheckType);
	//根据帐号查找判断是定期还是活期
	CString strCardID=_T("");
	this->GetDlgItemText(IDC_CARDID_EDT,strCardID);
	CString strCheck=_T("");
	strCheck=(CString)strCardID[0]+(CString)strCardID[1];
	if(strCheck=="01")
		strCheckType="活期";
	else if(strCheck=="02")
			strCheckType="定期";
		else
			{
				MessageBox("输入帐号有误，请重新输入！",NULL,MB_ICONERROR);
				return;
			}
	if(strCheckType=="活期")//开始处理活期
	{
		strSqlText=_T("select * from CurrentInfo where CardId ='");
		CString strId=_T("");
		strId=m_FetchList.GetItemText(1,0);
		strSqlText=strSqlText+strId+CString("'");
		_CurrentInfo *pCurrentInfo=NULL;
		pCurrentInfo=(_CurrentInfo *)ado->ExecuteSql(strSqlText,2);
		//首先将利息置0
		m_FetchList.SetItemText(1,3,NULL);
		if(pCurrentInfo!=NULL)
			this->WriteCurrentList(pCurrentInfo);
		else
			{
				MessageBox("这是一个新帐号,无钱可取！",NULL,MB_ICONASTERISK);
				this->EmptyTable();
				delete ado;
				return;
			}
		delete pCurrentInfo;
	}
	else//开始处理定期
	{
		strSqlText=_T("select * from FixInfo where CardId ='");
		CString strId=_T("");
		strId=m_FetchList.GetItemText(1,0);
		strSqlText=strSqlText+strId+CString("'");
		_FixInfo *pFixInfo=NULL;
		pFixInfo=(_FixInfo *)ado->ExecuteSql(strSqlText,3);
		if(pFixInfo!=NULL)
			this->WriteFixList(pFixInfo);			
		else
			{
				MessageBox("这是一个新帐号,无钱可取！",NULL,MB_ICONASTERISK);
				this->EmptyTable();
				delete ado;
				return;
			}
		delete pFixInfo;;
	}
	delete ado;
	return ;
}
void  CFetchPage::WriteCurrentList(_CurrentInfo * pCurrentInfo)
{
	//根据查询返回值，开始设置活期时第0行的数据
	m_FetchList.SetItemText(0,0,pCurrentInfo->CardId);
	CString strUserName=_T("");
	strUserName=m_FetchList.GetItemText(1,1);
	m_FetchList.SetItemText(0,1,strUserName);
	CString strTypeChange=_T("");
	strTypeChange.Format("%f",pCurrentInfo->MoneyBalance);
	m_FetchList.SetItemText(0,2,strTypeChange);
	strTypeChange.Format("%f",pCurrentInfo->AccrualBalance);
	m_FetchList.SetItemText(0,3,strTypeChange);
	m_FetchList.SetItemText(0,4,"活期");
	m_FetchList.SetItemText(0,5,pCurrentInfo->ExchangeDate);
	//开始读取最近的结算日期，算出天数，然后算出先前一笔交易到现在能拥有的利息数
	//设置到第1行的利息栏中
	int iDaySum=0;
	iDaySum=this->CountDay(pCurrentInfo);
	double dRate=0.0;
	dRate=this->GetRate();
	double dAccrualMomey=0.0;
	dAccrualMomey=(double)iDaySum*dRate*(pCurrentInfo->MoneyBalance)+pCurrentInfo->AccrualBalance;//先前到现在的存款能获利息计算完毕
	strTypeChange.Format("%f",dAccrualMomey);
	m_FetchList.SetItemText(1,3,strTypeChange);
}

void  CFetchPage::WriteFixList(_FixInfo * pFixInfo)
{
	m_FetchList.SetItemText(0,0,pFixInfo->CardId);
	m_FetchList.SetItemText(1,0,pFixInfo->CardId);
	//
	CString strUserName=_T("");
	strUserName=m_FetchList.GetItemText(1,1);
	m_FetchList.SetItemText(0,1,strUserName);
	m_FetchList.SetItemText(1,1,strUserName);
	//
	CString strTypeChange=_T("");
	strTypeChange.Format("%f",pFixInfo->MoneyBalance);
	m_FetchList.SetItemText(0,2,strTypeChange);
	m_FetchList.SetItemText(1,2,strTypeChange);
	//
	//strTypeChange.Format("%f",pFixInfo->AccrualBalance);
	m_FetchList.SetItemText(0,3,NULL);
	//判断是否到期
	if(this->CheckMatured(pFixInfo))
	{
		double dAccrualBalance=0.0;
		dAccrualBalance=pFixInfo->MoneyBalance*pFixInfo->AccrualRate;
		strTypeChange.Format("%f",dAccrualBalance);
		m_FetchList.SetItemText(1,3,strTypeChange);
		m_FetchList.SetItemText(1,4,"定期");
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
		m_FetchList.SetItemText(1,3,strTypeChange);
		m_FetchList.SetItemText(1,4,"活期");
	}
	//
	m_FetchList.SetItemText(0,5,pFixInfo->ExchangeDate);
	//
	m_FetchList.SetItemText(0,6,pFixInfo->MatureDate);
	//
	//开始写第二行的信息

}

// 计算上次交易到现在所经过的天数，每月按30天计算，每年12个月
int  CFetchPage::CountDay(_CurrentInfo *pCurrentInfo)
{
	CString strDate=_T("");
	CString strLastDate=_T("");
	CString strCurDate=_T("");
	strLastDate=pCurrentInfo->ExchangeDate;
	strCurDate=m_FetchList.GetItemText(1,5);
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

double  CFetchPage::GetRate(void)
{
	double dAccrualMomery=0.00005;
	return dAccrualMomery;
}

bool  CFetchPage::CheckCurrent(void)
{
	//判断此次输入金额是否为空,姓名是否为空,若有一个是空,返回
	CString strCheck=_T("");
	strCheck=_T("");
	strCheck=m_FetchList.GetItemText(1,0);
	if(strCheck=="")
	{
		MessageBox("未输入帐号,重新输入!",NULL,MB_ICONERROR);
		return FALSE;
	}
	strCheck=m_FetchList.GetItemText(1,1);
	if(strCheck=="")
	{
		MessageBox("此帐号无效,重新输入!",NULL,MB_ICONERROR);
		return FALSE;
	}
	strCheck=m_FetchList.GetItemText(1,2);
	if(strCheck=="")
	{
		MessageBox("没有输入此次要取出的金额,请重新输入!",NULL,MB_ICONERROR);
		return FALSE;
	}
	CString strCheck2=_T("");
	strCheck=m_FetchList.GetItemText(0,2);
	strCheck=m_FetchList.GetItemText(1,2);
	double dPre=0.0;
	double dCur=0.0;
	dPre=atof(strCheck.GetBuffer(strCheck.GetLength()));
	dCur=atof(strCheck2.GetBuffer(strCheck2.GetLength()));
	if(dPre<dCur)
	{
		MessageBox("本帐号不可透支，请重新输入金额！",NULL,MB_ICONERROR);
		return FALSE;
	}
	return TRUE;
}

bool  CFetchPage::CheckFix(void)
{
	CString strCheck=_T("");
	strCheck=m_FetchList.GetItemText(1,0);
	if(strCheck=="")
	{
		MessageBox("未输入帐号,重新输入!",NULL,MB_ICONERROR);
		return FALSE;
	}
	strCheck=m_FetchList.GetItemText(1,1);
	if(strCheck=="")
	{
		MessageBox("此帐号无效,重新输入!",NULL,MB_ICONERROR);
		return FALSE;
	}
	return TRUE;
}

BOOL  CFetchPage::WriteFixSql(void)
{
	CString strSqlText2=_T("insert into RecordInfo(CardId,MoneyBalance,ExchangeDate,AccrualBalance,MoneyType,InOut) values ('");
	CString strUserInput=_T("");
	CString strSign=_T("','");
	CString strDeleteSQl=_T("delete from FixInfo where CardId='");
	this->GetDlgItemText(IDC_CARDID_EDT,strUserInput);
	strDeleteSQl=strDeleteSQl+strUserInput+CString("'");
	/////////////////////////////////从表格中读取数
	strUserInput=m_FetchList.GetItemText(1,0);//CardId
	strSqlText2=strSqlText2+strUserInput+strSign;
	//
	strUserInput=m_FetchList.GetItemText(1,2);//MoneyBalance
	strSqlText2=strSqlText2+strUserInput+strSign;
	//
	strUserInput=m_FetchList.GetItemText(1,5);//ExchangeDate
	strSqlText2=strSqlText2+strUserInput+strSign;
	//
	strUserInput=m_FetchList.GetItemText(1,3); //AccrualBalance
	strSqlText2=strSqlText2+strUserInput+strSign;
	//
	strUserInput=m_FetchList.GetItemText(1,4);//MoneyType
	strSqlText2=strSqlText2+strUserInput+CString("','取')"); 
	//
	AdoWorker *ado=NULL;
	ado=new AdoWorker();
	BOOL bExec=FALSE;
	//先删除原有数据
	ado->ExecuteSql(strDeleteSQl);//删除定期存款中的该项数据
	bExec=ado->ExecuteSql(strSqlText2);//将数据插入到了record表格中
	delete ado;
	return bExec;
}

void  CFetchPage::EmptyTable(void)
{
	m_FetchList.DeleteAllItems();
	m_FetchList.InsertItem(0,NULL);
	m_FetchList.InsertItem(1,NULL);
	this->SetDlgItemText(IDC_CARDID_EDT,NULL);
	this->SetDlgItemText(IDC_MONEY_EDT,NULL);
	this->SetDlgItemText(IDC_PASS_EDT,NULL);
	CString strCurTime=_T("");
	strCurTime=this->FormatTime();
	m_FetchList.SetItemText(1,5,strCurTime);
	m_MoneyEdt.ShowWindow(SW_HIDE);
}
BOOL  CFetchPage::WriteCurrentSql(void)
{
	//若是表格中存在了记录，先删除
	CString strSqlText=_T("insert into CurrentInfo(CardId,MoneyBalance,ExchangeDate,AccrualBalance) values ('");
	CString strSqlText2=_T("insert into RecordInfo(CardId,MoneyBalance,ExchangeDate,AccrualBalance,InOut,MoneyType) values ('");
	CString strUserInput=_T("");
	CString strSign=_T("','");
	CString strDeleteSQl=_T("delete from CurrentInfo where CardId='");
	this->GetDlgItemText(IDC_CARDID_EDT,strUserInput);
	strDeleteSQl=strDeleteSQl+strUserInput+CString("'");
	/////////////////////////////////从表格中读取数
	strUserInput=m_FetchList.GetItemText(1,0);
	strSqlText=strSqlText+strUserInput+strSign;
	strSqlText2=strSqlText2+strUserInput+strSign;
	//开始相加上下两个表格中的金额结算
	double dCur=0.0;
	strUserInput=m_FetchList.GetItemText(1,2);
	dCur=atof(strUserInput.GetBuffer(strUserInput.GetLength()));
	double dPre=0.0;
	strUserInput=m_FetchList.GetItemText(0,2);
	dPre=atof(strUserInput.GetBuffer(strUserInput.GetLength()));
	strUserInput.Format("%f",dCur);
	strSqlText2=strSqlText2+strUserInput+strSign;

	dCur=dPre-dCur;
	if(dCur<0)
	{
		MessageBox("不能超支，取款申请不成功！",NULL,MB_ICONERROR);
		return FALSE;
	}
	strUserInput.Format("%f",dCur);

	strSqlText=strSqlText+strUserInput+strSign;
	//
	strUserInput=m_FetchList.GetItemText(1,5);
	strSqlText=strSqlText+strUserInput+strSign;
	strSqlText2=strSqlText2+strUserInput+strSign;
	//开始相加上下两个表格中的利息结算
	strUserInput=m_FetchList.GetItemText(1,3);
	if(strUserInput=="")
		strUserInput=_T("0");
	strSqlText=strSqlText+strUserInput+CString("')");
	strSqlText2=strSqlText2+strUserInput+CString("','取','活期')");
	AdoWorker *ado=NULL;
	ado=new AdoWorker();
	BOOL bExec=FALSE;
	//先删除原有数据
	ado->ExecuteSql(strDeleteSQl);
	ado->ExecuteSql(strSqlText2);
	bExec=ado->ExecuteSql(strSqlText);//将数据插入到了表格中
	delete ado;
	return bExec;
}

void CFetchPage::OnBnClickedFetchBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//开始判断是定期还是活期，根据不同的种类将有不同的数据处理方式
	CString strType=_T("");
	CString strCardID=_T("");
	this->GetDlgItemText(IDC_CARDID_EDT,strCardID);
	CString strCheck=_T("");
	strCheck=(CString)strCardID[0]+(CString)strCardID[1];
	if(strCheck=="01")
		strType="活期";
	else if(strCheck=="02")
		strType=="定期";
	else
	{
		MessageBox("输入帐号有误，请重新输入！",NULL,MB_ICONERROR);
		return;
	}
	if(strType=="活期")//活期处理
	{
		if(this->CheckCurrent())//返回真值,开始组织SQL语句,写数据库
		{
			if(this->WriteCurrentSql())//写数据库
			{
				CPrintDlg *pPrintDlg=NULL;
				pPrintDlg=new CPrintDlg();
				if(pPrintDlg->DoModal()==IDOK)
				{
					this->PrintTable();//打印数据表

				}
				delete pPrintDlg;
				MessageBox("活期期取款申请成功！",NULL,MB_ICONASTERISK);
			}
		}
		else
			return;
	}
	else//定期处理
	{
		if(this->CheckFix())//返回真值,开始组织SQL语句,写数据库
		{
			if(this->WriteFixSql())//写数据库
			{
				CPrintDlg *pPrintDlg=NULL;
				pPrintDlg=new CPrintDlg();
				if(pPrintDlg->DoModal()==IDOK)
				{
					this->PrintTable();//打印数据表
				}
				delete pPrintDlg;
				MessageBox("定期取款申请成功！",NULL,MB_ICONASTERISK);
			}
		}
		else
		{
			return;
		}
	}
	this->EmptyTable();
}

BOOL CFetchPage::CheckMatured(_FixInfo * pFixInfo)//开始判断是否到期
{
	COleDateTime CurTime;
	CurTime = COleDateTime::GetCurrentTime();
	int Cur_Year = 0;
	int Cur_Month = 0;
	int Cur_Day  = 0 ;
	Cur_Year = CurTime.GetYear();
	Cur_Month = CurTime.GetMonth();
	Cur_Day = CurTime.GetDay();
	//
	CString strDate=_T("");
	int iYear=0;
	int iMonth=0;
	int iDay=0;
	//得到日
	strDate=(CString)(pFixInfo->MatureDate[8])+(CString)(pFixInfo->MatureDate[9]);
	iDay=atoi(strDate.GetBuffer(strDate.GetLength()));
	strDate=_T("");
	//日处理完毕，开始处理月
	strDate=_T("");
	strDate=(CString)(pFixInfo->MatureDate[5])+(CString)(pFixInfo->MatureDate[6]);
	iMonth=atoi(strDate.GetBuffer(strDate.GetLength()));
	//月处理完毕，开始处理年
	strDate=_T("");
	strDate=(CString)(pFixInfo->MatureDate[0])+(CString)(pFixInfo->MatureDate[1]+(CString)(pFixInfo->MatureDate[2])+(CString)(pFixInfo->MatureDate[3]));
	iYear=atoi(strDate.GetBuffer(strDate.GetLength()));
	//所以得日期都已得到，开始判断是否到期
	if(Cur_Year>iYear)//年号不同，就绝对能确定已经到期
		return TRUE;
	else if(Cur_Year==iYear)//年号相等
	{
		if(Cur_Month>iMonth)//月不同
			return TRUE;
		else if(Cur_Month==iMonth)
				{
					if(Cur_Day>=iDay)
						return TRUE;
					else
						return FALSE;
				}
				else
					return FALSE;
	}
		 else
			 return FALSE;
}

void CFetchPage::OnBnClickedCancelBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	this->EmptyTable();
}
void  CFetchPage::PrintTable(void)
{
}