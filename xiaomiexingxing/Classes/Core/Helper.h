#ifndef __fish__Helper__
#define __fish__Helper__

#include "cocos2d.h"

USING_NS_CC;

enum NumberType
{
    GameNumberNormal = 0,
	GameNumberCurScore,		//��Ϸ��ǰ����
	GameNumberScore,		//������������
	GameNumberAward,		//������Ʒ
	GameNumberGoods,		//��������
	GameLottery,			//�齱
	GameChallenge			//��ս
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
