#ifndef PLAYERLOTTERYLAYER_H
#define PLAYERLOTTERYLAYER_H

#define LOTTERYDIS 25

#include "StudioLayer.h"
#include "Core/Helper.h"
#include "Data/GameData.h"
#include "GameDialogLayer.h"
#include <ui/UIButton.h>

class LotteryLayer : public StudioLayer
{
public:
	LotteryLayer();
	~LotteryLayer();
	CREATE_FUNC(LotteryLayer);
	virtual bool init();

	void onEnter();

private:
	void initUI();

	/*
	*功能:	奖品初始化，每次点击就改变
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-5-14:33
	*/
	void initLotteryUI();

	/*
	*功能:	按钮点击
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-5-16:08
	*/
	void onBtnClick(Ref* sender, Widget::TouchEventType type);

	/*
	*功能:	开始抽奖
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-6-9:29                                                                   
	*/
	void startLottery();

	/*
	*功能:	抽奖动作
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-6-9:29                                                                   
	*/
	void startLotteryActioin();

	/*
	*功能:	抽奖动作回调
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-9-10:14                                                                   
	*/
	void callBackLight(int pos);

	/*
	*功能:	抽奖结束后，奖品从相应位置移动至中心位置
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-9-10:12                                                                   
	*/
	void moveToCenter();

	/*
	*功能:	判断抽奖结果
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-9-10:15                                                                   
	*/
	bool judgeLotteryResult(int pos);

	string getLotteryPath(GoodsType type);

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

	void popOutDialog(PayType type);

	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

private:
	bool m_lotteryStatu;				//抽奖状态 true 正在进行 false 已结束或未开始
	int m_callbackCount;				//回调次数
	int m_lotteryResult;				//记录最后停留的位置
	Size lottSize;

private:
	SpriteBatchNode *m_batchNode;
	NumSprite *m_numSp;
	Button *m_startBtn;
	Button *m_closeBtn;
	Sprite *m_lightSp;	//物品上的光环
	Sprite *m_centerLightSp;	//中心位置上的
	Sprite *m_goodsLottery;
	NumSprite *m_numGoodsLottery;

	Vector<Node *> m_goodsBg;
	Vector<Node *> m_lottery;
	std::vector<Vec2> m_vecLotteryPos;	//奖品的位置
	std::vector<int> m_vecGoodsResult;	//奖品的种类
	std::vector<int> m_vecNumberResult;	//奖品的数量	
};

#endif

