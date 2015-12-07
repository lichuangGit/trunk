#include "GameLayer.h"
#include "MenuLayer.h"

GameLayer::GameLayer():
m_curTouchStatus(TouchStatus::Touch_Normal),
m_previousTouchStatus(TouchStatus::Touch_Normal),
m_starMatrix(nullptr),
m_levelMsg(nullptr),
m_targetScore(nullptr),
m_linkNum(nullptr),
m_starStatus(GameLayer::Status_Activity),
m_isPropUse(false),
m_isCongratulation(false),
m_pSpLevel(nullptr),
m_pSpProg(nullptr),
m_pSpLvAdd(nullptr),
m_pSpLvScore(nullptr),
m_pSpZengjia(nullptr),
m_pSpChenghao(nullptr),
m_iLvCount(0)
{
	m_enterTime = getCurrentDays(2);

	GameData::getInstance()->setGameMode(GameData::GameNormal);
}

GameLayer::~GameLayer()
{
	int tm = getCurrentDays(2);
	GameData::getInstance()->setGameDuration(GameData::getInstance()->getGameDuration() + (tm - m_enterTime) / 60.0f);
}

Scene *GameLayer::createScene()
{
	Audio::getInstance()->playBGM();

	auto scene = Scene::create();

	auto layer = GameLayer::create();

	if (layer == nullptr)
	{
		layer = GameLayer::create();
	}

	if (layer)
	{
		scene->addChild(layer);
	}

	return scene;
}

bool GameLayer::init() 
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

bool GameLayer::onTouchBegan(Touch* touch, Event* event)
{
	stopNoTouchAndWarning();

	if (!isReceiveTouchEvent())
	{
		return false;
	}

	//touch事件处理时，不允许点击道具，处理完方可点击，避免引起破碎过程中和道具使用产生的问题
	setIsPropUse(true);

	Vec2 p = touch->getLocation();

	if (m_starMatrix)
	{
		if (!m_starMatrix->onTouch(p))	//触摸无效区域
		{
			setIsPropUse(false);
		}
	}

	return true;
}

void GameLayer::onTouchEnded(Touch *touch, Event *event)
{
	//特殊情况下，主动调用onTouchEnded函数，星星初始化掉落完毕或换色弹窗关闭后
	if (touch == nullptr && event == nullptr)
	{
		scheduleOnce(schedule_selector(GameLayer::noTouchAndWarning), PropsWarningTime);
		return;
	}

	//非换色状态 即开始监控触摸
	if (getStarsStatus() != StarStatus::Status_Over && getStarsStatus() != StarStatus::Status_Activity)
	{
		scheduleOnce(schedule_selector(GameLayer::noTouchAndWarning), PropsWarningTime);
	}
}

void GameLayer::floatLevelWord()
{
	m_levelMsg = FloatWord::create(GameData::getInstance()->ChineseWord("guanqia")
		+ cocos2d::String::createWithFormat(": %d",
		GameData::getInstance()->getNextLevel())->getCString(),
		50, Vec2(VISIBLE_SIZE.width, VISIBLE_SIZE.height * 0.55));

	this->addChild(m_levelMsg);

	m_levelMsg->floatIn(0.3f, CC_CALLBACK_0(GameLayer::floatTargetScoreWord, this));

	Audio::getInstance()->playReadyGo();
}

void GameLayer::floatTargetScoreWord()
{
	m_targetScore = FloatWord::create(GameData::getInstance()->ChineseWord("mubiao")
		+ cocos2d::String::createWithFormat(": %d", GameData::getInstance()->getNextScore())->getCString()
		+ GameData::getInstance()->ChineseWord("fen"), 50,
		Vec2(VISIBLE_SIZE.width, VISIBLE_SIZE.height * 0.45));

	this->addChild(m_targetScore);

	m_targetScore->floatIn(0.3f, CC_CALLBACK_0(GameLayer::removeFloatWord, this));
}

void GameLayer::removeFloatWord()
{
	m_levelMsg->floatOut(0.3f, nullptr);
	m_targetScore->floatOut(0.3f, CC_CALLBACK_0(GameLayer::showStarMatrix, this));
}

void GameLayer::showStarMatrix()
{
	UmengUpload::startLevel(String::createWithFormat("level_%d", GameData::getInstance()->getNextLevel())->getCString());

	m_starMatrix = StarMatrix::create(this);
	this->addChild(m_starMatrix);

	m_isCongratulation = false;
	m_isPropUse = false;
}

void GameLayer::refreshMenu()
{
	m_topMenu->refresh();
}

void GameLayer::showLinkNum(int size)
{
	m_linkNum->stopAllActions();
	m_linkNum->setString(String::createWithFormat("%d", size)->getCString() + GameData::getInstance()->ChineseWord("lianji")
		+ String::createWithFormat("%d", size * size * 5)->getCString() + GameData::getInstance()->ChineseWord("fen"));
	m_linkNum->setVisible(true);
	auto delay = DelayTime::create(0.8f);
	auto call = CallFunc::create([&](){m_linkNum->setVisible(false); });
	m_linkNum->runAction(Sequence::create(delay, call, nullptr));
}

void GameLayer::gotoNextLevel()
{
	GameData::getInstance()->saveLastLevel();
	GameData::getInstance()->saveLastLevelSocre(GameData::getInstance()->getCurScore());
	GameData::getInstance()->setPreviousScore(GameData::getInstance()->getCurScore());
	if (GameData::getInstance()->getCurScore() > GameData::getInstance()->getHistoryHighestScore())
	{
		GameData::getInstance()->setHistoryHighestScore(GameData::getInstance()->getCurScore());
	}
	GameData::getInstance()->setCurLevel(GameData::getInstance()->getCurLevel() + 1);
	
	updateEveryScore(0);

	refreshMenu();

	floatLevelWord();
}

void GameLayer::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_BACK:
		if (!isReceiveTouchEvent() || m_isPropUse)
		{
			return;
		}

		stopNoTouchAndWarning();

		popOutDialog(NormalType::nGameSet);
		break;
	}
}

void GameLayer::updateEveryScore(int score)
{
	m_topMenu->updateEveryScore(score);
}

void GameLayer::startPassLevelDeal()
{
	if (m_isCongratulation)
	{
		return;
	}

	m_isCongratulation = true;

	congratulations();
	showCCParticleFireworksEffect(this);
}

void GameLayer::refreshScoreAndLinkNum(int link)
{
	refreshMenu();
	showLinkNum(link);
	updateLvAndExpereience(link);
	showLvToAddScore(link);
}

void GameLayer::floatLeftStarMsg(int leftNum)
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

	leftStarMsg->floatInOut(0.5f, 1.0f, CC_CALLBACK_0(GameLayer::gameOverToDealStar, this, jiangLiScore));
	scoreMsg->floatInOut(0.5f, 1.0f, nullptr);
}

void GameLayer::gameOverToDealStar(int score)
{
	updateEveryScore(score);

	refreshMenu();
	
	m_starMatrix->startClearStar();
}

void GameLayer::popOutDialog(NormalType type)
{
	StudioLayer *dialog = nullptr;

	if (type == NormalType::nGameSet)
	{
		dialog = SettingLayer::create();
	}
	else
	{
		dialog = GameDialogLayer::createNoraml(DialogType::NormalDialog, type, CC_CALLBACK_2(GameLayer::normalDialogCallBack, this));
	}

	if (dialog)
	{
		this->addChild(dialog);
	}
}

void GameLayer::popOutDialog(PayType type)
{
	auto dialog = GameDialogLayer::createPay(DialogType::PayDialog, type, CC_CALLBACK_3(GameLayer::payDialogCallBack, this));
	if (dialog)
	{
		this->addChild(dialog);
	}
}

void GameLayer::normalDialogCallBack(std::map<int, int> _map, NormalType type /* = nGameNone */)
{
	if (_map.empty())
	{
		if (type == NormalType::nGamePassed)
		{
			gotoNextLevel();
		}
	}
	else
	{
		int len = _map.size(), i = 0;
		for (auto it : _map)
		{
			i++;
			createGoodsAndMove((GoodsType)it.first, it.second, len == i);
		}
	}
}

void GameLayer::payDialogCallBack(int point, int result, std::map<int, int> _map)
{
	if (result == PayResult::Success)
	{
		if (point == PayPoint::Zhijietongguan)
		{
			//直接通关在原来分数的基础上，赠送距过关的分数差值
			updateEveryScore(GameData::getInstance()->getNextScore() - GameData::getInstance()->getInstance()->getCurScore());
		}
		if (point == PayPoint::Zhijietongguan || point == PayPoint::Tongguanbomb3 || point == PayPoint::Tongguanbomb6 || point == PayPoint::Tongguanbomb9 || 
			point == PayPoint::Tongguantsx3 || point == PayPoint::Tongguantsx6 || point == PayPoint::Tongguantsx9)//这些计费点成功需跳转下一关
		{
			//需要执行进入下一关的则可直接运行下面代码
			if (!_map.empty())
			{
				normalDialogCallBack(_map);
			}
		}
		else if (point == PayPoint::Chaozhilibao99 || point == PayPoint::Chaozhilibao130)
		{
			//只刷新物品数量的执行下面代码
			for (auto it : _map)
			{
				createGoodsAndMove((GoodsType)it.first, it.second);
			}
		}
	}
	else if (result == PayResult::Cancel || result == PayResult::Failed)
	{
		if (point == PayPoint::Tongguanbomb3 || point == PayPoint::Tongguanbomb6 || point == PayPoint::Tongguanbomb9 || 
			point == PayPoint::Tongguantsx3 || point == PayPoint::Tongguantsx6 || point == PayPoint::Tongguantsx9)
		{
			gotoNextLevel();
		}
		else if (point == PayPoint::Zhijietongguan)
		{
			floatFailedMove();
		}
	}

	if (point == PayPoint::Chaozhilibao99 || point == PayPoint::Chaozhilibao130)
	{
		scheduleOnce(schedule_selector(GameLayer::noTouchAndWarning), PropsWarningTime);
	}
}

void GameLayer::createGoodsAndMove(GoodsType type, int num, bool isNextLevel /* = false */)
{
	Vec2 pos;
	Sprite *sp = nullptr;

	if (type == GoodsType::Bomb)
	{
		sp = Sprite::createWithSpriteFrameName("bomb.png");
		pos = m_curBombPos;
	}
	else if (type == GoodsType::Tongsexiao)
	{
		sp = Sprite::createWithSpriteFrameName("tongsexiao.png");
		pos = m_curTongsexiaoPos;
	}
	else if (type == GoodsType::Huanse)
	{
		sp = Sprite::createWithSpriteFrameName("huanse.png");
		pos = m_curHuansePos;
	}
	else if (type == GoodsType::Chexiao)
	{
		sp = Sprite::createWithSpriteFrameName("chexiao.png");
		pos = m_curChexiaoPos;
	}
	else if (type == GoodsType::Shuaxin)
	{
		sp = Sprite::createWithSpriteFrameName("refurbish.png");
		pos = m_curShuaxinPos;
	}
	else if (type == GoodsType::Zuanshi)
	{
		sp = Sprite::createWithSpriteFrameName("zuanshi.png");
		sp->setScale(1.2f);
		pos = m_curZuanshiPos;
	}
	else
	{
		sp = Sprite::createWithSpriteFrameName("zuanshi.png");
		sp->setScale(1.2f);
		pos = m_curZuanshiPos;
	}

	if (pos == Vec2::ZERO)
	{
		return;
	}

	sp->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	this->addChild(sp);
	auto move = MoveTo::create(0.3f, pos);
	auto call = CallFuncN::create(CC_CALLBACK_1(GameLayer::updateGoodsNumberCallback, this, type, num));
	auto delay = DelayTime::create(0.2f);
	auto jump = JumpBy::create(0.4f, Vec2(0, 15), 25.0f, 2);
	if (isNextLevel)
	{
		auto callNextLevel = CallFunc::create(CC_CALLBACK_0(GameLayer::gotoNextLevel, this));
		sp->runAction(Sequence::create(EaseSineOut::create(move), jump, jump->reverse(), call, callNextLevel, nullptr));
	}
	else
	{
		sp->runAction(Sequence::create(EaseSineOut::create(move), jump, jump->reverse(), call, nullptr));
	}	
}

void GameLayer::updateGoodsNumberCallback(Node *pSender, GoodsType type, int num)
{
	if (pSender)
	{
		pSender->removeFromParentAndCleanup(true);
	}
	updateGoodsNumber(type, num);
}

void GameLayer::updateGoodsNumber(GoodsType type, int num)
{
	num = GameData::getInstance()->getGoodsNumber(type) + num;
	GameData::getInstance()->setGoodsNumber(type, num);
	switch (type)
	{
	case GoodsType::Bomb:
		m_bombProp->updatePropsNumber(num);
		break;
	case GoodsType::Tongsexiao:
		m_tongsexiaoProp->updatePropsNumber(num);
		break;
	case GoodsType::Huanse:
		m_huanseProp->updatePropsNumber(num);
		break;
	case GoodsType::Chexiao:
		m_chexiaoProp->updatePropsNumber(num);
		break;
	case GoodsType::Shuaxin:
		m_shuaxinProp->updatePropsNumber(num);
		break;
	case GoodsType::Zuanshi:
		m_topMenu->updateDiamondNumber(num);
		//num小于某个值时，可以给予警告，弹计费点
		break;
	}
}

SpriteBatchNode *GameLayer::getBatchNode()
{
	return m_spBatchNode;
}

void GameLayer::setStarsStatus(StarStatus status)
{
	m_starStatus = status;
}

GameLayer::StarStatus GameLayer::getStarsStatus()
{
	return m_starStatus;
}

void GameLayer::updateTouchStatus(TouchStatus status)
{
	//旧状态
	if (m_curTouchStatus != TouchStatus::Touch_Normal)
	{
		getPropByTouchStatus(m_curTouchStatus)->stopPropAction();
	}

	m_previousTouchStatus = m_curTouchStatus;

	//新状态
	if (m_curTouchStatus != status)
	{
		setCurTouchStatus(status);
		if (status != TouchStatus::Touch_Normal)//道具状态
		{
			getPropByTouchStatus(status)->goPropAction();
		}
	}
	else
	{
		if (status != TouchStatus::Touch_Normal)//道具状态恢复为正常状态
		{
			setCurTouchStatus(TouchStatus::Touch_Normal);//此处只有第二次点击同样道具才进来
		}
	}
}

void GameLayer::updateGoodsNumberByTouchStatus()
{
	if (m_previousTouchStatus != TouchStatus::Touch_Normal && m_previousTouchStatus != m_curTouchStatus)//确保此函数只会运行使用道具消耗物品处理，避免其他地方误调用导致的问题
	{
		GoodsType type = (GoodsType)getGoodsByStatus(m_previousTouchStatus);
		int num = GameData::getInstance()->getGoodsNumber(type);
		if (num > 0)
		{
			num = -1;
		}
		else
		{
			num = -getGoodsByStatus(m_previousTouchStatus, 2);
		}

		string name = "";

		switch (type)
		{
		case Bomb:
			name = Umeng_Id_Zhandan;
			break;
		case Tongsexiao:
			name = Umeng_Id_Tongsexiao;
			break;
		case Huanse:
			name = Umeng_Id_Huanse;
			break;
		case Chexiao:
			name = Umeng_Id_Chaoxiao;
			break;
		case Shuaxin:
			name = Umeng_Id_Shuaxin;
			break;
		}

		map<string, string> _map;
		if (num == -1)
		{
			_map["way"] = "prop";
		}
		else
		{
			_map["way"] = "zuanshi";
		}

		_map["playTime(m)"] = GameData::getInstance()->getGameDurationGPD();

		UmengUpload::event(name, &_map);

		updateGoodsNumber(num == -1 ? type : GoodsType::Zuanshi, num);
	}
}

void GameLayer::saveStarAtExitGame()
{
	if (m_starMatrix)
	{
		m_starMatrix->saveStarAtExitGame();
	}
}

void GameLayer::registerListener()
{
	auto keyboardlistener = EventListenerKeyboard::create();
	keyboardlistener->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardlistener, this);
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameLayer::initUI()
{
	this->registerListener();

	auto bgSp = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("popstar_bg.jpg"));
	bgSp->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	bgSp->setScaleY(SCALEFACTOR);
	this->addChild(bgSp);

	m_spBatchNode = SpriteBatchNode::create("game.png");
	this->addChild(m_spBatchNode);

	m_topMenu = TopMenu::create(this);

	m_linkNum = Label::create();
	m_linkNum->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height * 0.78));
	m_linkNum->setSystemFontSize(25);
	m_linkNum->setVisible(false);
	this->addChild(m_linkNum);

	m_bombProp = Props::create(GoodsType::Bomb, this, CC_CALLBACK_0(GameLayer::onMenuItemCallBack, this, GoodsType::Bomb));
	m_curBombPos = m_bombProp->getPosition();

	m_tongsexiaoProp = Props::create(GoodsType::Tongsexiao, this, CC_CALLBACK_0(GameLayer::onMenuItemCallBack, this, GoodsType::Tongsexiao));
	m_curTongsexiaoPos = m_tongsexiaoProp->getPosition();

	m_huanseProp = Props::create(GoodsType::Huanse, this, CC_CALLBACK_0(GameLayer::onMenuItemCallBack, this, GoodsType::Huanse));
	m_curHuansePos = m_huanseProp->getPosition();

	m_chexiaoProp = Props::create(GoodsType::Chexiao, this, CC_CALLBACK_0(GameLayer::onMenuItemCallBack, this, GoodsType::Chexiao));
	m_curChexiaoPos = m_chexiaoProp->getPosition();

	m_shuaxinProp = Props::create(GoodsType::Shuaxin, this, CC_CALLBACK_0(GameLayer::onMenuItemCallBack, this, GoodsType::Shuaxin));
	m_curShuaxinPos = m_shuaxinProp->getPosition();

	auto setSp = Sprite::createWithSpriteFrameName("menu_set.png");
	auto setItem = MenuItemSprite::create(setSp, setSp, CC_CALLBACK_0(GameLayer::onMenuItemCallBack, this, SetMenu));
	setItem->setPosition(Vec2(setSp->getContentSize().width * 0.6, VISIBLE_SIZE.height - setSp->getContentSize().height * 0.6));

	auto add = Sprite::createWithSpriteFrameName("addStar.png");
	auto addItem = MenuItemSprite::create(add, add, CC_CALLBACK_0(GameLayer::onMenuItemCallBack, this,AddMenu));
	addItem->setPosition(Vec2(VISIBLE_SIZE.width - add->getContentSize().width * 0.6, m_topMenu->m_moneyStar->getPositionY()));

	auto menu = Menu::create(setItem, m_bombProp, m_tongsexiaoProp, m_huanseProp, m_chexiaoProp, m_shuaxinProp, addItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	//等级加分
	auto spLv = Sprite::createWithSpriteFrameName("level.png");
	spLv->setPosition(Vec2(spLv->getContentSize().width * 0.6f, setItem->getPositionY() - setItem->getContentSize().height * 1.3f));
	m_spBatchNode->addChild(spLv);

	m_pSpLevel = NumSprite::create(GameData::getInstance()->getPlayerLv(), NumberType::GameNumberCurScore);
	m_pSpLevel->setPosition(Vec2(spLv->getContentSize().width * 1.5f, spLv->getPositionY()));
	m_spBatchNode->addChild(m_pSpLevel);

	auto jiantou = Sprite::createWithSpriteFrameName("jiantou.png");
	jiantou->setPosition(Vec2(spLv->getContentSize().width * 2.3f, spLv->getPositionY()));
	m_spBatchNode->addChild(jiantou);

	auto progSp = Sprite::createWithSpriteFrameName("progbg.png");
	progSp->setPosition(Vec2(spLv->getContentSize().width * 0.1f, spLv->getPositionY() - spLv->getContentSize().height * 1.5f));
	progSp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	m_spBatchNode->addChild(progSp);

	m_pSpProg = Sprite::createWithSpriteFrameName("prog.png");
	m_pSpProg->setPosition(progSp->getPosition());
	m_pSpProg->setScaleX(GameData::getInstance()->getExperienceValue() / GameData::getInstance()->getExperienceByLv());
	m_pSpProg->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	m_spBatchNode->addChild(m_pSpProg);

	m_pSpZengjia = Sprite::createWithSpriteFrameName("zengjia.png");
	m_pSpZengjia->setPosition(Vec2(spLv->getContentSize().width * 0.6f, m_pSpProg->getPositionY() - m_pSpProg->getContentSize().height * 1.5f));
	m_spBatchNode->addChild(m_pSpZengjia);
	//m_pSpZengjia->setVisible(false);

	m_pSpLvAdd = NumSprite::create(GameData::getInstance()->getPlayerLv(), NumberType::GameNumberCurScore);
	m_pSpLvAdd->setPosition(Vec2(m_pSpZengjia->getPositionX() + m_pSpZengjia->getContentSize().width, m_pSpZengjia->getPositionY()));
	m_spBatchNode->addChild(m_pSpLvAdd);
	//m_pSpLvAdd->setVisible(false);

	m_pSpChenghao = Sprite::createWithSpriteFrameName("chenghao.png");
	m_pSpChenghao->setPosition(Vec2(m_pSpZengjia->getPositionX() + m_pSpZengjia->getContentSize().width * 2.0f, m_pSpZengjia->getPositionY()));
	m_spBatchNode->addChild(m_pSpChenghao);
	//m_pSpChenghao->setVisible(false);

	m_pSpLvScore = NumSprite::create(0, NumberType::GameNumberCurScore);
	m_pSpLvScore->setPosition(Vec2(m_pSpChenghao->getPositionX() + m_pSpChenghao->getContentSize().width, m_pSpZengjia->getPositionY()));
	m_spBatchNode->addChild(m_pSpLvScore);
	//m_pSpLvScore->setVisible(false);

	this->floatLevelWord();
}

void GameLayer::congratulations()
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

void GameLayer::floatFailedMove()
{
	GameData::getInstance()->setIsGameOver(true);
	if (GameData::getInstance()->getCurScore() > GameData::getInstance()->getHistoryHighestScore())
	{
		GameData::getInstance()->setHistoryHighestScore(GameData::getInstance()->getCurScore());
	}

	auto gameover = Sprite::createWithSpriteFrameName("gameover.png");
	gameover->setPosition(Vec2(VISIBLE_SIZE.width, VISIBLE_SIZE.height / 2));
	m_spBatchNode->addChild(gameover);

	auto move = MoveTo::create(0.5f, Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	auto delay = DelayTime::create(0.7f);
	auto move1 = MoveTo::create(0.5f, Vec2(-gameover->getContentSize().width / 2, VISIBLE_SIZE.height / 2));
	auto call = CallFunc::create([&](){Director::getInstance()->replaceScene(MenuLayer::scene());});
	gameover->runAction(Sequence::create(move, delay, move1, call, nullptr));
}

void GameLayer::onMenuItemCallBack(int type)
{
	stopNoTouchAndWarning();

	if (!isReceiveTouchEvent())
	{
		return;
	}

	if (m_isPropUse && type != SetMenu && type != AddMenu)
	{
		return;
	}

	if (type == GoodsType::Bomb)
	{
		startDealWithBomb();
	}
	else if (type == GoodsType::Tongsexiao)
	{
		startDealWithTongsexiao();
	}
	else if (type == GoodsType::Huanse)
	{
		startDealWithHuanse();
	}
	else if (type == GoodsType::Chexiao)
	{
		startDealWithChexiao();
	}
	else if (type == GoodsType::Shuaxin)
	{
		startDealWithShuaxin();
	}
	else if (type == SetMenu)	//设置
	{
		popOutDialog(NormalType::nGameSet);
	}
	else if (type == AddMenu)	//购买钻石
	{
		/*map<string, string> _map;
		_map["position"] = "game";
		UmengUpload::event(Umeng_Id_Chaozhilibao, &_map);
		popOutDialog(cocos2d::random() % 100 < 50 ? PayType::pGameLibao99 : PayType::pGameLibao130);*/
		goLibao("game");
	}
}

void GameLayer::startDealWithBomb()
{
	//需点击炸弹 在点击一颗星星
	startDealWithProp(GoodsType::Bomb, TouchStatus::Touch_Bomb, Prop_Bomb_Money);
}

void GameLayer::startDealWithTongsexiao()
{
	//需点击同色消 在点击一颗星星
	startDealWithProp(GoodsType::Tongsexiao, TouchStatus::Touch_Tongsexiao, Prop_Tongsexiao_Money);
}

void GameLayer::startDealWithHuanse()
{
	//需点击换色 在点击一颗星星
	startDealWithProp(GoodsType::Huanse, TouchStatus::Touch_Huanse, Prop_Huanse_Money);
}

void GameLayer::startDealWithProp(GoodsType type, TouchStatus status, int money)
{
	if (GameData::getInstance()->getGoodsNumber(type) > 0 ||
		GameData::getInstance()->getGoodsNumber(GoodsType::Zuanshi) > money)
	{
		updateTouchStatus(status);
		scheduleOnce(schedule_selector(GameLayer::noTouchAndWarning), PropsWarningTime);
	}
	else//若钻石不足
	{
		string name = "";
		switch (type)
		{
		case Bomb:
			name = "zhandan";
			break;
		case Tongsexiao:
			name = "tongsexiao";
			break;
		case Huanse:
			name = "huanse";
			break;
		}
		goLibao(name);
		//popOutDialog(cocos2d::random() % 100 < 50 ? PayType::pGameLibao99 : PayType::pGameLibao130);
	}
}

void GameLayer::startDealWithChexiao()
{
	if (GameData::getInstance()->getGoodsNumber(GoodsType::Chexiao) > 0 ||
		GameData::getInstance()->getGoodsNumber(GoodsType::Zuanshi) > Prop_Chexiao_Money)
	{
		setStarsStatus(StarStatus::Status_Activity);
		updateTouchStatus(TouchStatus::Touch_Chexiao);

		setIsPropUse(true);
		
		bool is = false;
		
		if (m_starMatrix)
		{
			is = m_starMatrix->restorePreviousStars();
		}
		
		if (is)//避免误扣钻石
		{
			scheduleOnce(schedule_selector(GameLayer::afterChexiaoAndShuaxinDeal), 0.4f);
		}
		else
		{
			setIsPropUse(false);
			updateTouchStatus(GameLayer::Touch_Normal);
			setStarsStatus(StarStatus::Status_NoActivity);
			//暂时弹计费框，可改为提示玩家
			goLibao("chexiao");
			//popOutDialog(cocos2d::random() % 100 < 50 ? PayType::pGameLibao99 : PayType::pGameLibao130);
		}
	}
	else//若钻石不足
	{
		goLibao("chexiao");
		//popOutDialog(cocos2d::random() % 100 < 50 ? PayType::pGameLibao99 : PayType::pGameLibao130);
	}
}

void GameLayer::startDealWithShuaxin()
{
	if (GameData::getInstance()->getGoodsNumber(GoodsType::Shuaxin) > 0 ||
		GameData::getInstance()->getGoodsNumber(GoodsType::Zuanshi) > Prop_Shuaxin_Money)
	{
		setStarsStatus(StarStatus::Status_Activity);
		updateTouchStatus(TouchStatus::Touch_Shuanxin);
		
		setIsPropUse(true);

		if (m_starMatrix)
		{
			m_starMatrix->handlerRefurbish();
		}

		scheduleOnce(schedule_selector(GameLayer::afterChexiaoAndShuaxinDeal), 0.4f);
	}
	else//若钻石不足
	{
		goLibao("shuaxin");
		//popOutDialog(cocos2d::random() % 100 < 50 ? PayType::pGameLibao99 : PayType::pGameLibao130);
	}
}

void GameLayer::afterChexiaoAndShuaxinDeal(float f)
{
	updateTouchStatus(GameLayer::Touch_Normal);
	setIsPropUse(false);
	updateGoodsNumberByTouchStatus();
	setStarsStatus(StarStatus::Status_NoActivity);
	scheduleOnce(schedule_selector(GameLayer::noTouchAndWarning), PropsWarningTime);
}

Props *GameLayer::getPropByTouchStatus(TouchStatus status)
{
	switch (status)
	{
	case GameLayer::Touch_Bomb:
		return m_bombProp;
	case GameLayer::Touch_Tongsexiao:
		return m_tongsexiaoProp;
	case GameLayer::Touch_Huanse:
		return m_huanseProp;
	case GameLayer::Touch_Chexiao:
		return m_chexiaoProp;
	case GameLayer::Touch_Shuanxin:
		return m_shuaxinProp;
	}

	return nullptr;
}

int GameLayer::getGoodsByStatus(TouchStatus status, int type /* = 1 */)
{
	if (type == 1)
	{
		switch (status)
		{
		case GameLayer::Touch_Bomb:
			return GoodsType::Bomb;
		case GameLayer::Touch_Tongsexiao:
			return GoodsType::Tongsexiao;
		case GameLayer::Touch_Huanse:
			return GoodsType::Huanse;
		case GameLayer::Touch_Chexiao:
			return GoodsType::Chexiao;
		case GameLayer::Touch_Shuanxin:
			return GoodsType::Shuaxin;
		}
	}
	else
	{
		switch (status)
		{
		case GameLayer::Touch_Bomb:
			return Prop_Bomb_Money;
		case GameLayer::Touch_Tongsexiao:
			return Prop_Tongsexiao_Money;
		case GameLayer::Touch_Huanse:
			return Prop_Huanse_Money;
		case GameLayer::Touch_Chexiao:
			return Prop_Chexiao_Money;
		case GameLayer::Touch_Shuanxin:
			return Prop_Shuaxin_Money;
		}
	}

	return -1;
}

bool GameLayer::isReceiveTouchEvent()
{
	if (m_starStatus == StarStatus::Status_Ready || m_starStatus == StarStatus::Status_Over || m_starStatus == StarStatus::Status_Activity)
	{
		return false;
	}

	return true;
}

void GameLayer::noTouchAndWarning(float f)
{
	if (m_starMatrix)
	{
		m_starMatrix->noTouchAndWarning();
	}
}

void GameLayer::stopNoTouchAndWarning()
{
	//停止触摸提示
	if (m_starMatrix)
	{
		m_starMatrix->stopStarsAction();
	}

	unschedule(schedule_selector(GameLayer::noTouchAndWarning));
}

void GameLayer::goLibao(string name)
{
	map<string, string> _map;
	_map["position"] = name;
	UmengUpload::event(Umeng_Id_Chaozhilibao, &_map);
	popOutDialog(cocos2d::random() % 100 < 50 ? PayType::pGameLibao99 : PayType::pGameLibao130);
}

void GameLayer::updateLvAndExpereience(int leftStar)
{
	//先这样处理，消除一个星星，增加10个经验值
	float value = GameData::getInstance()->getExperienceValue() + leftStar * 20;
	float need = GameData::getInstance()->getExperienceByLv();
	if (value > need)
	{
		value = need;
	}
	GameData::getInstance()->setExperienceValue(value);
	m_pSpProg->setScaleX(value / need);

	if (value == need)
	{
		congratulationsUpgrade();
		scheduleOnce(schedule_selector(GameLayer::afterUpate), 0.4f);
	}
}

void GameLayer::congratulationsUpgrade()
{
	auto label = Label::create();
	label->setString("Congratulations to upgrade！");
	label->setPosition(m_linkNum->getPosition());
	this->addChild(label);
	label->runAction(Sequence::create(Blink::create(0.9f, 3), CallFuncN::create([&](Node*pSender){pSender->removeFromParentAndCleanup(true); }), nullptr));
}

void GameLayer::afterUpate(float f)
{
	GameData::getInstance()->setPlayerLv(GameData::getInstance()->getPlayerLv() + 1);
	GameData::getInstance()->setExperienceValue(0.0f);

	m_pSpProg->setScaleX(0.0f);
	m_pSpLevel->setValue(GameData::getInstance()->getPlayerLv());
}

void GameLayer::showLvToAddScore(int leftStar)
{
	/*if (!m_iLvCount)
	{
		m_pSpZengjia->setVisible(true);
		m_pSpLvAdd->setVisible(true);
		m_pSpChenghao->setVisible(true);
		m_pSpLvScore->setVisible(true);
	}*/
	
	m_iLvCount++;

	m_pSpLvAdd->setValue(GameData::getInstance()->getPlayerLv());
	m_pSpLvScore->setValue(leftStar);

	for (int i = 0; i < leftStar; i++)
	{
		auto sp = NumSprite::create(GameData::getInstance()->getPlayerLv(), NumberType::GameNumberCurScore);
		sp->setPosition(m_pSpLvAdd->getPosition());
		m_spBatchNode->addChild(sp);
		auto delay = DelayTime::create(i * 0.1f + 0.5f);
		auto move = MoveTo::create(0.4f, m_curScorePos);
		auto call = CallFuncN::create(CC_CALLBACK_1(GameLayer::dealLvAddScoreAfter, this, GameData::getInstance()->getPlayerLv()));
		/*auto call1 = CallFunc::create([=](){
			m_iLvCount--;
			if (!m_iLvCount)
			{
				m_pSpZengjia->setVisible(false);
				m_pSpLvAdd->setVisible(false);
				m_pSpChenghao->setVisible(false);
				m_pSpLvScore->setVisible(false);
			}
		});*/
		Sequence *seq = nullptr;

		if (i == leftStar - 1)
		{
			seq = Sequence::create(delay, move, call,/* call1,*/ nullptr);
		}
		else
		{
			seq = Sequence::create(delay, move, call, nullptr);
		}
		sp->runAction(seq);
	}
}

void GameLayer::dealLvAddScoreAfter(Node*pSender, int score)
{
	pSender->removeFromParentAndCleanup(true);
	updateEveryScore(score);
}
