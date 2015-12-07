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
	*功能:	进入新游戏
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-2-14:18                                                                   
	*/
	void goNewGame();

	/*
	*功能:	进入新游戏回调	如果有存档
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-2-14:18                                                                   
	*/
	void goNewGameCallBack();

	/*
	*功能:	继续游戏
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-2-14:45                                                                   
	*/
	void goContinueGame();

	/*
	*功能:	继续游戏 失败回调
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-2-16:45                                                                   
	*/
	void goContinueGameCallBack();

	/*
	*功能:	支付回调
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-2-16:57                                                                   
	*/
	void payDialogCallBack(int point, int result, std::map<int, int> _map);

	/*
	*功能:	更新物品数量，包括刷新页面显示
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-17-15:12
	*/
	void updateGoodsNumber(GoodsType type, int num);

	/*
	*功能:	商城调用
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-3-12:32                                                                   
	*/
	void goShop();

	/*
	*功能:	星星宝典
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-3-14:59                                                                   
	*/
	void goBaodian();

	/*
	*功能:	抽奖处理
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-5-11:32                                                                   
	*/
	void goLottery();

	/*
	*功能:	挑战模式
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-23-10:17                                                                   
	*/
	void goChallenge();

	/*
	*功能:	游戏弹框处理
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-10-14:27
	*/
	void popOutDialog(NormalType type, std::function<void(void)> func);
	void popOutDialog(PayType type);

	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

	/*
	*功能:
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-3-15:24                                                                   
	*/
	void goGameExitCallBack();
	void goExitLibao(float f);

	/*
	*功能:	签到检查
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-10-17:09                                                                   
	*/
	void checkLogin();

	/*
	*功能:	音乐控制
	*param:	is true 播放 false 停止
	*返回值:
	*作者: lichuang
	*日期:2015-11-2-13:08
	*/
	void musicOnOff(bool is);

private:
	bool m_isGameContinue;	//超值礼包位置 继续或超值礼包
	MenuItemSprite *itemOff;
	MenuItemSprite *itemOn;
};

#endif
