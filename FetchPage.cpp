//Download by http://www.NewXing.com
// FetchPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BankManager.h"
#include "FetchPage.h"
#include ".\fetchpage.h"
#include "_StructDefine.h"
#include "AdoWorker.h"
#include "PrintDlg.h"

// CFetchPage �Ի���

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


// CFetchPage ��Ϣ�������

void CFetchPage::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
}

void CFetchPage::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
}

BOOL CFetchPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	rc.top=rc.top+15;
	rc.left=rc.left+3;
	rc.bottom=rc.bottom-2;
	rc.right=rc.right-2;
	((CTabCtrl*)GetParent())->AdjustRect(false, &rc); 
	MoveWindow(&rc);
	//////////////////////////////////////////�������������
	m_CardIdEdt.SetLimitText(12);
	m_PassKeyEdt.SetLimitText(8);
	m_MoneyEdt.ShowWindow(SW_HIDE);
	//��ʼ���б��
	this->OnInitList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CFetchPage::OnInitList(void)
{
	m_FetchList.InsertColumn(0,"�����ʺ�",LVCFMT_LEFT,100);
	m_FetchList.InsertColumn(1,"����",LVCFMT_LEFT,60);
	m_FetchList.InsertColumn(2,"���(Ԫ)",LVCFMT_LEFT,60);
	m_FetchList.InsertColumn(3,"��Ϣ(Ԫ)",LVCFMT_LEFT,60);
	m_FetchList.InsertColumn(4,"ȡ������",LVCFMT_LEFT,60);
	m_FetchList.InsertColumn(5,"����ʱ��",LVCFMT_LEFT,75);
	m_FetchList.InsertColumn(6,"����ʱ��",LVCFMT_LEFT,75);
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
    m_FetchList.SetItemText(1,0,strCardID);//�����ʺ���
	////�ڴ���Ҫ�ж��������ݵ�λ�����������������Զ��������ݿ⣬��ѯ�����ʺź���ǰ������ʾ�ڱ����
	////������ѡ��ʹ����߿��ƺ�ʱҪ�Զ��������ݿ��ѯ
	int iStr=0;
	iStr=strCardID.GetLength();
	if(iStr==2)//�Զ�����ʺ��Ƕ��ڻ��ǻ���
	{
		if(strCardID=="01")//����
		{
			m_FetchList.SetItemText(1,4,"����");
			m_MoneyEdt.ShowWindow(SW_SHOW);
		}
		else if(strCardID=="02")//����
		{
			m_FetchList.SetItemText(1,4,"����");
			m_MoneyEdt.ShowWindow(SW_HIDE);
		}
		else
		{
			MessageBox("�������������͵��˺�,���������룡",NULL,MB_ICONERROR);
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
	m_FetchList.SetItemText(1,2,strMoney);//�����ʺ���
}


void CFetchPage::OnEnChangePassEdt()
{
	CString strCardID=_T("");
	this->GetDlgItemText(IDC_CARDID_EDT,strCardID);
	m_FetchList.SetItemText(1,0,strCardID);//�����ʺ���
	////�ڴ���Ҫ�ж��������ݵ�λ�����������������Զ��������ݿ⣬��ѯ�����ʺź���ǰ������ʾ�ڱ����
	////������ѡ��ʹ����߿��ƺ�ʱҪ�Զ��������ݿ��ѯ
	int iStr=0;
	iStr=strCardID.GetLength();
	if(iStr==2)//�Զ�����ʺ��Ƕ��ڻ��ǻ���
	{
		if(strCardID=="01")//����
		{
			m_FetchList.SetItemText(1,3,"����");
		}
		else if(strCardID=="02")//����
		{
			m_FetchList.SetItemText(1,3,"����");
		}
		else
		{
			MessageBox("�������������͵��˺�,���������룡",NULL,MB_ICONERROR);
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

void CFetchPage::ReadRecord(void)//����������˺ź������ѯ���ݿ⣬�õ��������жϸ��ʺ��Ƿ����
{
	CString strSqlText=_T("select UserName from UserInfo where CardId ='");
	CString strId=_T("");
	strId=m_FetchList.GetItemText(1,0);
	strSqlText=strSqlText+strId+CString("' and UserPass ='");
	//��ʼ��������ѯ����
	CString strPass=_T("");
	this->GetDlgItemText(IDC_PASS_EDT,strPass);
	strSqlText=strSqlText+strPass+CString("'");
	//////////////////////////////////����SQL���ִ����ʵ��
	AdoWorker *ado=NULL;
	_UserNameInfo *pUserNameInfo=NULL;
	ado=new AdoWorker();
	pUserNameInfo=(_UserNameInfo *)ado->ExecuteSql(strSqlText,5);
	CString strName=_T("");
	if(pUserNameInfo==NULL)
	{
		MessageBox(" �����ڸ��ʺŻ�����������ʺź��������ȷ�ԣ�",NULL,MB_ICONERROR);
		this->SetDlgItemText(IDC_CARDID_EDT,NULL);
		this->SetDlgItemText(IDC_MONEY_EDT,NULL);
		this->SetDlgItemText(IDC_PASS_EDT,NULL);
		delete pUserNameInfo;
		delete ado;
		return ;
	}
	else//�����������˺ţ��ڴ��趨����еڶ��е�����
	{
		strName=pUserNameInfo->UserName;
		m_FetchList.SetItemText(1,1,strName);
		delete pUserNameInfo;
	}
	//���˴��˺��Ѿ�ע�ᣬ����ǻ��ڻ��Ƕ���
	//����ǻ��ڣ����ҵ����һ�ν��׵ļ�¼�����Ƕ��ڣ�
	//�ڶ��ڼ�¼���в��ң�����Ƿ���ΪNULL���ܼ�������
	//������ǣ��������˺��Ѿ��д������ټ�����Ŷ��ڴ��
	CString strCheckType=_T("");
	//this->GetDlgItemText(IDC_TYPE_COMB,strCheckType);
	//�����ʺŲ����ж��Ƕ��ڻ��ǻ���
	CString strCardID=_T("");
	this->GetDlgItemText(IDC_CARDID_EDT,strCardID);
	CString strCheck=_T("");
	strCheck=(CString)strCardID[0]+(CString)strCardID[1];
	if(strCheck=="01")
		strCheckType="����";
	else if(strCheck=="02")
			strCheckType="����";
		else
			{
				MessageBox("�����ʺ��������������룡",NULL,MB_ICONERROR);
				return;
			}
	if(strCheckType=="����")//��ʼ�������
	{
		strSqlText=_T("select * from CurrentInfo where CardId ='");
		CString strId=_T("");
		strId=m_FetchList.GetItemText(1,0);
		strSqlText=strSqlText+strId+CString("'");
		_CurrentInfo *pCurrentInfo=NULL;
		pCurrentInfo=(_CurrentInfo *)ado->ExecuteSql(strSqlText,2);
		//���Ƚ���Ϣ��0
		m_FetchList.SetItemText(1,3,NULL);
		if(pCurrentInfo!=NULL)
			this->WriteCurrentList(pCurrentInfo);
		else
			{
				MessageBox("����һ�����ʺ�,��Ǯ��ȡ��",NULL,MB_ICONASTERISK);
				this->EmptyTable();
				delete ado;
				return;
			}
		delete pCurrentInfo;
	}
	else//��ʼ������
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
				MessageBox("����һ�����ʺ�,��Ǯ��ȡ��",NULL,MB_ICONASTERISK);
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
	//���ݲ�ѯ����ֵ����ʼ���û���ʱ��0�е�����
	m_FetchList.SetItemText(0,0,pCurrentInfo->CardId);
	CString strUserName=_T("");
	strUserName=m_FetchList.GetItemText(1,1);
	m_FetchList.SetItemText(0,1,strUserName);
	CString strTypeChange=_T("");
	strTypeChange.Format("%f",pCurrentInfo->MoneyBalance);
	m_FetchList.SetItemText(0,2,strTypeChange);
	strTypeChange.Format("%f",pCurrentInfo->AccrualBalance);
	m_FetchList.SetItemText(0,3,strTypeChange);
	m_FetchList.SetItemText(0,4,"����");
	m_FetchList.SetItemText(0,5,pCurrentInfo->ExchangeDate);
	//��ʼ��ȡ����Ľ������ڣ����������Ȼ�������ǰһ�ʽ��׵�������ӵ�е���Ϣ��
	//���õ���1�е���Ϣ����
	int iDaySum=0;
	iDaySum=this->CountDay(pCurrentInfo);
	double dRate=0.0;
	dRate=this->GetRate();
	double dAccrualMomey=0.0;
	dAccrualMomey=(double)iDaySum*dRate*(pCurrentInfo->MoneyBalance)+pCurrentInfo->AccrualBalance;//��ǰ�����ڵĴ���ܻ���Ϣ�������
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
	//�ж��Ƿ���
	if(this->CheckMatured(pFixInfo))
	{
		double dAccrualBalance=0.0;
		dAccrualBalance=pFixInfo->MoneyBalance*pFixInfo->AccrualRate;
		strTypeChange.Format("%f",dAccrualBalance);
		m_FetchList.SetItemText(1,3,strTypeChange);
		m_FetchList.SetItemText(1,4,"����");
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
		m_FetchList.SetItemText(1,4,"����");
	}
	//
	m_FetchList.SetItemText(0,5,pFixInfo->ExchangeDate);
	//
	m_FetchList.SetItemText(0,6,pFixInfo->MatureDate);
	//
	//��ʼд�ڶ��е���Ϣ

}

// �����ϴν��׵�������������������ÿ�°�30����㣬ÿ��12����
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
	//��ʼ�����������ݣ���ʼ������
	int iLast=0;
	int iCur=0;
	int iFlag=0;//��־�Ƿ��λ
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
	//�մ�����ϣ���ʼ������
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
	//�´�����ϣ���ʼ������
	strDate=_T("");
	strDate=(CString)(pCurrentInfo->ExchangeDate[0])+(CString)(pCurrentInfo->ExchangeDate[1]+(CString)(pCurrentInfo->ExchangeDate[2])+(CString)(pCurrentInfo->ExchangeDate[3]));
	iLast=atoi(strDate.GetBuffer(strDate.GetLength()));
	strDate=_T("");
	strDate=(CString)strCurDate[0]+(CString)strCurDate[1]+(CString)strCurDate[2]+(CString)strCurDate[3];
	iCur=atoi(strDate.GetBuffer(strDate.GetLength()));
	strDate=_T("");

	iYear=iCur-iLast-iFlag;

	//�괦�����
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
	//�жϴ˴��������Ƿ�Ϊ��,�����Ƿ�Ϊ��,����һ���ǿ�,����
	CString strCheck=_T("");
	strCheck=_T("");
	strCheck=m_FetchList.GetItemText(1,0);
	if(strCheck=="")
	{
		MessageBox("δ�����ʺ�,��������!",NULL,MB_ICONERROR);
		return FALSE;
	}
	strCheck=m_FetchList.GetItemText(1,1);
	if(strCheck=="")
	{
		MessageBox("���ʺ���Ч,��������!",NULL,MB_ICONERROR);
		return FALSE;
	}
	strCheck=m_FetchList.GetItemText(1,2);
	if(strCheck=="")
	{
		MessageBox("û������˴�Ҫȡ���Ľ��,����������!",NULL,MB_ICONERROR);
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
		MessageBox("���ʺŲ���͸֧�������������",NULL,MB_ICONERROR);
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
		MessageBox("δ�����ʺ�,��������!",NULL,MB_ICONERROR);
		return FALSE;
	}
	strCheck=m_FetchList.GetItemText(1,1);
	if(strCheck=="")
	{
		MessageBox("���ʺ���Ч,��������!",NULL,MB_ICONERROR);
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
	/////////////////////////////////�ӱ���ж�ȡ��
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
	strSqlText2=strSqlText2+strUserInput+CString("','ȡ')"); 
	//
	AdoWorker *ado=NULL;
	ado=new AdoWorker();
	BOOL bExec=FALSE;
	//��ɾ��ԭ������
	ado->ExecuteSql(strDeleteSQl);//ɾ�����ڴ���еĸ�������
	bExec=ado->ExecuteSql(strSqlText2);//�����ݲ��뵽��record�����
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
	//���Ǳ���д����˼�¼����ɾ��
	CString strSqlText=_T("insert into CurrentInfo(CardId,MoneyBalance,ExchangeDate,AccrualBalance) values ('");
	CString strSqlText2=_T("insert into RecordInfo(CardId,MoneyBalance,ExchangeDate,AccrualBalance,InOut,MoneyType) values ('");
	CString strUserInput=_T("");
	CString strSign=_T("','");
	CString strDeleteSQl=_T("delete from CurrentInfo where CardId='");
	this->GetDlgItemText(IDC_CARDID_EDT,strUserInput);
	strDeleteSQl=strDeleteSQl+strUserInput+CString("'");
	/////////////////////////////////�ӱ���ж�ȡ��
	strUserInput=m_FetchList.GetItemText(1,0);
	strSqlText=strSqlText+strUserInput+strSign;
	strSqlText2=strSqlText2+strUserInput+strSign;
	//��ʼ���������������еĽ�����
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
		MessageBox("���ܳ�֧��ȡ�����벻�ɹ���",NULL,MB_ICONERROR);
		return FALSE;
	}
	strUserInput.Format("%f",dCur);

	strSqlText=strSqlText+strUserInput+strSign;
	//
	strUserInput=m_FetchList.GetItemText(1,5);
	strSqlText=strSqlText+strUserInput+strSign;
	strSqlText2=strSqlText2+strUserInput+strSign;
	//��ʼ���������������е���Ϣ����
	strUserInput=m_FetchList.GetItemText(1,3);
	if(strUserInput=="")
		strUserInput=_T("0");
	strSqlText=strSqlText+strUserInput+CString("')");
	strSqlText2=strSqlText2+strUserInput+CString("','ȡ','����')");
	AdoWorker *ado=NULL;
	ado=new AdoWorker();
	BOOL bExec=FALSE;
	//��ɾ��ԭ������
	ado->ExecuteSql(strDeleteSQl);
	ado->ExecuteSql(strSqlText2);
	bExec=ado->ExecuteSql(strSqlText);//�����ݲ��뵽�˱����
	delete ado;
	return bExec;
}

void CFetchPage::OnBnClickedFetchBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ʼ�ж��Ƕ��ڻ��ǻ��ڣ����ݲ�ͬ�����ཫ�в�ͬ�����ݴ���ʽ
	CString strType=_T("");
	CString strCardID=_T("");
	this->GetDlgItemText(IDC_CARDID_EDT,strCardID);
	CString strCheck=_T("");
	strCheck=(CString)strCardID[0]+(CString)strCardID[1];
	if(strCheck=="01")
		strType="����";
	else if(strCheck=="02")
		strType=="����";
	else
	{
		MessageBox("�����ʺ��������������룡",NULL,MB_ICONERROR);
		return;
	}
	if(strType=="����")//���ڴ���
	{
		if(this->CheckCurrent())//������ֵ,��ʼ��֯SQL���,д���ݿ�
		{
			if(this->WriteCurrentSql())//д���ݿ�
			{
				CPrintDlg *pPrintDlg=NULL;
				pPrintDlg=new CPrintDlg();
				if(pPrintDlg->DoModal()==IDOK)
				{
					this->PrintTable();//��ӡ���ݱ�

				}
				delete pPrintDlg;
				MessageBox("������ȡ������ɹ���",NULL,MB_ICONASTERISK);
			}
		}
		else
			return;
	}
	else//���ڴ���
	{
		if(this->CheckFix())//������ֵ,��ʼ��֯SQL���,д���ݿ�
		{
			if(this->WriteFixSql())//д���ݿ�
			{
				CPrintDlg *pPrintDlg=NULL;
				pPrintDlg=new CPrintDlg();
				if(pPrintDlg->DoModal()==IDOK)
				{
					this->PrintTable();//��ӡ���ݱ�
				}
				delete pPrintDlg;
				MessageBox("����ȡ������ɹ���",NULL,MB_ICONASTERISK);
			}
		}
		else
		{
			return;
		}
	}
	this->EmptyTable();
}

BOOL CFetchPage::CheckMatured(_FixInfo * pFixInfo)//��ʼ�ж��Ƿ���
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
	//�õ���
	strDate=(CString)(pFixInfo->MatureDate[8])+(CString)(pFixInfo->MatureDate[9]);
	iDay=atoi(strDate.GetBuffer(strDate.GetLength()));
	strDate=_T("");
	//�մ�����ϣ���ʼ������
	strDate=_T("");
	strDate=(CString)(pFixInfo->MatureDate[5])+(CString)(pFixInfo->MatureDate[6]);
	iMonth=atoi(strDate.GetBuffer(strDate.GetLength()));
	//�´�����ϣ���ʼ������
	strDate=_T("");
	strDate=(CString)(pFixInfo->MatureDate[0])+(CString)(pFixInfo->MatureDate[1]+(CString)(pFixInfo->MatureDate[2])+(CString)(pFixInfo->MatureDate[3]));
	iYear=atoi(strDate.GetBuffer(strDate.GetLength()));
	//���Ե����ڶ��ѵõ�����ʼ�ж��Ƿ���
	if(Cur_Year>iYear)//��Ų�ͬ���;�����ȷ���Ѿ�����
		return TRUE;
	else if(Cur_Year==iYear)//������
	{
		if(Cur_Month>iMonth)//�²�ͬ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->EmptyTable();
}
void  CFetchPage::PrintTable(void)
{
}