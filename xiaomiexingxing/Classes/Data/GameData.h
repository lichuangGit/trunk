#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_
#include <string>
#include "Data/OBEncrytionUtil.h"
#include "Const.h"
#include "../Third/UmengUpload.h"

using namespace std;

/*
*功能:	获取时间
*param:	type 0 返回天数 1 返回分钟数 2 返回秒数
*返回值:
*作者: lichuang
*日期:2015-11-10-10:39                                                                   
*/
long getCurrentDays(int type);

class GameData
{
public:
	//游戏模式
	enum GameModeType
	{
		GameNormal = 0,			//普通模式即两颗消
		GameChallenge			//挑战模式
	};

	static GameData* getInstance();
	void init(int level, int score);

	/*当前等级*/
	void setCurLevel(int level);
	int getCurLevel();
	/*下一等级*/
	int getNextLevel();
	
	/*当前分数*/
	void setCurScore(int score);
	int getCurScore();
	/*通关分数*/
	int getNextScore();
	int getScoreByLevel(int level);

	/*奖励分数*/
	int getJiangli(int size);

public:
	/*
	*功能:	设置历史最高分
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-9-30-15:01                                                                   
	*/
	void setHistoryHighestScore(int score);
	int getHistoryHighestScore();

	/*
	*功能:	设置音乐播放
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-9-30-14:51                                                                   
	*/
	void setMusicIsPlay(bool is);
	bool getMusicIsPlay();

	/*
	*功能:	获取中文字符串
	*param:	wordId	键值 path 文件路径 默认为chineseWords.xml
	*返回值:
	*作者: lichuang
	*日期:2015-8-18-16:45
	*/
	string ChineseWord(const char* wordId, string path = "ChineseWords.xml");

	/*
	*功能:	设置当前游戏模式
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-9-30-15:19                                                                   
	*/
	CC_SYNTHESIZE(GameModeType, m_curGameMode, GameMode);

	/*
	*功能:	保存物品的数量
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-12-17:28                                                                   
	*/
	void setGoodsNumber(GoodsType type, int num);
	int getGoodsNumber(GoodsType type);

	/*
	*功能:	设置或保存游戏存档
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-30-18:30                                                                   
	*/
	void setIsGameArchive(bool is);
	bool getIsGameArchive();

	/*
	*功能:	游戏是否结束
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-2-13:49                                                                   
	*/
	void setIsGameOver(bool is);
	bool getIsGameOver();

	/*
	*功能:	新游戏，重置相关参数
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-2-14:25                                                                   
	*/
	void resetParams();

	/*
	*功能:	保存上一关
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-2-16:18                                                                   
	*/
	void setPreviousLevel(int lv);
	int getPreviousLevel();

	/*
	*功能:	保存上一关分数
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-2-16:23                                                                   
	*/
	void setPreviousScore(int score);
	int getPreviousScore();

	/*
	*功能:	保存最后的等级和分数
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-4-16:02                                                                   
	*/
	void saveLastLevel();
	int getLastLevel();
	void saveLastLevelSocre(int lastLevelSorce);
	int getLastLevelSocre();

	CC_SYNTHESIZE(bool, m_isGameLoginGift, IsGameLoginGift);	//登陆礼包控制
	CC_SYNTHESIZE(bool, m_isLogin, IsLogin);					//是否可以弹签到
	CC_SYNTHESIZE(int, m_challengeZuanshi, ChallengeZuanshi);	//挑战钻石

	/*
	*功能:	免费抽奖次数
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-5-15:56                                                                   
	*/
	void setFreeLotteryConut(int count);
	int getFreeLotteryCount();

	/*
	*功能:	设置玩家是否付费
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-6-17:34                                                                   
	*/
	void setIsPay(bool is);
	bool getIsPay();

	/*
	*功能: 连续签到天数
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-10-15:58                                                                   
	*/
	void setLoginDayNum(int num);
	int getLoginDayNum();

	/*
	*功能: 上次签到时间
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-10-16:30                                                                   
	*/
	void setLoginTime(long days);
	long getLoginTime();

	/*
	*功能:	记录每日首冲时间
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-23-9:36                                                                   
	*/
	void setFirstShopTime(long days);
	long getFirstShopTime();

	/*
	*功能:	游戏时长记录
	*param:	tm 分钟
	*返回值:
	*作者: lichuang
	*日期:2015-11-24-17:15                                                                   
	*/
	void setGameDuration(long tm);
	long getGameDuration();

	/*
	*功能:	游戏时间分布区间
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-12-2-20:46                                                                   
	*/
	string getGameDurationGPD();

	/*
	*功能:	获取或设置玩家等级
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-12-6-15:50                                                                   
	*/
	void setPlayerLv(int lv);
	int getPlayerLv();

	/*
	*功能:	玩家经验值
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-12-6-16:21                                                                   
	*/
	void setExperienceValue(float vl);
	float getExperienceValue();

	float getExperienceByLv();

private:
	GameData();
	~GameData();

	/*
	*功能:	读取存放中文的文件内容，保存到ValueMap中
	*param: path 文件路径
	*返回值:
	*作者: lichuang
	*日期:2015-8-18-16:51
	*/
	void readChineseWord(string path = "ChineseWords.xml");

private:
	static GameData* _instance;

private:
	int m_curLevel;			//当前关卡
	int m_nextLevel;		//下一关卡
	int m_previousScore;	//上一关分数
	int m_previousLevel;	//上一关	
	int m_curScore;			//当前分数
	int m_nextScore;		//下一关分数
	int m_historyHighestScore;	//历史最高分
	ValueMap m_chineseMap;	//保存从存放中文文件里读取的内容
	string m_path;			//中文文件路径
	
	bool m_isGameArchive;	//游戏存档
	int m_lastLevel;		//最后关卡
	int m_lastLevelScore;	//最后关卡分数
	bool m_isGameOver;		//游戏是否结束
	int m_freeLotteryCount;	//免费抽奖次数
	map<GoodsType, int> m_goodsMap;//物品数量
	bool m_isHavePay;		//玩家是否付过费
	int m_loginDayNum;		//连续签到天数
	long m_firstPayDay;		//每日首冲时间
	long m_gameDuration;	//游戏时长
	bool m_musicIsPlay;		//音乐播放控制
	int m_iCurLv;			//玩家当前等级
	float m_iCurExperience;	//当前经验值
	float m_iCurNeedExperience;//升级下一等级所需经验值
};
#endif
