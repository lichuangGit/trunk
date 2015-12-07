#include "StarBook.h"


StarBook::StarBook()
{
}


StarBook::~StarBook()
{
	TextureCache::getInstance()->removeTextureForKey(menuBg);
	TextureCache::getInstance()->removeTextureForKey("baodian.png");
}

bool StarBook::init()
{
	if (!StudioLayer::init(LayerOpacity))
	{
		return false;
	}

	TextureCache::getInstance()->addImage(menuBg);
	TextureCache::getInstance()->addImage("baodian.png");

	auto keyboardlistener = EventListenerKeyboard::create();
	keyboardlistener->onKeyReleased = CC_CALLBACK_2(StarBook::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardlistener, this);

	return true;
}

void StarBook::onEnter()
{
	StudioLayer::onEnter();

	initUI();
}

void StarBook::initUI()
{
	auto bg = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey(menuBg));
	bg->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	this->addChild(bg);

	auto text = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("baodian.png"));
	text->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	this->addChild(text);

	auto close = Sprite::createWithSpriteFrameName("menuClose.png");
	auto item = MenuItemSprite::create(close, close, CC_CALLBACK_0(StudioLayer::closeLayer, this));
	item->setPosition(bg->getPosition() + Vec2(bg->getContentSize().width / 2 - item->getContentSize().width * 0.7, bg->getContentSize().height / 2 - item->getContentSize().height * 0.7));

	auto menu = Menu::create(item, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}

void StarBook::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
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
