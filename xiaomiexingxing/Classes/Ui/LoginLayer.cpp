#include "LoginLayer.h"
#include "Data/GameData.h"

LoginLayer::LoginLayer():
m_isLogining(false)
{
}


LoginLayer::~LoginLayer()
{
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("login.plist");
	TextureCache::getInstance()->removeTextureForKey("otherDialogBg.png");
	TextureCache::getInstance()->removeTextureForKey("login.png");
}

bool LoginLayer::init()
{
	if (!StudioLayer::init(LayerOpacity))
	{
		return false;
	}

	TextureCache::getInstance()->addImage("otherDialogBg.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("login.plist");
	TextureCache::getInstance()->addImage("login.png");

	auto keyboardlistener = EventListenerKeyboard::create();
	keyboardlistener->onKeyReleased = CC_CALLBACK_2(LoginLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardlistener, this);

	return true;
}

void LoginLayer::onEnter()
{
	StudioLayer::onEnter();

	initUI();
}

void LoginLayer::initUI()
{
	auto bg = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("otherDialogBg.png"));
	bg->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	bg->setScaleX(1.1f);
	this->addChild(bg);

	SpriteBatchNode *batchNode = SpriteBatchNode::createWithTexture(TextureCache::getInstance()->getTextureForKey("login.png"));
	this->addChild(batchNode);

	auto title = Sprite::createWithSpriteFrameName("qiandao.png");
	title->setPosition(Vec2(bg->getPosition() + Vec2(0, bg->getContentSize().height / 2 - title->getContentSize().height)));
	batchNode->addChild(title);

	auto sp = Sprite::createWithSpriteFrameName("qiandao1.png");
	Size size = sp->getContentSize();
	sp->setPosition(Vec2(bg->getPosition() + Vec2(-size.width - 15, size.height * 0.6)));
	batchNode->addChild(sp);
	m_vecSp.pushBack(sp);

	auto sp1 = Sprite::createWithSpriteFrameName("qiandao2.png");
	sp1->setPosition(Vec2(bg->getPosition() + Vec2(0, size.height * 0.6)));
	batchNode->addChild(sp1);
	m_vecSp.pushBack(sp1);

	auto sp2 = Sprite::createWithSpriteFrameName("qiandao3.png");
	sp2->setPosition(Vec2(bg->getPosition() + Vec2(size.width + 15, size.height * 0.6)));
	batchNode->addChild(sp2);
	m_vecSp.pushBack(sp2);

	auto sp3 = Sprite::createWithSpriteFrameName("qiandao4.png");
	sp3->setPosition(Vec2(bg->getPosition() + Vec2(-size.width * 1.4 - 30, -size.height * 0.6)));
	batchNode->addChild(sp3);
	m_vecSp.pushBack(sp3);

	auto sp4 = Sprite::createWithSpriteFrameName("qiandao5.png");
	sp4->setPosition(Vec2(bg->getPosition() + Vec2(-size.width * 0.4 - 15, -size.height * 0.6)));
	batchNode->addChild(sp4);
	m_vecSp.pushBack(sp4);

	auto sp5 = Sprite::createWithSpriteFrameName("qiandao6.png");
	sp5->setPosition(Vec2(bg->getPosition() + Vec2(size.width * 0.4 + 15, -size.height * 0.6)));
	batchNode->addChild(sp5);
	m_vecSp.pushBack(sp5);

	auto sp6 = Sprite::createWithSpriteFrameName("qiandao7.png");
	sp6->setPosition(Vec2(bg->getPosition() + Vec2(size.width * 1.4 + 30, -size.height * 0.6)));
	batchNode->addChild(sp6);
	m_vecSp.pushBack(sp6);

	m_closeBtn = Button::create("menuClose.png", "menuClose.png", "menuClose.png", Widget::TextureResType::PLIST);
	m_closeBtn->setPosition(bg->getPosition() + Vec2(bg->getContentSize().width  * 1.1 / 2 - m_closeBtn->getContentSize().width  * 0.7, bg->getContentSize().height / 2 - m_closeBtn->getContentSize().height * 0.7));
	m_closeBtn->addTouchEventListener(CC_CALLBACK_2(LoginLayer::onBtnClick, this));
	this->addChild(m_closeBtn);

	m_okBtn = Button::create("get.png", "get.png", "get.png", Widget::TextureResType::PLIST);
	m_okBtn->setPosition(bg->getPosition() + Vec2(0, -bg->getContentSize().height / 2 + m_okBtn->getContentSize().height * 0.75));
	m_okBtn->addTouchEventListener(CC_CALLBACK_2(LoginLayer::onBtnClick, this));
	this->addChild(m_okBtn);

	auto scale = ScaleBy::create(1.0f, 0.8f);
	m_vecSp.at(GameData::getInstance()->getLoginDayNum())->runAction(RepeatForever::create(Sequence::create(scale, scale->reverse(), nullptr)));
}

void LoginLayer::onBtnClick(Ref* sender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::BEGAN)
	{
		if (m_closeBtn == sender)
		{
			StudioLayer::closeLayer();
		}
		else if (m_okBtn == sender)
		{
			if (m_isLogining)
			{
				return;
			}
			m_isLogining = true;

			GameData::getInstance()->setGoodsNumber(GoodsType::Zuanshi, GameData::getInstance()->getGoodsNumber(GoodsType::Zuanshi) + getZuanshiByDays(GameData::getInstance()->getLoginDayNum()));
			GameData::getInstance()->setLoginTime(getCurrentDays(0));
			GameData::getInstance()->setLoginDayNum(GameData::getInstance()->getLoginDayNum() >= 6 ? 6 : GameData::getInstance()->getLoginDayNum() + 1);

			auto scale = ScaleBy::create(0.3f, 0.8f);
			auto repeat = Repeat::create(Sequence::create(scale, scale->reverse(), nullptr), 3);
			auto call = CallFunc::create([=](){StudioLayer::closeLayer(); });
			m_okBtn->runAction(Sequence::createWithTwoActions(repeat, call));
		}
	}
}

int LoginLayer::getZuanshiByDays(int day)
{
	switch (day)
	{
	case 0:
		return 5;
	case 1:
		return 8;
	case 2:
		return 13;
	case 3:
		return 21;
	case 4:
		return 34;
	case 5:
		return 55;
	case 6:
	default:
		return 89;
	}
}

void LoginLayer::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	if (event->getType() == Event::Type::KEYBOARD)
	{
		event->stopPropagation();
	}
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_BACK:
		StudioLayer::closeLayer();
		break;
	}
}
