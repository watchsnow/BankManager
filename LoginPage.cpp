//Download by http://www.NewXing.com
// LoginPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BankManager.h"
#include "LoginPage.h"
#include ".\loginpage.h"
#include "AdoWorker.h"
#include "_StructDefine.h"
#include "PrintDlg.h"
// CLoginPage �Ի���

IMPLEMENT_DYNAMIC(CLoginPage, CDialog)
CLoginPage::CLoginPage(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginPage::IDD, pParent)
{
}

CLoginPage::~CLoginPage()
{
}

void CLoginPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOGIN_LIST, m_LoginList);
	DDX_Control(pDX, IDC_TYPE_COMB, m_TypeComb);
	DDX_Control(pDX, IDC_PASS_EIT, m_PassKeyEdt);
	DDX_Control(pDX, IDC_IDENTITY_EDT, m_IndentityIdEdt);
	DDX_Control(pDX, IDC_PHONE_EDT, m_Phone);
	DDX_Control(pDX, IDC_NAME_EDT, m_Name);
}


BEGIN_MESSAGE_MAP(CLoginPage, CDialog)
ON_CBN_SELCHANGE(IDC_CANTON_COMB, OnCbnSelchangeCantonComb)
ON_CBN_SELCHANGE(IDC_SECTION_COMB, OnCbnSelchangeSectionComb)
ON_EN_CHANGE(IDC_NAME_EDT, OnEnChangeNameEdt)
ON_EN_CHANGE(IDC_IDENTITY_EDT, OnEnChangeIdentityEdt)
ON_CBN_SELCHANGE(IDC_SEX_COMB, OnCbnSelchangeSexComb)
ON_EN_CHANGE(IDC_PHONE_EDT, OnEnChangePhoneEdt)
ON_BN_CLICKED(IDC_LOGIN_BTN, OnBnClickedLoginbtn)
ON_BN_CLICKED(IDOK, OnBnClickedOk)
ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
ON_CBN_SELCHANGE(IDC_TYPE_COMB, OnCbnSelchangeTypeComb)
ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
ON_EN_CHANGE(IDC_PASS_EIT, OnEnChangePassEit)
END_MESSAGE_MAP()
// CLoginPage ��Ϣ�������

BOOL CLoginPage::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//////////////////////////////////��ʼ���ƶ�����λ��
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
	m_PassKeyEdt.SetLimitText(8);
	m_IndentityIdEdt.SetLimitText(18);
	m_Phone.SetLimitText(12);
	m_Name.SetLimitText(10);
	//��ʼ���б��
	this->OnInitList();
	//////////////////////////////////��ʼ����Ͽ�
	CComboBox * pBo=(CComboBox*)this->GetDlgItem(IDC_CANTON_COMB);
	pBo->AddString("����");
	pBo->AddString("�㶫");
	pBo->SetCurSel(0);
	pBo=(CComboBox*)this->GetDlgItem(IDC_SECTION_COMB);
	pBo->AddString("��ɳ");
	pBo->AddString("��̶");
	pBo->AddString("����");
	pBo->SetCurSel(0);
	//this->OnCbnSelchangeSectionComb();
	//////////////////////////////////��ʼ���ʺ�������Ͽ�
	pBo=(CComboBox*)this->GetDlgItem(IDC_TYPE_COMB);
	pBo->AddString("����");
	pBo->AddString("����");
	pBo->SetCurSel(0);
	this->OnCbnSelchangeTypeComb();
	///////////////////////////////////��ʼ����Ů��Ͽ�
	pBo=(CComboBox*)this->GetDlgItem(IDC_SEX_COMB);
	pBo->AddString("��");
	pBo->AddString("Ů");
	pBo->SetCurSel(0);
	this->OnCbnSelchangeSexComb();
    ////////////////////////////////��Ͽ��ʼ������
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CLoginPage::OnCbnSelchangeCantonComb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strComBox=_T("");
	this->GetDlgItemText(IDC_CANTON_COMB,strComBox);
	CComboBox * pBo=NULL;
	int iCount=0;
	if(strComBox=="����")
	{
		pBo=(CComboBox*)this->GetDlgItem(IDC_SECTION_COMB);
		iCount=pBo->GetCount();
		for(;iCount>=0;iCount--)
			pBo->DeleteString(iCount);
		pBo->AddString("��ɳ");
		pBo->AddString("��̶");
		pBo->AddString("����");
		pBo->SetCurSel(0);
	}
	if(strComBox=="�㶫")
	{
		pBo=(CComboBox*)this->GetDlgItem(IDC_SECTION_COMB);
		iCount=pBo->GetCount();
		for(;iCount>=0;iCount--)
			pBo->DeleteString(iCount);
		pBo->AddString("����");
		pBo->AddString("����");
		pBo->AddString("��ɽ");
		pBo->SetCurSel(0);
	}
	//��ʼ��
	this->OnCbnSelchangeSectionComb();
}

void CLoginPage::OnCbnSelchangeSectionComb()
{
	//�ڴ˴���ʼ�Զ������ʺŵ�ǰ�벿��
	CString strCanton=_T("");
	CString strSection=_T("");
	CString strType=_T("");
	this->GetDlgItemText(IDC_CANTON_COMB,strCanton);
	this->GetDlgItemText(IDC_SECTION_COMB,strSection);
    this->GetDlgItemText(IDC_TYPE_COMB,strType);
	CString strCardID=_T("");
	strCardID=this->AutoCreateID(strCanton,strSection,strType);
	m_LoginList.SetItemText(0,0,strCardID);
}

//�Զ������ʺŵ�ǰ������
CString CLoginPage::AutoCreateID(CString canton, CString section,CString type)
{
	CString strID=_T("");
	////////////////////////////////////////////////////////
	if(type=="����")
		strID=_T("01");
	else if(type==_T("����"))
		strID=_T("02");
		  else
				{
					strID=_T("ERROR");
					return strID;
				}
	/////////////////////////////////////////////////////////
	if(canton=="����")
		strID+=_T("01");
	else if(canton=="�㶫")
			strID+=_T("02");
		 else
		 {
			strID=_T("ERROR");
			return strID;
		 }
	////////////////////////////////////////////////////////
	if(section=="��ɳ")
		strID+=_T("001");
	else if(section=="��̶")
		  strID+=_T("002");
	     else if(section=="����")
		         strID+=_T("003");
			  else if(section=="����")
						strID+=_T("001");
				   else	if(section=="����")
						strID+=_T("002");
						else if(section=="��ɽ")
								strID+=_T("003");
							 else
							 {
								strID=_T("ERROR");
								return strID ;
							 }
	m_LoginList.SetItemText(0,0,strID);
	/////////////////////////////////////////////////////////////ǰ�벿���˺�������ɣ���ʼ�������ݼ�¼���ɺ�벿��
    int iRecord=0;
	iRecord=this->ReadHistory();
	CString strIFormat=_T("");
	strIFormat=this->IntFormat(iRecord);
	strID+=strIFormat;
	return strID;
}
void CLoginPage::OnInitList(void)
{
	m_LoginList.InsertColumn(0,"�ʺ�(�Զ�����)",LVCFMT_LEFT,120);
	m_LoginList.InsertColumn(1,"����",LVCFMT_LEFT,80);
	m_LoginList.InsertColumn(2,"�Ա�",LVCFMT_LEFT,60);
	m_LoginList.InsertColumn(3,"���֤����",LVCFMT_LEFT,130);
	m_LoginList.InsertColumn(4,"�ƶ��绰",LVCFMT_LEFT,100);
	m_LoginList.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_LoginList.InsertItem(0,NULL);
	return ;
}

void CLoginPage::OnEnChangeNameEdt()
{
    CString strName=_T("");
	this->GetDlgItemText(IDC_NAME_EDT,strName);
	m_LoginList.SetItemText(0,1,strName);

}

void CLoginPage::OnEnChangeIdentityEdt()
{
	CString strID=_T("");
	this->GetDlgItemText(IDC_IDENTITY_EDT,strID);
	m_LoginList.SetItemText(0,3,strID);
}
void CLoginPage::OnCbnSelchangeSexComb()
{
	CString strSex=_T("");
	this->GetDlgItemText(IDC_SEX_COMB,strSex);
	m_LoginList.SetItemText(0,2,strSex);
}
void CLoginPage::OnEnChangePhoneEdt()
{
	CString strPhone=_T("");
	this->GetDlgItemText(IDC_PHONE_EDT,strPhone);
	m_LoginList.SetItemText(0,4,strPhone);
}
void CLoginPage::OnBnClickedOk()
{
}
void CLoginPage::OnBnClickedCancel()
{
}
void CLoginPage::OnCbnSelchangeTypeComb()
{
	this->OnCbnSelchangeSectionComb();
}

long CLoginPage::ReadHistory(void)
{
	//////////////////////////////////����SQL���
	CString strSqlText=_T("select count(*) from UserInfo where CardId like '");
	CString strId=_T("");
	strId=m_LoginList.GetItemText(0,0);
	strSqlText=strSqlText+strId+CString("%'");
    //////////////////////////////////����SQL���ִ����ʵ��
	AdoWorker *ado=NULL;
	_IntInfo *pIntInfo=NULL;
	ado=new AdoWorker();
    pIntInfo=(_IntInfo *)ado->ExecuteSql(strSqlText,0);
	long iCardSum=10;
	iCardSum=pIntInfo->lSum;
	delete pIntInfo;
	delete ado;
	return iCardSum;
}

CString CLoginPage::IntFormat(long iRecord)
{
	CString strI=_T("");
	strI.Format("%d",iRecord);
	int istrLen=0;
	istrLen=strI.GetLength();
	int i0Len=0;
	i0Len=5-istrLen;
	CString str0=_T("");
	for(;i0Len>0;i0Len--)
		str0+=_T("0");
	str0+=strI;
	return str0;
}
void CLoginPage::OnBnClickedLoginbtn()//���������Ƿ���ȷ����ȷ��д���ݿ�
{
	if(this->CheckNeed())//��������Ƿ���ȷ��������ȷ����ʼд���ݿ�
	{
		CString strSqlText=_T("insert into UserInfo (CardId,UserName,UserSex,UserId,UserPhone,UserPass) values ('");
		CString strUserInput=_T("");
		CString strSign=_T("','");
		/////////////////////////////////�ӱ���ж�ȡ��
		strUserInput=m_LoginList.GetItemText(0,0);
		strSqlText=strSqlText+strUserInput+strSign;
		strUserInput=m_LoginList.GetItemText(0,1);
		strSqlText=strSqlText+strUserInput+strSign;
		strUserInput=m_LoginList.GetItemText(0,2);
		strSqlText=strSqlText+strUserInput+strSign;
		strUserInput=m_LoginList.GetItemText(0,3);
		strSqlText=strSqlText+strUserInput+strSign;
		strUserInput=m_LoginList.GetItemText(0,4);
		strSqlText=strSqlText+strUserInput+strSign;
		this->GetDlgItemText(IDC_PASS_EIT,strUserInput);
		strSqlText=strSqlText+strUserInput+CString("')");
		AdoWorker *ado=NULL;
		ado=new AdoWorker();
		if(ado->ExecuteSql(strSqlText))//���濪ʼ��ӡ���ú��������
			{
				CPrintDlg *pPrintDlg=NULL;
				pPrintDlg=new CPrintDlg();
				if(pPrintDlg->DoModal()==IDOK)
				{
					this->PrintTable();//��ӡ���ݱ�

				}
				delete pPrintDlg;
				MessageBox("�û�ע��ɹ���",NULL,MB_ICONASTERISK);
				this->EmptyTable();				
			}
		delete ado;
	}
	return ;
}
bool CLoginPage::CheckNeed(void)
{
	CString strUserInput=_T("");
	/////////////////////////////////�ӱ���ж�ȡ����
	 strUserInput=m_LoginList.GetItemText(0,1);
	if(strUserInput=="")
	{
		MessageBox("δ�����û��������������ע�ᣡ",NULL,MB_ICONERROR);
		return false;
	}
	 strUserInput=m_LoginList.GetItemText(0,3);
	 if(strUserInput=="")
	 {
		 MessageBox("δ�����û����֤���룬�������ע�ᣡ",NULL,MB_ICONERROR);
		 return false;
	 }
	 strUserInput=m_LoginList.GetItemText(0,4);
	 if(strUserInput=="")
	 {
		 MessageBox("δ������ϵ��ʽ���������ע�ᣡ",NULL,MB_ICONERROR);
		 return false;
	 }
	 strUserInput=_T("");
	 this->GetDlgItemText(IDC_PASS_EIT,strUserInput);
	 if(strUserInput.GetLength()!=8)
	 {
		 MessageBox("�˺�����û��8λ���������ע�ᣡ",NULL,MB_ICONERROR);
		 return false;
	 }
	return true;
}

void CLoginPage::EmptyTable(void)
{
	///////////////// ���������д�ؼ�
	this->SetDlgItemText(IDC_NAME_EDT,NULL);
	this->SetDlgItemText(IDC_IDENTITY_EDT,NULL);
	this->SetDlgItemText(IDC_PHONE_EDT,NULL);
	this->SetDlgItemText(IDC_PASS_EIT,NULL);
	m_LoginList.DeleteItem(0);//ɾ������е�������(��0��)
	m_LoginList.InsertItem(0,NULL);//�²���һ��
	this->OnCbnSelchangeSexComb();//���Ա�������
	this->OnCbnSelchangeTypeComb();//�Զ����������˺�
}

void CLoginPage::OnBnClickedCancelBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->EmptyTable();
}
void CLoginPage::PrintTable(void)
{

}

void CLoginPage::OnEnChangePassEit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
    MessageBox("");
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
