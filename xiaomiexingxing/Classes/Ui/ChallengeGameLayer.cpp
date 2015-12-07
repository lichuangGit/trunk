#include "ChallengeGameLayer.h"


ChallengeGameLayer::ChallengeGameLayer() :
m_starMatrix(nullptr),
m_levelMsg(nullptr),
m_targetScore(nullptr),
m_linkNum(nullptr),
m_starStatus(ChallengeGameLayer::Status_Activity),
m_isCongratulation(false)
{
	GameData::getInstance()->setGameMode(GameData::GameChallenge);
}


ChallengeGameLayer::~ChallengeGameLayer()
{
}

Scene *ChallengeGameLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = ChallengeGameLayer::create();

	if (layer == nullptr)
	{
		layer = ChallengeGameLayer::create();
	}

	if (layer)
	{
		scene->addChild(layer);
	}

	return scene;
}

bool ChallengeGameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	SpriteFrameCache::getInstance()->removeSpriteFrames();
	TextureCache::getInstance()->removeAllTextures();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("star.plist");
	TextureCache::getInstance()->addImage("star.png");
	TextureCache::getInstance()->addImage("popstar_bg.jpg");
	TextureCache::getInstance()->addImage("blue_bum.png");
	TextureCache::getInstance()->addImage("green_bum.png");
	TextureCache::getInstance()->addImage("orange_bum.png");
	TextureCache::getInstance()->addImage("purple_bum.png");
	TextureCache::getInstance()->addImage("red_bum.png");
	
	initUI();
	
	return true;
}

bool ChallengeGameLayer::onTouchBegan(Touch* touch, Event* event)
{
	stopNoTouchAndWarning();

	if (!isReceiveTouchEvent())
	{
		return false;
	}

	Vec2 p = touch->getLocation();

	if (m_starMatrix)
	{
		if (!m_starMatrix->onTouch(p))	//触摸无效区域
		{
		}
	}

	return true;
}

void ChallengeGameLayer::onTouchEnded(Touch *touch, Event *event)
{
	//特殊情况下，主动调用onTouchEnded函数，星星初始化掉落完毕或换色弹窗关闭后
	if (touch == nullptr && event == nullptr)
	{
		scheduleOnce(schedule_selector(ChallengeGameLayer::noTouchAndWarning), PropsWarningTime);
		return;
	}

	//非换色状态 即开始监控触摸
	if (getStarsStatus() != ChallengeGameLayer::StarStatus::Status_Over && getStarsStatus() != ChallengeGameLayer::StarStatus::Status_Activity)
	{
		scheduleOnce(schedule_selector(ChallengeGameLayer::noTouchAndWarning), PropsWarningTime);
	}
}

void ChallengeGameLayer::floatLevelWord()
{
	m_levelMsg = FloatWord::create(GameData::getInstance()->ChineseWord("guanqia")
		+ cocos2d::String::createWithFormat(": %d",
		1)->getCString(),
		50, Vec2(VISIBLE_SIZE.width, VISIBLE_SIZE.height * 0.55));

	this->addChild(m_levelMsg);

	m_levelMsg->floatIn(0.3f, CC_CALLBACK_0(ChallengeGameLayer::floatTargetScoreWord, this));

	Audio::getInstance()->playReadyGo();
}

void ChallengeGameLayer::floatTargetScoreWord()
{
	m_targetScore = FloatWord::create(GameData::getInstance()->ChineseWord("mubiao")
		+ cocos2d::String::createWithFormat(": %d", ChallengeScore)->getCString()
		+ GameData::getInstance()->ChineseWord("fen"), 50,
		Vec2(VISIBLE_SIZE.width, VISIBLE_SIZE.height * 0.45));

	this->addChild(m_targetScore);

	m_targetScore->floatIn(0.3f, CC_CALLBACK_0(ChallengeGameLayer::removeFloatWord, this));
}

void ChallengeGameLayer::removeFloatWord()
{
	m_levelMsg->floatOut(0.3f, nullptr);
	m_targetScore->floatOut(0.3f, CC_CALLBACK_0(ChallengeGameLayer::showStarMatrix, this));
}

void ChallengeGameLayer::showStarMatrix()
{
	m_starMatrix = ChallengeStarMatrix::create(this);
	this->addChild(m_starMatrix);

	m_isCongratulation = false;
}

void ChallengeGameLayer::refreshMenu()
{
	m_topMenu->refresh();
}

void ChallengeGameLayer::showLinkNum(int size)
{
	m_linkNum->stopAllActions();
	m_linkNum->setString(String::createWithFormat("%d", size)->getCString() + GameData::getInstance()->ChineseWord("lianji")
		+ String::createWithFormat("%d", size * size * 5)->getCString() + GameData::getInstance()->ChineseWord("fen"));
	m_linkNum->setVisible(true);
	auto delay = DelayTime::create(0.8f);
	auto call = CallFunc::create([&](){m_linkNum->setVisible(false); });
	m_linkNum->runAction(Sequence::create(delay, call, nullptr));
}

void ChallengeGameLayer::gotoNextLevel()
{
	GameData::getInstance()->setChallengeZuanshi(0);
	scheduleOnce(schedule_selector(ChallengeGameLayer::goLibao), 0.5f);
}

void ChallengeGameLayer::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_BACK:
		if (!isReceiveTouchEvent())
		{
			return;
		}

		stopNoTouchAndWarning();

		popOutDialog(NormalType::nGameSet);
		break;
	}
}

void ChallengeGameLayer::updateEveryScore(int score)
{
	m_topMenu->updateEveryScore(score);
}

void ChallengeGameLayer::startPassLevelDeal()
{
	if (m_isCongratulation)
	{
		return;
	}

	m_isCongratulation = true;

	congratulations();
	showCCParticleFireworksEffect(this);
}

void ChallengeGameLayer::refreshScoreAndLinkNum(int link)
{
	refreshMenu();
	showLinkNum(link);
}

void ChallengeGameLayer::floatLeftStarMsg(int leftNum)
{
	auto leftStarMsg = FloatWord::create(GameData::getInstance()->ChineseWord("shengyu")
		+ String::createWithFormat("%d", leftNum)->getCString() + GameData::getInstance()->ChineseWord("ge"), 50,
		Vec2(VISIBLE_SIZE.width, VISIBLE_SIZE.height * 0.55));
	this->addChild(leftStarMsg);

	int jiangLiScore = GameData::getInstance()->getJiangli(leftNum);
	auto scoreMsg = FloatWord::create(GameData::getInstance()->ChineseWord("jiangli")
		+ String::createWithFormat("%d", jiangLiScore)->getCString() + GameData::getInstance()->ChineseWord("fen"), 50,
		Vec2(VISIBLE_SIZE.width, VISIBLE_SIZE.height * 0.45));
	this->addChild(scoreMsg);

	leftStarMsg->floatInOut(0.5f, 1.0f, CC_CALLBACK_0(ChallengeGameLayer::gameOverToDealStar, this, jiangLiScore));
	scoreMsg->floatInOut(0.5f, 1.0f, nullptr);
}

void ChallengeGameLayer::gameOverToDealStar(int score)
{
	updateEveryScore(score);

	refreshMenu();

	m_starMatrix->startClearStar();
}

void ChallengeGameLayer::popOutDialog(NormalType type)
{
	StudioLayer *dialog = nullptr;

	if (type == NormalType::nGameSet)
	{
		dialog = SettingLayer::create();
	}
	else
	{
		dialog = GameDialogLayer::createNoraml(DialogType::NormalDialog, type, CC_CALLBACK_2(ChallengeGameLayer::normalDialogCallBack, this));
	}

	if (dialog)
	{
		this->addChild(dialog);
	}
}

void ChallengeGameLayer::popOutDialog(PayType type)
{
	auto dialog = GameDialogLayer::createPay(DialogType::PayDialog, type, CC_CALLBACK_3(ChallengeGameLayer::payDialogCallBack, this));
	if (dialog)
	{
		this->addChild(dialog);
	}
}

void ChallengeGameLayer::normalDialogCallBack(std::map<int, int> _map, NormalType type /* = nGameNone */)
{
	int len = _map.size(), i = 0;
	for (auto it : _map)
	{
		i++;
		updateGoodsNumber((GoodsType)it.first, it.second);
	}

	if (type == NormalType::nGamePassed)
	{
		gotoNextLevel();
	}
}

void ChallengeGameLayer::payDialogCallBack(int point, int result, std::map<int, int> _map)
{
	if (result == PayResult::Success)
	{
		if (point == PayPoint::Chaozhilibao99 || point == PayPoint::Chaozhilibao130)
		{
			for (auto it : _map)
			{
				updateGoodsNumber((GoodsType)it.first, it.second);
			}
		}
	}
	else if (result == PayResult::Cancel || result == PayResult::Failed)
	{
	}

	if (point == PayPoint::Chaozhilibao99 || point == PayPoint::Chaozhilibao130)
	{
		if (getStarsStatus() == ChallengeGameLayer::Status_Over)
		{
			Director::getInstance()->replaceScene(MenuLayer::scene());
		}
		else
		{
			scheduleOnce(schedule_selector(ChallengeGameLayer::noTouchAndWarning), PropsWarningTime);
		}	
	}
}

void ChallengeGameLayer::updateGoodsNumber(GoodsType type, int num)
{
	num = GameData::getInstance()->getGoodsNumber(type) + num;
	GameData::getInstance()->setGoodsNumber(type, num);
	switch (type)
	{
	case GoodsType::Zuanshi:
		m_topMenu->updateDiamondNumber(num);
		//num小于某个值时，可以给予警告，弹计费点
		break;
	}
}

SpriteBatchNode *ChallengeGameLayer::getBatchNode()
{
	return m_spBatchNode;
}

void ChallengeGameLayer::setStarsStatus(ChallengeGameLayer::StarStatus status)
{
	m_starStatus = status;
}

ChallengeGameLayer::StarStatus ChallengeGameLayer::getStarsStatus()
{
	return m_starStatus;
}

void ChallengeGameLayer::floatFailedMove()
{
	if (GameData::getInstance()->getCurScore() > GameData::getInstance()->getHistoryHighestScore())
	{
		GameData::getInstance()->setHistoryHighestScore(GameData::getInstance()->getCurScore());
	}
	
	GameData::getInstance()->setGoodsNumber(GoodsType::Zuanshi, GameData::getInstance()->getGoodsNumber(GoodsType::Zuanshi) - GameData::getInstance()->getChallengeZuanshi());
	GameData::getInstance()->setChallengeZuanshi(0);

	auto gameover = Sprite::createWithSpriteFrameName("gameover.png");
	gameover->setPosition(Vec2(VISIBLE_SIZE.width, VISIBLE_SIZE.height / 2));
	m_spBatchNode->addChild(gameover);

	auto move = MoveTo::create(0.5f, Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	auto delay = DelayTime::create(0.7f);
	auto move1 = MoveTo::create(0.5f, Vec2(-gameover->getContentSize().width / 2, VISIBLE_SIZE.height / 2));
	auto call = CallFunc::create([&](){Director::getInstance()->replaceScene(MenuLayer::scene()); });
	gameover->runAction(Sequence::create(move, delay, move1, call, nullptr));
}

int ChallengeGameLayer::getCurScore()
{
	return m_topMenu->getCurScore();
}

void ChallengeGameLayer::registerListener()
{
	auto keyboardlistener = EventListenerKeyboard::create();
	keyboardlistener->onKeyReleased = CC_CALLBACK_2(ChallengeGameLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardlistener, this);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ChallengeGameLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(ChallengeGameLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void ChallengeGameLayer::initUI()
{
	this->registerListener();

	auto bgSp = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("popstar_bg.jpg"));
	bgSp->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	bgSp->setScaleY(SCALEFACTOR);
	this->addChild(bgSp);

	m_spBatchNode = SpriteBatchNode::create("game.png");
	this->addChild(m_spBatchNode);

	m_topMenu = ChallengeTopMenu::create(this);

	m_linkNum = Label::create();
	m_linkNum->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height * 0.78));
	m_linkNum->setSystemFontSize(25);
	m_linkNum->setVisible(false);
	this->addChild(m_linkNum);

	auto setSp = Sprite::createWithSpriteFrameName("menu_set.png");
	auto setItem = MenuItemSprite::create(setSp, setSp, CC_CALLBACK_0(ChallengeGameLayer::onMenuItemCallBack, this, SetMenu));
	setItem->setPosition(Vec2(setSp->getContentSize().width * 0.6, VISIBLE_SIZE.height - setSp->getContentSize().height * 0.6));

	auto add = Sprite::createWithSpriteFrameName("addStar.png");
	auto addItem = MenuItemSprite::create(add, add, CC_CALLBACK_0(ChallengeGameLayer::onMenuItemCallBack, this, AddMenu));
	addItem->setPosition(Vec2(VISIBLE_SIZE.width - add->getContentSize().width * 0.6, m_topMenu->m_moneyStar->getPositionY()));

	auto menu = Menu::create(setItem, addItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	this->floatLevelWord();
}

void ChallengeGameLayer::congratulations()
{
	auto uplev = Sprite::createWithSpriteFrameName("uplev.png");
	uplev->setPosition(Vec2(VISIBLE_SIZE.width - uplev->getContentSize().width / 2, VISIBLE_SIZE.height*0.75));
	m_spBatchNode->addChild(uplev);
	auto blink = Blink::create(3, 6);
	auto funcall = CallFuncN::create([&](Node *pSender){pSender->removeFromParentAndCleanup(true); });
	auto seq = Sequence::create(blink, funcall, NULL);
	uplev->runAction(seq);
	Audio::getInstance()->playWin();
}

void ChallengeGameLayer::onMenuItemCallBack(int type)
{
	stopNoTouchAndWarning();

	if (!isReceiveTouchEvent())
	{
		return;
	}

	if (type == SetMenu)	//设置
	{
		popOutDialog(NormalType::nGameSet);
	}
	else if (type == AddMenu)	//购买钻石
	{
		popOutDialog(cocos2d::random() % 100 < 50 ? PayType::pGameLibao99 : PayType::pGameLibao130);
	}
}

bool ChallengeGameLayer::isReceiveTouchEvent()
{
	if (m_starStatus == ChallengeGameLayer::StarStatus::Status_Ready || m_starStatus == ChallengeGameLayer::StarStatus::Status_Over || m_starStatus == ChallengeGameLayer::StarStatus::Status_Activity)
	{
		return false;
	}

	return true;
}

void ChallengeGameLayer::noTouchAndWarning(float f)
{
	if (m_starMatrix)
	{
		m_starMatrix->noTouchAndWarning();
	}
}

void ChallengeGameLayer::stopNoTouchAndWarning()
{
	if (m_starMatrix)
	{
		m_starMatrix->stopStarsAction();
	}

	unschedule(schedule_selector(ChallengeGameLayer::noTouchAndWarning));
}

void ChallengeGameLayer::goLibao(float f)
{
	popOutDialog(cocos2d::random() % 100 < 50 ? PayType::pGameLibao99 : PayType::pGameLibao130);
}
