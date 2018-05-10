//Download by http://www.NewXing.com
#ifndef _STRUCTDEFIE_
#define _STRUCTDEFIE_
///////////////////////////////////定义返回相似账号数量的查询
typedef struct IntInfo 
{
  long lSum;
}_IntInfo;
///////////////////////////////////定义用户信息返回的查询
typedef struct UserInfo 
{
  CString CardId;
  CString UserName;
  CString UserSex;
  CString UserId;
  CString UserPhone;
  CString UserPass;
}_UserInfo;
//////////////////////////////////定义活期存款信息返回的查询
typedef struct CurrentInfo 
{
	CString CardId;
	//CString UserName;
	double MoneyBalance;
	CString ExchangeDate;
	double AccrualBalance;
}_CurrentInfo;
//////////////////////////////////定义定期存款信息返回的查询
typedef struct FixInfo 
{
	CString CardId;
	//CString UserName;
	double MoneyBalance;
	CString ExchangeDate;
	CString MatureDate;
	double AccrualRate;
}_FixInfo;
//////////////////////////////////定义交易记录信息返回的查询
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
///////////////////////////////查找该账号是否存在，返回仅仅是姓名
typedef struct UserNameInfo 
{
	CString UserName;
}_UserNameInfo;
#endif