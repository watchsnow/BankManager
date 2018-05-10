//Download by http://www.NewXing.com
// BowerPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BankManager.h"
#include "BowerPage.h"
#include ".\bowerpage.h"
#include "_StructDefine.h"
#include "AdoWorker.h"
#include "PrintDlg.h"


// CBowerPage �Ի���

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


// CBowerPage ��Ϣ�������

BOOL CBowerPage::OnInitDialog()
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
	m_PassKeyEdt.SetLimitText(8);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CBowerPage::OnEnChangeCardidEdt()
{
	CString strCardID=_T("");
	this->GetDlgItemText(IDC_CARDID_EDT,strCardID);
	////�ڴ���Ҫ�ж��������ݵ�λ�����������������Զ��������ݿ⣬��ѯ�����ʺź���ǰ������ʾ�ڱ����
	////������ѡ��ʹ����߿��ƺ�ʱҪ�Զ��������ݿ��ѯ
	int iStr=0;
	iStr=strCardID.GetLength();
	if(iStr==2)//�Զ�����ʺ��Ƕ��ڻ��ǻ���
	{
		if(!(strCardID=="01"||strCardID=="02"))//����
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
	{
		CString strName=_T("");
		strName=this->ReadRecord();
		if(strName!="")//ȷ�����û�����
		{
			this->ReadExchangeRecord(strName);//���ʻ��Ѿ����ڣ�����������ȷ,��ʼ�ڽ��׼�¼���в�����ؼ�¼
		}
		else
			MessageBox("�������������û�");
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
		if(strName!="")//ȷ�����û�����
		{
			this->ReadExchangeRecord(strName);//���ʻ��Ѿ����ڣ�����������ȷ,��ʼ�ڽ��׼�¼���в�����ؼ�¼
		}
		else
			MessageBox("�������������ʺţ������ʺ�����������!",NULL,MB_ICONERROR);
	}
}
CString CBowerPage::ReadRecord(void)
{
	CString strSqlText=_T("select UserName from UserInfo where CardId ='");
	CString strId=_T("");
	this->GetDlgItemText(IDC_CARDID_EDT,strId);
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
		this->SetDlgItemText(IDC_PASS_EDT,NULL);
		delete pUserNameInfo;
		delete ado;
		return NULL;
	}
	else//�����������˺ţ��ڴ��趨����еڶ��е�����
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
			MessageBox("û�и��û��Ľ�����Ϣ��",NULL,MB_ICONQUESTION);
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
	m_BowerList.InsertColumn(0,"�����ʺ�",LVCFMT_LEFT,100);
	m_BowerList.InsertColumn(1,"����",LVCFMT_LEFT,60);
	m_BowerList.InsertColumn(2,"���(Ԫ)",LVCFMT_LEFT,80);
	m_BowerList.InsertColumn(3,"��Ϣ(Ԫ)",LVCFMT_LEFT,80);
	m_BowerList.InsertColumn(4,"����ʱ��",LVCFMT_LEFT,80);
	m_BowerList.InsertColumn(5,"��/ȡ",LVCFMT_LEFT,50);
	m_BowerList.InsertColumn(6,"��������",LVCFMT_LEFT,60);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->SetDlgItemText(IDC_CARDID_EDT,NULL);
	this->SetDlgItemText(IDC_PASS_EDT,NULL);
	m_BowerList.DeleteAllItems();
}

void CBowerPage::OnBnClickedPrintBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CPrintDlg *pPrintDlg=NULL;
	pPrintDlg=new CPrintDlg();
	if(pPrintDlg->DoModal()==IDOK)
	{
		this->PrintTable();//��ӡ���ݱ�

	}
	delete pPrintDlg;
}

void CBowerPage::PrintTable(void)
{
}

void CBowerPage::OnLvnItemchangedUserList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
