#include "ShopLayer.h"

ShopLayer::ShopLayer()
{
}


ShopLayer::~ShopLayer()
{
	TextureCache::getInstance()->removeTextureForKey("menubg.png");
	TextureCache::getInstance()->removeTextureForKey("shapp.png");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("lottery.plist");
}

bool ShopLayer::init()
{
	if (!StudioLayer::init(LayerOpacity))
	{
		return false;
	}

	TextureCache::getInstance()->addImage("menubg.png");
	TextureCache::getInstance()->addImage("shapp.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("lottery.plist");

	auto keyboardlistener = EventListenerKeyboard::create();
	keyboardlistener->onKeyReleased = CC_CALLBACK_2(ShopLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardlistener, this);

	return true;
}

void ShopLayer::onEnter()
{
	StudioLayer::onEnter();

	initUI();
}

void ShopLayer::initUI()
{
	auto bg = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("menubg.png"));
	bg->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	bg->setScale(1.15f);
	this->addChild(bg);

	Size size = bg->getContentSize() * 1.15f;

	auto text = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("shapp.png"));
	text->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	text->setScale(1.15f);
	this->addChild(text);

	m_btnClose = Button::create("menuClose.png", "menuClose.png", "menuClose.png", Widget::TextureResType::PLIST);
	m_btnClose->setPosition(bg->getPosition() + Vec2(size.width / 2 - m_btnClose->getContentSize().width  * 0.7, size.height / 2 - m_btnClose->getContentSize().height * 0.7));
	m_btnClose->addTouchEventListener(CC_CALLBACK_2(ShopLayer::onBtnClick, this));
	m_btnClose->setPressedActionEnabled(true);
	this->addChild(m_btnClose);

	m_btnTwo = Button::create("twoyuan.png", "twoyuan.png", "twoyuan.png", Widget::TextureResType::PLIST);
	m_btnTwo->setPosition(bg->getPosition() + Vec2(size.width * 0.32, size.height / 5));
	m_btnTwo->addTouchEventListener(CC_CALLBACK_2(ShopLayer::onBtnClick, this));
	m_btnTwo->setPressedActionEnabled(true);
	this->addChild(m_btnTwo);

	m_btnFour = Button::create("fouryuan.png", "fouryuan.png", "fouryuan.png", Widget::TextureResType::PLIST);
	m_btnFour->setPosition(bg->getPosition() + Vec2(size.width * 0.32, size.height / 10 - 5));
	m_btnFour->addTouchEventListener(CC_CALLBACK_2(ShopLayer::onBtnClick, this));
	m_btnFour->setPressedActionEnabled(true);
	this->addChild(m_btnFour);

	m_btnSix = Button::create("sixyuan.png", "sixyuan.png", "sixyuan.png", Widget::TextureResType::PLIST);
	m_btnSix->setPosition(bg->getPosition() + Vec2(size.width * 0.32, -10));
	m_btnSix->addTouchEventListener(CC_CALLBACK_2(ShopLayer::onBtnClick, this));
	m_btnSix->setPressedActionEnabled(true);
	this->addChild(m_btnSix);

	m_btnTen = Button::create("tenyuan.png", "tenyuan.png", "tenyuan.png", Widget::TextureResType::PLIST);
	m_btnTen->setPosition(bg->getPosition() + Vec2(size.width * 0.32, -size.height / 7.5));
	m_btnTen->addTouchEventListener(CC_CALLBACK_2(ShopLayer::onBtnClick, this));
	m_btnTen->setPressedActionEnabled(true);
	this->addChild(m_btnTen);

	m_numSp = NumSprite::create(GameData::getInstance()->getGoodsNumber(GoodsType::Zuanshi), NumberType::GameLottery);
	m_numSp->setPosition(Vec2(bg->getPosition() + Vec2(-bg->getContentSize().width / 3.2, bg->getContentSize().height / 2.75)));
	this->addChild(m_numSp);
}

void ShopLayer::onBtnClick(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::BEGAN)
	{
		Button *btn = (Button *)pSender;
		if (btn == m_btnTwo)
		{
			popOutDialog(PayType::pGameTwo);
		}
		else if (btn == m_btnFour)
		{
			popOutDialog(PayType::pGameFour);
		}
		else if (btn == m_btnSix)
		{
			popOutDialog(PayType::pGameSix);
		}
		else if (btn == m_btnTen)
		{
			popOutDialog(PayType::pGameTen);
		}
		else if (btn == m_btnClose)
		{
			StudioLayer::closeLayer();
		}
	}
}

void ShopLayer::popOutDialog(PayType type)
{
	auto dialog = GameDialogLayer::createPay(DialogType::PayDialog, type, CC_CALLBACK_3(ShopLayer::payDialogCallBack, this));
	if (dialog)
	{
		this->addChild(dialog);
	}
}

void ShopLayer::payDialogCallBack(int point, int result, std::map<int, int> _map)
{
	if (result == PayResult::Success)
	{
		if (!_map.empty())
		{
			for (auto it : _map)
			{
				updateGoodsNumber((GoodsType)it.first, it.second);
			}
		}
	}
}

void ShopLayer::updateGoodsNumber(GoodsType type, int num)
{
	num = GameData::getInstance()->getGoodsNumber(type) + num;
	GameData::getInstance()->setGoodsNumber(type, num);

	if (type == GoodsType::Zuanshi)
	{
		m_numSp->setValue(num);
	}
}

void ShopLayer::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
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
