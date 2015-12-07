#include "Helper.h"
USING_NS_CC;

NumSprite* NumSprite::create(int num, NumberType pType)
{
   
    NumSprite* n = new NumSprite;
	n->m_num = num;
	n->m_type = pType;
	//nup_X.png,应该是一个全透明的图片，就是用来占位子的
	Value name;
	if (pType == GameNumberScore)
	{
		name = Value("fs_X.png");
	}
	else if (pType == GameChallenge)
	{
		name = Value("tz_X.png");
	}
	else
	{
		name = Value("nub_X.png");
	}
	
	n->initWithSpriteFrameName(name.asString());
    n->autorelease();
        
	n->createNumSprite();
	
    return n;
}


void NumSprite::setOpacity(GLubyte opacity)
{
    Vector<Node *> n = getChildren();
	for (auto pcd : n)
	{
		((Sprite*)pcd)->setOpacity(opacity);
	}
}

void NumSprite::setValue(int num)
{
	if (m_num == num)
	{
		return;
	}

	this->removeAllChildrenWithCleanup(true);
	m_num = num;

	Value name;
	if (m_type == GameNumberScore)
	{
		name = Value("fs_X.png");
	}
	else if (m_type == GameChallenge)
	{
		name = Value("tz_X.png");
	}
	else
	{
		name = Value("nub_X.png");
	}

	this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name.asString()));
	createNumSprite(false);
}

void NumSprite::setColor(const Color3B& color)
{
	if (m_color == color)
	{
		return;
	}

	m_color = color;

	Vector<Node *> n = getChildren();
	for (auto pcd : n)
	{
		((Sprite*)pcd)->setColor(m_color);
	}
}

void NumSprite::createNumSprite(bool is /* = true */)
{
	char str[256] = { 0 };
	char name[32];
	sprintf(str, "%d", m_num);

	float width = 0;
	float height = 0;
	for (int i = 0; i < sizeof(str); i++)
	{
		if (str[i] == 0)
			break;
		if (m_type == NumberType::GameNumberScore)
		{
			sprintf(name, "nub_%c.png", str[i]);
		}
		else if (m_type == NumberType::GameNumberCurScore)
		{
			sprintf(name, "sj%c.png", str[i]);
		}
		else if (m_type == NumberType::GameNumberAward)
		{
			sprintf(name, "sj%c.png", str[i]);
		}
		else if (m_type == NumberType::GameNumberGoods)
		{
			sprintf(name, "sj%c.png", str[i]);
		}
		else if (m_type == NumberType::GameLottery)
		{
			sprintf(name, "jl_%c.png", str[i]);
		}
		else if (m_type == NumberType::GameChallenge)
		{
			sprintf(name, "tz_%c.png", str[i]);
		}		
		else
		{
			sprintf(name, "sj%c.png", str[i]);
		}		

		Sprite *p = NULL;

		p = Sprite::createWithSpriteFrameName(name);
		this->addChild(p);
		p->setAnchorPoint(Vec2());
		p->setPosition(ccp(width, 0));
		height = p->getContentSize().height;
		width += p->getContentSize().width;

		if (is)
		{
			if (m_type == NumberType::GameNumberCurScore)
			{
				p->setColor(Color3B::YELLOW);
				m_color = Color3B::YELLOW;
			}
			else if (m_type == GameNumberAward)
			{
				p->setColor(Color3B::ORANGE);
				m_color = Color3B::ORANGE;
			}
			else if (m_type == NumberType::GameNumberGoods)
			{
				p->setColor(Color3B::RED);
				m_color = Color3B::RED;
			}
		}
		else
		{
			if (m_color != Color3B::BLACK)
			{
				p->setColor(m_color);
			}			
		}
	}

	this->setContentSize(Size(width, height));
}
