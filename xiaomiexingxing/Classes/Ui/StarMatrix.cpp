#include "StarMatrix.h"
#include "Data/GameData.h"
#include "Core/ComboEffect.h"
#include "Data/GameData.h"
#include "Core/CCShake.h"
#include "ShadeLayer.h"

string starpath[] = { "green_bum.png", "red_bum.png", "orange_bum.png", "purple_bum.png", "blue_bum.png" };

StarMatrix::StarMatrix():
clearSumTime(0),
m_layer(nullptr),
m_starBatchNode(nullptr),
isStarSeclected(true)
{
	m_particleBatchNode.clear();
	m_vecSaveStars.clear();
	m_starsNext.clear();
}

StarMatrix::~StarMatrix()
{
	unschedule(schedule_selector(StarMatrix::updateStar));
}

StarMatrix* StarMatrix::create(GameLayer* layer) 
{
	StarMatrix* ret = new StarMatrix();
	if (ret && ret->init(layer))
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);

	return nullptr;
}

bool StarMatrix::init(GameLayer* layer) 
{
	if (!Node::init()) 
	{
		return false;
	}

	m_layer = layer;
	memset(stars, 0, sizeof(Star*) * ROW_NUM * COL_NUM);
	memset(backStar, 0, sizeof(Sprite*) * ROW_NUM * COL_NUM);
	m_layer->setStarsStatus(GameLayer::Status_Ready);

	initMatrix();

	schedule(schedule_selector(StarMatrix::updateStar));

	return true;
}

bool isCheckJsonStr(string jsonStr)
{
	string str = jsonStr;
	int num = 0;

	if (jsonStr.empty())
	{
		return true;
	}

	while (1)
	{
		int re = str.find_first_of("-1", 0);
		if (re != string::npos)
		{
			num++;
			str = str.substr(re + 2, str.length() - re - 2);
		}
		else
		{
			break;
		}
	}

	if (num == ROW_NUM * COL_NUM)
	{
		return true;
	}

	return false;
}

void StarMatrix::initMatrix()
{
	m_starBatchNode = SpriteBatchNode::createWithTexture(TextureCache::getInstance()->getTextureForKey("star.png"));
	this->addChild(m_starBatchNode);

	for (int i = 0; i < COLOR_MAX_NUM; i++)
	{
		ParticleBatchNode *node = ParticleBatchNode::createWithTexture(TextureCache::getInstance()->getTextureForKey(starpath[i]));
		this->addChild(node);
		m_particleBatchNode.pushBack(node);
	}

	if (GameData::getInstance()->getIsGameArchive())
	{
		GameData::getInstance()->setIsGameArchive(false);
		
		string jsonStr = JsonUtils::getInstance()->getStringFromeFile(JsonUtils::getInstance()->getSavePath());
		JsonUtils::getInstance()->clearFile();

		if (!isCheckJsonStr(jsonStr))
		{
			//检测字符串
			for (int i = 0; i < ROW_NUM; i++)
			{
				string str = "row";
				str = str + cocos2d::CCString::createWithFormat("%d", i)->getCString();
				for (int j = 0; j < COL_NUM; j++)
				{
					string row = jsonStr.substr(0, jsonStr.find_first_of("}", 0) + 1);
					jsonStr = jsonStr.erase(0, jsonStr.find_first_of("}", 0) + 1);

					string str1 = str + "col" + cocos2d::CCString::createWithFormat("%d", j)->getCString();
					int color = JsonUtils::getInstance()->getIntFromeJson(row, str1);
					if (color != -1)
					{
						stars[i][j] = createStar(i, j, color);
						m_starBatchNode->addChild(stars[i][j]);
						backStar[i][j] = Sprite::createWithSpriteFrameName("black.png");
						backStar[i][j]->setPosition(getPositionByIndex(i, j));
						m_starBatchNode->addChild(backStar[i][j]);
						backStar[i][j]->setVisible(false);
					}					
				}
			}
		}

		return;
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

void StarMatrix::updateStar(float f) 
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
		if (m_layer->getStarsStatus() == GameLayer::Status_Ready || m_layer->getStarsStatus() == GameLayer::Status_Activity)
		{
			m_layer->onTouchEnded(nullptr, nullptr);
		}
		if (m_layer->getCurTouchStatus() != GameLayer::Touch_Chexiao && m_layer->getCurTouchStatus() != GameLayer::Touch_Shuanxin && m_layer->getStarsStatus() != GameLayer::Status_Over)
		{
			m_layer->setStarsStatus(GameLayer::Status_NoActivity);
		}
	}
}

bool StarMatrix::onTouch(const Vec2& p) 
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

		switch (m_layer->getCurTouchStatus())
		{
		case GameLayer::Touch_Normal:
			getSelectedList(s);
			break;
		case GameLayer::Touch_Bomb:
			getBombSelectedList(s);
			break;
		case GameLayer::Touch_Tongsexiao:
			getSameColorSelectedList(s);
			break;
		case GameLayer::Touch_Huanse:
			backStar[s->getIndexI()][s->getIndexJ()]->setVisible(true);
			neadChangeColorStar = s;
			s->setScale(0.8f);
			{
				auto layer = ShadeLayer::create(s->getColor());
				this->addChild(layer);
			}
			return true;
		case GameLayer::Touch_Chexiao:
			break;
		case GameLayer::Touch_Shuanxin:
			break;
		}

		currentSelectedNum = 0;
		
		m_layer->updateTouchStatus(GameLayer::Touch_Normal);
		m_layer->updateGoodsNumberByTouchStatus();
		m_layer->setStarsStatus(GameLayer::Status_Activity);

		if (selectedList.size() > 1 ||(selectedList.size() == 1 && m_layer->getPreviousTouchStatus() == GameLayer::Touch_Tongsexiao))
		{
			saveStars();
		}

		if (selectedList.size() > 0)
		{
			schedule(schedule_selector(StarMatrix::deleteSelectedListDelay), ONE_CLEAR_TIME, selectedList.size() - 1, 0.05f);
		}

		return true;
	}
}

void StarMatrix::updateStarColor(int color, bool isComplete/* =false */, bool isChange/* =false */)
{
	if (neadChangeColorStar != nullptr)
	{
		int i = 0, j = 0;

		i = neadChangeColorStar->getIndexI();
		j = neadChangeColorStar->getIndexJ();
		if (color != -1)
		{
			//移除之前的
			stars[i][j]->removeFromParentAndCleanup(true);
			stars[i][j] = nullptr;

			stars[i][j] = createStar(i, j, color, false);
			m_starBatchNode->addChild(stars[i][j]);
		}
		
		if (isComplete)
		{
			backStar[i][j]->setVisible(false);
			stars[i][j]->setScale(1.0f);
			if (isChange)
			{
				saveStars(i, j, isChange);
				//扣钻
				m_layer->updateTouchStatus(GameLayer::Touch_Normal);
				m_layer->updateGoodsNumberByTouchStatus();
			}
			m_layer->setIsPropUse(false);
			m_layer->onTouchEnded(nullptr, nullptr);
			neadChangeColorStar = nullptr;
			isStarSeclected = true;
		}
		else
		{
			backStar[i][j]->setVisible(true);
			stars[i][j]->setScale(0.8f);
		}
	}
}

Point StarMatrix::getPositionByIndex(int i, int j)
{
	float x = j * REAL_STAR_WIDTH + REAL_STAR_WIDTH / 2;
	float y = (COL_NUM - i) * REAL_STAR_HEIGHT - REAL_STAR_HEIGHT / 2 + STAR_BOTTOM;
	return Vec2(x, y);
}

Star* StarMatrix::getStarByTouch(const Point& p)
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

void StarMatrix::getSameColorList(Star* s, deque<Star*> &result)
{
	//deque<Star*> select;
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

void StarMatrix::getSelectedList(Star* s)
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

//顺序播放星星破碎的效果
void StarMatrix::deleteSelectedListDelay(float f) 
{
	if (selectedList.size() <= 1 && m_layer->getPreviousTouchStatus() != GameLayer::Touch_Tongsexiao)
	{
		backStar[selectedList.at(0)->getIndexI()][selectedList.at(0)->getIndexJ()]->setVisible(false);
		selectedList.at(0)->setSelected(false);

		isStarSeclected = true;

		m_layer->setIsPropUse(false);
		m_layer->setStarsStatus(GameLayer::Status_NoActivity);
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
		auto callback = CallFuncN::create(CC_CALLBACK_1(StarMatrix::refreshEveryScore, this, 10 * (currentSelectedNum + 1) - 5));
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
		m_layer->setStarsStatus(GameLayer::Status_Over);
		m_layer->floatLeftStarMsg(getLeftStarNum());
	}
	else
	{
		m_layer->setIsPropUse(false);
	}
}

void StarMatrix::refreshEveryScore(Node *node, int score)
{
	node->removeFromParentAndCleanup(true);
	m_layer->updateEveryScore(score);
}

void StarMatrix::adjustMatrix() 
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

bool StarMatrix::isEnded()
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

void StarMatrix::clearMatrixOneByOne() 
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
	
	unschedule(schedule_selector(StarMatrix::clearCallBack));
	m_layer->setStarsStatus(GameLayer::Status_Over);

	//转到下一关或者弹出结束游戏的窗口
	if (GameData::getInstance()->getCurScore() >= GameData::getInstance()->getNextScore())	//通关
	{		
		if (GameData::getInstance()->getNextLevel() % 2 != 0)
		{
			UmengUpload::finishLevel(String::createWithFormat("level_%d", GameData::getInstance()->getNextLevel())->getCString());
			m_layer->popOutDialog(NormalType::nGamePassed);
		}
		else
		{
			UmengUpload::failLevel(String::createWithFormat("level_%d", GameData::getInstance()->getNextLevel())->getCString());
			m_layer->popOutDialog(PayType::pGamePassed);
		}
	}
	else
	{
		m_layer->popOutDialog(PayType::pGameFailed);
	}
	this->removeFromParentAndCleanup(true);
}

void StarMatrix::clearCallBack(float f)
{
	clearSumTime += f;
	if (clearSumTime > ONE_CLEAR_TIME) 
	{
		clearMatrixOneByOne();
		clearSumTime = 0;
	}
}

void StarMatrix::startClearStar()
{
	schedule(schedule_selector(StarMatrix::clearCallBack));
}

int StarMatrix::getLeftStarNum()
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

void StarMatrix::noTouchAndWarning()
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

void StarMatrix::stopStarsAction()
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

Star *StarMatrix::createStar(int row, int col, int color, bool isMove/* =true */)
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

void StarMatrix::restoreNewStars(int row, int col, int color)
{
	/*if (stars[row][col]) 这段代码有点武断鲁莽，先删除所有星星，再重新创建
	{
		stars[row][col]->removeFromParentAndCleanup(true);
		stars[row][col] = nullptr;
	}

	if (color != -1)
	{
		stars[row][col] = createStar(row, col, color, false);
		stars[row][col]->setOpacity(0);
		stars[row][col]->runAction(FadeIn::create(0.5f));
		m_starBatchNode->addChild(stars[row][col]);
		backStar[row][col]->setVisible(false);
	}*/

	//下面这段代码，如果前后两次星星颜色一致，无需经过删除再创建，只需执行动作
	if (stars[row][col] && color != -1 && stars[row][col]->getColor() != color)//其位置不为空，且前后两次星星颜色不一致时，移除
	{
		stars[row][col]->removeFromParentAndCleanup(true);
	}

	if (color != -1 && (stars[row][col] == nullptr || stars[row][col]->getColor() != color))//上次有效颜色，且和本次不同或本次为空
	{
		stars[row][col] = createStar(row, col, color, false);
		stars[row][col]->setOpacity(0);
		m_starBatchNode->addChild(stars[row][col]);
	}

	if (backStar[row][col]->isVisible())
	{
		backStar[row][col]->setVisible(false);
	}

	if (stars[row][col])
	{
		stars[row][col]->runAction(Sequence::create(FadeIn::create(0.2f), nullptr));
	}
}

bool StarMatrix::restorePreviousStars()
{
	if (m_vecSaveStars.empty())
	{
		return false;
	}


	std::map<int, vector<int>> temp = m_vecSaveStars.at(m_vecSaveStars.size() - 1);

	for (int i = 0; i < ROW_NUM; i++)
	{
		vector<int> vec = temp.at(i);
		for (int j = 0; j < COL_NUM; j++)
		{
			auto call = CallFunc::create(CC_CALLBACK_0(StarMatrix::restoreNewStars, this, i, j, vec.at(j)));
			if (stars[i][j] != nullptr)
			{
				stars[i][j]->runAction(Sequence::create(FadeOut::create(0.2f), call, nullptr));
			}
			else
			{
				this->runAction(Sequence::create(DelayTime::create(0.2f), call, nullptr));
			}
		}
	}

	m_vecSaveStars.pop_back();
	
	return true;
}

void StarMatrix::saveStars(int rowIndex /* = 0 */, int colIndex /* = 0 */, bool isCheck /* = false */)
{
	std::map<int, vector<int>> temp;
	for (int i = 0; i < ROW_NUM; i++)
	{
		std::vector<int> row;
		for (int j = 0; j < COL_NUM; j++)
		{
			if (stars[i][j] != nullptr)
				row.push_back(stars[i][j]->getColor());
			else
				row.push_back(-1);

			if (isCheck && rowIndex == i && colIndex == j)
			{
				row.pop_back();
				row.push_back(neadChangeColorStar->getColor());
			}
		}
		temp.insert(pair<int, vector<int>>(i, row));
	}
	m_vecSaveStars.push_back(temp);
}

void StarMatrix::saveStarAtExitGame()
{
	JsonUtils::getInstance()->clearFile();

	for (int i = 0; i < ROW_NUM; i++)
	{
		std::vector<int> row;
		string str = "row";
		str = str + cocos2d::CCString::createWithFormat("%d", i)->getCString();

		for (int j = 0; j < COL_NUM; j++)
		{
			string str1 = str + "col" + cocos2d::CCString::createWithFormat("%d", j)->getCString();
			if (stars[i][j] != nullptr)
				JsonUtils::getInstance()->setIntToJson(str1, stars[i][j]->getColor());
			else
				JsonUtils::getInstance()->setIntToJson(str1, -1);
		}
	}

	JsonUtils::getInstance()->saveData();
}

void StarMatrix::getBombSelectedList(Star* s) 
{
	selectedList.clear();
	int index_i = s->getIndexI();
	int index_j = s->getIndexJ();

	//在以被点中的星星为中心的5X5的范围内，记录存在的星星
	for (int i = index_i - Bomb_Range; i <= index_i + Bomb_Range; ++i)
	{
		for (int j = index_j - Bomb_Range; j <= index_j + Bomb_Range; ++j) 
		{
			if ((i >= 0 && i <= 9) && (j >= 0 && j <= 9))
			{
				if (stars[i][j] != nullptr) 
				{
					selectedList.push_back(stars[i][j]);
				}
			}
		}
	}
}

void StarMatrix::getSameColorSelectedList(Star* s)
{
	selectedList.clear();
	int color = s->getColor();

	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++)
		{
			if (stars[i][j] != nullptr && stars[i][j]->getColor() == color)
			{
				selectedList.push_back(stars[i][j]);
			}
		}
	}
}

void StarMatrix::handlerRefurbish() 
{
	saveStars();

	vector<int> existColor;
	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++)
		{
			if (existColor.size() == COLOR_MAX_NUM)
			{
				break;
			}
			if (stars[i][j] != nullptr)
			{
				int color = stars[i][j]->getColor();
				if (std::find(existColor.begin(),existColor.end(),color) == existColor.end())
				{
					existColor.push_back(color);
				}
			}
		}
	}

	int size = existColor.size();

	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++) 
		{
			if (stars[i][j] != nullptr)
			{
				auto call = CallFunc::create(CC_CALLBACK_0(StarMatrix::restoreNewStars, this, i, j, existColor.at(cocos2d::random()%size)));
				stars[i][j]->runAction(Sequence::create(FadeOut::create(0.2f), call, nullptr));
			}
		}
	}
}
