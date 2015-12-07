#include "MenuLayer.h"


MenuLayer::MenuLayer()
{
	m_isGameContinue = true;
}


MenuLayer::~MenuLayer()
{
	/*SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Ui.plist");
	TextureCache::getInstance()->removeTextureForKey("bg_menuscene.jpg");
	TextureCache::getInstance()->removeTextureForKey("Ui.png");*/
}

Scene *MenuLayer::scene()
{
	auto scene = Scene::create();

	auto layer = MenuLayer::create();

	if (layer == nullptr)
	{
		layer = MenuLayer::create();
	}

	if (layer)
	{
		Audio::getInstance()->playBGM();
		scene->addChild(layer);
	}

	return scene;
}

bool MenuLayer::init()
{
	if (!StudioLayer::init(0, false))
	{
		return false;
	}

	SpriteFrameCache::getInstance()->removeSpriteFrames();
	TextureCache::getInstance()->removeAllTextures();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Ui.plist");
	TextureCache::getInstance()->addImage("bg_menuscene.jpg");
	TextureCache::getInstance()->addImage("Ui.png");

	auto keyboardlistener = EventListenerKeyboard::create();
	keyboardlistener->onKeyReleased = CC_CALLBACK_2(MenuLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardlistener, this);

	return true;
}

void MenuLayer::onEnter()
{
	StudioLayer::onEnter();

	initUI();

	if (GameData::getInstance()->getIsGameLoginGift())
	{
		GameData::getInstance()->setIsGameLoginGift(false);
		popOutDialog(PayType::pGameLogin);
	}
	else
	{
		//签到
		checkLogin();		
	}
}

void MenuLayer::initUI()
{
	auto bg = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("bg_menuscene.jpg"));
	bg->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	bg->setScaleY(SCALEFACTOR);
	this->addChild(bg);

	auto batchNode = SpriteBatchNode::createWithTexture(TextureCache::getInstance()->addImage("Ui.png"));
	this->addChild(batchNode);

	auto title = Sprite::createWithSpriteFrameName("popstar5S.png");
	title->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height + title->getContentSize().height * 0.5));
	batchNode->addChild(title);
		
	auto move = MoveBy::create(0.5f, Vec2(0, -title->getContentSize().height * 1.1));
	auto ease = EaseBounceOut::create(move);
	auto call = CallFuncN::create([&](Node *pSender){
		auto scale = ScaleBy::create(1.0f, 0.8f);
		auto seq = Sequence::create(scale, scale->reverse(), nullptr);
		pSender->runAction(RepeatForever::create(seq));
	});
	title->runAction(Sequence::create(ease, call, nullptr));

	auto light = Sprite::createWithSpriteFrameName("stage_clear_bg.png");
	light->setPosition(Vec2(VISIBLE_SIZE.width * 0.85, VISIBLE_SIZE.height * 0.55));
	light->setScale(0.4f);
	batchNode->addChild(light);
	light->runAction(RepeatForever::create(RotateBy::create(3.0f, 360)));

	auto spNew = Sprite::createWithSpriteFrameName("new_game.png");
	auto itemNew = MenuItemSprite::create(spNew, spNew, CC_CALLBACK_0(MenuLayer::onMenuItemCallBack, this, MenuType::NewGame));
	itemNew->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height * 0.55));

	auto spPrize = Sprite::createWithSpriteFrameName("choujiang.png");
	auto itemPrize = MenuItemSprite::create(spPrize, spPrize, CC_CALLBACK_0(MenuLayer::onMenuItemCallBack, this, MenuType::Choujiang));
	itemPrize->setPosition(Vec2(VISIBLE_SIZE.width * 0.85, VISIBLE_SIZE.height * 0.55));

	auto spChallenge = Sprite::createWithSpriteFrameName("challenge.png");
	auto itemChallenge = MenuItemSprite::create(spChallenge, spChallenge, CC_CALLBACK_0(MenuLayer::onMenuItemCallBack, this, MenuType::Challenge));
	itemChallenge->setPosition(Vec2(VISIBLE_SIZE.width * 0.15, VISIBLE_SIZE.height * 0.55));

	auto spContinue = Sprite::createWithSpriteFrameName("continue.png");
	auto itemContinue = MenuItemSprite::create(spContinue, spContinue, CC_CALLBACK_0(MenuLayer::onMenuItemCallBack, this, MenuType::ContinueGame));
	itemContinue->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height * 0.4));

	auto spShop = Sprite::createWithSpriteFrameName("shop.png");
	auto itemShop = MenuItemSprite::create(spShop, spShop, CC_CALLBACK_0(MenuLayer::onMenuItemCallBack, this, MenuType::Shop));
	itemShop->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height * 0.25));
	
	auto scale = ScaleBy::create(1.0f, 0.8f);
	auto spBigBag = Sprite::createWithSpriteFrameName("firsPay.png");
	auto itemBigBag = MenuItemSprite::create(spBigBag, spBigBag, CC_CALLBACK_0(MenuLayer::onMenuItemCallBack, this, MenuType::Libao));
	itemBigBag->setPosition(Vec2(VISIBLE_SIZE.width * 0.15, VISIBLE_SIZE.height * 0.25));
	itemBigBag->runAction(RepeatForever::create(Sequence::create(scale, scale->reverse(), nullptr)));

	auto spText = Sprite::createWithSpriteFrameName("popText.png");
	auto itemText = MenuItemSprite::create(spText, spText, CC_CALLBACK_0(MenuLayer::onMenuItemCallBack, this, MenuType::Baodian));
	itemText->setPosition(Vec2(VISIBLE_SIZE.width * 0.85, VISIBLE_SIZE.height * 0.25));
	
	auto spOn = Sprite::createWithSpriteFrameName("musicon.png");
	itemOn = MenuItemSprite::create(spOn, spOn, CC_CALLBACK_0(MenuLayer::onMenuItemCallBack, this, MenuType::MusicOn));
	itemOn->setPosition(Vec2(VISIBLE_SIZE.width - itemOn->getContentSize().width, VISIBLE_SIZE.height - itemOn->getContentSize().height));

	auto spOff = Sprite::createWithSpriteFrameName("musicoff.png");
	itemOff = MenuItemSprite::create(spOff, spOff, CC_CALLBACK_0(MenuLayer::onMenuItemCallBack, this, MenuType::MusicOff));
	itemOff->setPosition(Vec2(VISIBLE_SIZE.width-itemOff->getContentSize().width,VISIBLE_SIZE.height-itemOff->getContentSize().height));

	if (GameData::getInstance()->getMusicIsPlay())
	{
		itemOff->setVisible(false);
	}
	else
	{
		itemOn->setVisible(false);
	}

	auto menu = Menu::create(itemNew, itemPrize, itemChallenge, itemContinue, itemShop, itemBigBag, itemText, itemOff, itemOn, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}

void MenuLayer::onMenuItemCallBack(MenuType type)
{
	switch (type)
	{
	case MenuLayer::NewGame:
		goNewGame();
		break;
	case MenuLayer::ContinueGame:
		goContinueGame();
		break;
	case MenuLayer::Shop:
		goShop();
		break;
	case MenuLayer::Choujiang:
		goLottery();
		break;
	case MenuLayer::Challenge:
		goChallenge();
		break;
	case MenuLayer::Libao:
		m_isGameContinue = false;
		{
			map<string, string> _map;
			_map["position"] = "menu";
			UmengUpload::event(Umeng_Id_Chaozhilibao, &_map);
		}
		popOutDialog(cocos2d::random() % 100 < 50 ? PayType::pGameLibao99 : PayType::pGameLibao130);
		break;
	case MenuLayer::Baodian:
		goBaodian();
		break;
	case MenuType::MusicOff:
		musicOnOff(true);
		break;
	case MenuType::MusicOn:
		musicOnOff(false);
		break;
	default:
		break;
	}
}

void MenuLayer::goNewGame()
{
	if (!GameData::getInstance()->getIsGameOver() && GameData::getInstance()->getIsGameArchive())//未失败且有存档
	{
		popOutDialog(NormalType::nGameArchive, CC_CALLBACK_0(MenuLayer::goNewGameCallBack, this));
	}
	else
	{
		goNewGameCallBack();
	}	
}

void MenuLayer::goNewGameCallBack()
{
	GameData::getInstance()->resetParams();
	Director::getInstance()->replaceScene(GameLayer::createScene());
}

void MenuLayer::goContinueGame()
{
	if (GameData::getInstance()->getIsGameOver())//游戏失败
	{
		if (GameData::getInstance()->getGoodsNumber(GoodsType::Zuanshi) >= GameContinueZuanshi)
		{
			popOutDialog(NormalType::nGameContinue, CC_CALLBACK_0(MenuLayer::goContinueGameCallBack, this));
		}
		else//弹礼包
		{
			m_isGameContinue = true;
			map<string, string> _map;
			_map["position"] = "continue";
			UmengUpload::event(Umeng_Id_Chaozhilibao, &_map);
			popOutDialog(cocos2d::random() % 100 < 50 ? PayType::pGameLibao99 : PayType::pGameLibao130);
		}
	}
	else
	{
		if (!GameData::getInstance()->getIsGameArchive())//游戏无存档相当于新玩家第一次进入
		{
			goNewGameCallBack();
		}
		else//读取存档
		{
			GameData::getInstance()->init(GameData::getInstance()->getLastLevel(), GameData::getInstance()->getLastLevelSocre());
			Director::getInstance()->replaceScene(GameLayer::createScene());
		}
	}
}

void MenuLayer::goContinueGameCallBack()
{
	GameData::getInstance()->setGoodsNumber(GoodsType::Zuanshi, GameData::getInstance()->getGoodsNumber(GoodsType::Zuanshi) - GameContinueZuanshi);
	GameData::getInstance()->init(GameData::getInstance()->getPreviousLevel() + 1 , GameData::getInstance()->getPreviousScore());
	Director::getInstance()->replaceScene(GameLayer::createScene());
}

void MenuLayer::payDialogCallBack(int point, int result, std::map<int, int> _map)
{
	if (result == PayResult::Success)
	{
		if (!_map.empty())
		{
			//只刷新物品数量的执行下面代码
			for (auto it : _map)
			{
				updateGoodsNumber((GoodsType)it.first, it.second);
			}
		}
		if (point == PayPoint::Chaozhilibao99 || point == PayPoint::Chaozhilibao130)
		{
			if (m_isGameContinue)
			{
				GameData::getInstance()->init(GameData::getInstance()->getPreviousLevel() + 1, GameData::getInstance()->getPreviousScore());
				Director::getInstance()->replaceScene(GameLayer::createScene());
			}
		}
	}
	else if (result == PayResult::Failed || result == PayResult::Cancel)
	{
	}

	if (point == PayPoint::Exitgift)
	{
		UmengUpload::end();
		Director::getInstance()->end();
	}
	else if (point == PayPoint::Logingift)
	{
		checkLogin();
	}
}

void MenuLayer::updateGoodsNumber(GoodsType type, int num)
{
	num = GameData::getInstance()->getGoodsNumber(type) + num;
	GameData::getInstance()->setGoodsNumber(type, num);
}

void MenuLayer::goShop()
{
	ADDCHILD_FUNC(ShopLayer)
}

void MenuLayer::goBaodian()
{
	UmengUpload::event(Umeng_Id_Baodin);
	ADDCHILD_FUNC(StarBook)
}

void MenuLayer::goLottery()
{
	UmengUpload::event(Umeng_Id_Choujiang);
	ADDCHILD_FUNC(LotteryLayer)
}

void MenuLayer::goChallenge()
{
	UmengUpload::event(Umeng_Id_Tiaozhan);
	ADDCHILD_FUNC(ChallengeLayer)
}

void MenuLayer::popOutDialog(NormalType type, std::function<void(void)> func)
{
	StudioLayer *dialog = nullptr;

	dialog = GameDialogLayer::createNoramlNoData(DialogType::NormalDialog, type, func);

	if (dialog)
	{
		this->addChild(dialog);
	}
}

void MenuLayer::popOutDialog(PayType type)
{
	auto dialog = GameDialogLayer::createPay(DialogType::PayDialog, type, CC_CALLBACK_3(MenuLayer::payDialogCallBack, this));
	if (dialog)
	{
		this->addChild(dialog);
	}
}

void MenuLayer::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_BACK:
		popOutDialog(NormalType::nGameExit, CC_CALLBACK_0(MenuLayer::goGameExitCallBack, this));
		break; 
	}
}

void MenuLayer::goGameExitCallBack()
{
	//popOutDialog(PayType::pGameExit);//因按钮位置重合，点击退出对话框也同时点击了退出礼包确定按钮
	scheduleOnce(schedule_selector(MenuLayer::goExitLibao), 0.5f);
}

void MenuLayer::goExitLibao(float f)
{
	popOutDialog(PayType::pGameExit);
}

void MenuLayer::checkLogin()
{
	if (GameData::getInstance()->getIsLogin())
	{
		GameData::getInstance()->setIsLogin(false);
		int last = GameData::getInstance()->getLoginTime();
		int cur = getCurrentDays(0);
		int ret = cur - last;
		if (ret == 1)	//连续登陆
		{
			ADDCHILD_FUNC(LoginLayer)
		}
		else if (ret > 1)	//签到中断
		{
			GameData::getInstance()->setLoginDayNum(0);
			ADDCHILD_FUNC(LoginLayer)
		}
	}
}

void MenuLayer::musicOnOff(bool is)
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
