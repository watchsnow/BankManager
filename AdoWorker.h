//Download by http://www.NewXing.com
#pragma once
class AdoWorker
{
public:
	AdoWorker(void);
	~AdoWorker(void);
public:
	BOOL ExecuteSql(CString strSqlText);
	void *ExecuteSql(CString strSqlText,int iFlag);
private:
	_RecordsetPtr m_pRecordset;
private:
	void *ChooseStructFill(int);
	void *FillIntInfo();
	void *FillUserInfo();
	void *FillCurrentInfo();
	void *FillFixInfo();
	void *FillRecordInfo();
	void *FillUserNameInfo();
};
