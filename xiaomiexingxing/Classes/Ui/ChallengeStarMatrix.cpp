#include "ChallengeStarMatrix.h"
#include "Data/GameData.h"
#include "Core/ComboEffect.h"
#include "Data/GameData.h"
#include "Core/CCShake.h"

extern string starpath[];

ChallengeStarMatrix::ChallengeStarMatrix():
clearSumTime(0),
m_layer(nullptr),
m_starBatchNode(nullptr),
isStarSeclected(true)
{
	m_particleBatchNode.clear();
	m_starsNext.clear();
}

ChallengeStarMatrix::~ChallengeStarMatrix()
{
	unschedule(schedule_selector(ChallengeStarMatrix::updateStar));
}

ChallengeStarMatrix* ChallengeStarMatrix::create(ChallengeGameLayer* layer) 
{
	ChallengeStarMatrix* ret = new ChallengeStarMatrix();
	if (ret && ret->init(layer))
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);

	return nullptr;
}

bool ChallengeStarMatrix::init(ChallengeGameLayer* layer) 
{
	if (!Node::init()) 
	{
		return false;
	}

	m_layer = layer;
	memset(stars, 0, sizeof(Star*) * ROW_NUM * COL_NUM);
	memset(backStar, 0, sizeof(Sprite*) * ROW_NUM * COL_NUM);
	m_layer->setStarsStatus(ChallengeGameLayer::Status_Ready);
	
	initMatrix();
	
	schedule(schedule_selector(ChallengeStarMatrix::updateStar));

	return true;
}

void ChallengeStarMatrix::initMatrix()
{
	m_starBatchNode = SpriteBatchNode::createWithTexture(TextureCache::getInstance()->getTextureForKey("star.png"));
	this->addChild(m_starBatchNode);

	for (int i = 0; i < COLOR_MAX_NUM; i++)
	{
		ParticleBatchNode *node = ParticleBatchNode::createWithTexture(TextureCache::getInstance()->getTextureForKey(starpath[i]));
		this->addChild(node);
		m_particleBatchNode.pushBack(node);
	}

	int starColorNum[5];

	for (int i = 0; i < sizeof(starColorNum) / sizeof(starColorNum[0]); i++)
	{
		starColorNum[i] = 0;
	}

	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++)
		{
			int color = cocos2d::random() % COLOR_MAX_NUM;
			//找出颜色最多的合最少的星星
			switch (color)
			{
			case Star::Color::BLUE:
				starColorNum[0]++;
				break;
			case Star::Color::GREEN:
				starColorNum[1]++;
				break;
			case Star::Color::YELLOW:
				starColorNum[2]++;
				break;
			case Star::Color::RED:
				starColorNum[3]++;
				break;
			case Star::Color::PURPLE:
				starColorNum[4]++;
				break;
			}
			stars[i][j] = createStar(i, j, color);
			m_starBatchNode->addChild(stars[i][j]);
			//边框
			backStar[i][j] = Sprite::createWithSpriteFrameName("black.png");
			backStar[i][j]->setPosition(getPositionByIndex(i, j));
			backStar[i][j]->setVisible(false);
			m_starBatchNode->addChild(backStar[i][j]);
		}
	}

	int maxColorNum = starColorNum[0], minColorNum = starColorNum[0], minColor = Star::Color::BLUE, maxColor =
		Star::Color::BLUE;

	for (int i = 1; i < 5; i++)
	{
		if (starColorNum[i] > maxColorNum)
		{
			maxColorNum = starColorNum[i];
			switch (i)
			{
			case 1:
				maxColor = Star::Color::GREEN;
				break;
			case 2:
				maxColor = Star::Color::YELLOW;
				break;
			case 3:
				maxColor = Star::Color::RED;
				break;
			case 4:
				maxColor = Star::Color::PURPLE;
				break;
			default:
				break;
			}
		}
		if (starColorNum[i] < minColorNum)
		{
			minColorNum = starColorNum[i];
			switch (i)
			{
			case 1:
				minColor = Star::Color::GREEN;
				break;
			case 2:
				minColor = Star::Color::YELLOW;
				break;
			case 3:
				minColor = Star::Color::RED;
				break;
			case 4:
				minColor = Star::Color::PURPLE;
				break;
			default:
				break;
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		int position = abs(cocos2d::random() % (minColorNum - i));
		int temp = 0;
		for (int i = 0; i < ROW_NUM; i++)
		{
			for (int j = 0; j < COL_NUM; j++)
			{
				if (stars[i][j]->getColor() == minColor)
				{
					temp++;
					if (temp == position)
					{
						stars[i][j]->removeFromParentAndCleanup(true);
						stars[i][j] = createStar(i, j, maxColor);
						m_starBatchNode->addChild(stars[i][j]);
					}
				}
			}
		}
	}
}

void ChallengeStarMatrix::updateStar(float f) 
{
	int i = 0, j = 0;
	
	int alreadyMove = 0;
	int starCount = 0;

	for (; i < ROW_NUM; i++) 
	{
		for (j = 0; j < COL_NUM; j++) 
		{
			if (stars[i][j] != nullptr)
			{
				starCount++;
				if (stars[i][j]->updatePosition())
					alreadyMove++;
			}				
		}
	}

	//星星全部移动到正取位置后
	if (starCount == alreadyMove)
	{
		if (m_layer->getStarsStatus() == ChallengeGameLayer::Status_Ready || m_layer->getStarsStatus() == ChallengeGameLayer::Status_Activity)
		{
			m_layer->onTouchEnded(nullptr, nullptr);
		}
		if (m_layer->getStarsStatus() != ChallengeGameLayer::Status_Over)
		{
			m_layer->setStarsStatus(ChallengeGameLayer::Status_NoActivity);
		}
	}
}

bool ChallengeStarMatrix::onTouch(const Vec2& p) 
{
	Star* s = getStarByTouch(p);
	if (s == nullptr)
	{
		return false;
	}
	else
	{
		if (!isStarSeclected)
		{
			return false;
		}

		isStarSeclected = false;
		
		getSelectedList(s);

		currentSelectedNum = 0;
		m_layer->setStarsStatus(ChallengeGameLayer::Status_Activity);

		if (selectedList.size() > 0)
		{
			schedule(schedule_selector(ChallengeStarMatrix::deleteSelectedListDelay), ONE_CLEAR_TIME, selectedList.size() - 1, 0.05f);
		}

		return true;
	}
}

Point ChallengeStarMatrix::getPositionByIndex(int i, int j)
{
	float x = j * REAL_STAR_WIDTH + REAL_STAR_WIDTH / 2;
	float y = (COL_NUM - i) * REAL_STAR_HEIGHT - REAL_STAR_HEIGHT / 2 + STAR_BOTTOM;
	return Vec2(x, y);
}

Star* ChallengeStarMatrix::getStarByTouch(const Point& p)
{
	if (p.y < STAR_BOTTOM)
	{
		return nullptr;
	}
	int k = (p.y - STAR_BOTTOM) / REAL_STAR_HEIGHT; //这里要用K转一下int 不然得不到正确结果
	int i = ROW_NUM - 1 - k;
	int j = p.x / REAL_STAR_WIDTH;
	if (i >= 0 && i < ROW_NUM && j >= 0 && j < COL_NUM && stars[i][j] != nullptr) 
	{
		return stars[i][j];
	}
		
	return nullptr;
}

void ChallengeStarMatrix::getSelectedList(Star* s)
{
	selectedList.clear();
	deque<Star*> travelList;
	travelList.push_back(s);
	deque<Star*>::iterator it;

	for (it = travelList.begin(); it != travelList.end();) 
	{
		Star* star = *it;
		Star* linkStar = nullptr;
		int index_i = star->getIndexI();
		int index_j = star->getIndexJ();
		//上
		if (index_i - 1 >= 0 && (linkStar = stars[index_i - 1][index_j])) {
			if (!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i - 1][index_j]);
		}
		//下
		if (index_i + 1 < ROW_NUM && (linkStar = stars[index_i + 1][index_j])) {
			if (!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i + 1][index_j]);
		}
		//左
		if (index_j - 1 >= 0 && (linkStar = stars[index_i][index_j - 1])) {
			if (!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i][index_j - 1]);
		}
		//右
		if (index_j + 1 < COL_NUM && (linkStar = stars[index_i][index_j + 1])) {
			if (!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i][index_j + 1]);
		}
		if (!star->isSelected()) {
			star->setSelected(true);
			selectedList.push_back(star);

			backStar[star->getIndexI()][star->getIndexJ()]->setVisible(true);

			//抖动效果
			Shake* shake = Shake::create(200.0, 0, 10.0);
			shake->startWithTarget(star);
			shake->update(200.0);
		}
		travelList.pop_front();
		it = travelList.begin();
	}
}

void ChallengeStarMatrix::getSameColorList(Star* s, deque<Star*> &result)
{
	deque<Star*> travelList;
	travelList.push_back(s);
	deque<Star*>::iterator it;
	for (it = travelList.begin(); it != travelList.end();)
	{
		Star* star = *it;
		Star* linkStar = nullptr;
		int index_i = star->getIndexI();
		int index_j = star->getIndexJ();
		//上
		if (index_i - 1 >= 0 && (linkStar = stars[index_i - 1][index_j])) {
			if (std::find(result.begin(), result.end(), linkStar) == result.end() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i - 1][index_j]);
		}
		//下
		if (index_i + 1 < ROW_NUM && (linkStar = stars[index_i + 1][index_j])) {
			if (std::find(result.begin(), result.end(), linkStar) == result.end() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i + 1][index_j]);
		}
		//左
		if (index_j - 1 >= 0 && (linkStar = stars[index_i][index_j - 1])) {
			if (std::find(result.begin(), result.end(), linkStar) == result.end() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i][index_j - 1]);
		}
		//右
		if (index_j + 1 < COL_NUM && (linkStar = stars[index_i][index_j + 1])) {
			if (std::find(result.begin(), result.end(), linkStar) == result.end() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i][index_j + 1]);
		}
		if (std::find(result.begin(), result.end(), star) == result.end()) {
			result.push_back(star);
		}
		travelList.pop_front();
		it = travelList.begin();
	}
}

//顺序播放星星破碎的效果
void ChallengeStarMatrix::deleteSelectedListDelay(float f) 
{
	if (selectedList.size() <= 1)
	{
		backStar[selectedList.at(0)->getIndexI()][selectedList.at(0)->getIndexJ()]->setVisible(false);
		selectedList.at(0)->setSelected(false);

		isStarSeclected = true;

		m_layer->setStarsStatus(ChallengeGameLayer::Status_NoActivity);
		return;
	}

	if (currentSelectedNum < selectedList.size())
	{
		Star* star = selectedList.at(currentSelectedNum);
		if (star == nullptr)
			return;

		backStar[star->getIndexI()][star->getIndexJ()]->setVisible(false);
		//粒子效果
		showStarParticleEffect(star->getColor(), star->getPosition(), m_particleBatchNode.at(star->getColor()));
		auto scoreNum = NumSprite::create(10 * (currentSelectedNum + 1) - 5, NumberType::GameNumberScore);
		scoreNum->setPosition(star->getPosition());
		m_starBatchNode->addChild(scoreNum);
		int y = VISIBLE_SIZE.height - 130 - star->getPositionY();
		int x = VISIBLE_SIZE.width / 2 - 30 - star->getPositionX();
		int px = star->getPositionX();
		int py = star->getPositionY();

		PointArray *arr = PointArray::create(4);
		arr->addControlPoint(star->getPosition());
		arr->addControlPoint(Vec2(px + x*0.25, py + y*0.25));
		arr->addControlPoint(Vec2(px + x*0.75, py + y*0.75));
		arr->addControlPoint(m_layer->m_curScorePos);
		auto cardinal = CardinalSplineTo::create(0.4f, arr, 0);
		auto fadeout = FadeOut::create(0.1f);
		auto callback = CallFuncN::create(CC_CALLBACK_1(ChallengeStarMatrix::refreshEveryScore, this, 10 * (currentSelectedNum + 1) - 5));
		auto seq = Sequence::create(cardinal, fadeout, callback, NULL);
		scoreNum->runAction(seq);

		int i = star->getIndexI();
		int j = star->getIndexJ();
		star->removeFromParentAndCleanup(true);
		stars[i][j] = nullptr;
		//播放音效
		Audio::getInstance()->playPop();
		if (++currentSelectedNum < selectedList.size()) 
		{
			return;
		}
	}
	showComboEffect(selectedList.size(), m_starBatchNode);
	Audio::getInstance()->playCombo(selectedList.size());
	isStarSeclected = true;
	m_layer->refreshScoreAndLinkNum(selectedList.size());
	adjustMatrix();
	if (isEnded())
	{
		m_layer->setStarsStatus(ChallengeGameLayer::Status_Over);
		m_layer->floatLeftStarMsg(getLeftStarNum());
	}
}

void ChallengeStarMatrix::refreshEveryScore(Node *node, int score)
{
	node->removeFromParentAndCleanup(true);
	m_layer->updateEveryScore(score);
}

void ChallengeStarMatrix::adjustMatrix() 
{
	//垂直方向调整
	for (int i = ROW_NUM - 1; i >= 0; i--) 
	{
		for (int j = COL_NUM - 1; j >= 0; j--) 
		{
			if (stars[i][j] == nullptr) 
			{
				int up = i;
				int dis = 0;
				while (stars[up][j] == nullptr) 
				{
					dis++;
					up--;
					if (up < 0) 
					{
						break;
					}
				}

				for (int begin_i = i - dis; begin_i >= 0; begin_i--) 
				{
					if (stars[begin_i][j] == nullptr)
						continue;
					Star* s = stars[begin_i + dis][j] = stars[begin_i][j];
					s->setIndex_ij(begin_i + dis, j);
					s->setDesPosition(getPositionByIndex(begin_i + dis, j));
					stars[begin_i][j] = nullptr;
				}
			} 
			else
			{
				continue;
			}
		}
	}
	//水平方向调整
	for (int j = 0; j < COL_NUM; j++) 
	{
		if (stars[ROW_NUM - 1][j] == nullptr) 
		{
			int des = 0;
			int right = j;
			while (stars[ROW_NUM - 1][right] == nullptr) 
			{
				des++;
				right++;
			}
			for (int begin_i = 0; begin_i < ROW_NUM; begin_i++) 
			{
				for (int begin_j = j + des; begin_j < COL_NUM; begin_j++)
				{
					if (stars[begin_i][begin_j] == nullptr)
						continue;
					Star* s = stars[begin_i][begin_j - des] = stars[begin_i][begin_j];
					s->setIndex_ij(begin_i, begin_j - des);
					s->setDesPosition(getPositionByIndex(begin_i, begin_j - des));
					stars[begin_i][begin_j] = nullptr;
 				}
			}
		}
	}

}

bool ChallengeStarMatrix::isEnded()
{
	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++) 
		{
			if (stars[i][j] == nullptr)
				continue;
			int curColor = stars[i][j]->getColor();
			//上
			if (i - 1 >= 0 && stars[i - 1][j] != nullptr && stars[i - 1][j]->getColor() == curColor)
				return false;
			//下
			if (i + 1 < ROW_NUM && stars[i + 1][j] != nullptr && stars[i + 1][j]->getColor() == curColor)
				return false;
			//左
			if (j - 1 >= 0 && stars[i][j - 1] != nullptr && stars[i][j - 1]->getColor() == curColor)
				return false;
			//右
			if (j + 1 < COL_NUM && stars[i][j + 1] != nullptr && stars[i][j + 1]->getColor() == curColor)
				return false;
		}
	}
	
	return true;
}

void ChallengeStarMatrix::clearMatrixOneByOne() 
{
	for (int i = 0; i < ROW_NUM; i++) 
	{
		for (int j = 0; j < COL_NUM; j++) 
		{
			if (backStar[i][j] != nullptr) 
			{
				backStar[i][j]->removeFromParentAndCleanup(true);
				backStar[i][j] = nullptr;
			}
			
			if (stars[i][j] == nullptr)
				continue;
			Audio::getInstance()->playPop();
			showStarParticleEffect(stars[i][j]->getColor(), stars[i][j]->getPosition(), m_particleBatchNode.at(stars[i][j]->getColor()));
			stars[i][j]->removeFromParentAndCleanup(true);
			stars[i][j] = nullptr;
			return;
		}
	}
	
	unschedule(schedule_selector(ChallengeStarMatrix::clearCallBack));
	m_layer->setStarsStatus(ChallengeGameLayer::Status_Over);
		
	//转到下一关或者弹出结束游戏的窗口
	if (m_layer->getCurScore() >= ChallengeScore)	//通关
	{
		m_layer->popOutDialog(NormalType::nGamePassed);
	}
	else
	{
		m_layer->floatFailedMove();
	}
	this->removeFromParentAndCleanup(true);
}

void ChallengeStarMatrix::clearCallBack(float f)
{
	clearSumTime += f;
	if (clearSumTime > ONE_CLEAR_TIME) 
	{
		clearMatrixOneByOne();
		clearSumTime = 0;
	}
}

void ChallengeStarMatrix::startClearStar()
{
	schedule(schedule_selector(ChallengeStarMatrix::clearCallBack));
}

int ChallengeStarMatrix::getLeftStarNum()
{
	int ret = 0;
	for (int i = 0; i < ROW_NUM; i++) 
	{
		for (int j = 0; j < COL_NUM; j++) 
		{
			if (stars[i][j] == nullptr)
				continue;
			ret++;
		}
	}
	return ret;
}

void ChallengeStarMatrix::noTouchAndWarning()
{
	if (!m_starsNext.empty())
	{
		return;
	}

	deque<deque<Star*>> previous;
	previous.clear();
	int len = 0;

	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++)
		{
			Star *s = stars[i][j];
			if (s)
			{
				m_starsNext.clear();
				getSameColorList(s, m_starsNext);
				if (len < m_starsNext.size())
				{
					len = m_starsNext.size();
					previous.clear();
					previous.push_back(m_starsNext);
				}
				else if (len == m_starsNext.size())
				{
					previous.push_back(m_starsNext);
				}
			}			
		}
	}

	m_starsNext.clear();

	if (len == 0)
	{
		return;
	}

	m_starsNext = previous.at(cocos2d::random() % len);

	for (auto it : m_starsNext)
	{
		Star *s = (Star*)it;		
		auto scale = ScaleBy::create(0.8f, 0.8f);

		backStar[s->getIndexI()][s->getIndexJ()]->setVisible(true);
		backStar[s->getIndexI()][s->getIndexJ()]->runAction(RepeatForever::create(Sequence::create(scale, scale->reverse(), nullptr)));
		s->runAction(RepeatForever::create(Sequence::create(scale->clone(), scale->reverse(), nullptr)));
	}
}

void ChallengeStarMatrix::stopStarsAction()
{
	if (!m_starsNext.empty())
	{
		for (auto it : m_starsNext)
		{
			Star *s = (Star*)it;
			if (s->getColor() < Star::Color::GREEN || s->getColor() > Star::Color::BLUE)
			{
				continue;
			}
			s->stopAllActions();
			s->setScale(1.0f);
			Sprite *back = backStar[s->getIndexI()][s->getIndexJ()];
			back->stopAllActions();
			back->setScale(1.0f);
			back->setVisible(false);
		}
		m_starsNext.clear();
	}
}

Star *ChallengeStarMatrix::createStar(int row, int col, int color, bool isMove/* =true */)
{
	Star* star = Star::create(color);
	if (isMove)
	{
		star->setPosition(getPositionByIndex(row, col) + Point(0, 100 + (ROW_NUM - row) * 7 + 5 * col + STAR_BOTTOM));
	}
	else
	{
		star->setPosition(getPositionByIndex(row, col));
	}
	star->setDesPosition(getPositionByIndex(row, col));
	star->setIndex_ij(row, col);

	return star;
}
