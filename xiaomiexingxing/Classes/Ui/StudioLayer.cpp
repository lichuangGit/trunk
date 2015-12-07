#include "StudioLayer.h"


StudioLayer::StudioLayer()
	:m_layerColor(nullptr)
{
}


StudioLayer::~StudioLayer()
{
}

bool StudioLayer::init(int opacity /* = 0 */, bool isMove /* = true */)
{
	if (!Layer::init())
	{
		return false;
	}

	m_opacity = opacity;

	if (isMove)
	{
		if (opacity)
		{
			initLayerColor(0);
		}
		this->setPosition(Vec2(0, VISIBLE_SIZE.height));
		fadeInLayer();		
	}
	else
	{
		if (opacity)
		{
			initLayerColor(opacity);
		}
	}

	return true;
}

void StudioLayer::onEnter()
{
	Layer::onEnter();

	registerListener();
}

void StudioLayer::initLayerColor(int opacity)
{
	m_layerColor = LayerColor::create();
	m_layerColor->setColor(Color3B::BLACK);
	m_layerColor->setOpacity(opacity);
	m_layerColor->setContentSize(Size(VISIBLE_SIZE.width, VISIBLE_SIZE.height));
	this->addChild(m_layerColor);
}

//void StudioLayer::closeLayer(Ref *pSender, Widget::TouchEventType type)
//{
//	if (m_layerColor)
//	{
//		m_layerColor->setOpacity(0);
//	}
//	auto moveBack = MoveBy::create(0.2f, Vec2(-100, 0));
//	auto move = MoveBy::create(0.3f, Vec2(VISIBLE_SIZE.width, 0));
//	auto call = CallFunc::create([=](){this->removeFromParentAndCleanup(true); });
//	auto seq = Sequence::create(moveBack, move, call, nullptr);
//
//	this->runAction(seq);
//}

void StudioLayer::closeLayer()
{
	m_layerColor->setOpacity(0);
	
	auto move = MoveBy::create(0.5f, Vec2(0, VISIBLE_SIZE.height));
	this->runAction(Sequence::create(move, CallFunc::create(CC_CALLBACK_0(StudioLayer::removeSelf, this)), nullptr));
}

void StudioLayer::removeSelf()
{
	this->removeFromParentAndCleanup(true);
}

void StudioLayer::registerListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(StudioLayer::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool StudioLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void StudioLayer::fadeInLayer()
{
	auto move = MoveBy::create(0.5f, Vec2(0, -VISIBLE_SIZE.height));
	auto ease = EaseBounceOut::create(move);
	Sequence *seq;
	if (m_opacity)
	{
		auto call = CallFunc::create(CC_CALLBACK_0(StudioLayer::setLayerOpacity, this, 8));
		auto call1 = CallFunc::create(CC_CALLBACK_0(StudioLayer::setLayerOpacity, this, 4));
		auto call2 = CallFunc::create(CC_CALLBACK_0(StudioLayer::setLayerOpacity, this, 2));
		auto call3 = CallFunc::create(CC_CALLBACK_0(StudioLayer::setLayerOpacity, this, 1));
		auto delay = DelayTime::create(0.1f);
		seq = Sequence::create(ease, call, delay, call1, delay->clone(), call2, delay->clone(), call3, nullptr);
	}
	else
	{
		seq = Sequence::create(ease, nullptr);
	}
	
	this->runAction(seq);
}

void StudioLayer::setLayerOpacity(int value)
{
	m_layerColor->setOpacity(m_opacity / value);
}
