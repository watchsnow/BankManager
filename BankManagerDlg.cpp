//Download by http://www.NewXing.com
// BankManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BankManager.h"
#include "BankManagerDlg.h"
#include ".\bankmanagerdlg.h"
#include "SkinPlusPlus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CBankManagerDlg 对话框



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


// CBankManagerDlg 消息处理程序

BOOL CBankManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	if(!(this->OnInitChk())||!(this->OnInitPage()))
		return FALSE;
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBankManagerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CBankManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBankManagerDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnOK();
}

void CBankManagerDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnCancel();
}

void CBankManagerDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_pConnection->State) 
		m_pConnection->Close();
	CDialog::OnCancel();
	CDialog::OnClose();
}

int CBankManagerDlg::OnInitChk(void)
{
	//取得左边分组框的屏幕坐标
	HWND hWnd;
	hWnd=m_ChooseStc.GetSafeHwnd();
	CWnd *pWnd;
	pWnd=this->FromHandle(hWnd);
	CRect lpRect;
	pWnd->GetWindowRect(lpRect);
	this->ScreenToClient(lpRect);
	//在 lpRect中保存了左边分组框的用户区域坐标
	//开始处理6个按钮的样式和位置
	//初始化坐标信息
	int iChkWide=lpRect.right-lpRect.left-2;//每个按钮的宽度
	int iChkHeight=(lpRect.bottom-lpRect.top-15)/6;//每个按钮的高度
	int iChkLeft=lpRect.left+2;//第一个按钮左上角x坐标
	int iChkTop=lpRect.top+15;//第一个按钮的左上角Y坐标
	///////////////////////////////////////////////// 处理完第一个图标按钮
	hWnd=m_LoginChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_LoginChk.SetIcon(IDI_KEY2ICO,IDI_KEY1ICO);
	m_LoginChk.SetTooltipText(_T("打开新用户注册的工作区域，请填写相关内容，完成注册！"));
	m_LoginChk.DrawTransparent(TRUE);
	m_LoginChk.MoveWindow(iChkLeft,iChkTop,iChkWide,iChkHeight);//移动第一个按钮
	m_LoginChk.SetCheck(1);
    iChkTop+=iChkHeight;
	////////////////////////////////////////////////第一个图标按钮处理完毕
	///////////////////////////////////////////////// 处理完第一个图标按钮
	hWnd=m_SavingChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_SavingChk.SetIcon(IDI_KEY2ICO,IDI_KEY1ICO);
	m_SavingChk.SetTooltipText(_T("打开存款工作区域，请填写相关内容，完成存款！"));
	m_SavingChk.DrawTransparent(TRUE);
	m_SavingChk.MoveWindow(iChkLeft,iChkTop,iChkWide,iChkHeight);//移动第一个按钮
	iChkTop+=iChkHeight;
	////////////////////////////////////////////////第一个图标按钮处理完毕
	///////////////////////////////////////////////// 处理完第一个图标按钮
	hWnd=m_FetchChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_FetchChk.SetIcon(IDI_KEY2ICO,IDI_KEY1ICO);
	m_FetchChk.SetTooltipText(_T("打开取款工作区域，请填写相关内容，完成取款！"));
	m_FetchChk.DrawTransparent(TRUE);
	m_FetchChk.MoveWindow(iChkLeft,iChkTop,iChkWide,iChkHeight);//移动第一个按钮
	iChkTop+=iChkHeight;
	////////////////////////////////////////////////第一个图标按钮处理完毕
	///////////////////////////////////////////////// 处理完第一个图标按钮
	hWnd=m_ChangePwChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_ChangePwChk.SetIcon(IDI_KEY2ICO,IDI_KEY1ICO);
	m_ChangePwChk.SetTooltipText(_T("打开用户修改密码的工作区域，请填写相关内容，完成密码修改！"));
	m_ChangePwChk.DrawTransparent(TRUE);
	m_ChangePwChk.MoveWindow(iChkLeft,iChkTop,iChkWide,iChkHeight);//移动第一个按钮
	iChkTop+=iChkHeight;
	////////////////////////////////////////////////第一个图标按钮处理完毕
	///////////////////////////////////////////////// 处理完第一个图标按钮
	hWnd=m_ExchangeChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_ExchangeChk.SetIcon(IDI_KEY2ICO,IDI_KEY1ICO);
	m_ExchangeChk.SetTooltipText(_T("打开交易查询的工作区域，请填写相关内容，完成注册！"));
	m_ExchangeChk.DrawTransparent(TRUE);
	m_ExchangeChk.MoveWindow(iChkLeft,iChkTop,iChkWide,iChkHeight);//移动第一个按钮
	iChkTop+=iChkHeight;
	////////////////////////////////////////////////第一个图标按钮处理完毕
	///////////////////////////////////////////////// 处理完第一个图标按钮
	hWnd=m_DeleteLoginChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_DeleteLoginChk.SetIcon(IDI_KEY2ICO,IDI_KEY1ICO);
	m_DeleteLoginChk.SetTooltipText(_T("打开销户工作区域，请填写相关内容，完成用户的注销！"));
	m_DeleteLoginChk.DrawTransparent(TRUE);
	m_DeleteLoginChk.MoveWindow(iChkLeft,iChkTop,iChkWide,iChkHeight);//移动第一个按钮
	////////////////////////////////////////////////第一个图标按钮处理完毕
	//处理退出按钮
	hWnd=m_CancelBtn.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_CancelBtn.SetIcon(IDI_CANCELICO);
	m_CancelBtn.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);
	m_CancelBtn.SetTooltipText(_T("退出此程序！"));
	m_CancelBtn.DrawTransparent(TRUE);
	
	return 1;
}

void CBankManagerDlg::OnBnClickedLoginchk()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	this->OnClose();
}

// //用来初始化６个工作区页面
int CBankManagerDlg::OnInitPage(void)
{
	//取得右边分组框的屏幕坐标
	HWND hWnd;
	hWnd=m_WorkStc.GetSafeHwnd();
	CWnd *pWnd;
	pWnd=this->FromHandle(hWnd);
	CRect lpRect;
	pWnd->GetWindowRect(lpRect);
	this->ScreenToClient(lpRect);
	//在 lpRect中保存了右边分组框的用户区域坐标
	//开始处理6个ｐａｇｅ的样式和位置
	//初始化坐标信息
	int iPageWide=lpRect.right-lpRect.left;//每个page的宽度
	int iPageHeight=(lpRect.bottom-lpRect.top);//每个page的高度
	int iPageLeft=lpRect.left;//第一个按钮左上角x坐标
	int iPageTop=lpRect.top;//第一个按钮的左上角Y坐标
	///////////////////////////////////////////////// 处理第page
	//开始生成右边页面中的6个工作区域窗口
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
	////////////////////////////////////////////////page处理完毕
	return 1;
}
