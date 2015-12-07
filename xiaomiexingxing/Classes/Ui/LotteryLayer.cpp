#include "LotteryLayer.h"

LotteryLayer::LotteryLayer() :
m_batchNode(nullptr),
m_numSp(nullptr),
m_startBtn(nullptr),
m_closeBtn(nullptr),
m_lotteryStatu(false),
m_callbackCount(0),
m_lotteryResult(0),
m_lightSp(nullptr),
m_centerLightSp(nullptr),
m_goodsLottery(nullptr),
m_numGoodsLottery(nullptr)
{
}

LotteryLayer::~LotteryLayer()
{
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("lottery.plist");
	TextureCache::getInstance()->removeTextureForKey("lottery.png");
	TextureCache::getInstance()->removeTextureForKey("menubg.png");
}

bool LotteryLayer::init()
{
	if (!StudioLayer::init(LayerOpacity))
	{
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("lottery.plist");
	TextureCache::getInstance()->addImage("lottery.png");
	TextureCache::getInstance()->addImage("menubg.png");

	auto keyboardlistener = EventListenerKeyboard::create();
	keyboardlistener->onKeyReleased = CC_CALLBACK_2(LotteryLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardlistener, this);

	return true;
}

void LotteryLayer::onEnter()
{
	StudioLayer::onEnter();

	initUI();
}

void LotteryLayer::initUI()
{
	auto bg = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("menubg.png"));
	bg->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	this->addChild(bg);

	Size size = bg->getContentSize();

	m_startBtn = Button::create("start.png", "start.png", "start.png", TextureResType::PLIST);
	m_startBtn->setPosition(Vec2(VISIBLE_SIZE.width * 0.5, VISIBLE_SIZE.height * 0.4));
	m_startBtn->addTouchEventListener(CC_CALLBACK_2(LotteryLayer::onBtnClick, this));
	m_startBtn->setPressedActionEnabled(true);
	this->addChild(m_startBtn);

	m_closeBtn = Button::create("menuClose.png", "menuClose.png", "menuClose.png", TextureResType::PLIST);
	m_closeBtn->setPosition(Vec2(VISIBLE_SIZE.width * 0.5 + size.width * 0.5 - m_closeBtn->getContentSize().width * 0.7, VISIBLE_SIZE.height * 0.5 + size.height * 0.5 - m_closeBtn->getContentSize().height * 0.7));
	m_closeBtn->addTouchEventListener(CC_CALLBACK_2(LotteryLayer::onBtnClick, this));
	m_closeBtn->setPressedActionEnabled(true);
	this->addChild(m_closeBtn);

	m_batchNode = SpriteBatchNode::createWithTexture(TextureCache::getInstance()->getTextureForKey("lottery.png"));
	this->addChild(m_batchNode);

	auto lotteryCenterbg = Sprite::createWithSpriteFrameName("lotterycenterbg.png");
	lotteryCenterbg->setPosition(Vec2(VISIBLE_SIZE.width * 0.5, VISIBLE_SIZE.height * 0.55));
	m_batchNode->addChild(lotteryCenterbg);

	auto lotteryda = Sprite::createWithSpriteFrameName("lotterybg.png");
	lotteryda->setPosition(lotteryCenterbg->getPosition());
	lotteryda->setScale(1.5f);
	m_batchNode->addChild(lotteryda);

	auto lotterycenter = Sprite::createWithSpriteFrameName("lotterycenter.png");
	lotterycenter->setPosition(lotteryCenterbg->getPosition());
	m_batchNode->addChild(lotterycenter);

	m_centerLightSp = Sprite::createWithSpriteFrameName("light.png");
	m_centerLightSp->setPosition(lotteryCenterbg->getPosition());
	m_centerLightSp->setVisible(false);
	m_batchNode->addChild(m_centerLightSp);

	m_lightSp = Sprite::createWithSpriteFrameName("lotterycirle.png");
	m_lightSp->setVisible(false);
	m_lightSp->setScale(1.15f);
	m_batchNode->addChild(m_lightSp);

	//奖品
	auto lottery1 = Sprite::createWithSpriteFrameName("lotterybg.png");
	int x = VISIBLE_SIZE.width / 2 - size.width / 2;
	int dis = (size.width - lottery1->getContentSize().width * 4 - LOTTERYDIS * 2) / 3.0;
	int y = lotteryCenterbg->getPositionY() + lotteryCenterbg->getContentSize().height * 0.72;
	lottSize = lottery1->getContentSize();
	lottery1->setPosition(Vec2(x + LOTTERYDIS + lottery1->getContentSize().width / 2, y));
	m_batchNode->addChild(lottery1);
	m_goodsBg.pushBack(lottery1);

	auto lottery2 = Sprite::createWithSpriteFrameName("lotterybg.png");
	lottery2->setPosition(Vec2(lottery1->getPositionX() + lottSize.width + dis, y));
	m_batchNode->addChild(lottery2);
	m_goodsBg.pushBack(lottery2);

	auto lottery3 = Sprite::createWithSpriteFrameName("lotterybg.png");
	lottery3->setPosition(Vec2(lottery2->getPositionX() + lottSize.width + dis, y));
	m_batchNode->addChild(lottery3);
	m_goodsBg.pushBack(lottery3);

	auto lottery4 = Sprite::createWithSpriteFrameName("lotterybg.png");
	lottery4->setPosition(Vec2(lottery3->getPositionX() + lottSize.width + dis, y));
	m_batchNode->addChild(lottery4);
	m_goodsBg.pushBack(lottery4);

	auto lottery5 = Sprite::createWithSpriteFrameName("lotterybg.png");
	lottery5->setPosition(Vec2(lottery4->getPositionX(), y - dis - lottSize.height));
	m_batchNode->addChild(lottery5);
	m_goodsBg.pushBack(lottery5);

	auto lottery6 = Sprite::createWithSpriteFrameName("lotterybg.png");
	lottery6->setPosition(Vec2(lottery4->getPositionX(), lottery5->getPositionY() - dis - lottSize.height));
	m_batchNode->addChild(lottery6);
	m_goodsBg.pushBack(lottery6);

	auto lottery7 = Sprite::createWithSpriteFrameName("lotterybg.png");
	lottery7->setPosition(Vec2(lottery4->getPositionX(), lottery6->getPositionY() - dis - lottSize.height));
	m_batchNode->addChild(lottery7);
	m_goodsBg.pushBack(lottery7);

	auto lottery8 = Sprite::createWithSpriteFrameName("lotterybg.png");
	lottery8->setPosition(Vec2(lottery4->getPositionX(), lottery7->getPositionY() - dis - lottSize.height));
	m_batchNode->addChild(lottery8);
	m_goodsBg.pushBack(lottery8);

	auto lottery9 = Sprite::createWithSpriteFrameName("lotterybg.png");
	lottery9->setPosition(Vec2(lottery8->getPositionX() - dis - lottSize.width, lottery8->getPositionY()));
	m_batchNode->addChild(lottery9);
	m_goodsBg.pushBack(lottery9);

	auto lottery10 = Sprite::createWithSpriteFrameName("lotterybg.png");
	lottery10->setPosition(Vec2(lottery9->getPositionX() - dis - lottSize.width, lottery8->getPositionY()));
	m_batchNode->addChild(lottery10);
	m_goodsBg.pushBack(lottery10);

	auto lottery11 = Sprite::createWithSpriteFrameName("lotterybg.png");
	lottery11->setPosition(Vec2(lottery10->getPositionX() - dis - lottSize.width, lottery8->getPositionY()));
	m_batchNode->addChild(lottery11);
	m_goodsBg.pushBack(lottery11);

	auto lottery12 = Sprite::createWithSpriteFrameName("lotterybg.png");
	lottery12->setPosition(Vec2(lottery11->getPositionX(), lottery11->getPositionY() + dis + lottSize.width));
	m_batchNode->addChild(lottery12);
	m_goodsBg.pushBack(lottery12);

	auto lottery13 = Sprite::createWithSpriteFrameName("lotterybg.png");
	lottery13->setPosition(Vec2(lottery11->getPositionX(), lottery12->getPositionY() + dis + lottSize.width));
	m_batchNode->addChild(lottery13);
	m_goodsBg.pushBack(lottery13);

	auto lottery14 = Sprite::createWithSpriteFrameName("lotterybg.png");
	lottery14->setPosition(Vec2(lottery11->getPositionX(), lottery13->getPositionY() + dis + lottSize.width));
	m_batchNode->addChild(lottery14);
	m_goodsBg.pushBack(lottery14);

	m_vecLotteryPos.push_back(lottery1->getPosition());
	m_vecLotteryPos.push_back(lottery2->getPosition());
	m_vecLotteryPos.push_back(lottery3->getPosition());
	m_vecLotteryPos.push_back(lottery4->getPosition());
	m_vecLotteryPos.push_back(lottery5->getPosition());
	m_vecLotteryPos.push_back(lottery6->getPosition());
	m_vecLotteryPos.push_back(lottery7->getPosition());
	m_vecLotteryPos.push_back(lottery8->getPosition());
	m_vecLotteryPos.push_back(lottery9->getPosition());
	m_vecLotteryPos.push_back(lottery10->getPosition());
	m_vecLotteryPos.push_back(lottery11->getPosition());
	m_vecLotteryPos.push_back(lottery12->getPosition());
	m_vecLotteryPos.push_back(lottery13->getPosition());
	m_vecLotteryPos.push_back(lottery14->getPosition());

	initLotteryUI();

	auto info = Sprite::createWithSpriteFrameName("lotteryinfo.png");
	info->setPosition(bg->getPosition() + Vec2(0, -bg->getContentSize().height * 0.45));
	info->setAnchorPoint(Vec2(0.5f, 0.0f));
	m_batchNode->addChild(info);

	m_numSp = NumSprite::create(GameData::getInstance()->getFreeLotteryCount(), NumberType::GameLottery);
	m_numSp->setPosition(info->getPosition());
	m_numSp->setAnchorPoint(Vec2(0.5f, 0.0f));
	m_batchNode->addChild(m_numSp);
}

void LotteryLayer::initLotteryUI()
{
	if (!m_vecNumberResult.empty())
	{
		m_vecNumberResult.clear();
	}

	if (!m_vecGoodsResult.empty())
	{
		m_vecGoodsResult.clear();
	}

	if (!m_lottery.empty())
	{
		for (auto node : m_lottery)
		{
			node->removeFromParentAndCleanup(true);
		}
		m_lottery.clear();
	}
	
	vector<int> vec;

	for (int i = 0; i < 11; i++)
	{
		vec.push_back(cocos2d::random() % 5 + 1);
	}
	vec.push_back(GoodsType::Zuanshi);
	vec.push_back(GoodsType::Zuanshi);
	vec.push_back(GoodsType::Zuanshi);

	random_shuffle(vec.begin(), vec.end());

	vector<int> zuanshi;
	zuanshi.push_back(3000);
	zuanshi.push_back(300);
	zuanshi.push_back(100);
	random_shuffle(zuanshi.begin(), zuanshi.end());

	int i = 0;

	for (auto it : vec)
	{
		int num = 0;
		if (it != GoodsType::Zuanshi)
		{
			num = cocos2d::random() % 3 + 1;
		}
		else
		{
			int r = cocos2d::random() % zuanshi.size();
			num = zuanshi.at(r);
			zuanshi.erase(zuanshi.begin() + r);
		}
		auto sp = Sprite::createWithSpriteFrameName(getLotteryPath((GoodsType)it));
		sp->setPosition(m_vecLotteryPos.at(i));
		m_batchNode->addChild(sp);
		m_lottery.pushBack(sp);

		auto numSp = NumSprite::create(num, NumberType::GameLottery);
		numSp->setPosition(sp->getPosition() + Vec2(0, -sp->getContentSize().height / 4));
		m_batchNode->addChild(numSp);
		m_lottery.pushBack(numSp);

		m_vecGoodsResult.push_back(it);
		m_vecNumberResult.push_back(num);

		i++;
	}
}

void LotteryLayer::onBtnClick(Ref* sender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::BEGAN)
	{
		if (m_lotteryStatu)
		{
			return;
		}

		if (m_startBtn == (Button*)sender)
		{
			startLottery();
		}
		else
		{
			StudioLayer::closeLayer();
		}
	}
}

void LotteryLayer::startLottery()
{
	m_lotteryStatu = true;

	if (GameData::getInstance()->getFreeLotteryCount() > 0)
	{
		GameData::getInstance()->setFreeLotteryConut(GameData::getInstance()->getFreeLotteryCount() - 1);
		m_numSp->setValue(GameData::getInstance()->getFreeLotteryCount());
		startLotteryActioin();
	}
	else
	{
		if (GameData::getInstance()->getGoodsNumber(GoodsType::Zuanshi) >= LotteryZuanshi)
		{
			GameData::getInstance()->setGoodsNumber(GoodsType::Zuanshi, GameData::getInstance()->getGoodsNumber(GoodsType::Zuanshi) - LotteryZuanshi);
			startLotteryActioin();
		}
		else
		{
			popOutDialog(cocos2d::random() % 100 < 50 ? PayType::pGameLibao99 : PayType::pGameLibao130);
			m_lotteryStatu = false;
			m_callbackCount = 0;
			m_lotteryResult = 0;
		}
	}
}

void LotteryLayer::startLotteryActioin()
{
	if (m_goodsLottery)
	{
		m_goodsLottery->removeFromParentAndCleanup(true);
		m_goodsLottery = nullptr;
	}

	if (m_numGoodsLottery)
	{
		m_numGoodsLottery->removeFromParentAndCleanup(true);
		m_numGoodsLottery = nullptr;
	}

	initLotteryUI();

	int rand = cocos2d::random() % 14;

	m_lightSp->setPosition(m_vecLotteryPos.at(rand));
	m_lightSp->setVisible(true);

	auto delay = DelayTime::create(0.5f);
	auto call = CallFunc::create(CC_CALLBACK_0(LotteryLayer::callBackLight, this, rand));

	m_lightSp->runAction(Sequence::create(delay, call, nullptr));

	m_centerLightSp->setVisible(true);
	auto delay1 = DelayTime::create(0.3f);
	auto call1 = CallFunc::create([=](){m_centerLightSp->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("light1.png")); });
	auto call2 = CallFunc::create([=](){m_centerLightSp->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("light.png")); });
	m_centerLightSp->runAction(RepeatForever::create(Sequence::create(delay1, call1,delay1->clone(),call2, nullptr)));
}

void LotteryLayer::callBackLight(int pos)
{
	if (m_callbackCount >= 48)
	{		
		if (judgeLotteryResult(pos))
		{
			m_lotteryStatu = false;
			m_lotteryResult = pos;
			m_callbackCount = 0;
			moveToCenter();
			return;
		}
	}
	
	m_callbackCount++;
	float tm = 0.0f;
	if (m_callbackCount <= 4)
	{
		tm = 0.5f;
	}
	else if (m_callbackCount > 4 && m_callbackCount <= 42)
	{
		tm = 0.1f;
	}
	else if (m_callbackCount > 42/* && m_callbackCount <= 47*/)
	{
		tm = 0.5f;
	}
	
	if (pos == 13)
	{
		pos = -1;
	}

	m_lightSp->setPosition(m_vecLotteryPos.at(pos + 1));

	auto delay = DelayTime::create(tm);
	auto call = CallFunc::create(CC_CALLBACK_0(LotteryLayer::callBackLight, this, pos + 1));
	m_lightSp->runAction(Sequence::create(delay, call, nullptr));
}

void LotteryLayer::moveToCenter()
{
	m_centerLightSp->stopAllActions();
	m_centerLightSp->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("light.png"));
	m_lightSp->setVisible(false);

	auto scale = ScaleBy::create(0.5f, 1.2f);
	m_lottery.at(m_lotteryResult * 2)->runAction(Repeat::create(Sequence::create(scale, scale->reverse(), nullptr), 3));
	auto scale1 = scale->clone();
	m_lottery.at(m_lotteryResult * 2 + 1)->runAction(Repeat::create(Sequence::create(scale1, scale1->reverse(), nullptr), 3));
	auto scale2 = scale->clone();

	auto call = CallFunc::create([=](){
		auto move = MoveTo::create(1.0f, Vec2(VISIBLE_SIZE.width * 0.5, VISIBLE_SIZE.height * 0.55));
		m_goodsLottery = Sprite::createWithSpriteFrameName(getLotteryPath((GoodsType)m_vecGoodsResult.at(m_lotteryResult)));
		m_goodsLottery->setPosition(m_lottery.at(m_lotteryResult * 2)->getPosition());
		m_batchNode->addChild(m_goodsLottery);
		m_numGoodsLottery = NumSprite::create(m_vecNumberResult.at(m_lotteryResult), NumberType::GameLottery);
		m_numGoodsLottery->setPosition(m_lottery.at(m_lotteryResult * 2 + 1)->getPosition());
		m_batchNode->addChild(m_numGoodsLottery);

		m_goodsLottery->runAction(move);

		auto move1 = MoveTo::create(1.0f, Vec2(VISIBLE_SIZE.width * 0.5, VISIBLE_SIZE.height * 0.55) + Vec2(0, -m_goodsLottery->getContentSize().height / 4));
		auto call = CallFunc::create([=](){updateGoodsNumber((GoodsType)m_vecGoodsResult.at(m_lotteryResult), m_vecNumberResult.at(m_lotteryResult)); });

		m_numGoodsLottery->runAction(Sequence::create(move1, call, nullptr));
	});

	m_goodsBg.at(m_lotteryResult)->runAction(Sequence::create(Repeat::create(Sequence::create(scale2, scale2->reverse(), nullptr), 3), call, nullptr));
}

bool LotteryLayer::judgeLotteryResult(int pos)
{
	int number = m_vecNumberResult.at(pos);
	if (m_vecGoodsResult.at(pos) == GoodsType::Zuanshi)
	{
		if (number == 3000)
		{
			return false;
		}
		else if (number == 300) //付费用户可以
		{
			if (GameData::getInstance()->getIsPay())
			{
				return false;
			}
		}
	}

	return true;
}

string LotteryLayer::getLotteryPath(GoodsType type)
{
	switch (type)
	{
	case Bomb:
		return "zhadan.png";
	case Tongsexiao:
		return "tongsexiao.png";
	case Huanse:
		return "huanse.png";
	case Chexiao:
		return "chexiao.png";
	case Shuaxin:
		return "shuaxin.png";
	case Zuanshi:
		return "zuanshi.png";
	}

	return "";
}

void LotteryLayer::payDialogCallBack(int point, int result, std::map<int, int> _map)
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
	}
}

void LotteryLayer::updateGoodsNumber(GoodsType type, int num)
{
	num = GameData::getInstance()->getGoodsNumber(type) + num;
	GameData::getInstance()->setGoodsNumber(type, num);
}

void LotteryLayer::popOutDialog(PayType type)
{
	auto dialog = GameDialogLayer::createPay(DialogType::PayDialog, type, CC_CALLBACK_3(LotteryLayer::payDialogCallBack, this));
	if (dialog)
	{
		this->addChild(dialog);
	}
}

void LotteryLayer::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
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
