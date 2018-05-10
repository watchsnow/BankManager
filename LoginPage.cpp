//Download by http://www.NewXing.com
// LoginPage.cpp : 实现文件
//

#include "stdafx.h"
#include "BankManager.h"
#include "LoginPage.h"
#include ".\loginpage.h"
#include "AdoWorker.h"
#include "_StructDefine.h"
#include "PrintDlg.h"
// CLoginPage 对话框

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
// CLoginPage 消息处理程序

BOOL CLoginPage::OnInitDialog()
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
	/////////////////////////////////开始设置Edit框中容纳数据的个数
	m_PassKeyEdt.SetLimitText(8);
	m_IndentityIdEdt.SetLimitText(18);
	m_Phone.SetLimitText(12);
	m_Name.SetLimitText(10);
	//初始化列表框
	this->OnInitList();
	//////////////////////////////////初始化组合框
	CComboBox * pBo=(CComboBox*)this->GetDlgItem(IDC_CANTON_COMB);
	pBo->AddString("湖南");
	pBo->AddString("广东");
	pBo->SetCurSel(0);
	pBo=(CComboBox*)this->GetDlgItem(IDC_SECTION_COMB);
	pBo->AddString("长沙");
	pBo->AddString("湘潭");
	pBo->AddString("常德");
	pBo->SetCurSel(0);
	//this->OnCbnSelchangeSectionComb();
	//////////////////////////////////初始化帐号类型组合框
	pBo=(CComboBox*)this->GetDlgItem(IDC_TYPE_COMB);
	pBo->AddString("活期");
	pBo->AddString("定期");
	pBo->SetCurSel(0);
	this->OnCbnSelchangeTypeComb();
	///////////////////////////////////初始化男女组合框
	pBo=(CComboBox*)this->GetDlgItem(IDC_SEX_COMB);
	pBo->AddString("男");
	pBo->AddString("女");
	pBo->SetCurSel(0);
	this->OnCbnSelchangeSexComb();
    ////////////////////////////////组合框初始化结束
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CLoginPage::OnCbnSelchangeCantonComb()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strComBox=_T("");
	this->GetDlgItemText(IDC_CANTON_COMB,strComBox);
	CComboBox * pBo=NULL;
	int iCount=0;
	if(strComBox=="湖南")
	{
		pBo=(CComboBox*)this->GetDlgItem(IDC_SECTION_COMB);
		iCount=pBo->GetCount();
		for(;iCount>=0;iCount--)
			pBo->DeleteString(iCount);
		pBo->AddString("长沙");
		pBo->AddString("湘潭");
		pBo->AddString("常德");
		pBo->SetCurSel(0);
	}
	if(strComBox=="广东")
	{
		pBo=(CComboBox*)this->GetDlgItem(IDC_SECTION_COMB);
		iCount=pBo->GetCount();
		for(;iCount>=0;iCount--)
			pBo->DeleteString(iCount);
		pBo->AddString("深圳");
		pBo->AddString("广州");
		pBo->AddString("佛山");
		pBo->SetCurSel(0);
	}
	//初始化
	this->OnCbnSelchangeSectionComb();
}

void CLoginPage::OnCbnSelchangeSectionComb()
{
	//在此处开始自动生成帐号的前半部分
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

//自动生成帐号的前本部分
CString CLoginPage::AutoCreateID(CString canton, CString section,CString type)
{
	CString strID=_T("");
	////////////////////////////////////////////////////////
	if(type=="活期")
		strID=_T("01");
	else if(type==_T("定期"))
		strID=_T("02");
		  else
				{
					strID=_T("ERROR");
					return strID;
				}
	/////////////////////////////////////////////////////////
	if(canton=="湖南")
		strID+=_T("01");
	else if(canton=="广东")
			strID+=_T("02");
		 else
		 {
			strID=_T("ERROR");
			return strID;
		 }
	////////////////////////////////////////////////////////
	if(section=="长沙")
		strID+=_T("001");
	else if(section=="湘潭")
		  strID+=_T("002");
	     else if(section=="常德")
		         strID+=_T("003");
			  else if(section=="深圳")
						strID+=_T("001");
				   else	if(section=="广州")
						strID+=_T("002");
						else if(section=="佛山")
								strID+=_T("003");
							 else
							 {
								strID=_T("ERROR");
								return strID ;
							 }
	m_LoginList.SetItemText(0,0,strID);
	/////////////////////////////////////////////////////////////前半部分账号生成完成，开始读书数据记录生成后半部分
    int iRecord=0;
	iRecord=this->ReadHistory();
	CString strIFormat=_T("");
	strIFormat=this->IntFormat(iRecord);
	strID+=strIFormat;
	return strID;
}
void CLoginPage::OnInitList(void)
{
	m_LoginList.InsertColumn(0,"帐号(自动生成)",LVCFMT_LEFT,120);
	m_LoginList.InsertColumn(1,"姓名",LVCFMT_LEFT,80);
	m_LoginList.InsertColumn(2,"性别",LVCFMT_LEFT,60);
	m_LoginList.InsertColumn(3,"身份证号码",LVCFMT_LEFT,130);
	m_LoginList.InsertColumn(4,"移动电话",LVCFMT_LEFT,100);
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
	//////////////////////////////////创建SQL语句
	CString strSqlText=_T("select count(*) from UserInfo where CardId like '");
	CString strId=_T("");
	strId=m_LoginList.GetItemText(0,0);
	strSqlText=strSqlText+strId+CString("%'");
    //////////////////////////////////创建SQL语句执行类实例
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
void CLoginPage::OnBnClickedLoginbtn()//检验输入是否正确，正确后写数据库
{
	if(this->CheckNeed())//检查输入是否正确，若是正确，开始写数据库
	{
		CString strSqlText=_T("insert into UserInfo (CardId,UserName,UserSex,UserId,UserPhone,UserPass) values ('");
		CString strUserInput=_T("");
		CString strSign=_T("','");
		/////////////////////////////////从表格中读取数
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
		if(ado->ExecuteSql(strSqlText))//里面开始打印设置和清空数据
			{
				CPrintDlg *pPrintDlg=NULL;
				pPrintDlg=new CPrintDlg();
				if(pPrintDlg->DoModal()==IDOK)
				{
					this->PrintTable();//打印数据表

				}
				delete pPrintDlg;
				MessageBox("用户注册成功！",NULL,MB_ICONASTERISK);
				this->EmptyTable();				
			}
		delete ado;
	}
	return ;
}
bool CLoginPage::CheckNeed(void)
{
	CString strUserInput=_T("");
	/////////////////////////////////从表格中读取数据
	 strUserInput=m_LoginList.GetItemText(0,1);
	if(strUserInput=="")
	{
		MessageBox("未输入用户姓名，不能完成注册！",NULL,MB_ICONERROR);
		return false;
	}
	 strUserInput=m_LoginList.GetItemText(0,3);
	 if(strUserInput=="")
	 {
		 MessageBox("未输入用户身份证号码，不能完成注册！",NULL,MB_ICONERROR);
		 return false;
	 }
	 strUserInput=m_LoginList.GetItemText(0,4);
	 if(strUserInput=="")
	 {
		 MessageBox("未输入联系方式，不能完成注册！",NULL,MB_ICONERROR);
		 return false;
	 }
	 strUserInput=_T("");
	 this->GetDlgItemText(IDC_PASS_EIT,strUserInput);
	 if(strUserInput.GetLength()!=8)
	 {
		 MessageBox("账号密码没有8位，不能完成注册！",NULL,MB_ICONERROR);
		 return false;
	 }
	return true;
}

void CLoginPage::EmptyTable(void)
{
	///////////////// 清空资料填写控件
	this->SetDlgItemText(IDC_NAME_EDT,NULL);
	this->SetDlgItemText(IDC_IDENTITY_EDT,NULL);
	this->SetDlgItemText(IDC_PHONE_EDT,NULL);
	this->SetDlgItemText(IDC_PASS_EIT,NULL);
	m_LoginList.DeleteItem(0);//删除表格中的所有行(就0行)
	m_LoginList.InsertItem(0,NULL);//新插入一行
	this->OnCbnSelchangeSexComb();//将性别填入表格
	this->OnCbnSelchangeTypeComb();//自动重新生成账号
}

void CLoginPage::OnBnClickedCancelBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	this->EmptyTable();
}
void CLoginPage::PrintTable(void)
{

}

void CLoginPage::OnEnChangePassEit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
    MessageBox("");
	// TODO:  在此添加控件通知处理程序代码
}
