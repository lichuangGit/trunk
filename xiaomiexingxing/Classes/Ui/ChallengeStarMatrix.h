#ifndef CHALLENGESTARMATRIX_H
#define CHALLENGESTARMATRIX_H
#include "cocos2d.h"
#include "Star.h"
#include "ChallengeGameLayer.h"
#include "StarParticle.h"
#include <deque>

USING_NS_CC;
using namespace std;
class ChallengeGameLayer;

class ChallengeStarMatrix : public Node
{
public:
	
	ChallengeStarMatrix();
	~ChallengeStarMatrix();

	static ChallengeStarMatrix* create(ChallengeGameLayer* layer);

	virtual bool init(ChallengeGameLayer* layer);

	void initMatrix();

	void updateStar(float f);

	/*
	*功能:	触摸星星处理
	*param:	true 表示点击到星星所在区域 反之false 
	*返回值:
	*作者: lichuang
	*日期:2015-10-16-14:29                                                                   
	*/
	bool onTouch(const Vec2& p);
	
	/*
		判断是否还有星星相连
	*/
	bool isEnded();

	/*
		消除剩余星星
	*/
	void clearMatrixOneByOne();

	/*
		消除星星定时回调
	*/
	void clearCallBack(float f);

	/*
	*功能:	游戏本关结束时，剩余星星播放破碎效果
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-9-17:37                                                                   
	*/
	void startClearStar();

	/*
	*功能:	游戏结束时获取剩余星星个数
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-9-16:39                                                                   
	*/
	int getLeftStarNum();

	/*
	*功能:	显示数量最多的星星
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-4-16:31                                                                   
	*/
	void noTouchAndWarning();

	/*
	*功能:	停止触摸星星闪闪提示
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-4-17:44                                                                   
	*/
	void stopStarsAction();

private:
   	Point getPositionByIndex(int i,int j);
	Star* getStarByTouch(const Point& p);
	void getSelectedList(Star* s);
	void getSameColorList(Star* s, deque<Star*> &result);
	void deleteSelectedListDelay(float f);			//播放星星破碎效果
	void adjustMatrix();
	void refreshEveryScore(Node *node, int score);

	Star *createStar(int row, int col, int color, bool isMove=true);

private:
	Star* stars[ROW_NUM][COL_NUM];
	Sprite* backStar[ROW_NUM][COL_NUM];

	deque<Star*> selectedList;
	deque<Star*> m_starsNext;
	int currentSelectedNum; //当前显示删除动画的星星
	ChallengeGameLayer* m_layer;
	float clearSumTime;
	
	bool isStarSeclected;

	SpriteBatchNode *m_starBatchNode;
	Vector<ParticleBatchNode *> m_particleBatchNode;
};
#endif
