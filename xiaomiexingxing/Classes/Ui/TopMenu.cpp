#include "TopMenu.h"
#include "Data/GameData.h"
#include "GameLayer.h"

TopMenu::~TopMenu()
{
}

TopMenu::TopMenu():
m_layer(nullptr)
{
}

TopMenu *TopMenu::create(GameLayer *layer)
{
	TopMenu *top = new TopMenu;
	if (top && top->init(layer))
	{
		return top;
	}

	CC_SAFE_DELETE(top);

	return nullptr;
}


bool TopMenu::init(GameLayer *layer)
{
	m_layer = layer;
	SpriteBatchNode *batch = m_layer->getBatchNode();

	auto highestSprite = Sprite::createWithSpriteFrameName("heightscore.png");
	highestSprite->setPosition(Vec2(VISIBLE_SIZE.width * 0.4, VISIBLE_SIZE.height - highestSprite->getContentSize().height));

	batch->addChild(highestSprite);

	m_highestScore = NumSprite::create(GameData::getInstance()->getHistoryHighestScore());
	m_highestScore->setPosition(Vec2(VISIBLE_SIZE.width * 0.55, highestSprite->getPositionY()));
	batch->addChild(m_highestScore);

	auto levelSprite = Sprite::createWithSpriteFrameName("guanqia.png");
	levelSprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	levelSprite->setPosition(Vec2(VISIBLE_SIZE.width * 0.7, highestSprite->getPositionY()));
	batch->addChild(levelSprite);

	m_level = NumSprite::create(GameData::getInstance()->getNextLevel());
	m_level->setPosition(Vec2(VISIBLE_SIZE.width / 2 + levelSprite->getContentSize().width / 2 + levelSprite->getPositionX() / 2, levelSprite->getPositionY()));
	batch->addChild(m_level);

	auto targetSprite = Sprite::createWithSpriteFrameName("targetscore.png");
	targetSprite->setPosition(highestSprite->getPosition() + Vec2(-targetSprite->getContentSize().width * 0.45, -targetSprite->getContentSize().height * 2));
	batch->addChild(targetSprite);

	m_targetScore = NumSprite::create(GameData::getInstance()->getNextScore());
	m_targetScore->setPosition(Vec2(VISIBLE_SIZE.width * 0.55, targetSprite->getPositionY()));
	batch->addChild(m_targetScore);

	auto scoreSprite = Sprite::createWithSpriteFrameName("curscore.png");
	scoreSprite->setPosition(Vec2(VISIBLE_SIZE.width*0.4, targetSprite->getPositionY() - scoreSprite->getContentSize().height * 1.5f));
	batch->addChild(scoreSprite);

	m_curScore = NumSprite::create(GameData::getInstance()->getCurScore(), NumberType::GameNumberCurScore);
	m_curScore->setPosition(scoreSprite->getPosition() + Vec2(0, 3));
	batch->addChild(m_curScore);

	if (GameData::getInstance()->getCurScore() >= GameData::getInstance()->getNextScore())
	{
		m_curScore->setColor(Color3B::GREEN);
	}

	auto moneySprite = Sprite::createWithSpriteFrameName("zuanshibg.png");
	moneySprite->setPosition(scoreSprite->getPosition() + Vec2(scoreSprite->getContentSize().width * 1.5, 0));
	batch->addChild(moneySprite);

	m_layer->m_curScorePos = m_curScore->getPosition();
	m_layer->m_curZuanshiPos = moneySprite->getPosition() + Vec2(-moneySprite->getContentSize().width * 0.35, 0);

	m_moneyStar = NumSprite::create(GameData::getInstance()->getGoodsNumber(GoodsType::Zuanshi));
	m_moneyStar->setPosition(moneySprite->getPosition() + Vec2(15, 0));
	batch->addChild(m_moneyStar);

	
	
	return true;
}

void TopMenu::refresh()
{
	if (GameData::getInstance()->getCurScore() > GameData::getInstance()->getHistoryHighestScore())
	{
		GameData::getInstance()->setHistoryHighestScore(GameData::getInstance()->getCurScore());
	}
	m_highestScore->setValue(GameData::getInstance()->getHistoryHighestScore());

	m_level->setValue(GameData::getInstance()->getNextLevel());

	if (GameData::getInstance()->getGameMode() == GameData::GameNormal)
	{
		m_targetScore->setValue(GameData::getInstance()->getNextScore());
	}
	
	m_moneyStar->setValue(GameData::getInstance()->getGoodsNumber(GoodsType::Zuanshi));
}

void TopMenu::updateDiamondNumber(int num)
{
	m_moneyStar->setValue(num);
}

void TopMenu::updateEveryScore(int score)
{
	if (score != 0)
	{
		GameData::getInstance()->setCurScore(GameData::getInstance()->getCurScore() + score);
		m_curScore->setValue(GameData::getInstance()->getCurScore());
	}

	int targetscore = GameData::getInstance()->getGameMode() == GameData::GameModeType::GameNormal ? GameData::getInstance()->getNextScore() : ChallengeScore;
	if (GameData::getInstance()->getCurScore() >= targetscore)
	{	
		if (m_layer->getStarsStatus() != GameLayer::Status_Over)
		{
			m_layer->startPassLevelDeal();
		}
		m_curScore->setColor(Color3B::GREEN);		
	}
	else/* if (score == 0)*/
	{
		m_curScore->setColor(Color3B::YELLOW);
	}
}
