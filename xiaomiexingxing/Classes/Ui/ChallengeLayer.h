#ifndef CHALLENGELAYER_H
#define CHALLENGELAYER_H

#include "StudioLayer.h"
#include "Data/GameData.h"
#include "Core/Helper.h"
#include "GameDialogLayer.h"
#include "ChallengeGameLayer.h"

class ChallengeLayer : public StudioLayer
{
public:
	ChallengeLayer();
	~ChallengeLayer();

	virtual bool init();
	CREATE_FUNC(ChallengeLayer);

	void onEnter();

private:
	void initUI();

	void onBtnClick(Ref *pSender, Widget::TouchEventType type);

	/*
	*功能:	游戏弹框处理
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-10-14:27
	*/
	void popOutDialog(PayType type);

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

	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

private:
	Button *m_btnAdd;
	Button *m_btnSub;
	Button *m_btnStart;
	Button *m_btnClose;

	NumSprite *m_zuanshiCount;//奖励
	NumSprite *m_betSp;//投注
	NumSprite *m_numSp;
};


#endif


