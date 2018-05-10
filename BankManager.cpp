//Download by http://www.NewXing.com
// BankManager.cpp : ����Ӧ�ó��������Ϊ��
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


// CBankManagerApp ����

CBankManagerApp::CBankManagerApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CBankManagerApp ����

CBankManagerApp theApp;


// CBankManagerApp ��ʼ��

BOOL CBankManagerApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();
    //////////////////////////////////////////////////
	InitializeSkin(_T("skin\\Topax.ssk"));
	//////////////////////////////////////////////////
	if(!AfxOleInit())//��ʼ��COM��
	{
		AfxMessageBox("OLE��ʼ������!");
		return FALSE;
	} 
    //////////////////////////////////////////////////����һ�����ݿ��ȫ������ʵ�����Ժ����������ݿ�
	HRESULT hr; 
	try {
		hr = m_pConnection.CreateInstance("ADODB.Connection",NULL,CLSCTX_ALL);///����Connection���� 
        
		if(SUCCEEDED(hr)) 
		{ 
			hr = m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=BankDataFile.mdb","","",adModeUnknown); 
			///�������ݿ� ///����һ���������ִ��е�Provider�����ACCESS2000�����ģ�����ACCESS97,��Ҫ��Ϊ:Provider=Microsoft.Jet.OLEDB.3.51; 
		} 
	} 
	catch(_com_error e)///��׽�쳣 
	{ 
		CString errormessage; 
		errormessage.Format("�������ݿ�ʧ��!\r\n������Ϣ:%s",e.ErrorMessage()); 
		AfxMessageBox(errormessage);///��ʾ������Ϣ 
	} 
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CBankManagerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȷ�������ر�
		//�Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//�Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	// ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
