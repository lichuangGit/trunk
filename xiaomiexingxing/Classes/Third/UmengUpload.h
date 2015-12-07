#ifndef UMENGUPLOAD_H
#define UMENGUPLOAD_H

#include "cocos2d.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "libmobclickcpp/include/MobClickCpp.h"
#endif

USING_NS_CC;
using namespace std;

#define Umeng_Id_Baodin			"baodian"		//���Ǳ�����ͳ��
#define Umeng_Id_Tiaozhan		"tiaozhan"		//��սģʽ���ͳ��
#define Umeng_Id_TiaozhanStart	"tiaozhan"		//��սģʽ��ʼ���ͳ��
#define Umeng_Id_Choujiang		"choujiang"		//�齱���ͳ��
#define Umeng_Id_Chaozhilibao	"chaozhilibao"	//��ֵ���
#define Umeng_Id_Zhandan		"zhadan"		//ը��
#define Umeng_Id_Tongsexiao		"tongsexiao"	//ͬɫ��
#define Umeng_Id_Huanse			"huanse"		//��ɫ
#define Umeng_Id_Chaoxiao		"chexiao"		//����
#define Umeng_Id_Shuaxin		"shuaxin"		//ˢ��
#define Umeng_Id_Exit			"gameExit"		//��Ϸ�˳�
#define Umeng_Id_Payrequest		"payRequest"	//֧������
#define Umeng_Id_Payqueren		"pyaQueren"		//֧��ȷ��
#define Umeng_Id_Paycancel		"payCancel"		//֧��ȡ��
#define Umeng_Id_Paysuccess		"paySuccess"	//֧���ɹ�
#define Umeng_Id_Payfailed		"payFailed"		//֧��ʧ��
#define Umeng_Id_Upgrade		"gameUpgrade"	//����

class UmengUpload
{
public:
	UmengUpload();
	~UmengUpload();

	/*
	*����:	�ȼ�ͳ��
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-24-10:38                                                                   
	*/
	static void setLevel(string lv);

	/*
	*����:	����ͳ��
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-24-10:38                                                                   
	*/
	static void pay(double cash, int source, double coin);

	/*
	*����:	����ͳ��
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-24-10:37                                                                   
	*/
	static void use(string item, int amount, double price);

	/*
	*����:	����ͳ��
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-24-10:37                                                                   
	*/
	static void bonus(double coin, int source);
	static void bonus(string item, int amount, double price, int source);

	/*
	*����:	�ؿ�ͳ��
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-24-10:40                                                                   
	*/
	static void startLevel(string level);
	static void finishLevel(string level);
	static void failLevel(string level);

	/*
	*����:	�����¼�
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-24-10:41                                                                   
	*/
	static void event(string eventId, const char * label = NULL);

	/*
	*����:	�����¼�
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-24-10:41                                                                   
	*/
	static void event(string eventId, map<string, string> *attributes, int counter = 0);

	/*
	*����:		��Ϸ�˳�
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-24-17:51                                                                   
	*/
	static void end();
};

#endif
