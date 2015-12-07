#include "Props.h"
#include "GameLayer.h"

Props::Props():
m_layer(nullptr),
m_propType(GoodsType::goodsNone),
m_propNumber(nullptr),
m_actionStatus(false),
m_isDoAction(false)
{
}


Props::~Props()
{
}

Props *Props::create(GoodsType type, GameLayer *layer, const ccMenuCallback& callback)
{
	Props *pRet = new Props;

	if (pRet && pRet->init(type,layer,callback))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	
	return nullptr;
}

bool Props::init(GoodsType type, GameLayer *layer, const ccMenuCallback& callback)
{
	m_propType = type;
	m_layer = layer;
	m_propName = getProps();

	auto sp = Sprite::createWithSpriteFrameName(m_propName);

	if (!MenuItemSprite::initWithNormalSprite(sp, sp, nullptr, callback))
	{
		return false;
	}

	
	Size size = sp->getContentSize();

	float middle = (Prop_Middle - size.width * Prop_Count) / (Prop_Count - 1);
	float x = Prop_LeftRight + (m_propType - 1 + 0.5) * size.width + middle * (m_propType - 1);
	this->setPosition(Vec2(x, size.height));

	//显示道具数量
	if (GameData::getInstance()->getGoodsNumber(m_propType) > 0)
	{
		m_propNumber = NumSprite::create(GameData::getInstance()->getGoodsNumber(m_propType), NumberType::GameNumberGoods);
		m_propNumber->setPosition(this->getContentSize().width / 2 + x, size.height / 2);
		m_layer->getBatchNode()->addChild(m_propNumber);
	}

	if (type == GoodsType::Bomb || type == GoodsType::Tongsexiao || type == GoodsType::Huanse)
	{
		m_isDoAction = true;
	}

	return true;
}

void Props::updatePropsNumber(int num)
{
	if (num > 0)
	{
		if (m_propNumber == nullptr)
		{
			m_propNumber = NumSprite::create(num, NumberType::GameNumberGoods);
			m_propNumber->setPosition(this->getContentSize().width, 0);
			this->addChild(m_propNumber);
		}
		else
		{
			m_propNumber->setValue(num);
		}
	}
	else
	{
		m_propNumber->removeFromParentAndCleanup(true);
		m_propNumber = nullptr;
	}
}

void Props::goPropAction()
{
	if (!getDoAction())
	{
		return;
	}
	auto scale = ScaleBy::create(0.5f, 0.5f);
	this->runAction(RepeatForever::create(Sequence::create(scale, scale->reverse(), nullptr)));
	setActionStatus(true);
}

void Props::stopPropAction()
{
	this->stopAllActions();
	this->setScale(1.0f);
	setActionStatus(false);
}

string Props::getProps()
{
	switch (m_propType)
	{
	case GoodsType::Bomb:
		return "bomb.png";
	case GoodsType::Tongsexiao:
		return "tongsexiao.png";
	case GoodsType::Huanse:
		return "huanse.png";
	case GoodsType::Chexiao:
		return "chexiao.png";
	case  GoodsType::Shuaxin:
		return "refurbish.png";
	}

	return nullptr;
}
