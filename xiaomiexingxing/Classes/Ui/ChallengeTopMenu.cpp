#include "ChallengeTopMenu.h"
#include "Data/GameData.h"
#include "ChallengeGameLayer.h"

ChallengeTopMenu::~ChallengeTopMenu()
{
}

ChallengeTopMenu::ChallengeTopMenu():
m_layer(nullptr),
m_score(0)
{
}

ChallengeTopMenu *ChallengeTopMenu::create(ChallengeGameLayer *layer)
{
	ChallengeTopMenu *top = new ChallengeTopMenu;
	if (top && top->init(layer))
	{
		return top;
	}

	CC_SAFE_DELETE(top);

	return nullptr;
}

bool ChallengeTopMenu::init(ChallengeGameLayer *layer)
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

	m_level = NumSprite::create(1);
	m_level->setPosition(Vec2(VISIBLE_SIZE.width / 2 + levelSprite->getContentSize().width / 2 + levelSprite->getPositionX() / 2, levelSprite->getPositionY()));
	batch->addChild(m_level);

	auto targetSprite = Sprite::createWithSpriteFrameName("targetscore.png");
	targetSprite->setPosition(highestSprite->getPosition() + Vec2(-targetSprite->getContentSize().width * 0.45, -targetSprite->getContentSize().height * 2));
	batch->addChild(targetSprite);

	m_targetScore = NumSprite::create(ChallengeScore);
	m_targetScore->setPosition(Vec2(VISIBLE_SIZE.width * 0.55, targetSprite->getPositionY()));
	batch->addChild(m_targetScore);

	auto scoreSprite = Sprite::createWithSpriteFrameName("curscore.png");
	scoreSprite->setPosition(Vec2(VISIBLE_SIZE.width*0.4, targetSprite->getPositionY() - scoreSprite->getContentSize().height));
	batch->addChild(scoreSprite);

	m_curScore = NumSprite::create(m_score, NumberType::GameNumberCurScore);
	m_curScore->setPosition(scoreSprite->getPosition() + Vec2(0, 3));
	batch->addChild(m_curScore);


	auto moneySprite = Sprite::createWithSpriteFrameName("zuanshibg.png");
	moneySprite->setPosition(scoreSprite->getPosition() + Vec2(scoreSprite->getContentSize().width * 1.5, 0));
	batch->addChild(moneySprite);

	m_layer->m_curScorePos = m_curScore->getPosition();

	m_moneyStar = NumSprite::create(GameData::getInstance()->getGoodsNumber(GoodsType::Zuanshi));
	m_moneyStar->setPosition(moneySprite->getPosition() + Vec2(15, 0));
	batch->addChild(m_moneyStar);
	
	return true;
}

void ChallengeTopMenu::refresh()
{
	if (m_score > GameData::getInstance()->getHistoryHighestScore())
	{
		GameData::getInstance()->setHistoryHighestScore(m_score);
	}
	m_highestScore->setValue(GameData::getInstance()->getHistoryHighestScore());

	/*m_level->setValue(1);

	if (GameData::getInstance()->getGameMode() == GameData::GameNormal)
	{
		m_targetScore->setValue(GameData::getInstance()->getNextScore());
	}*/
	
	m_moneyStar->setValue(GameData::getInstance()->getGoodsNumber(GoodsType::Zuanshi));
}

void ChallengeTopMenu::updateDiamondNumber(int num)
{
	m_moneyStar->setValue(num);
}

int ChallengeTopMenu::getCurScore()
{
	return m_score;
}

void ChallengeTopMenu::updateEveryScore(int score)
{
	if (score != 0)
	{
		m_score += score;
		m_curScore->setValue(m_score);
	}

	if (m_score >= ChallengeScore)
	{	
		if (m_layer->getStarsStatus() != ChallengeGameLayer::Status_Over)
		{
			m_layer->startPassLevelDeal();
		}
		m_curScore->setColor(Color3B::GREEN);		
	}
	else
	{
		m_curScore->setColor(Color3B::YELLOW);
	}
}
