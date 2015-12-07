#include "SettingLayer.h"

SettingLayer::SettingLayer() : 
isGoHome(false)
{
}


SettingLayer::~SettingLayer()
{
	if (!isGoHome)
	{
		SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("gameset.plist");
	}
	TextureCache::getInstance()->removeTextureForKey(DialogPathBg);
}

bool SettingLayer::init()
{
	if (!StudioLayer::init(LayerOpacity))
	{
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameset.plist");
	TextureCache::getInstance()->addImage(DialogPathBg);

	auto keyboardlistener = EventListenerKeyboard::create();
	keyboardlistener->onKeyReleased = CC_CALLBACK_2(SettingLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardlistener, this);

	return true;
}

void SettingLayer::onEnter()
{
	StudioLayer::onEnter();

	initUI();
}

void SettingLayer::initUI()
{
	auto bg = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey(DialogPathBg));
	bg->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	this->addChild(bg);

	auto spTitle = Sprite::createWithSpriteFrameName("pause.png");
	spTitle->setPosition(bg->getPosition() + Vec2(0, bg->getContentSize().height / 2 - spTitle->getContentSize().height));
	this->addChild(spTitle);

	auto spText = Sprite::createWithSpriteFrameName("pausewenzi.png");
	spText->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	this->addChild(spText);

	auto spContinue = Sprite::createWithSpriteFrameName("gamecontinue.png");
	auto itemContinue = MenuItemSprite::create(spContinue, spContinue, CC_CALLBACK_0(SettingLayer::onMenuCallBack, this, 0));
	itemContinue->setPosition(bg->getPosition() + Vec2(0, -bg->getContentSize().height / 2 + itemContinue->getContentSize().height));

	auto spReturn = Sprite::createWithSpriteFrameName("return.png");
	auto itemReturn = MenuItemSprite::create(spReturn, spReturn, CC_CALLBACK_0(SettingLayer::onMenuCallBack, this, 1));
	itemReturn->setPosition(itemContinue->getPosition() + Vec2(-itemReturn->getContentSize().width * 2, 0));

	auto spOn = Sprite::createWithSpriteFrameName("musicon.png");
	itemOn = MenuItemSprite::create(spOn, spOn, CC_CALLBACK_0(SettingLayer::onMenuCallBack, this, 2));
	itemOn->setPosition(itemContinue->getPosition() + Vec2(itemOn->getContentSize().width * 2, 0));

	auto spOff = Sprite::createWithSpriteFrameName("musicoff.png");
	itemOff = MenuItemSprite::create(spOff, spOff, CC_CALLBACK_0(SettingLayer::onMenuCallBack, this, 3));
	itemOff->setPosition(itemContinue->getPosition() + Vec2(itemOff->getContentSize().width * 2, 0));

	if (GameData::getInstance()->getMusicIsPlay())
	{
		itemOff->setVisible(false);
	}
	else
	{
		itemOn->setVisible(false);
	}

	auto menu = Menu::create(itemReturn, itemContinue, itemOn, itemOff, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}

void SettingLayer::onMenuCallBack(int type)
{
	if (type == 0)//继续
	{
		if (GameData::getInstance()->getGameMode() == GameData::GameNormal)
		{
			((GameLayer*)this->getParent())->onTouchEnded(nullptr, nullptr);
		}
		else
		{
			((ChallengeGameLayer*)this->getParent())->onTouchEnded(nullptr, nullptr);
		}
		StudioLayer::closeLayer();
	}
	else if (type == 1)//返回主页
	{
		goHome();
	}
	else if (type == 2)//音乐开
	{
		musicOnOff(false);
	}
	else if (type == 3)//音乐关
	{
		musicOnOff(true);
	}
}

void SettingLayer::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	if (event->getType() == Event::Type::KEYBOARD)
	{
		event->stopPropagation();
	}
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_BACK:
		if (GameData::getInstance()->getGameMode() == GameData::GameNormal)
		{
			((GameLayer*)this->getParent())->onTouchEnded(nullptr, nullptr);
		}
		else
		{
			((ChallengeGameLayer*)this->getParent())->onTouchEnded(nullptr, nullptr);
		}
		StudioLayer::closeLayer();
		break;
	}
}

void SettingLayer::musicOnOff(bool is)
{
	GameData::getInstance()->setMusicIsPlay(is);
	itemOff->setVisible(!is);
	itemOn->setVisible(is);
	if (is)
	{
		Audio::getInstance()->playBGM();
	}
	else
	{
		Audio::getInstance()->stopBGM();
	}
}

void SettingLayer::goHome()
{
	isGoHome = true;

	if (GameData::getInstance()->getGameMode() == GameData::GameNormal)
	{
		GameData::getInstance()->setIsGameArchive(true);
		GameData::getInstance()->saveLastLevel();
		GameData::getInstance()->saveLastLevelSocre(GameData::getInstance()->getCurScore());
		GameData::getInstance()->setIsGameOver(false);
		((GameLayer*)this->getParent())->saveStarAtExitGame();
	}
	else
	{
		GameData::getInstance()->setGoodsNumber(GoodsType::Zuanshi, GameData::getInstance()->getGoodsNumber(GoodsType::Zuanshi) - GameData::getInstance()->getChallengeZuanshi());
		GameData::getInstance()->setChallengeZuanshi(0);
	}
	Director::getInstance()->replaceScene(MenuLayer::scene());
}
