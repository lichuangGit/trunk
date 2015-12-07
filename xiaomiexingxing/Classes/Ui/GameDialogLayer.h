#ifndef GAMEDIALOGLAYER_H
#define GAMEDIALOGLAYER_H

#include "StudioLayer.h"

enum DialogType
{
	NormalDialog = 0,	//��ͨ�Ի���
	PayDialog			//���ѶԻ���
};
//�Ի����������
enum NormalType
{
	nGameNone,			//��
	nGamePassed,		//��Ϸͨ��	�����������ȡ
	nGameSet,			//��Ϸ����ҳ��
	nGameExit,			//��Ϸ�Ƴ���ʾ
	nGameArchive,		//����Ϸ�浵��ʾ
	nGameContinue		//������Ϸʧ����ʧ��ʯ��ʾ
};
enum PayType
{
	pGameFailed = 0,	//��Ϸʧ��
	pGamePassed,		//��Ϸͨ��	ż���ظ�����ȡ
	pGameLibao99,		//99������
	pGameLibao130,		//130������
	pGameExit,			//�˳����
	pGameLogin,			//��½���
	pGameTwo,			//��Ԫ���
	pGameFour,			//��Ԫ���
	pGameSix,			//��Ԫ���
	pGameTen			//ʮԪ���
};

class GameDialogLayer : public StudioLayer
{
public:
	//�Ի�������
	
	GameDialogLayer();
	~GameDialogLayer();

	virtual bool init(DialogType type, int childType, std::function<void(void)> func);
	virtual bool init(DialogType type, int childType, std::function<void(map<int, int>, NormalType)> func);
	virtual bool init(DialogType type, int childType, std::function<void(int, int, map<int, int>)> func);
	/*
	*����:	�����Ի���
	*param: type �Ի������� childType �������� func �ص�����
	*����ֵ:
	*����: lichuang
	*����:2015-10-10-15:15                                                                   
	*/
	static GameDialogLayer *createNoramlNoData(DialogType type, int childType, std::function<void(void)> func);
	static GameDialogLayer *createNoraml(DialogType type, int childType, std::function<void(map<int, int>, NormalType)> func);// �Ǹ���
	static GameDialogLayer *createPay(DialogType type, int childType, std::function<void(int, int, map<int, int>)> func);//����

	void onEnter();

private:
	void initUI();

	/*
	*����:	��ʼ��ͨ����ʾ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-10-16:51                                                                   
	*/
	void initUiWithGamePassed();
	
	/*
	*����:	��ʼ������Ϸ�浵��ʾ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-30-18:24                                                                   
	*/
	void initUiWithGameArchive();

	/*
	*����:	��ʼ����title��
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-3-14:01                                                                   
	*/
	void initUiWithGameHaveTitle();

	/*
	*����:	��ʼ�����ѽ���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-15-17:02                                                                   
	*/
	void initPayDialog();

	/*
	*����:	������Դ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-10-17:41                                                                   
	*/
	void initFrame();

	/*
	*����:	�˵��ص�����
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-12-13:58                                                                   
	*/
	void onMenuItemCallBack(int type);

	/*
	*����:	�رմ���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-12-15:20                                                                   
	*/
	void dealClose();

	/*
	*����:	ȷ������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-12-15:20                                                                   
	*/
	void dealOk();

	/*
	*����:	��ͨ�ؿ��Ի���رմ���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-12-17:44                                                                   
	*/
	void normalDealClose();

	/*
	*����:	��ͨ�ؿ��Ի���ȷ������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-12-17:44
	*/
	void normalDealOk();

	/*
	*����:	���ѹؿ��Ի���رմ���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-12-17:48                                                                   
	*/
	void payDealClose();

	/*
	*����:	���ѹؿ��Ի���ȷ������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-12-17:48
	*/
	void payDealOk();

	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

	/*
	*����:	����̳��Ƿ���ÿ���׳�
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-23-9:43                                                                   
	*/
	bool checkFirstShop();

private:
	std::function<void(void)> m_noDataFunc;
	std::function<void(map<int, int>, NormalType)> m_func; //����������ͶԻ���ص�
	std::function<void(int, int, map<int, int>)>	m_payFunc;//���ѶԻ���ص�
	DialogType m_dialogType;
	int m_childType;
	Sprite *m_dialogBg;

	/***********������ GamePassed  pGameFailed �Ի��� begin*******************/
	
	int m_goodsNum;		//�ؿ�������Ʒ����
	GoodsType m_goodsType;	//�ؿ�������Ʒ����
	string m_goodsName;		//�ؿ�������Ʒ����

	std::map<int, int> m_goodsMap;	//������Ʒ key ���� value ����

	//���Ѷ���������ʯ
	int m_freeGoodsNum;

	/***********������ GamePassed pGameFailed �Ի��� end*******************/

	PayPoint m_payPoint;
};

#endif
