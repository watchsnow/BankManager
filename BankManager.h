//Download by http://www.NewXing.com
// BankManager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CBankManagerApp:
// �йش����ʵ�֣������ BankManager.cpp
//

class CBankManagerApp : public CWinApp
{
public:
	CBankManagerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBankManagerApp theApp;
