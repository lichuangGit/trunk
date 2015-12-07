#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_

#include "cocos2d.h"
#include "Data/Const.h"
#include "Data/GameData.h"
#include "TopMenu.h"
#include "StarMatrix.h"
#include "Core/FloatWord.h"
#include "Data/Audio.h"
#include "Ui/GameDialogLayer.h"
#include <map>
#include "Props.h"
#include "SettingLayer.h"

using namespace std;
USING_NS_CC;
class StarMatrix;

//gamelayer 菜单
#define SetMenu 6
#define AddMenu 7

class GameLayer: public Layer 
{
public:
	//当前触摸状态
	enum TouchStatus
	{
		Touch_Normal = 0,	//正常状态
		Touch_Bomb,			//炸弹道具
		Touch_Tongsexiao,	//同色消除
		Touch_Huanse,		//换色道具
		Touch_Chexiao,		//撤销道具
		Touch_Shuanxin		//刷新道具
	};
	//星星状态
	enum StarStatus
	{
		Status_Ready,		//初始状态
		Status_Activity,	//活动状态 即星星破碎或移动
		Status_NoActivity,	//非活动状态
		Status_Over			//关卡结束状态
	};
public:
	static Scene *createScene();
	CREATE_FUNC(GameLayer);
	virtual bool init();

	CC_SYNTHESIZE(TouchStatus, m_curTouchStatus, CurTouchStatus);	//当前触摸状态
	CC_SYNTHESIZE(TouchStatus, m_previousTouchStatus, PreviousTouchStatus);//上次状态

	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch *touch, Event *event);
	
	void floatLevelWord();
	void floatTargetScoreWord();
	void removeFloatWord();
	void showStarMatrix();
	
	void refreshMenu();
	void showLinkNum(int size);

	/*
	*功能:	进入下一关
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-13-10:07                                                                   
	*/
	void gotoNextLevel();

	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

	/*
	*功能:	每个星星破碎后，分数移动完后，更新分数
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-9-9:20                                                                   
	*/
	void updateEveryScore(int score);

	/*
	*功能:	星星破碎后，添加分数完毕后，通关提示,包括特效提示、粒子提示、音乐播放
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-9-13:49                                                                   
	*/
	void startPassLevelDeal();

	/*
	*功能:	每次触摸，所有星星破碎后，分数刷新和连击提示
	*param: link 星星连击数 默认 0 即不提示连击数，只刷新
	*返回值:
	*作者: lichuang
	*日期:2015-10-9-14:27                                                                   
	*/
	void refreshScoreAndLinkNum(int link = 0);

	/*
	*功能:	本关结束，提示玩家
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-9-18:07                                                                   
	*/
	void floatLeftStarMsg(int leftNum);

	/*
	*功能:	奖励分数飘完后的处理
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-9-18:08                                                                   
	*/
	void gameOverToDealStar(int score);

	/*
	*功能:	游戏弹框处理
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-10-14:27                                                                   
	*/
	void popOutDialog(NormalType type);
	void popOutDialog(PayType type);

	/*
	*功能:	游戏over后，弹框回调处理函数
	*param: _map 物品集合 key 物品种类 value 物品数量
	*返回值:
	*作者: lichuang
	*日期:2015-10-12-16:50                                                                   
	*/
	void normalDialogCallBack(std::map<int, int> _map, NormalType type = nGameNone);
	void payDialogCallBack(int point, int result, std::map<int, int> _map);

	/*
	*功能:	创建一个物品的移动处理 
	*param: type 物品种类 num 数量 isNextLevel 是否进入下一关 因物品的数量改变发生在消耗、购买(可能发生在游戏结束的时候，故最后一个物品动作完成之后进入下一关)
	*返回值:
	*作者: lichuang
	*日期:2015-10-12-16:56                                                                   
	*/
	void createGoodsAndMove(GoodsType type, int num, bool isNextLevel = false);

	/*
	*功能:	更新物品数量,用于对话框里免费或购买物品，刷新gamelayer数字
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-12-17:23                                                                   
	*/
	void updateGoodsNumberCallback(Node *pSender, GoodsType type, int num);
	
	/*
	*功能:	更新物品数量，包括刷新页面显示
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-17-15:12                                                                   
	*/
	void updateGoodsNumber(GoodsType type, int num);

	SpriteBatchNode *getBatchNode();

	/*
	*功能:	设置星星的状态 true 活动状态 false 静止状态
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-9-16:26
	*/
	void setStarsStatus(StarStatus status);
	StarStatus getStarsStatus();

	/*
	*功能:	道具是否正在使用中，true 是 false 否  因同色消、撤销、刷新使用期间即程序还没处理完，若进行其他操作可能引起其他问题
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-16-14:25                                                                   
	*/
	CC_SYNTHESIZE(bool, m_isPropUse, IsPropUse);

	/*
	*功能:	更新状态标志，在星星破碎后调用
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-16-15:59                                                                   
	*/
	void updateTouchStatus(TouchStatus status);

	/*
	*功能:	用于道具消耗，更新物品显示,通过状态
	*param: status 上次状态
	*返回值:
	*作者: lichuang
	*日期:2015-10-16-17:34                                                                   
	*/
	void updateGoodsNumberByTouchStatus();

	/*
	*功能:	从游戏页面离开时，保存存档，以便在主页可点继续
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-2-10:27                                                                   
	*/
	void saveStarAtExitGame();

private:
	void registerListener();	//lichuang 2015/4/22 封装注册监听函数

	void initUI();

	void congratulations();

	GameLayer();
	~GameLayer();

	/*
	*功能:	游戏失败飘字处理
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-14-14:33                                                                   
	*/
	void floatFailedMove();

	/*
	*功能:	菜单回调处理
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-14-17:19                                                                   
	*/
	void onMenuItemCallBack(int type);

	/*
	*功能:	炸弹处理
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-15-16:24                                                                   
	*/
	void startDealWithBomb();

	/*
	*功能:	同色消处理
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-15-16:24                                                                   
	*/
	void startDealWithTongsexiao();

	/*
	*功能:	处理换色
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-15-16:26                                                                   
	*/
	void startDealWithHuanse();

	/*
	*功能:	炸弹、同色消、换色处理
	*param: type 道具类型 status 道具对应的状态 money 道具对应的钻石价格
	*返回值:
	*作者: lichuang
	*日期:2015-11-5-9:14                                                                   
	*/
	void startDealWithProp(GoodsType type, TouchStatus status, int money);

	/*
	*功能:	处理撤销
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-15-16:27                                                                   
	*/
	void startDealWithChexiao();

	/*
	*功能:	处理刷新
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-15-16:28                                                                   
	*/
	void startDealWithShuaxin();

	/*
	*功能:	撤销或刷新点击后，处理状态
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-29-18:26                                                                   
	*/
	void afterChexiaoAndShuaxinDeal(float f);

	/*
	*功能:	根据状态返回对应的道具对象
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-16-11:27                                                                   
	*/
	Props *getPropByTouchStatus(TouchStatus status);

	/*
	*功能:	由状态获取物品类型或者物品钻石价格
	*param: type 决定返回值意义 1 返回物品类型GoodsType 2 返回物品钻石价格
	*返回值:
	*作者: lichuang
	*日期:2015-10-17-15:34                                                                   
	*/
	int getGoodsByStatus(TouchStatus status, int type = 1);

	/*
	*功能:	判断当前游戏状态，是否响应用户的操作	避免用户在不当时间的操作引起的问题
	*param:
	*返回值:	true 响应 false 不响应
	*作者: lichuang
	*日期:2015-10-15-16:16                                                                   
	*/
	bool isReceiveTouchEvent();

	/*
	*功能:	当前关卡是否提示成功
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-17-20:27                                                                   
	*/
	CC_SYNTHESIZE(bool, m_isCongratulation, IsCongratulation);

	/*
	*功能: 5秒没有操作，就作出提示
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-4-16:23                                                                   
	*/
	void noTouchAndWarning(float f);

	/*
	*功能:	停止触摸警告
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-12-13:59                                                                   
	*/
	void stopNoTouchAndWarning();

	/*
	*功能:	弹超值礼包
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-24-14:31                                                                   
	*/
	void goLibao(string name);

	/*
	*功能:	刷新等级及经验值
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-12-6-16:32                                                                   
	*/
	void updateLvAndExpereience(int leftStar);

	/*
	*功能:	升级提示
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-12-6-19:55                                                                   
	*/
	void congratulationsUpgrade();

	/*
	*功能:	延时修改经验条
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-12-6-19:54                                                                   
	*/
	void afterUpate(float f);

	/*
	*功能:	显示等级加分提示
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-12-6-20:29                                                                   
	*/
	void showLvToAddScore(int leftStar);

	/*
	*功能:	等级加分移动后出理
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-12-6-20:47                                                                   
	*/
	void dealLvAddScoreAfter(Node*pSender, int score);

private:
	TopMenu *m_topMenu;			//游戏相关信息
	StarMatrix *m_starMatrix;

	FloatWord *m_levelMsg;
	FloatWord *m_targetScore;
	Label* m_linkNum;		//连击提示
	SpriteBatchNode *m_spBatchNode;
	StarStatus m_starStatus;	//星星的当前状态

	//道具
	Props *m_bombProp;
	Props *m_tongsexiaoProp;
	Props *m_huanseProp;
	Props *m_chexiaoProp;
	Props *m_shuaxinProp;

	int m_enterTime;	//记录玩家进入时间

	NumSprite *m_pSpLevel;	// 玩家等级
	Sprite *m_pSpProg;		//经验条
	Sprite *m_pSpZengjia;
	Sprite *m_pSpChenghao;
	NumSprite *m_pSpLvAdd;
	NumSprite *m_pSpLvScore;
	int m_iLvCount;

public:
	Vec2 m_curScorePos;		//当前分数位置
	Vec2 m_curZuanshiPos;
	Vec2 m_curBombPos;
	Vec2 m_curTongsexiaoPos;
	Vec2 m_curHuansePos;
	Vec2 m_curChexiaoPos;
	Vec2 m_curShuaxinPos;
};

#endif
