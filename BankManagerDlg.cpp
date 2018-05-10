//Download by http://www.NewXing.com
// BankManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BankManager.h"
#include "BankManagerDlg.h"
#include ".\bankmanagerdlg.h"
#include "SkinPlusPlus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CBankManagerDlg �Ի���



CBankManagerDlg::CBankManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBankManagerDlg::IDD, pParent),m_LoginPage(NULL),m_SavingPage(NULL),m_FetchPage(NULL)
	,m_ModifyPage(NULL),m_BowerPage(NULL),m_DeletePage(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBankManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOGINCHK, m_LoginChk);
	DDX_Control(pDX, IDC_SAVINGCHK, m_SavingChk);
	DDX_Control(pDX, IDC_FETCHCHK, m_FetchChk);
	DDX_Control(pDX, IDC_CHANGEPWCHK, m_ChangePwChk);
	DDX_Control(pDX, IDC_EXCHANGECHK, m_ExchangeChk);
	DDX_Control(pDX, IDC_DELETEUSERCHK, m_DeleteLoginChk);
	DDX_Control(pDX, IDC_CHOOSESTC, m_ChooseStc);
	DDX_Control(pDX, IDC_WORKSTC, m_WorkStc);
	DDX_Control(pDX, IDC_CANCELBTN, m_CancelBtn);
}

BEGIN_MESSAGE_MAP(CBankManagerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_LOGINCHK, OnBnClickedLoginchk)
	ON_BN_CLICKED(IDC_SAVINGCHK, OnBnClickedSavingchk)
	ON_BN_CLICKED(IDC_FETCHCHK, OnBnClickedFetchchk)
	ON_BN_CLICKED(IDC_CHANGEPWCHK, OnBnClickedChangepwchk)
	ON_BN_CLICKED(IDC_EXCHANGECHK, OnBnClickedExchangechk)
	ON_BN_CLICKED(IDC_DELETEUSERCHK, OnBnClickedDeleteuserchk)
	ON_BN_CLICKED(IDC_CANCELBTN, OnBnClickedCancelbtn)
END_MESSAGE_MAP()


// CBankManagerDlg ��Ϣ�������

BOOL CBankManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	if(!(this->OnInitChk())||!(this->OnInitPage()))
		return FALSE;
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CBankManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBankManagerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CBankManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBankManagerDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnOK();
}

void CBankManagerDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnCancel();
}

void CBankManagerDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_pConnection->State) 
		m_pConnection->Close();
	CDialog::OnCancel();
	CDialog::OnClose();
}

int CBankManagerDlg::OnInitChk(void)
{
	//ȡ����߷�������Ļ����
	HWND hWnd;
	hWnd=m_ChooseStc.GetSafeHwnd();
	CWnd *pWnd;
	pWnd=this->FromHandle(hWnd);
	CRect lpRect;
	pWnd->GetWindowRect(lpRect);
	this->ScreenToClient(lpRect);
	//�� lpRect�б�������߷������û���������
	//��ʼ����6����ť����ʽ��λ��
	//��ʼ��������Ϣ
	int iChkWide=lpRect.right-lpRect.left-2;//ÿ����ť�Ŀ��
	int iChkHeight=(lpRect.bottom-lpRect.top-15)/6;//ÿ����ť�ĸ߶�
	int iChkLeft=lpRect.left+2;//��һ����ť���Ͻ�x����
	int iChkTop=lpRect.top+15;//��һ����ť�����Ͻ�Y����
	///////////////////////////////////////////////// �������һ��ͼ�갴ť
	hWnd=m_LoginChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_LoginChk.SetIcon(IDI_KEY2ICO,IDI_KEY1ICO);
	m_LoginChk.SetTooltipText(_T("�����û�ע��Ĺ�����������д������ݣ����ע�ᣡ"));
	m_LoginChk.DrawTransparent(TRUE);
	m_LoginChk.MoveWindow(iChkLeft,iChkTop,iChkWide,iChkHeight);//�ƶ���һ����ť
	m_LoginChk.SetCheck(1);
    iChkTop+=iChkHeight;
	////////////////////////////////////////////////��һ��ͼ�갴ť�������
	///////////////////////////////////////////////// �������һ��ͼ�갴ť
	hWnd=m_SavingChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_SavingChk.SetIcon(IDI_KEY2ICO,IDI_KEY1ICO);
	m_SavingChk.SetTooltipText(_T("�򿪴�����������д������ݣ���ɴ�"));
	m_SavingChk.DrawTransparent(TRUE);
	m_SavingChk.MoveWindow(iChkLeft,iChkTop,iChkWide,iChkHeight);//�ƶ���һ����ť
	iChkTop+=iChkHeight;
	////////////////////////////////////////////////��һ��ͼ�갴ť�������
	///////////////////////////////////////////////// �������һ��ͼ�갴ť
	hWnd=m_FetchChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_FetchChk.SetIcon(IDI_KEY2ICO,IDI_KEY1ICO);
	m_FetchChk.SetTooltipText(_T("��ȡ�����������д������ݣ����ȡ�"));
	m_FetchChk.DrawTransparent(TRUE);
	m_FetchChk.MoveWindow(iChkLeft,iChkTop,iChkWide,iChkHeight);//�ƶ���һ����ť
	iChkTop+=iChkHeight;
	////////////////////////////////////////////////��һ��ͼ�갴ť�������
	///////////////////////////////////////////////// �������һ��ͼ�갴ť
	hWnd=m_ChangePwChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_ChangePwChk.SetIcon(IDI_KEY2ICO,IDI_KEY1ICO);
	m_ChangePwChk.SetTooltipText(_T("���û��޸�����Ĺ�����������д������ݣ���������޸ģ�"));
	m_ChangePwChk.DrawTransparent(TRUE);
	m_ChangePwChk.MoveWindow(iChkLeft,iChkTop,iChkWide,iChkHeight);//�ƶ���һ����ť
	iChkTop+=iChkHeight;
	////////////////////////////////////////////////��һ��ͼ�갴ť�������
	///////////////////////////////////////////////// �������һ��ͼ�갴ť
	hWnd=m_ExchangeChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_ExchangeChk.SetIcon(IDI_KEY2ICO,IDI_KEY1ICO);
	m_ExchangeChk.SetTooltipText(_T("�򿪽��ײ�ѯ�Ĺ�����������д������ݣ����ע�ᣡ"));
	m_ExchangeChk.DrawTransparent(TRUE);
	m_ExchangeChk.MoveWindow(iChkLeft,iChkTop,iChkWide,iChkHeight);//�ƶ���һ����ť
	iChkTop+=iChkHeight;
	////////////////////////////////////////////////��һ��ͼ�갴ť�������
	///////////////////////////////////////////////// �������һ��ͼ�갴ť
	hWnd=m_DeleteLoginChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_DeleteLoginChk.SetIcon(IDI_KEY2ICO,IDI_KEY1ICO);
	m_DeleteLoginChk.SetTooltipText(_T("������������������д������ݣ�����û���ע����"));
	m_DeleteLoginChk.DrawTransparent(TRUE);
	m_DeleteLoginChk.MoveWindow(iChkLeft,iChkTop,iChkWide,iChkHeight);//�ƶ���һ����ť
	////////////////////////////////////////////////��һ��ͼ�갴ť�������
	//�����˳���ť
	hWnd=m_CancelBtn.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_CancelBtn.SetIcon(IDI_CANCELICO);
	m_CancelBtn.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);
	m_CancelBtn.SetTooltipText(_T("�˳��˳���"));
	m_CancelBtn.DrawTransparent(TRUE);
	
	return 1;
}

void CBankManagerDlg::OnBnClickedLoginchk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_LoginChk.SetCheck(1);
	m_SavingChk.SetCheck(0);
	m_FetchChk.SetCheck(0);
	m_ChangePwChk.SetCheck(0);
	m_ExchangeChk.SetCheck(0);
	m_DeleteLoginChk.SetCheck(0);
	m_SavingPage.ShowWindow(SW_HIDE);
	m_FetchPage.ShowWindow(SW_HIDE);
	m_ModifyPage.ShowWindow(SW_HIDE);
	m_BowerPage.ShowWindow(SW_HIDE);
	m_DeletePage.ShowWindow(SW_HIDE);
	///////////////////////////////////////
	m_LoginPage.ShowWindow(SW_SHOW);
	

}

void CBankManagerDlg::OnBnClickedSavingchk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_LoginChk.SetCheck(0);
	m_SavingChk.SetCheck(1);
	m_FetchChk.SetCheck(0);
	m_ChangePwChk.SetCheck(0);
	m_ExchangeChk.SetCheck(0);
	m_DeleteLoginChk.SetCheck(0);
	m_LoginPage.ShowWindow(SW_HIDE);
	m_FetchPage.ShowWindow(SW_HIDE);
	m_ModifyPage.ShowWindow(SW_HIDE);
	m_BowerPage.ShowWindow(SW_HIDE);
	m_DeletePage.ShowWindow(SW_HIDE);
	////////////////////////////////////////
	m_SavingPage.ShowWindow(SW_SHOW);
}

void CBankManagerDlg::OnBnClickedFetchchk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_LoginChk.SetCheck(0);
	m_SavingChk.SetCheck(0);
	m_FetchChk.SetCheck(1);
	m_ChangePwChk.SetCheck(0);
	m_ExchangeChk.SetCheck(0);
	m_DeleteLoginChk.SetCheck(0);
	m_LoginPage.ShowWindow(SW_HIDE);
	m_SavingPage.ShowWindow(SW_HIDE);
	m_ModifyPage.ShowWindow(SW_HIDE);
	m_BowerPage.ShowWindow(SW_HIDE);
	m_DeletePage.ShowWindow(SW_HIDE);
	//////////////////////////////////////////////////
	m_FetchPage.ShowWindow(SW_SHOW);
}

void CBankManagerDlg::OnBnClickedChangepwchk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_LoginChk.SetCheck(0);
	m_SavingChk.SetCheck(0);
	m_FetchChk.SetCheck(0);
	m_ChangePwChk.SetCheck(1);
	m_ExchangeChk.SetCheck(0);
	m_DeleteLoginChk.SetCheck(0);
	m_LoginPage.ShowWindow(SW_HIDE);
	m_SavingPage.ShowWindow(SW_HIDE);
	m_FetchPage.ShowWindow(SW_HIDE);
	m_BowerPage.ShowWindow(SW_HIDE);
	m_DeletePage.ShowWindow(SW_HIDE);
	//////////////////////////////////////////////////
	m_ModifyPage.ShowWindow(SW_SHOW);
}

void CBankManagerDlg::OnBnClickedExchangechk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_LoginChk.SetCheck(0);
	m_SavingChk.SetCheck(0);
	m_FetchChk.SetCheck(0);
	m_ChangePwChk.SetCheck(0);
	m_ExchangeChk.SetCheck(1);
	m_DeleteLoginChk.SetCheck(0);
	m_LoginPage.ShowWindow(SW_HIDE);
	m_SavingPage.ShowWindow(SW_HIDE);
	m_ModifyPage.ShowWindow(SW_HIDE);
	m_FetchPage.ShowWindow(SW_HIDE);
	m_DeletePage.ShowWindow(SW_HIDE);
	//////////////////////////////////////////////////
	m_BowerPage.ShowWindow(SW_SHOW);

	
}

void CBankManagerDlg::OnBnClickedDeleteuserchk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_LoginChk.SetCheck(0);
	m_SavingChk.SetCheck(0);
	m_FetchChk.SetCheck(0);
	m_ChangePwChk.SetCheck(0);
	m_ExchangeChk.SetCheck(0);
	m_DeleteLoginChk.SetCheck(1);
	m_FetchPage.ShowWindow(SW_HIDE);
	m_LoginPage.ShowWindow(SW_HIDE);
	m_SavingPage.ShowWindow(SW_HIDE);
	m_ModifyPage.ShowWindow(SW_HIDE);
	m_BowerPage.ShowWindow(SW_HIDE);
	//////////////////////////////////////////////////
	m_DeletePage.ShowWindow(SW_SHOW);

	
}

void CBankManagerDlg::OnBnClickedCancelbtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->OnClose();
}

// //������ʼ������������ҳ��
int CBankManagerDlg::OnInitPage(void)
{
	//ȡ���ұ߷�������Ļ����
	HWND hWnd;
	hWnd=m_WorkStc.GetSafeHwnd();
	CWnd *pWnd;
	pWnd=this->FromHandle(hWnd);
	CRect lpRect;
	pWnd->GetWindowRect(lpRect);
	this->ScreenToClient(lpRect);
	//�� lpRect�б������ұ߷������û���������
	//��ʼ����6����������ʽ��λ��
	//��ʼ��������Ϣ
	int iPageWide=lpRect.right-lpRect.left;//ÿ��page�Ŀ��
	int iPageHeight=(lpRect.bottom-lpRect.top);//ÿ��page�ĸ߶�
	int iPageLeft=lpRect.left;//��һ����ť���Ͻ�x����
	int iPageTop=lpRect.top;//��һ����ť�����Ͻ�Y����
	///////////////////////////////////////////////// �����page
	//��ʼ�����ұ�ҳ���е�6���������򴰿�
	m_LoginPage.Create(IDD_LOGIN_PAGE,pWnd);
	m_LoginPage.ShowWindow(SW_SHOW);
	//////////////////////////
	m_SavingPage.Create(IDD_SAVING_PAGE,pWnd);
	m_SavingPage.ShowWindow(SW_HIDE);
	//////////////////////////
	m_FetchPage.Create(IDD_FETCH_PAGE,pWnd);
	m_FetchPage.ShowWindow(SW_HIDE);
	/////////////////////////
	m_ModifyPage.Create(IDD_MODIFY_PAGE,pWnd);
	m_ModifyPage.ShowWindow(SW_HIDE);
	/////////////////////////
	m_BowerPage.Create(IDD_BOWER_PAGE,pWnd);
	m_BowerPage.ShowWindow(SW_HIDE);
	////////////////////////
	m_DeletePage.Create(IDD_DELETE_PAGE,pWnd);
	m_DeletePage.ShowWindow(SW_HIDE);
	////////////////////////////////////////////////page�������
	return 1;
}
