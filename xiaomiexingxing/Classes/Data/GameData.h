#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_
#include <string>
#include "Data/OBEncrytionUtil.h"
#include "Const.h"
#include "../Third/UmengUpload.h"

using namespace std;

/*
*����:	��ȡʱ��
*param:	type 0 �������� 1 ���ط����� 2 ��������
*����ֵ:
*����: lichuang
*����:2015-11-10-10:39                                                                   
*/
long getCurrentDays(int type);

class GameData
{
public:
	//��Ϸģʽ
	enum GameModeType
	{
		GameNormal = 0,			//��ͨģʽ��������
		GameChallenge			//��սģʽ
	};

	static GameData* getInstance();
	void init(int level, int score);

	/*��ǰ�ȼ�*/
	void setCurLevel(int level);
	int getCurLevel();
	/*��һ�ȼ�*/
	int getNextLevel();
	
	/*��ǰ����*/
	void setCurScore(int score);
	int getCurScore();
	/*ͨ�ط���*/
	int getNextScore();
	int getScoreByLevel(int level);

	/*��������*/
	int getJiangli(int size);

public:
	/*
	*����:	������ʷ��߷�
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-9-30-15:01                                                                   
	*/
	void setHistoryHighestScore(int score);
	int getHistoryHighestScore();

	/*
	*����:	�������ֲ���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-9-30-14:51                                                                   
	*/
	void setMusicIsPlay(bool is);
	bool getMusicIsPlay();

	/*
	*����:	��ȡ�����ַ���
	*param:	wordId	��ֵ path �ļ�·�� Ĭ��ΪchineseWords.xml
	*����ֵ:
	*����: lichuang
	*����:2015-8-18-16:45
	*/
	string ChineseWord(const char* wordId, string path = "ChineseWords.xml");

	/*
	*����:	���õ�ǰ��Ϸģʽ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-9-30-15:19                                                                   
	*/
	CC_SYNTHESIZE(GameModeType, m_curGameMode, GameMode);

	/*
	*����:	������Ʒ������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-12-17:28                                                                   
	*/
	void setGoodsNumber(GoodsType type, int num);
	int getGoodsNumber(GoodsType type);

	/*
	*����:	���û򱣴���Ϸ�浵
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-30-18:30                                                                   
	*/
	void setIsGameArchive(bool is);
	bool getIsGameArchive();

	/*
	*����:	��Ϸ�Ƿ����
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-2-13:49                                                                   
	*/
	void setIsGameOver(bool is);
	bool getIsGameOver();

	/*
	*����:	����Ϸ��������ز���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-2-14:25                                                                   
	*/
	void resetParams();

	/*
	*����:	������һ��
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-2-16:18                                                                   
	*/
	void setPreviousLevel(int lv);
	int getPreviousLevel();

	/*
	*����:	������һ�ط���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-2-16:23                                                                   
	*/
	void setPreviousScore(int score);
	int getPreviousScore();

	/*
	*����:	�������ĵȼ��ͷ���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-4-16:02                                                                   
	*/
	void saveLastLevel();
	int getLastLevel();
	void saveLastLevelSocre(int lastLevelSorce);
	int getLastLevelSocre();

	CC_SYNTHESIZE(bool, m_isGameLoginGift, IsGameLoginGift);	//��½�������
	CC_SYNTHESIZE(bool, m_isLogin, IsLogin);					//�Ƿ���Ե�ǩ��
	CC_SYNTHESIZE(int, m_challengeZuanshi, ChallengeZuanshi);	//��ս��ʯ

	/*
	*����:	��ѳ齱����
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-5-15:56                                                                   
	*/
	void setFreeLotteryConut(int count);
	int getFreeLotteryCount();

	/*
	*����:	��������Ƿ񸶷�
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-6-17:34                                                                   
	*/
	void setIsPay(bool is);
	bool getIsPay();

	/*
	*����: ����ǩ������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-10-15:58                                                                   
	*/
	void setLoginDayNum(int num);
	int getLoginDayNum();

	/*
	*����: �ϴ�ǩ��ʱ��
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-10-16:30                                                                   
	*/
	void setLoginTime(long days);
	long getLoginTime();

	/*
	*����:	��¼ÿ���׳�ʱ��
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-23-9:36                                                                   
	*/
	void setFirstShopTime(long days);
	long getFirstShopTime();

	/*
	*����:	��Ϸʱ����¼
	*param:	tm ����
	*����ֵ:
	*����: lichuang
	*����:2015-11-24-17:15                                                                   
	*/
	void setGameDuration(long tm);
	long getGameDuration();

	/*
	*����:	��Ϸʱ��ֲ�����
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-12-2-20:46                                                                   
	*/
	string getGameDurationGPD();

	/*
	*����:	��ȡ��������ҵȼ�
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-12-6-15:50                                                                   
	*/
	void setPlayerLv(int lv);
	int getPlayerLv();

	/*
	*����:	��Ҿ���ֵ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-12-6-16:21                                                                   
	*/
	void setExperienceValue(float vl);
	float getExperienceValue();

	float getExperienceByLv();

private:
	GameData();
	~GameData();

	/*
	*����:	��ȡ������ĵ��ļ����ݣ����浽ValueMap��
	*param: path �ļ�·��
	*����ֵ:
	*����: lichuang
	*����:2015-8-18-16:51
	*/
	void readChineseWord(string path = "ChineseWords.xml");

private:
	static GameData* _instance;

private:
	int m_curLevel;			//��ǰ�ؿ�
	int m_nextLevel;		//��һ�ؿ�
	int m_previousScore;	//��һ�ط���
	int m_previousLevel;	//��һ��	
	int m_curScore;			//��ǰ����
	int m_nextScore;		//��һ�ط���
	int m_historyHighestScore;	//��ʷ��߷�
	ValueMap m_chineseMap;	//����Ӵ�������ļ����ȡ������
	string m_path;			//�����ļ�·��
	
	bool m_isGameArchive;	//��Ϸ�浵
	int m_lastLevel;		//���ؿ�
	int m_lastLevelScore;	//���ؿ�����
	bool m_isGameOver;		//��Ϸ�Ƿ����
	int m_freeLotteryCount;	//��ѳ齱����
	map<GoodsType, int> m_goodsMap;//��Ʒ����
	bool m_isHavePay;		//����Ƿ񸶹���
	int m_loginDayNum;		//����ǩ������
	long m_firstPayDay;		//ÿ���׳�ʱ��
	long m_gameDuration;	//��Ϸʱ��
	bool m_musicIsPlay;		//���ֲ��ſ���
	int m_iCurLv;			//��ҵ�ǰ�ȼ�
	float m_iCurExperience;	//��ǰ����ֵ
	float m_iCurNeedExperience;//������һ�ȼ����辭��ֵ
};
#endif
