//Download by http://www.NewXing.com
// SavingPage.cpp : 实现文件
//

#include "stdafx.h"
#include "BankManager.h"
#include "SavingPage.h"
#include ".\savingpage.h"
#include "AdoWorker.h"
#include "_StructDefine.h"
#include "PrintDlg.h"

// CSavingPage 对话框

IMPLEMENT_DYNAMIC(CSavingPage, CDialog)
CSavingPage::CSavingPage(CWnd* pParent /*=NULL*/)
	: CDialog(CSavingPage::IDD, pParent)
{
}

CSavingPage::~CSavingPage()
{
}

void CSavingPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SAVING_LIST, m_SavingList);
	DDX_Control(pDX, IDC_TYPE_COMB, m_TypeComb);
	DDX_Control(pDX, IDC_TIME_STC, m_DingStc);
	DDX_Control(pDX, IDC_TIME_COMB, m_TimeComB);
	DDX_Control(pDX, IDC_CARDID_EDT, m_CardIdEdt);
	DDX_Control(pDX, IDC_RATE_EDT, m_RateEdt);
}


BEGIN_MESSAGE_MAP(CSavingPage, CDialog)
	ON_EN_CHANGE(IDC_CARDID_EDT, OnEnChangeCardidEdt)
	ON_CBN_SELCHANGE(IDC_TYPE_COMB, OnCbnSelchangeTypeComb)
	ON_EN_CHANGE(IDC_MONEY_EDT, OnEnChangeMoneyEdt)
	ON_CBN_SELCHANGE(IDC_TIME_COMB, OnCbnSelchangeTimeComb)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SAVING_BTN, OnBnClickedSavingBtn)
END_MESSAGE_MAP()


// CSavingPage 消息处理程序

BOOL CSavingPage::OnInitDialog()
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
	///////////////////////////////////初始化定活期组合框
	CComboBox * pBo=NULL;
	pBo=(CComboBox*)this->GetDlgItem(IDC_TYPE_COMB);
	pBo->AddString("活期");
	pBo->AddString("定期");
	pBo->SetCurSel(0);
	this->OnCbnSelchangeTypeComb();
	//////////////////////////////////初始化时间组合框
	pBo=(CComboBox*)this->GetDlgItem(IDC_TIME_COMB);
	pBo->AddString("半年");
	pBo->AddString("一年");
	pBo->AddString("一年半");
	pBo->AddString("两年");
	pBo->SetCurSel(0);
	////////////////////////////////组合框初始化结束
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSavingPage::OnEnChangeCardidEdt()
{
	CString strCardID=_T("");
	this->GetDlgItemText(IDC_CARDID_EDT,strCardID);
	m_SavingList.SetItemText(1,0,strCardID);//设置帐号栏
	////在此中要判断输入数据的位数，若数据已满则自动连接数据库，查询此人帐号和以前的余额，显示在表格中
	////定活期选择和此两者控制何时要自动连接数据库查询
	int iStr=0;
	iStr=strCardID.GetLength();
	if(iStr==2)//自动检查帐号是定期还是活期
	{
		if(strCardID=="01")//活期
		{
			CComboBox * pBo=NULL;
			pBo=(CComboBox*)this->GetDlgItem(IDC_TYPE_COMB);
			pBo->SetCurSel(0);
			this->OnCbnSelchangeTypeComb();
		}
		else if(strCardID=="02")
		{
			CComboBox * pBo=NULL;
			pBo=(CComboBox*)this->GetDlgItem(IDC_TYPE_COMB);
			pBo->SetCurSel(1);
			this->OnCbnSelchangeTypeComb();
		}
		     else
			 {
				 MessageBox("不存在这样类型的账号,请重新输入！",NULL,MB_ICONERROR);
				 this->SetDlgItemText(IDC_CARDID_EDT,NULL);
			 }
	}
	if(iStr==12)
		this->SureIdExist();
}

void CSavingPage::OnEnChangeMoneyEdt()
{
	CString strMoney=_T("");
	this->GetDlgItemText(IDC_MONEY_EDT,strMoney);
	m_SavingList.SetItemText(1,2,strMoney);//设置金额栏

}

void CSavingPage::OnCbnSelchangeTypeComb()
{
	// TODO: 在此添加控件通知处理程序代码
	///////////////////////////////////////设置表格今天的时间，方便后面的初始化
	CString strCurTime=_T("");
	strCurTime=this->FormatTime(0);
	m_SavingList.SetItemText(1,5,strCurTime);
   ////////////////////////////////////////定活设置
	CString strType=_T("");
	this->GetDlgItemText(IDC_TYPE_COMB,strType);
	m_SavingList.SetItemText(1,4,strType);//设置活期或者定期
	if(strType=="定期")
	{
		m_DingStc.ShowWindow(SW_SHOW);
		m_TimeComB.ShowWindow(SW_SHOW);
		this->OnCbnSelchangeTimeComb();
	}
	else
	{
		m_DingStc.ShowWindow(SW_HIDE);
		m_TimeComB.ShowWindow(SW_HIDE);
		this->SetDlgItemText(IDC_RATE_EDT,"0.00005");
		CString strRate=_T("");
		this->GetDlgItemText(IDC_RATE_EDT,strRate);
		m_SavingList.SetItemText(1,6,NULL);//活期是设置到期时间为空
	}
}

void CSavingPage::OnInitList(void)
{
	m_SavingList.InsertColumn(0,"银行帐号",LVCFMT_LEFT,100);
	m_SavingList.InsertColumn(1,"姓名",LVCFMT_LEFT,60);
	m_SavingList.InsertColumn(2,"金额(元)",LVCFMT_LEFT,60);
	m_SavingList.InsertColumn(3,"利息结算(元)",LVCFMT_LEFT,80);
	m_SavingList.InsertColumn(4,"存款类型",LVCFMT_LEFT,60);
	m_SavingList.InsertColumn(5,"交易时间",LVCFMT_LEFT,75);
	m_SavingList.InsertColumn(6,"到期时间",LVCFMT_LEFT,75);
	m_SavingList.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_SavingList.InsertItem(0,NULL);
	m_SavingList.InsertItem(1,NULL);
	return ;
}
CString CSavingPage::FormatTime(int iFlag)
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
	if(iFlag)//此时是求取到期日期
	{
	  CString strTimeCom=_T("");
	  this->GetDlgItemText(IDC_TIME_COMB,strTimeCom);
	  if(strTimeCom=="半年")
		  Cur_Month+=6;
	  if(strTimeCom=="一年")
		  Cur_Month+=12;
	  if(strTimeCom=="一年半")
		  Cur_Month+=18;
	  if(strTimeCom=="两年")
		  Cur_Month+=24;
      Cur_Year+=Cur_Month/12;
	  Cur_Month=Cur_Month%12;
	}
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

void CSavingPage::OnCbnSelchangeTimeComb()
{
	// TODO: 在此添加控件通知处理程序代码
	//开始填写利率
	CString strTimeCom=_T("");
	this->GetDlgItemText(IDC_TIME_COMB,strTimeCom);
	if(strTimeCom=="半年")
		this->SetDlgItemText(IDC_RATE_EDT,"0.01");
	if(strTimeCom=="一年")
		this->SetDlgItemText(IDC_RATE_EDT,"0.03");
	if(strTimeCom=="一年半")
		this->SetDlgItemText(IDC_RATE_EDT,"0.05");
	if(strTimeCom=="两年")
		this->SetDlgItemText(IDC_RATE_EDT,"0.07");
	CString strRate=_T("");
	this->GetDlgItemText(IDC_RATE_EDT,strRate);
	//m_SavingList.SetItemText(1,3,strRate);
	///////////////////////////////开始填写时间
	CString strTime=_T("");
	strTime=this->FormatTime(1);
	m_SavingList.SetItemText(1,6,strTime);
}
void CSavingPage::OnBnClickedCancel()
{
}
void CSavingPage::OnBnClickedOk()
{
}
void CSavingPage::SureIdExist(void)//根据输入的账号和密码查询数据库，得到姓名，判断该帐号是否存在
{
	CString strSqlText=_T("select UserName from UserInfo where CardId ='");
	CString strId=_T("");
	strId=m_SavingList.GetItemText(1,0);
	strSqlText=strSqlText+strId+CString("'");
	//////////////////////////////////创建SQL语句执行类实例
	AdoWorker *ado=NULL;
	_UserNameInfo *pUserNameInfo=NULL;
	ado=new AdoWorker();
	pUserNameInfo=(_UserNameInfo *)ado->ExecuteSql(strSqlText,5);
	CString strName=_T("");
	if(pUserNameInfo==NULL)
	{
		MessageBox("没有这样的账号，请先注册或者检查账号的正确性！",NULL,MB_ICONERROR);
		this->SetDlgItemText(IDC_CARDID_EDT,NULL);
		this->SetDlgItemText(IDC_MONEY_EDT,NULL);
		delete pUserNameInfo;
		delete ado;
		return ;
	}
	else//存在这样的账号，在此设定表格中第二行的姓名
	{
		strName=pUserNameInfo->UserName;
		m_SavingList.SetItemText(1,1,strName);
		delete pUserNameInfo;
	}
	//到此此账号已经注册，检查是活期还是定期
	//如果是活期，查找到最后一次交易的记录，若是定期，
	//在定期记录表中查找，如果是返回为NULL才能继续办理，
	//如果不是，表明该账号已经有存款，不能再继续存放定期存款
	CString strCheckType=_T("");
	this->GetDlgItemText(IDC_TYPE_COMB,strCheckType);
	if(strCheckType=="活期")//开始处理活期
	{
		strSqlText=_T("select * from CurrentInfo where CardId ='");
		CString strId=_T("");
		strId=m_SavingList.GetItemText(1,0);
		strSqlText=strSqlText+strId+CString("'");
		_CurrentInfo *pCurrentInfo=NULL;
		pCurrentInfo=(_CurrentInfo *)ado->ExecuteSql(strSqlText,2);
		//首先将利息置0
		m_SavingList.SetItemText(1,3,NULL);
		if(pCurrentInfo!=NULL)
			this->WriteCurrentList(pCurrentInfo);
		else
			MessageBox("这是一个新帐号！",NULL,MB_ICONASTERISK);
		delete pCurrentInfo;
	}
	else//开始处理定期
	{
		strSqlText=_T("select * from FixInfo where CardId ='");
		CString strId=_T("");
		strId=m_SavingList.GetItemText(1,0);
		strSqlText=strSqlText+strId+CString("'");
		_FixInfo *pFixInfo=NULL;
		pFixInfo=(_FixInfo *)ado->ExecuteSql(strSqlText,3);
		if(pFixInfo!=NULL)
			{
				this->WriteFixList(pFixInfo);
				MessageBox("此帐号已经有定期存款，不能再用此帐号存款!",NULL,MB_ICONERROR);
				CPrintDlg *pPrintDlg=NULL;
				pPrintDlg=new CPrintDlg();
				if(pPrintDlg->DoModal()==IDOK)
				{
					this->PrintTable();//打印数据表

				}
				delete pPrintDlg;
				this->EmptyTable();
			}
		else
			MessageBox("此定期帐号中无存款，可存！",NULL,MB_ICONASTERISK);
		delete pFixInfo;;
	}
	delete ado;
	return ;
}
void CSavingPage::WriteCurrentList(_CurrentInfo * pCurrentInfo)
{
	//根据查询返回值，开始设置活期时第0行的数据
	m_SavingList.SetItemText(0,0,pCurrentInfo->CardId);
	CString strUserName=_T("");
	strUserName=m_SavingList.GetItemText(1,1);
	m_SavingList.SetItemText(0,1,strUserName);
	CString strTypeChange=_T("");
	strTypeChange.Format("%f",pCurrentInfo->MoneyBalance);
	m_SavingList.SetItemText(0,2,strTypeChange);
	strTypeChange.Format("%f",pCurrentInfo->AccrualBalance);
	m_SavingList.SetItemText(0,3,strTypeChange);
	m_SavingList.SetItemText(0,4,"活期");
	m_SavingList.SetItemText(0,5,pCurrentInfo->ExchangeDate);
	//开始读取最近的结算日期，算出天数，然后算出先前一笔交易到现在能拥有的利息数
	//设置到第1行的利息栏中
	int iDaySum=0;
	iDaySum=this->CountDay(pCurrentInfo);
	double dRate=0.0;
	dRate=this->GetRate();
	double dAccrualMomey=0.0;
	dAccrualMomey=(double)iDaySum*dRate*(pCurrentInfo->MoneyBalance)+pCurrentInfo->AccrualBalance;//先前到现在的存款能获利息计算完毕
	strTypeChange.Format("%f",dAccrualMomey);
	m_SavingList.SetItemText(1,3,strTypeChange);
}

void CSavingPage::WriteFixList(_FixInfo * pFixInfo)
{
	m_SavingList.SetItemText(0,0,pFixInfo->CardId);
	m_SavingList.SetItemText(1,0,NULL);
	CString strUserName=_T("");
	strUserName=m_SavingList.GetItemText(1,1);
	m_SavingList.SetItemText(0,1,strUserName);
	m_SavingList.SetItemText(1,1,NULL);
	CString strTypeChange=_T("");
	strTypeChange.Format("%f",pFixInfo->MoneyBalance);
	m_SavingList.SetItemText(0,2,strTypeChange);
	m_SavingList.SetItemText(0,4,"定期");
	m_SavingList.SetItemText(0,5,pFixInfo->ExchangeDate);
	m_SavingList.SetItemText(0,6,pFixInfo->MatureDate);
}

// 计算上次交易到现在所经过的天数，每月按30天计算，每年12个月
int CSavingPage::CountDay(_CurrentInfo *pCurrentInfo)
{
	CString strDate=_T("");
	CString strLastDate=_T("");
	CString strCurDate=_T("");
	strLastDate=pCurrentInfo->ExchangeDate;
	strCurDate=m_SavingList.GetItemText(1,5);
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

double CSavingPage::GetRate(void)
{
	double dAccrualMomery=0.0;
	CString strAccrualRate=_T("");
	this->GetDlgItemText(IDC_RATE_EDT,strAccrualRate);
	dAccrualMomery=atof(strAccrualRate.GetBuffer(strAccrualRate.GetLength()));
	return dAccrualMomery;
}

void CSavingPage::OnBnClickedSavingBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//开始判断是定期还是活期，根据不同的种类将有不同的数据处理方式
	CString strType=_T("");
	this->GetDlgItemText(IDC_TYPE_COMB,strType);
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
				MessageBox("活期期存款申请成功！",NULL,MB_ICONASTERISK);
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
				MessageBox("定期存款申请成功！",NULL,MB_ICONASTERISK);
			}
		}
		else
			{
				return;
			}
	}
	this->EmptyTable();
}

bool CSavingPage::CheckCurrent(void)
{
	//判断此次输入金额是否为空,姓名是否为空,若有一个是空,返回
	CString strCheck=_T("");
	strCheck=_T("");
	strCheck=m_SavingList.GetItemText(1,0);
	if(strCheck=="")
	{
		MessageBox("未输入帐号,重新输入!",NULL,MB_ICONERROR);
		return FALSE;
	}
	strCheck=m_SavingList.GetItemText(1,1);
	if(strCheck=="")
	{
		MessageBox("此帐号无效,重新输入!",NULL,MB_ICONERROR);
		return FALSE;
	}
	strCheck=m_SavingList.GetItemText(1,2);
	if(strCheck=="")
	{
		MessageBox("没有输入此次要存入的金额,请重新输入!",NULL,MB_ICONERROR);
		return FALSE;
	}
	strCheck=_T("");
	strCheck=m_SavingList.GetItemText(1,1);
	if(strCheck=="")
	{
		MessageBox("数据库中没有此帐号,请检查帐号,重新输入!",NULL,MB_ICONERROR);
		return FALSE;
	}
	return TRUE;
}

bool CSavingPage::CheckFix(void)
{
	CString strCheck=_T("");
	strCheck=m_SavingList.GetItemText(1,0);
	if(strCheck=="")
	{
		MessageBox("未输入帐号,重新输入!",NULL,MB_ICONERROR);
		return FALSE;
	}
	strCheck=m_SavingList.GetItemText(1,1);
	if(strCheck=="")
	{
		MessageBox("此帐号无效,重新输入!",NULL,MB_ICONERROR);
		return FALSE;
	}
	strCheck=m_SavingList.GetItemText(0,0);
	if(strCheck!="")
	{
	  MessageBox("这个定期账号已有存款，不能再存入！",NULL,MB_ICONERROR);
	  return false;
	}
	strCheck=m_SavingList.GetItemText(1,2);
	if(strCheck=="")
	{
		MessageBox("未输入定期存款的金额，请重新输入！",NULL,MB_ICONERROR);
		return false;
	}
	return TRUE;
}

BOOL CSavingPage::WriteFixSql(void)
{
	CString strSqlText=_T("insert into FixInfo(CardId,MoneyBalance,ExchangeDate,MatureDate,AccrualRate) values ('");
	CString strSqlText2=_T("insert into RecordInfo(CardId,MoneyBalance,ExchangeDate,AccrualBalance,InOut,MoneyType) values ('");
	CString strUserInput=_T("");
	CString strSign=_T("','");
	CString strDeleteSQl=_T("delete from FixInfo where CardId='");
	this->GetDlgItemText(IDC_CARDID_EDT,strUserInput);
	strDeleteSQl=strDeleteSQl+strUserInput+CString("'");
	/////////////////////////////////从表格中读取数
	strUserInput=m_SavingList.GetItemText(1,0);
	strSqlText=strSqlText+strUserInput+strSign;
	strSqlText2=strSqlText2+strUserInput+strSign;
	//
	strUserInput=m_SavingList.GetItemText(1,2);
	strSqlText=strSqlText+strUserInput+strSign;
	strSqlText2=strSqlText2+strUserInput+strSign;
	//
	strUserInput=m_SavingList.GetItemText(1,5);
	strSqlText=strSqlText+strUserInput+strSign;
	strSqlText2=strSqlText2+strUserInput+CString("','0','存','定期')");
	//
	strUserInput=m_SavingList.GetItemText(1,6);
	strSqlText=strSqlText+strUserInput+strSign;
	//
	this->GetDlgItemText(IDC_RATE_EDT,strUserInput);
	strSqlText=strSqlText+strUserInput+CString("')");
	//
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

void CSavingPage::EmptyTable(void)
{
	m_SavingList.DeleteAllItems();
	m_SavingList.InsertItem(0,NULL);
	m_SavingList.InsertItem(1,NULL);
	this->SetDlgItemText(IDC_CARDID_EDT,NULL);
	this->SetDlgItemText(IDC_MONEY_EDT,NULL);
	this->OnCbnSelchangeTypeComb();
}
BOOL CSavingPage::WriteCurrentSql(void)
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
	strUserInput=m_SavingList.GetItemText(1,0);
	strSqlText=strSqlText+strUserInput+strSign;
	strSqlText2=strSqlText2+strUserInput+strSign;
	//开始相加上下两个表格中的金额结算
	double dCur=0.0;
	strUserInput=m_SavingList.GetItemText(1,2);
	dCur=atof(strUserInput.GetBuffer(strUserInput.GetLength()));
	double dPre=0.0;
	strUserInput=m_SavingList.GetItemText(0,2);
	dPre=atof(strUserInput.GetBuffer(strUserInput.GetLength()));
	strUserInput.Format("%f",dCur);
	strSqlText2=strSqlText2+strUserInput+strSign;
	dCur=dCur+dPre;
	strUserInput.Format("%f",dCur);
	strSqlText=strSqlText+strUserInput+strSign;	
	//
	strUserInput=m_SavingList.GetItemText(1,5);
	strSqlText=strSqlText+strUserInput+strSign;
	strSqlText2=strSqlText2+strUserInput+strSign;
	//开始相加上下两个表格中的利息结算
	strUserInput=m_SavingList.GetItemText(1,3);
	if(strUserInput=="")
		strUserInput=_T("0");
	strSqlText=strSqlText+strUserInput+CString("')");
	strSqlText2=strSqlText2+strUserInput+CString("','存','活期')");
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
void CSavingPage::PrintTable(void)
{
}
