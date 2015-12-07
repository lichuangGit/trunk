#ifndef _STARMATRIX_H_
#define _STARMATRIX_H_
#include "cocos2d.h"
#include "Star.h"
#include "GameLayer.h"
#include "StarParticle.h"
#include <deque>
#include "Data/JsonUtils.h"

USING_NS_CC;
using namespace std;
class GameLayer;

class StarMatrix : public Node
{
public:
	
	StarMatrix();
	~StarMatrix();

	static StarMatrix* create(GameLayer* layer);

	virtual bool init(GameLayer* layer);

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

	void handlerRefurbish();

	/*
	*功能:	恢复上次的星星布局
	*param: 
	*返回值: true 表示有星星需要恢复， false 无星星需要恢复
	*作者: lichuang
	*日期:2015-10-29-15:40                                                                   
	*/
	bool restorePreviousStars();

	/*
	*功能:	星星破碎前，保存星星的布局
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-2-12:50                                                                   
	*/
	void saveStars(int rowIndex = 0, int colIndex = 0, bool isCheck = false);

	/*
	*功能:	离开游戏页面时，将星星布局保存到json文件
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-2-12:51                                                                   
	*/
	void saveStarAtExitGame();
	
	/*
		更新星星颜色
	*/
	void updateStarColor(int color, bool isComplete=false, bool isChange=false);
	
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
	void getBombSelectedList(Star* s);
	void getSameColorSelectedList(Star* s);

	Star *createStar(int row, int col, int color, bool isMove=true);

	/*
	*功能:	恢复某个位置上次颜色的星星
	*param: row 行 col 列 color 上次颜色
	*返回值:
	*作者: lichuang
	*日期:2015-10-29-14:58                                                                   
	*/
	void restoreNewStars(int row, int col, int color);

public:	
	std::vector<vector<vector<int>>> startsIndexVec;	

private:
	Star* stars[ROW_NUM][COL_NUM];
	Sprite* backStar[ROW_NUM][COL_NUM];

	deque<Star*> selectedList;
	deque<Star*> m_starsNext;
	int currentSelectedNum; //当前显示删除动画的星星
	GameLayer* m_layer;
	float clearSumTime;
	
	bool isStarSeclected;
	Star *neadChangeColorStar;

	SpriteBatchNode *m_starBatchNode;
	Vector<ParticleBatchNode *> m_particleBatchNode;
	vector<map<int, vector<int>>> m_vecSaveStars;	//保存星星布局
};
#endif
