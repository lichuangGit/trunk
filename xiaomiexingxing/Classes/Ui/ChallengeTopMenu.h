#ifndef CHALLENGETOPMENU_H
#define CHALLENGETOPMENU_H

#include "cocos2d.h"
#include "Data/Const.h"
#include "Core/Helper.h"

USING_NS_CC;

class ChallengeGameLayer;

class ChallengeTopMenu : public Ref
{
public:
	virtual bool init(ChallengeGameLayer *layer);
	static ChallengeTopMenu *create(ChallengeGameLayer *layer);

	void refresh();
	void updateEveryScore(int score);
	~ChallengeTopMenu();
	ChallengeTopMenu();

	/*
		更新钻石数量
	*/
	void updateDiamondNumber(int num);

	int getCurScore();

public:
	NumSprite *m_moneyStar;

private:
	NumSprite *m_highestScore;
	NumSprite *m_level;
	NumSprite *m_targetScore;
	NumSprite *m_curScore;
	ChallengeGameLayer *m_layer;
	int m_score;
};
#endif
