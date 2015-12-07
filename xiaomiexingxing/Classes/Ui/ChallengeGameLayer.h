#ifndef CHALLENGEGAMELAYER_H
#define CHALLENGEGAMELAYER_H

#include "StudioLayer.h"
#include "Data/Const.h"
#include "Data/GameData.h"
#include "ChallengeTopMenu.h"
#include "ChallengeStarMatrix.h"
#include "Core/FloatWord.h"
#include "Data/Audio.h"
#include "Ui/GameDialogLayer.h"
#include "SettingLayer.h"

class ChallengeStarMatrix;

class ChallengeGameLayer : public Layer
{
public:
	ChallengeGameLayer();
	~ChallengeGameLayer();

	static Scene *createScene();
	CREATE_FUNC(ChallengeGameLayer);
	virtual bool init();

	//星星状态
	enum StarStatus
	{
		Status_Ready,		//初始状态
		Status_Activity,	//活动状态 即星星破碎或移动
		Status_NoActivity,	//非活动状态
		Status_Over			//关卡结束状态
	};

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
	void setStarsStatus(ChallengeGameLayer::StarStatus status);
	ChallengeGameLayer::StarStatus getStarsStatus();

	/*
	*功能:	游戏失败飘字处理
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-14-14:33
	*/
	void floatFailedMove();

	/*
	*功能:	获取当前分数
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-15-12:24                                                                   
	*/
	int getCurScore();

private:
	void registerListener();	//lichuang 2015/4/22 封装注册监听函数

	void initUI();

	void congratulations();

	/*
	*功能:	菜单回调处理
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-14-17:19
	*/
	void onMenuItemCallBack(int type);
	
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
	*功能:	挑战结束后转超值礼包
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-15-17:51                                                                   
	*/
	void goLibao(float f);

private:
	ChallengeTopMenu *m_topMenu;			//游戏相关信息
	ChallengeStarMatrix *m_starMatrix;

	FloatWord *m_levelMsg;
	FloatWord *m_targetScore;
	Label* m_linkNum;		//连击提示
	SpriteBatchNode *m_spBatchNode;
	ChallengeGameLayer::StarStatus m_starStatus;	//星星的当前状态

public:
	Vec2 m_curScorePos;		//当前分数位置
	Vec2 m_curZuanshiPos;
};

#endif


