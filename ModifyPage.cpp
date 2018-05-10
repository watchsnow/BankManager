//Download by http://www.NewXing.com
// ModifyPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BankManager.h"
#include "ModifyPage.h"
#include ".\modifypage.h"
#include "AdoWorker.h"
#include "_StructDefine.h"
#include "PrintDlg.h"


// CModifyPage �Ի���

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


// CModifyPage ��Ϣ�������

BOOL CModifyPage::OnInitDialog()
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
	/////////////////////////////////���崰�����ý���
	/////////////////////////////////��ʼ����Edit�����������ݵĸ���
	m_PassWordEdt.SetLimitText(8);
	m_CardIdEdt.SetLimitText(12);
	m_NewPassEdt.SetLimitText(8);
	/////////////////////////////////�������������봰��
	m_GroupStc.ShowWindow(SW_HIDE);
	m_NewStc.ShowWindow(SW_HIDE);
	m_NewPassEdt.ShowWindow(SW_HIDE);
	//��ʼ���б��
	this->OnInitList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CModifyPage::OnInitList(void)
{
	m_UserList.InsertColumn(0,"�ʺ�",LVCFMT_LEFT,120);
	m_UserList.InsertColumn(1,"����",LVCFMT_LEFT,80);
	m_UserList.InsertColumn(2,"�Ա�",LVCFMT_LEFT,60);
	m_UserList.InsertColumn(3,"���֤����",LVCFMT_LEFT,130);
	m_UserList.InsertColumn(4,"�ƶ��绰",LVCFMT_LEFT,100);
	m_UserList.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_UserList.InsertItem(0,NULL);
}

void CModifyPage::OnEnChangeCardidEdt()
{
	CString strCardID=_T("");
	this->GetDlgItemText(IDC_CARDID_EDT,strCardID);
	m_UserList.SetItemText(0,0,strCardID);//�����ʺ���
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
		if(this->ReadRecord())//�û�����
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
		if(this->ReadRecord())//���û�����
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

BOOL CModifyPage::ReadRecord(void)//����������˺ź������ѯ���ݿ⣬�жϸ��ʺ��Ƿ���ڣ��������Ƿ���ȷ
{
	CString strSqlText=_T("select * from UserInfo where CardId ='");
	CString strId=_T("");
	strId=m_UserList.GetItemText(0,0);
	strSqlText=strSqlText+strId+CString("' and UserPass ='");
	//��ʼ��������ѯ����
	CString strPass=_T("");
	this->GetDlgItemText(IDC_PASS_EDT,strPass);
	strSqlText=strSqlText+strPass+CString("'");
	//////////////////////////////////����SQL���ִ����ʵ��
	AdoWorker *ado=NULL;
	_UserInfo *pUserInfo=NULL;
	ado=new AdoWorker();
	pUserInfo=(_UserInfo *)ado->ExecuteSql(strSqlText,1);
	CString strUserInfo=_T("");
	if(pUserInfo==NULL)
	{
		MessageBox(" �����ڸ��ʺŻ�����������ʺź��������ȷ�ԣ�",NULL,MB_ICONERROR);
		delete pUserInfo;
		delete ado;
		return FALSE;
	}
	else//�����������˺ţ��ڴ��趨����е�һ�е���������
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
	//������������λ��
	CString strCheck=_T("");
	this->GetDlgItemText(IDC_NEWPASS_EDT,strCheck);
	int iSum=0;
	iSum=strCheck.GetLength();
	if(iSum!=8)
	{
		MessageBox("�������λ��ӦΪ8λ,��������",NULL,MB_ICONERROR);
		return;
	}
	//��������ȷ����ʼ��֯SQL��䣬д���ݿ�
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
			this->PrintTable();//��ӡ���ݱ�

		}
		delete pPrintDlg;
		MessageBox("�޸�����ɹ���",NULL,MB_ICONASTERISK);
		this->EmptyTable();
	}
	else
		MessageBox("�޸����벻�ɹ���",NULL,MB_ICONERROR);

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->EmptyTable();
}
void CModifyPage::PrintTable()
{
}