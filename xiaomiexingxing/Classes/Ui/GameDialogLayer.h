#ifndef GAMEDIALOGLAYER_H
#define GAMEDIALOGLAYER_H

#include "StudioLayer.h"

enum DialogType
{
	NormalDialog = 0,	//普通对话框
	PayDialog			//付费对话框
};
//对话框具体类型
enum NormalType
{
	nGameNone,			//无
	nGamePassed,		//游戏通过	奇数关免费领取
	nGameSet,			//游戏设置页面
	nGameExit,			//游戏推出提示
	nGameArchive,		//新游戏存档提示
	nGameContinue		//继续游戏失败消失钻石提示
};
enum PayType
{
	pGameFailed = 0,	//游戏失败
	pGamePassed,		//游戏通过	偶数关付费领取
	pGameLibao99,		//99钻大礼包
	pGameLibao130,		//130钻大礼包
	pGameExit,			//退出礼包
	pGameLogin,			//登陆礼包
	pGameTwo,			//两元礼包
	pGameFour,			//四元礼包
	pGameSix,			//六元礼包
	pGameTen			//十元礼包
};

class GameDialogLayer : public StudioLayer
{
public:
	//对话框类型
	
	GameDialogLayer();
	~GameDialogLayer();

	virtual bool init(DialogType type, int childType, std::function<void(void)> func);
	virtual bool init(DialogType type, int childType, std::function<void(map<int, int>, NormalType)> func);
	virtual bool init(DialogType type, int childType, std::function<void(int, int, map<int, int>)> func);
	/*
	*功能:	创建对话框
	*param: type 对话框类型 childType 具体类型 func 回调函数
	*返回值:
	*作者: lichuang
	*日期:2015-10-10-15:15                                                                   
	*/
	static GameDialogLayer *createNoramlNoData(DialogType type, int childType, std::function<void(void)> func);
	static GameDialogLayer *createNoraml(DialogType type, int childType, std::function<void(map<int, int>, NormalType)> func);// 非付费
	static GameDialogLayer *createPay(DialogType type, int childType, std::function<void(int, int, map<int, int>)> func);//付费

	void onEnter();

private:
	void initUI();

	/*
	*功能:	初始化通关提示
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-10-16:51                                                                   
	*/
	void initUiWithGamePassed();
	
	/*
	*功能:	初始化新游戏存档提示
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-30-18:24                                                                   
	*/
	void initUiWithGameArchive();

	/*
	*功能:	初始化有title的
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-3-14:01                                                                   
	*/
	void initUiWithGameHaveTitle();

	/*
	*功能:	初始化付费界面
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-15-17:02                                                                   
	*/
	void initPayDialog();

	/*
	*功能:	加载资源
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-10-17:41                                                                   
	*/
	void initFrame();

	/*
	*功能:	菜单回调处理
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-12-13:58                                                                   
	*/
	void onMenuItemCallBack(int type);

	/*
	*功能:	关闭处理
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-12-15:20                                                                   
	*/
	void dealClose();

	/*
	*功能:	确定处理
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-12-15:20                                                                   
	*/
	void dealOk();

	/*
	*功能:	普通关卡对话框关闭处理
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-12-17:44                                                                   
	*/
	void normalDealClose();

	/*
	*功能:	普通关卡对话框确定处理
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-12-17:44
	*/
	void normalDealOk();

	/*
	*功能:	付费关卡对话框关闭处理
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-12-17:48                                                                   
	*/
	void payDealClose();

	/*
	*功能:	付费关卡对话框确定处理
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-12-17:48
	*/
	void payDealOk();

	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

	/*
	*功能:	检查商城是否是每日首冲
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-23-9:43                                                                   
	*/
	bool checkFirstShop();

private:
	std::function<void(void)> m_noDataFunc;
	std::function<void(map<int, int>, NormalType)> m_func; //用于免费赠送对话框回调
	std::function<void(int, int, map<int, int>)>	m_payFunc;//付费对话框回调
	DialogType m_dialogType;
	int m_childType;
	Sprite *m_dialogBg;

	/***********适用于 GamePassed  pGameFailed 对话框 begin*******************/
	
	int m_goodsNum;		//关卡奖励物品个数
	GoodsType m_goodsType;	//关卡奖励物品类型
	string m_goodsName;		//关卡奖励物品名字

	std::map<int, int> m_goodsMap;	//奖励物品 key 类型 value 个数

	//付费额外赠送钻石
	int m_freeGoodsNum;

	/***********适用于 GamePassed pGameFailed 对话框 end*******************/

	PayPoint m_payPoint;
};

#endif
