//Download by http://www.NewXing.com
#include "StdAfx.h"
#include ".\adoworker.h"
#include "_StructDefine.h"
AdoWorker::AdoWorker(void)
{
	m_pRecordset=NULL;
	HRESULT hr; 
	try {
		hr = m_pRecordset.CreateInstance("ADODB.Recordset");;///����Recordset���� 
		} 
	catch(_com_error e)///��׽�쳣 
	{ 
		CString errormessage; 
		errormessage.Format("�������ݿ�ʧ��!\r\n������Ϣ:%s",e.ErrorMessage()); 
		AfxMessageBox(errormessage);///��ʾ������Ϣ
		return;
	} 
}

AdoWorker::~AdoWorker(void)
{
}
BOOL AdoWorker::ExecuteSql(CString strSqlText)//����ִ���޷��ص����
{
	//AfxMessageBox(strSqlText);
	_bstr_t vSqlText=_bstr_t(strSqlText);
	_variant_t RecordsAffected; 
	m_pConnection->Execute(vSqlText,&RecordsAffected,adCmdText);
	if(m_pRecordset->State) 
		m_pRecordset->Close();
	if(RecordsAffected.lVal>0)
	   return TRUE;
	else 
	   return FALSE;
}
void *AdoWorker::ExecuteSql(CString strSqlText,int iFlag)//����ִ���з��ص���䣬����Ϊvoid��ָ�룬������������ǿ��ת��
{
  //AfxMessageBox(strSqlText); 
  _bstr_t vSqlText=_bstr_t(strSqlText);
   _variant_t RecordsAffected; 
   m_pRecordset=m_pConnection->Execute(vSqlText,&RecordsAffected,adCmdText);
   ////////////////////////////////////////////�жϲ�ѯ�Ƿ�ɹ����ɹ���Ӧ���ؼ�¼��
   if(m_pRecordset->adoEOF) 
	{ if(m_pRecordset->State)
	      m_pRecordset->Close();
	  return (void *)NULL;
	}
   ////////////////////////////////////////////
   void *pVoid=NULL;
   pVoid=this->ChooseStructFill(iFlag);
   if(m_pRecordset->State) 
	   m_pRecordset->Close();
   return pVoid;
}
void *AdoWorker::ChooseStructFill(int iFlag)
{
	 void *pVoid=NULL;
	switch(iFlag)
	{
	case 0:
		pVoid=this->FillIntInfo();
		break;
	case 1:
		pVoid=this->FillUserInfo();
		break;
	case 2:
		pVoid=this->FillCurrentInfo();
		break;
	case 3:
		pVoid=this->FillFixInfo();
		break;
	case 4:
		pVoid=this->FillRecordInfo();
		break;
	case 5:
		pVoid=this->FillUserNameInfo();
	default:
		break;
	}
	return pVoid;
}
void *AdoWorker::FillIntInfo()
{
	_IntInfo *pIntInfo=NULL;
	pIntInfo=new _IntInfo;
	_variant_t vIntInfo;
	vIntInfo=m_pRecordset->GetCollect(_variant_t((long)0));
	pIntInfo->lSum=vIntInfo.lVal;
	return (void *)pIntInfo;
}
void *AdoWorker::FillUserInfo()
{
	_UserInfo *pUserInfo=NULL;
	pUserInfo=new _UserInfo;
	_variant_t vUserInfo;
	vUserInfo=m_pRecordset->GetCollect("CardId");
	pUserInfo->CardId=(CString)vUserInfo;
	vUserInfo.Clear();
	vUserInfo=m_pRecordset->GetCollect("UserName");
	pUserInfo->UserName=(CString)vUserInfo;
	vUserInfo.Clear();
	vUserInfo=m_pRecordset->GetCollect("UserId");
	pUserInfo->UserId=(CString)vUserInfo;
	vUserInfo.Clear();
	vUserInfo=m_pRecordset->GetCollect("UserSex");
	pUserInfo->UserSex=(CString)vUserInfo;
	vUserInfo.Clear();
	vUserInfo=m_pRecordset->GetCollect("UserPhone");
	pUserInfo->UserPhone=(CString)vUserInfo;
	vUserInfo.Clear();
	vUserInfo=m_pRecordset->GetCollect("UserPass");
	pUserInfo->UserPass=(CString)vUserInfo;
	vUserInfo.Clear();
	return (void *)pUserInfo;
}
void *AdoWorker::FillCurrentInfo()
{
	_CurrentInfo *pCurrentInfo=NULL;
	pCurrentInfo=new _CurrentInfo;
    _variant_t vCurrentInfo;
	vCurrentInfo=m_pRecordset->GetCollect("CardId");
	pCurrentInfo->CardId=(CString)vCurrentInfo;
	vCurrentInfo.Clear();
	vCurrentInfo=m_pRecordset->GetCollect("ExchangeDate");
	pCurrentInfo->ExchangeDate=(CString)vCurrentInfo;
	vCurrentInfo.Clear();
	vCurrentInfo=m_pRecordset->GetCollect("MoneyBalance");
	pCurrentInfo->MoneyBalance=vCurrentInfo.dblVal;
	vCurrentInfo.Clear();
	vCurrentInfo=m_pRecordset->GetCollect("AccrualBalance");
	pCurrentInfo->AccrualBalance=vCurrentInfo.dblVal;
	vCurrentInfo.Clear();
	return (void *)pCurrentInfo;
}
void *AdoWorker::FillFixInfo()
{
	_FixInfo *pFixInfo=NULL;
	pFixInfo=new _FixInfo;
	_variant_t vFixInfo;
	vFixInfo=m_pRecordset->GetCollect("CardId");
	pFixInfo->CardId=(CString)vFixInfo;
	vFixInfo.Clear();
	vFixInfo=m_pRecordset->GetCollect("MoneyBalance");
	pFixInfo->MoneyBalance=vFixInfo.dblVal;
	vFixInfo.Clear();
	vFixInfo=m_pRecordset->GetCollect("ExchangeDate");
	pFixInfo->ExchangeDate=(CString)vFixInfo;
	vFixInfo.Clear();
	vFixInfo=m_pRecordset->GetCollect("MatureDate");
	pFixInfo->MatureDate=(CString)vFixInfo;
	vFixInfo.Clear();
	vFixInfo=m_pRecordset->GetCollect("AccrualRate");
	pFixInfo->AccrualRate=vFixInfo.dblVal;
	vFixInfo.Clear();
	return (void *)pFixInfo;
}
void *AdoWorker::FillRecordInfo()
{
	_RecordInfo *pRecordInfo=NULL;
	_RecordInfo *pRecordHeader=NULL;
	_RecordInfo *pRecordPre=NULL;
	_variant_t vRecordInfo;
	int iNodeFlag=1;
	for(;!(m_pRecordset->adoEOF);)
	{
		pRecordInfo=new _RecordInfo;
		pRecordInfo->Next=NULL;
		if(iNodeFlag==1)//�ж����Ƿ��ǵ�һ�ν����ڵ�
		{
			pRecordHeader=pRecordInfo;
			pRecordPre=pRecordInfo;
			iNodeFlag++;
		}
		else
		{
			pRecordPre->Next=pRecordInfo;
			pRecordPre=pRecordInfo;
		}
		/////////////////////////////////��ʼ���ڵ�
        vRecordInfo=m_pRecordset->GetCollect("CardId");
		pRecordInfo->CardId=(CString)vRecordInfo;
		vRecordInfo.Clear();
		vRecordInfo=m_pRecordset->GetCollect("ExchangeDate");
		pRecordInfo->ExchangeDate=(CString)vRecordInfo;
		vRecordInfo.Clear();
		vRecordInfo=m_pRecordset->GetCollect("MoneyType");
		pRecordInfo->MoneyType=(CString)vRecordInfo;
		vRecordInfo.Clear();
		vRecordInfo=m_pRecordset->GetCollect("InOut");
		pRecordInfo->InOut=(CString)vRecordInfo;
		vRecordInfo.Clear();
		vRecordInfo=m_pRecordset->GetCollect("MoneyBalance");
		pRecordInfo->MoneryBalance=vRecordInfo.dblVal;
		vRecordInfo.Clear();
		vRecordInfo=m_pRecordset->GetCollect("AccrualBalance");
		pRecordInfo->AccrualBalance=vRecordInfo.dblVal;
		vRecordInfo.Clear();
		/////////////////////////////////�ڵ�������
		////////////////////////////////m_pRecordsetָ�����
		m_pRecordset->MoveNext();
	}
	return (void *)pRecordHeader;
}
void *AdoWorker::FillUserNameInfo()
{
	_UserNameInfo *pUserNameInfo=NULL;
	pUserNameInfo=new _UserNameInfo;
	_variant_t vUserNameInfo;
	vUserNameInfo=m_pRecordset->GetCollect("UserName");
	pUserNameInfo->UserName=(CString)vUserNameInfo;
	vUserNameInfo.Clear();
	return (void *)pUserNameInfo;
}