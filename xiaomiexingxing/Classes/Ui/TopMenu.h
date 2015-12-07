#ifndef _TOPMENU_H_
#define _TOPMENU_H_

#include "cocos2d.h"
#include "Data/Const.h"
#include <ui/UIButton.h>
#include "Core/Helper.h"

USING_NS_CC;
using namespace cocos2d::ui;

class GameLayer;

class TopMenu : public Ref
{
public:
	virtual bool init(GameLayer *layer);
	static TopMenu *create(GameLayer *layer);

	void refresh();
	void updateEveryScore(int score);
	~TopMenu();
	TopMenu();

	/*
		更新钻石数量
	*/
	void updateDiamondNumber(int num);

public:
	NumSprite *m_moneyStar;

private:
	NumSprite *m_highestScore;
	NumSprite *m_level;
	NumSprite *m_targetScore;
	NumSprite *m_curScore;
	GameLayer *m_layer;
};
#endif
