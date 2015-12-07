#ifndef __fish__Helper__
#define __fish__Helper__

#include "cocos2d.h"

USING_NS_CC;

enum NumberType
{
    GameNumberNormal = 0,
	GameNumberCurScore,		//游戏当前分数
	GameNumberScore,		//奖励分数数字
	GameNumberAward,		//奖励物品
	GameNumberGoods,		//道具数量
	GameLottery,			//抽奖
	GameChallenge			//挑战
};

class NumSprite : public Sprite
{
public:
    static NumSprite* create(int num, NumberType pType = GameNumberNormal);
    virtual void setOpacity(GLubyte opacity);
	void setValue(int num);
	void setColor(const Color3B& color);

	inline Color3B getColor(){ return m_color; }

private:
	void createNumSprite(bool is = true);
	int m_num;
	NumberType m_type;
	Color3B m_color;
};



#endif
