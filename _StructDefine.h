//Download by http://www.NewXing.com
#ifndef _STRUCTDEFIE_
#define _STRUCTDEFIE_
///////////////////////////////////���巵�������˺������Ĳ�ѯ
typedef struct IntInfo 
{
  long lSum;
}_IntInfo;
///////////////////////////////////�����û���Ϣ���صĲ�ѯ
typedef struct UserInfo 
{
  CString CardId;
  CString UserName;
  CString UserSex;
  CString UserId;
  CString UserPhone;
  CString UserPass;
}_UserInfo;
//////////////////////////////////������ڴ����Ϣ���صĲ�ѯ
typedef struct CurrentInfo 
{
	CString CardId;
	//CString UserName;
	double MoneyBalance;
	CString ExchangeDate;
	double AccrualBalance;
}_CurrentInfo;
//////////////////////////////////���嶨�ڴ����Ϣ���صĲ�ѯ
typedef struct FixInfo 
{
	CString CardId;
	//CString UserName;
	double MoneyBalance;
	CString ExchangeDate;
	CString MatureDate;
	double AccrualRate;
}_FixInfo;
//////////////////////////////////���彻�׼�¼��Ϣ���صĲ�ѯ
typedef struct RecordInfo 
{
	CString CardId;
	//CString UserName;
	double MoneryBalance;
	CString MoneyType;
	CString ExchangeDate;
	double AccrualBalance;
	CString InOut;
	struct RecordInfo *Next;
}_RecordInfo;
///////////////////////////////���Ҹ��˺��Ƿ���ڣ����ؽ���������
typedef struct UserNameInfo 
{
	CString UserName;
}_UserNameInfo;
#endif