#ifndef UMENGUPLOAD_H
#define UMENGUPLOAD_H

#include "cocos2d.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "libmobclickcpp/include/MobClickCpp.h"
#endif

USING_NS_CC;
using namespace std;

#define Umeng_Id_Baodin			"baodian"		//星星宝典点击统计
#define Umeng_Id_Tiaozhan		"tiaozhan"		//挑战模式点击统计
#define Umeng_Id_TiaozhanStart	"tiaozhan"		//挑战模式开始点击统计
#define Umeng_Id_Choujiang		"choujiang"		//抽奖点击统计
#define Umeng_Id_Chaozhilibao	"chaozhilibao"	//超值礼包
#define Umeng_Id_Zhandan		"zhadan"		//炸弹
#define Umeng_Id_Tongsexiao		"tongsexiao"	//同色消
#define Umeng_Id_Huanse			"huanse"		//换色
#define Umeng_Id_Chaoxiao		"chexiao"		//撤销
#define Umeng_Id_Shuaxin		"shuaxin"		//刷新
#define Umeng_Id_Exit			"gameExit"		//游戏退出
#define Umeng_Id_Payrequest		"payRequest"	//支付请求
#define Umeng_Id_Payqueren		"pyaQueren"		//支付确认
#define Umeng_Id_Paycancel		"payCancel"		//支付取消
#define Umeng_Id_Paysuccess		"paySuccess"	//支付成功
#define Umeng_Id_Payfailed		"payFailed"		//支付失败
#define Umeng_Id_Upgrade		"gameUpgrade"	//升级

class UmengUpload
{
public:
	UmengUpload();
	~UmengUpload();

	/*
	*功能:	等级统计
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-24-10:38                                                                   
	*/
	static void setLevel(string lv);

	/*
	*功能:	购买统计
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-24-10:38                                                                   
	*/
	static void pay(double cash, int source, double coin);

	/*
	*功能:	消耗统计
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-24-10:37                                                                   
	*/
	static void use(string item, int amount, double price);

	/*
	*功能:	奖励统计
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-24-10:37                                                                   
	*/
	static void bonus(double coin, int source);
	static void bonus(string item, int amount, double price, int source);

	/*
	*功能:	关卡统计
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-24-10:40                                                                   
	*/
	static void startLevel(string level);
	static void finishLevel(string level);
	static void failLevel(string level);

	/*
	*功能:	计数事件
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-24-10:41                                                                   
	*/
	static void event(string eventId, const char * label = NULL);

	/*
	*功能:	计算事件
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-24-10:41                                                                   
	*/
	static void event(string eventId, map<string, string> *attributes, int counter = 0);

	/*
	*功能:		游戏退出
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-24-17:51                                                                   
	*/
	static void end();
};

#endif
