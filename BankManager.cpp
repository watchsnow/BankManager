//Download by http://www.NewXing.com
// BankManager.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "BankManager.h"
#include "BankManagerDlg.h"
#include "SkinPlusPlus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBankManagerApp

BEGIN_MESSAGE_MAP(CBankManagerApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CBankManagerApp 构造

CBankManagerApp::CBankManagerApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CBankManagerApp 对象

CBankManagerApp theApp;


// CBankManagerApp 初始化

BOOL CBankManagerApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControls()。否则，将无法创建窗口。
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();
    //////////////////////////////////////////////////
	InitializeSkin(_T("skin\\Topax.ssk"));
	//////////////////////////////////////////////////
	if(!AfxOleInit())//初始化COM库
	{
		AfxMessageBox("OLE初始化出错!");
		return FALSE;
	} 
    //////////////////////////////////////////////////创建一个数据库的全局连接实例，以后不再连接数据库
	HRESULT hr; 
	try {
		hr = m_pConnection.CreateInstance("ADODB.Connection",NULL,CLSCTX_ALL);///创建Connection对象 
        
		if(SUCCEEDED(hr)) 
		{ 
			hr = m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=BankDataFile.mdb","","",adModeUnknown); 
			///连接数据库 ///上面一句中连接字串中的Provider是针对ACCESS2000环境的，对于ACCESS97,需要改为:Provider=Microsoft.Jet.OLEDB.3.51; 
		} 
	} 
	catch(_com_error e)///捕捉异常 
	{ 
		CString errormessage; 
		errormessage.Format("连接数据库失败!\r\n错误信息:%s",e.ErrorMessage()); 
		AfxMessageBox(errormessage);///显示错误信息 
	} 
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CBankManagerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用“确定”来关闭
		//对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用“取消”来关闭
		//对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	// 而不是启动应用程序的消息泵。
	return FALSE;
}
