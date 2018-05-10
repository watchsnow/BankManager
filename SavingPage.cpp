//Download by http://www.NewXing.com
// SavingPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BankManager.h"
#include "SavingPage.h"
#include ".\savingpage.h"
#include "AdoWorker.h"
#include "_StructDefine.h"
#include "PrintDlg.h"

// CSavingPage �Ի���

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


// CSavingPage ��Ϣ�������

BOOL CSavingPage::OnInitDialog()
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
	//��ʼ���б��
	this->OnInitList();
	/////////////////////////////////���崰�����ý���
	/////////////////////////////////���ãţ��������������ݵĸ���
	m_CardIdEdt.SetLimitText(12);
	///////////////////////////////////��ʼ����������Ͽ�
	CComboBox * pBo=NULL;
	pBo=(CComboBox*)this->GetDlgItem(IDC_TYPE_COMB);
	pBo->AddString("����");
	pBo->AddString("����");
	pBo->SetCurSel(0);
	this->OnCbnSelchangeTypeComb();
	//////////////////////////////////��ʼ��ʱ����Ͽ�
	pBo=(CComboBox*)this->GetDlgItem(IDC_TIME_COMB);
	pBo->AddString("����");
	pBo->AddString("һ��");
	pBo->AddString("һ���");
	pBo->AddString("����");
	pBo->SetCurSel(0);
	////////////////////////////////��Ͽ��ʼ������
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSavingPage::OnEnChangeCardidEdt()
{
	CString strCardID=_T("");
	this->GetDlgItemText(IDC_CARDID_EDT,strCardID);
	m_SavingList.SetItemText(1,0,strCardID);//�����ʺ���
	////�ڴ���Ҫ�ж��������ݵ�λ�����������������Զ��������ݿ⣬��ѯ�����ʺź���ǰ������ʾ�ڱ����
	////������ѡ��ʹ����߿��ƺ�ʱҪ�Զ��������ݿ��ѯ
	int iStr=0;
	iStr=strCardID.GetLength();
	if(iStr==2)//�Զ�����ʺ��Ƕ��ڻ��ǻ���
	{
		if(strCardID=="01")//����
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
				 MessageBox("�������������͵��˺�,���������룡",NULL,MB_ICONERROR);
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
	m_SavingList.SetItemText(1,2,strMoney);//���ý����

}

void CSavingPage::OnCbnSelchangeTypeComb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	///////////////////////////////////////���ñ������ʱ�䣬�������ĳ�ʼ��
	CString strCurTime=_T("");
	strCurTime=this->FormatTime(0);
	m_SavingList.SetItemText(1,5,strCurTime);
   ////////////////////////////////////////��������
	CString strType=_T("");
	this->GetDlgItemText(IDC_TYPE_COMB,strType);
	m_SavingList.SetItemText(1,4,strType);//���û��ڻ��߶���
	if(strType=="����")
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
		m_SavingList.SetItemText(1,6,NULL);//���������õ���ʱ��Ϊ��
	}
}

void CSavingPage::OnInitList(void)
{
	m_SavingList.InsertColumn(0,"�����ʺ�",LVCFMT_LEFT,100);
	m_SavingList.InsertColumn(1,"����",LVCFMT_LEFT,60);
	m_SavingList.InsertColumn(2,"���(Ԫ)",LVCFMT_LEFT,60);
	m_SavingList.InsertColumn(3,"��Ϣ����(Ԫ)",LVCFMT_LEFT,80);
	m_SavingList.InsertColumn(4,"�������",LVCFMT_LEFT,60);
	m_SavingList.InsertColumn(5,"����ʱ��",LVCFMT_LEFT,75);
	m_SavingList.InsertColumn(6,"����ʱ��",LVCFMT_LEFT,75);
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
	if(iFlag)//��ʱ����ȡ��������
	{
	  CString strTimeCom=_T("");
	  this->GetDlgItemText(IDC_TIME_COMB,strTimeCom);
	  if(strTimeCom=="����")
		  Cur_Month+=6;
	  if(strTimeCom=="һ��")
		  Cur_Month+=12;
	  if(strTimeCom=="һ���")
		  Cur_Month+=18;
	  if(strTimeCom=="����")
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ʼ��д����
	CString strTimeCom=_T("");
	this->GetDlgItemText(IDC_TIME_COMB,strTimeCom);
	if(strTimeCom=="����")
		this->SetDlgItemText(IDC_RATE_EDT,"0.01");
	if(strTimeCom=="һ��")
		this->SetDlgItemText(IDC_RATE_EDT,"0.03");
	if(strTimeCom=="һ���")
		this->SetDlgItemText(IDC_RATE_EDT,"0.05");
	if(strTimeCom=="����")
		this->SetDlgItemText(IDC_RATE_EDT,"0.07");
	CString strRate=_T("");
	this->GetDlgItemText(IDC_RATE_EDT,strRate);
	//m_SavingList.SetItemText(1,3,strRate);
	///////////////////////////////��ʼ��дʱ��
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
void CSavingPage::SureIdExist(void)//����������˺ź������ѯ���ݿ⣬�õ��������жϸ��ʺ��Ƿ����
{
	CString strSqlText=_T("select UserName from UserInfo where CardId ='");
	CString strId=_T("");
	strId=m_SavingList.GetItemText(1,0);
	strSqlText=strSqlText+strId+CString("'");
	//////////////////////////////////����SQL���ִ����ʵ��
	AdoWorker *ado=NULL;
	_UserNameInfo *pUserNameInfo=NULL;
	ado=new AdoWorker();
	pUserNameInfo=(_UserNameInfo *)ado->ExecuteSql(strSqlText,5);
	CString strName=_T("");
	if(pUserNameInfo==NULL)
	{
		MessageBox("û���������˺ţ�����ע����߼���˺ŵ���ȷ�ԣ�",NULL,MB_ICONERROR);
		this->SetDlgItemText(IDC_CARDID_EDT,NULL);
		this->SetDlgItemText(IDC_MONEY_EDT,NULL);
		delete pUserNameInfo;
		delete ado;
		return ;
	}
	else//�����������˺ţ��ڴ��趨����еڶ��е�����
	{
		strName=pUserNameInfo->UserName;
		m_SavingList.SetItemText(1,1,strName);
		delete pUserNameInfo;
	}
	//���˴��˺��Ѿ�ע�ᣬ����ǻ��ڻ��Ƕ���
	//����ǻ��ڣ����ҵ����һ�ν��׵ļ�¼�����Ƕ��ڣ�
	//�ڶ��ڼ�¼���в��ң�����Ƿ���ΪNULL���ܼ�������
	//������ǣ��������˺��Ѿ��д������ټ�����Ŷ��ڴ��
	CString strCheckType=_T("");
	this->GetDlgItemText(IDC_TYPE_COMB,strCheckType);
	if(strCheckType=="����")//��ʼ�������
	{
		strSqlText=_T("select * from CurrentInfo where CardId ='");
		CString strId=_T("");
		strId=m_SavingList.GetItemText(1,0);
		strSqlText=strSqlText+strId+CString("'");
		_CurrentInfo *pCurrentInfo=NULL;
		pCurrentInfo=(_CurrentInfo *)ado->ExecuteSql(strSqlText,2);
		//���Ƚ���Ϣ��0
		m_SavingList.SetItemText(1,3,NULL);
		if(pCurrentInfo!=NULL)
			this->WriteCurrentList(pCurrentInfo);
		else
			MessageBox("����һ�����ʺţ�",NULL,MB_ICONASTERISK);
		delete pCurrentInfo;
	}
	else//��ʼ������
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
				MessageBox("���ʺ��Ѿ��ж��ڴ��������ô��ʺŴ��!",NULL,MB_ICONERROR);
				CPrintDlg *pPrintDlg=NULL;
				pPrintDlg=new CPrintDlg();
				if(pPrintDlg->DoModal()==IDOK)
				{
					this->PrintTable();//��ӡ���ݱ�

				}
				delete pPrintDlg;
				this->EmptyTable();
			}
		else
			MessageBox("�˶����ʺ����޴��ɴ棡",NULL,MB_ICONASTERISK);
		delete pFixInfo;;
	}
	delete ado;
	return ;
}
void CSavingPage::WriteCurrentList(_CurrentInfo * pCurrentInfo)
{
	//���ݲ�ѯ����ֵ����ʼ���û���ʱ��0�е�����
	m_SavingList.SetItemText(0,0,pCurrentInfo->CardId);
	CString strUserName=_T("");
	strUserName=m_SavingList.GetItemText(1,1);
	m_SavingList.SetItemText(0,1,strUserName);
	CString strTypeChange=_T("");
	strTypeChange.Format("%f",pCurrentInfo->MoneyBalance);
	m_SavingList.SetItemText(0,2,strTypeChange);
	strTypeChange.Format("%f",pCurrentInfo->AccrualBalance);
	m_SavingList.SetItemText(0,3,strTypeChange);
	m_SavingList.SetItemText(0,4,"����");
	m_SavingList.SetItemText(0,5,pCurrentInfo->ExchangeDate);
	//��ʼ��ȡ����Ľ������ڣ����������Ȼ�������ǰһ�ʽ��׵�������ӵ�е���Ϣ��
	//���õ���1�е���Ϣ����
	int iDaySum=0;
	iDaySum=this->CountDay(pCurrentInfo);
	double dRate=0.0;
	dRate=this->GetRate();
	double dAccrualMomey=0.0;
	dAccrualMomey=(double)iDaySum*dRate*(pCurrentInfo->MoneyBalance)+pCurrentInfo->AccrualBalance;//��ǰ�����ڵĴ���ܻ���Ϣ�������
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
	m_SavingList.SetItemText(0,4,"����");
	m_SavingList.SetItemText(0,5,pFixInfo->ExchangeDate);
	m_SavingList.SetItemText(0,6,pFixInfo->MatureDate);
}

// �����ϴν��׵�������������������ÿ�°�30����㣬ÿ��12����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ʼ�ж��Ƕ��ڻ��ǻ��ڣ����ݲ�ͬ�����ཫ�в�ͬ�����ݴ���ʽ
	CString strType=_T("");
	this->GetDlgItemText(IDC_TYPE_COMB,strType);
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
				MessageBox("�����ڴ������ɹ���",NULL,MB_ICONASTERISK);
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
				MessageBox("���ڴ������ɹ���",NULL,MB_ICONASTERISK);
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
	//�жϴ˴��������Ƿ�Ϊ��,�����Ƿ�Ϊ��,����һ���ǿ�,����
	CString strCheck=_T("");
	strCheck=_T("");
	strCheck=m_SavingList.GetItemText(1,0);
	if(strCheck=="")
	{
		MessageBox("δ�����ʺ�,��������!",NULL,MB_ICONERROR);
		return FALSE;
	}
	strCheck=m_SavingList.GetItemText(1,1);
	if(strCheck=="")
	{
		MessageBox("���ʺ���Ч,��������!",NULL,MB_ICONERROR);
		return FALSE;
	}
	strCheck=m_SavingList.GetItemText(1,2);
	if(strCheck=="")
	{
		MessageBox("û������˴�Ҫ����Ľ��,����������!",NULL,MB_ICONERROR);
		return FALSE;
	}
	strCheck=_T("");
	strCheck=m_SavingList.GetItemText(1,1);
	if(strCheck=="")
	{
		MessageBox("���ݿ���û�д��ʺ�,�����ʺ�,��������!",NULL,MB_ICONERROR);
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
		MessageBox("δ�����ʺ�,��������!",NULL,MB_ICONERROR);
		return FALSE;
	}
	strCheck=m_SavingList.GetItemText(1,1);
	if(strCheck=="")
	{
		MessageBox("���ʺ���Ч,��������!",NULL,MB_ICONERROR);
		return FALSE;
	}
	strCheck=m_SavingList.GetItemText(0,0);
	if(strCheck!="")
	{
	  MessageBox("��������˺����д������ٴ��룡",NULL,MB_ICONERROR);
	  return false;
	}
	strCheck=m_SavingList.GetItemText(1,2);
	if(strCheck=="")
	{
		MessageBox("δ���붨�ڴ��Ľ����������룡",NULL,MB_ICONERROR);
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
	/////////////////////////////////�ӱ���ж�ȡ��
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
	strSqlText2=strSqlText2+strUserInput+CString("','0','��','����')");
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
	//��ɾ��ԭ������
	ado->ExecuteSql(strDeleteSQl);
	ado->ExecuteSql(strSqlText2);
	bExec=ado->ExecuteSql(strSqlText);//�����ݲ��뵽�˱����
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
	//���Ǳ���д����˼�¼����ɾ��
	CString strSqlText=_T("insert into CurrentInfo(CardId,MoneyBalance,ExchangeDate,AccrualBalance) values ('");
	CString strSqlText2=_T("insert into RecordInfo(CardId,MoneyBalance,ExchangeDate,AccrualBalance,InOut,MoneyType) values ('");
	CString strUserInput=_T("");
	CString strSign=_T("','");
	CString strDeleteSQl=_T("delete from CurrentInfo where CardId='");
	this->GetDlgItemText(IDC_CARDID_EDT,strUserInput);
	strDeleteSQl=strDeleteSQl+strUserInput+CString("'");
	/////////////////////////////////�ӱ���ж�ȡ��
	strUserInput=m_SavingList.GetItemText(1,0);
	strSqlText=strSqlText+strUserInput+strSign;
	strSqlText2=strSqlText2+strUserInput+strSign;
	//��ʼ���������������еĽ�����
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
	//��ʼ���������������е���Ϣ����
	strUserInput=m_SavingList.GetItemText(1,3);
	if(strUserInput=="")
		strUserInput=_T("0");
	strSqlText=strSqlText+strUserInput+CString("')");
	strSqlText2=strSqlText2+strUserInput+CString("','��','����')");
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
void CSavingPage::PrintTable(void)
{
}
