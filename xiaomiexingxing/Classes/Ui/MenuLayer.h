#ifndef MENULAYER_H
#define MENULAYER_H

#include "StudioLayer.h"
#include "ShopLayer.h"
#include "StarBook.h"
#include "GameLayer.h"
#include "LotteryLayer.h"
#include "LoginLayer.h"
#include "ChallengeLayer.h"

class MenuLayer	: public StudioLayer
{
public:
	enum MenuType
	{
		NewGame = 0,
		ContinueGame,
		Shop,
		Choujiang,
		Challenge,
		Libao,
		Baodian,
		MusicOff,
		MusicOn
	};
	MenuLayer();
	~MenuLayer();

	static Scene *scene();
	virtual bool init();
	void onEnter();
	CREATE_FUNC(MenuLayer);

private:
	void initUI();

	void onMenuItemCallBack(MenuType type);

	/*
	*����:	��������Ϸ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-2-14:18                                                                   
	*/
	void goNewGame();

	/*
	*����:	��������Ϸ�ص�	����д浵
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-2-14:18                                                                   
	*/
	void goNewGameCallBack();

	/*
	*����:	������Ϸ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-2-14:45                                                                   
	*/
	void goContinueGame();

	/*
	*����:	������Ϸ ʧ�ܻص�
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-2-16:45                                                                   
	*/
	void goContinueGameCallBack();

	/*
	*����:	֧���ص�
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-2-16:57                                                                   
	*/
	void payDialogCallBack(int point, int result, std::map<int, int> _map);

	/*
	*����:	������Ʒ����������ˢ��ҳ����ʾ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-17-15:12
	*/
	void updateGoodsNumber(GoodsType type, int num);

	/*
	*����:	�̳ǵ���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-3-12:32                                                                   
	*/
	void goShop();

	/*
	*����:	���Ǳ���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-3-14:59                                                                   
	*/
	void goBaodian();

	/*
	*����:	�齱����
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-5-11:32                                                                   
	*/
	void goLottery();

	/*
	*����:	��սģʽ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-23-10:17                                                                   
	*/
	void goChallenge();

	/*
	*����:	��Ϸ������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-10-14:27
	*/
	void popOutDialog(NormalType type, std::function<void(void)> func);
	void popOutDialog(PayType type);

	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

	/*
	*����:
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-3-15:24                                                                   
	*/
	void goGameExitCallBack();
	void goExitLibao(float f);

	/*
	*����:	ǩ�����
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-10-17:09                                                                   
	*/
	void checkLogin();

	/*
	*����:	���ֿ���
	*param:	is true ���� false ֹͣ
	*����ֵ:
	*����: lichuang
	*����:2015-11-2-13:08
	*/
	void musicOnOff(bool is);

private:
	bool m_isGameContinue;	//��ֵ���λ�� ������ֵ���
	MenuItemSprite *itemOff;
	MenuItemSprite *itemOn;
};

#endif
