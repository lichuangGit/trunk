#include "Data/GameData.h"
#include "cocos2d.h"

USING_NS_CC;

GameData* GameData::_instance = nullptr;

long getCurrentDays(int type)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	struct timeval now;

	gettimeofday(&now, NULL);
	if (type == 0)
	{
		return now.tv_sec / (60 * 60 * 24);
	}
	else if (type == 1)
	{
		return now.tv_sec / 60;
	}
	else
	{
		return now.tv_sec;
	}
#else
	time_t timep;

	time(&timep);
	if (type == 0)
	{
		return timep / (60 * 60 * 24);
	}
	else if (type == 1)
	{
		return timep / 60;
	}
	else
	{
		return timep;
	}
#endif
}

GameData::GameData()
{
	m_isGameArchive = LoadBooleanFormXML("oiolisgamlkenarjchihdfve", false);
	m_historyHighestScore = getHistoryHighestScore();
	m_lastLevel = LoadIntergerFormXML("lastLevel", 0);
	m_lastLevelScore = LoadIntergerFormXML("lastLevelSorce", 0);
	m_isGameOver = LoadBooleanFormXML("ythbgajmeokvenbnbr", false);
	m_previousLevel = LoadIntergerFormXML("phgjrejviouklsulllkcvcx", 0);
	m_previousScore = LoadIntergerFormXML("dtrhbgprjhevlkiousplscweormneb", 0);
	m_isGameLoginGift = true;
	m_freeLotteryCount = LoadIntergerFormXML("dfrevcxelotteiujrycoupmnbnt", 0);
	m_isHavePay = LoadBooleanFormXML("yifgsgdjipuimaqwqywexc", false);
	m_loginDayNum = LoadIntergerFormXML("yhlfohugghojindaeercy", 0);
	m_isLogin = true;
	m_firstPayDay = LoadIntergerFormXML("tyfiytyhtrsjjtshjkhnmobbp", 0);
	m_challengeZuanshi = 0;
	m_gameDuration = LoadIntergerFormXML("gdfafgtrmehjdukjratlnbvioyn", 0);
	m_musicIsPlay = LoadBooleanFormXML("mufasicdfdfprrldfafyg", true);
	m_iCurLv = LoadIntergerFormXML("rfdplfdacygehrljfreveoknjlt", 0);
	m_iCurExperience = LoadIntergerFormXML("dfteumnxpmnbvriencesvalrcvbue", 0);

	m_iCurNeedExperience = (m_iCurLv + 1) * 1000;

	for (int i = 1; i <= GoodsType::Zuanshi;i++)
	{
		String *str = String::createWithFormat("jjjgdmtytrovoddtdfdaydfp%de", i);
		m_goodsMap.insert(pair<GoodsType, int>((GoodsType)i, LoadIntergerFormXML(str->getCString(), i == GoodsType::Tongsexiao ? 1 : 0)));
	}

	this->init(0, 0);
}

GameData* GameData::getInstance()
{
	if (_instance == 0)
	{
		_instance = new GameData();
	}
	return _instance;
}

void GameData::init(int level, int socre)
{
	setIsGameOver(false);
	setCurLevel(level);
	setCurScore(socre);
}

void GameData::setCurLevel(int level)
{
	if (level < 0)
	{
		return;
	}
	setPreviousLevel(m_curLevel);
	m_curLevel = level;
	m_nextLevel = level + 1;
	m_nextScore = getScoreByLevel(m_nextLevel);
}

int GameData::getCurLevel()
{
	return m_curLevel;
}

int GameData::getNextLevel()
{
	return m_nextLevel;
}

void GameData::setCurScore(int score)
{
	m_curScore = score;
}

int GameData::getCurScore()
{
	return m_curScore;
}

int GameData::getNextScore()
{
	return m_nextScore;
}

int GameData::getScoreByLevel(int level)
{
	int score = 0;
	if (level == 1)
	{
		score = 500;
	}
	else if (level == 2)
	{
		score = 2000;
	}
	else if (level == 3)
	{
		score = 6000;
	}
	else if((level >= 4) && (level <= 8))
	{
		score = 6000 + 3000 * (level - 3);
	}
	else if ((level >= 9) && (level <= 14))
	{
		score = 21000 + 3500 * (level - 8);
	}
	else
	{
		score = 42000 + 4000 * (level - 14);
	}
	return score;
}

int GameData::getJiangli(int size)
{
	int jiangli[10][2] =
	{
		{ 0, 2000 },
		{ 1, 1980 },
		{ 2, 1920 },
		{ 3, 1820 },
		{ 4, 1680 },
		{ 5, 1500 },
		{ 6, 1280 },
		{ 7, 1020 },
		{ 8, 720 },
		{ 9, 380 }
	};

	if (size > 9 || size < 0)
	{
		return 0;
	}
	return jiangli[size][1];
}

void GameData::saveLastLevel()
{
	SaveIntegerToXML("lastLevel", m_curLevel);
	m_lastLevel = m_curLevel;
}
int GameData::getLastLevel()
{
	return m_lastLevel;
}

void GameData::saveLastLevelSocre(int lastLevelSorce)
{
	SaveIntegerToXML("lastLevelSorce", lastLevelSorce);
	m_lastLevelScore = lastLevelSorce;
}

int GameData::getLastLevelSocre()
{
	return m_lastLevelScore;
}

void GameData::setFreeLotteryConut(int count)
{
	SaveIntegerToXML("dfrevcxelotteiujrycoupmnbnt", count);
	m_freeLotteryCount = count;
}

int GameData::getFreeLotteryCount()
{
	return m_freeLotteryCount;
}

void GameData::setIsPay(bool is)
{
	SaveBooleanToXML("yifgsgdjipuimaqwqywexc", is);
	m_isHavePay = is;
}

bool GameData::getIsPay()
{
	return m_isHavePay;
}

void GameData::setLoginDayNum(int num)
{
	SaveIntegerToXML("yhlfohugghojindaeercy", num);
	m_loginDayNum = num;
}

int GameData::getLoginDayNum()
{
	return m_loginDayNum;
}

void GameData::setLoginTime(long days)
{
	SaveIntegerToXML("yglrterohgrthfintuikmimme", days);
}

long GameData::getLoginTime()
{
	return LoadIntergerFormXML("yglrterohgrthfintuikmimme", 0);
}

void GameData::setFirstShopTime(long days)
{
	SaveIntegerToXML("tyfiytyhtrsjjtshjkhnmobbp", days);
	m_firstPayDay = days;
}

long GameData::getFirstShopTime()
{
	return m_firstPayDay;
}

void GameData::setGameDuration(long tm)
{
	SaveIntegerToXML("gdfafgtrmehjdukjratlnbvioyn", tm);
	m_gameDuration = tm;
}

long GameData::getGameDuration()
{
	return m_gameDuration;
}

string GameData::getGameDurationGPD()
{
	if (m_gameDuration > 0 && m_gameDuration <= 5)
	{
		return "0~5";
	}
	else if (m_gameDuration > 5 && m_gameDuration <= 15)
	{
		return "5~15";
	}
	else if (m_gameDuration > 15 && m_gameDuration <= 30)
	{
		return "15~30";
	}
	else if (m_gameDuration > 30 && m_gameDuration <= 60)
	{
		return "30~60";
	}
	else if (m_gameDuration > 60 && m_gameDuration <= 120)
	{
		return "60~120";
	}
	else if (m_gameDuration > 120 && m_gameDuration <= 240)
	{
		return "120~240";
	}
	else
	{
		return "240+";
	}
}

void GameData::setPlayerLv(int lv)
{
	SaveIntegerToXML("rfdplfdacygehrljfreveoknjlt", lv);
	m_iCurLv = lv;
	m_iCurNeedExperience = (m_iCurLv + 1) * 10000;
	UmengUpload::setLevel(String::createWithFormat("level_%d", lv)->getCString());
	map<string, string> _map;
	_map["playTime"] = getGameDurationGPD();
	UmengUpload::event(Umeng_Id_Upgrade, &_map);
}

int GameData::getPlayerLv()
{
	return m_iCurLv;
}

void GameData::setExperienceValue(float
	vl)
{
	SaveIntegerToXML("dfteumnxpmnbvriencesvalrcvbue", vl);
	m_iCurExperience = vl;
}

float GameData::getExperienceValue()
{
	return m_iCurExperience;
}

float GameData::getExperienceByLv()
{
	return m_iCurNeedExperience;
}

void GameData::setHistoryHighestScore(int score)
{
	SaveIntegerToXML("dfdHfdfistdfdfovryHihughhgfestShnmxcoiuikre", score);
}

int GameData::getHistoryHighestScore()
{
	return LoadIntergerFormXML("dfdHfdfistdfdfovryHihughhgfestShnmxcoiuikre", 0);
}

void GameData::setMusicIsPlay(bool is)
{
	SaveBooleanToXML("mufasicdfdfprrldfafyg", is);
	m_musicIsPlay = is;
}

bool GameData::getMusicIsPlay()
{
	return m_musicIsPlay;
}

string GameData::ChineseWord(const char* wordId, string path)
{
	if (m_path != path)
	{
		readChineseWord(path);
	}
	return m_chineseMap.at(wordId).asString();
}

void GameData::setGoodsNumber(GoodsType type, int num)
{
	String *str = String::createWithFormat("jjjgdmtytrovoddtdfdaydfp%de", type);
	SaveIntegerToXML(str->getCString(), num);
	m_goodsMap[type] = num;
}

int GameData::getGoodsNumber(GoodsType type)
{
	return m_goodsMap[type];
}

void GameData::setIsGameArchive(bool is)
{
	SaveBooleanToXML("oiolisgamlkenarjchihdfve", is);
	m_isGameArchive = is;
}

bool GameData::getIsGameArchive()
{
	return m_isGameArchive;
}

void GameData::setIsGameOver(bool is)
{
	SaveBooleanToXML("ythbgajmeokvenbnbr", is);
	m_isGameOver = is;
}

bool GameData::getIsGameOver()
{
	return m_isGameOver;
}

void GameData::resetParams()
{
	setIsGameArchive(false);
	setIsGameOver(false);
	setCurLevel(0);
	setCurScore(0);
	m_previousScore = 0;
}

void GameData::setPreviousLevel(int lv)
{
	SaveIntegerToXML("phgjrejviouklsulllkcvcx", lv);
	m_previousLevel = lv;
}

int GameData::getPreviousLevel()
{
	return m_previousLevel;
}

void GameData::setPreviousScore(int score)
{
	SaveIntegerToXML("dtrhbgprjhevlkiousplscweormneb", score);
	m_previousScore = score;
}

int GameData::getPreviousScore()
{
	return m_previousScore;
}

void GameData::readChineseWord(string path)
{
	if (m_path != path)
	{
		m_path = path;
		m_chineseMap.clear();
		ValueVector txt_vec = FileUtils::getInstance()->getValueVectorFromFile(path);
		m_chineseMap = txt_vec.at(0).asValueMap();
	}
}