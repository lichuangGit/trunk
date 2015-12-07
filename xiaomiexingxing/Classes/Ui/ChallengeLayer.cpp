#include "ChallengeLayer.h"


ChallengeLayer::ChallengeLayer()
{
}


ChallengeLayer::~ChallengeLayer()
{
	TextureCache::getInstance()->removeTextureForKey("otherDialogBg.png");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("challenge.plist");
}

bool ChallengeLayer::init()
{
	if (!StudioLayer::init(LayerOpacity))
	{
		return false;
	}

	TextureCache::getInstance()->addImage("otherDialogBg.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("challenge.plist");

	auto keyboardlistener = EventListenerKeyboard::create();
	keyboardlistener->onKeyReleased = CC_CALLBACK_2(ChallengeLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardlistener, this);

	return true;
}

void ChallengeLayer::onEnter()
{
	StudioLayer::onEnter();

	initUI();
}

void ChallengeLayer::initUI()
{
	auto bg = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("otherDialogBg.png"));
	bg->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	this->addChild(bg);

	auto text = Sprite::createWithSpriteFrameName("tiaozhan.png");
	text->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2 + bg->getContentSize().height / 2 - text->getContentSize().height / 2));
	this->addChild(text);

	m_btnSub = Button::create("jian.png", "jian.png", "jian.png", TextureResType::PLIST);
	m_btnSub->setPosition(text->getPosition() + Vec2(-text->getContentSize().width * 0.3 , -m_btnSub->getContentSize().height));
	m_btnSub->addTouchEventListener(CC_CALLBACK_2(ChallengeLayer::onBtnClick, this));
	m_btnSub->setPressedActionEnabled(true);
	this->addChild(m_btnSub);

	m_btnAdd = Button::create("jia.png", "jia.png", "jia.png", TextureResType::PLIST);
	m_btnAdd->setPosition(text->getPosition() + Vec2(text->getContentSize().width * 0.27, -m_btnAdd->getContentSize().height));
	m_btnAdd->addTouchEventListener(CC_CALLBACK_2(ChallengeLayer::onBtnClick, this));
	m_btnAdd->setPressedActionEnabled(true);
	this->addChild(m_btnAdd);

	m_btnStart = Button::create("tiaozhanstart.png", "tiaozhanstart.png", "tiaozhanstart.png", TextureResType::PLIST);
	m_btnStart->setPosition(text->getPosition() + Vec2(0, -text->getContentSize().height / 2 - m_btnStart->getContentSize().height / 1.7));
	m_btnStart->addTouchEventListener(CC_CALLBACK_2(ChallengeLayer::onBtnClick, this));
	m_btnStart->setPressedActionEnabled(true);
	this->addChild(m_btnStart);

	m_btnClose = Button::create("menuClose.png", "menuClose.png", "menuClose.png", Widget::TextureResType::PLIST);
	m_btnClose->setPosition(bg->getPosition() + Vec2(bg->getContentSize().width / 2 - m_btnClose->getContentSize().width  * 0.7, bg->getContentSize().height / 2 - m_btnClose->getContentSize().height * 0.7));
	m_btnClose->addTouchEventListener(CC_CALLBACK_2(ChallengeLayer::onBtnClick, this));
	m_btnClose->setPressedActionEnabled(true);
	this->addChild(m_btnClose);

	auto batchNode = SpriteBatchNode::create("challenge.png");
	this->addChild(batchNode);

	auto sp = Sprite::createWithSpriteFrameName("wode.png");
	sp->setPosition(bg->getPosition() + Vec2(-15, -bg->getContentSize().height / 2 + sp->getContentSize().height * 0.55));
	sp->setAnchorPoint(Vec2(0, 0));
	batchNode->addChild(sp);

	m_betSp = NumSprite::create(0, NumberType::GameChallenge);
	m_betSp->setPosition(text->getPosition() + Vec2(-10, -m_btnAdd->getContentSize().height));
	batchNode->addChild(m_betSp);

	m_zuanshiCount = NumSprite::create(0, NumberType::GameChallenge);
	m_zuanshiCount->setPosition(text->getPosition() + Vec2(m_btnAdd->getContentSize().width * 1.1, -m_btnStart->getContentSize().height * 1.53));
	batchNode->addChild(m_zuanshiCount);

	auto score = NumSprite::create(3100, NumberType::GameChallenge);
	score->setPosition(text->getPosition() + Vec2(m_btnAdd->getContentSize().width * 1.1, -m_btnStart->getContentSize().height * 2.2));
	batchNode->addChild(score);

	m_numSp = NumSprite::create(GameData::getInstance()->getGoodsNumber(GoodsType::Zuanshi), NumberType::GameChallenge);
	m_numSp->setPosition(sp->getPosition() + Vec2(sp->getContentSize().width * 0.65, sp->getContentSize().height*0.5));
	batchNode->addChild(m_numSp);
}

void ChallengeLayer::onBtnClick(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::BEGAN)
	{
		Button *btn = (Button *)pSender;
		if (btn == m_btnAdd)
		{
			if (GameData::getInstance()->getChallengeZuanshi() + 1 > GameData::getInstance()->getGoodsNumber(GoodsType::Zuanshi)	)//若钻石不足，弹出礼包
			{
				popOutDialog(cocos2d::random() % 100 < 50 ? PayType::pGameLibao99 : PayType::pGameLibao130);
			}
			else
			{
				GameData::getInstance()->setChallengeZuanshi(GameData::getInstance()->getChallengeZuanshi() + 1);
				m_zuanshiCount->setValue(GameData::getInstance()->getChallengeZuanshi() * 5);
				m_betSp->setValue(GameData::getInstance()->getChallengeZuanshi());
			}
		}
		else if (btn == m_btnSub)
		{
			if (GameData::getInstance()->getChallengeZuanshi() > 0)
			{
				GameData::getInstance()->setChallengeZuanshi(GameData::getInstance()->getChallengeZuanshi() - 1);
				m_zuanshiCount->setValue(GameData::getInstance()->getChallengeZuanshi() * 5);
				m_betSp->setValue(GameData::getInstance()->getChallengeZuanshi());
			}
		}
		else if (btn == m_btnStart)
		{
			if (GameData::getInstance()->getChallengeZuanshi() > 0)
			{
				map<string, string> _map;
				_map["zuanshi"] = cocos2d::Value(GameData::getInstance()->getChallengeZuanshi()).asString();
				UmengUpload::event(Umeng_Id_TiaozhanStart, &_map);
				Director::getInstance()->replaceScene(ChallengeGameLayer::createScene());
			}
		}
		else if (btn == m_btnClose)
		{
			GameData::getInstance()->setChallengeZuanshi(0);
			StudioLayer::closeLayer();
		}
	}
}

void ChallengeLayer::popOutDialog(PayType type)
{
	auto dialog = GameDialogLayer::createPay(DialogType::PayDialog, type, CC_CALLBACK_3(ChallengeLayer::payDialogCallBack, this));
	if (dialog)
	{
		this->addChild(dialog);
	}
}

void ChallengeLayer::payDialogCallBack(int point, int result, std::map<int, int> _map)
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

void ChallengeLayer::updateGoodsNumber(GoodsType type, int num)
{
	num = GameData::getInstance()->getGoodsNumber(type) + num;
	GameData::getInstance()->setGoodsNumber(type, num);
	if (type == GoodsType::Zuanshi)
	{
		m_numSp->setValue(num);
	}
}

void ChallengeLayer::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	if (event->getType() == Event::Type::KEYBOARD)
	{
		event->stopPropagation();
	}
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_BACK:
		GameData::getInstance()->setChallengeZuanshi(0);
		StudioLayer::closeLayer();
		break;
	}
}
