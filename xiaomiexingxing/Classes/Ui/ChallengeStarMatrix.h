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
	*����:	�������Ǵ���
	*param:	true ��ʾ����������������� ��֮false 
	*����ֵ:
	*����: lichuang
	*����:2015-10-16-14:29                                                                   
	*/
	bool onTouch(const Vec2& p);
	
	/*
		�ж��Ƿ�����������
	*/
	bool isEnded();

	/*
		����ʣ������
	*/
	void clearMatrixOneByOne();

	/*
		�������Ƕ�ʱ�ص�
	*/
	void clearCallBack(float f);

	/*
	*����:	��Ϸ���ؽ���ʱ��ʣ�����ǲ�������Ч��
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-9-17:37                                                                   
	*/
	void startClearStar();

	/*
	*����:	��Ϸ����ʱ��ȡʣ�����Ǹ���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-9-16:39                                                                   
	*/
	int getLeftStarNum();

	/*
	*����:	��ʾ������������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-4-16:31                                                                   
	*/
	void noTouchAndWarning();

	/*
	*����:	ֹͣ��������������ʾ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-4-17:44                                                                   
	*/
	void stopStarsAction();

private:
   	Point getPositionByIndex(int i,int j);
	Star* getStarByTouch(const Point& p);
	void getSelectedList(Star* s);
	void getSameColorList(Star* s, deque<Star*> &result);
	void deleteSelectedListDelay(float f);			//������������Ч��
	void adjustMatrix();
	void refreshEveryScore(Node *node, int score);

	Star *createStar(int row, int col, int color, bool isMove=true);

private:
	Star* stars[ROW_NUM][COL_NUM];
	Sprite* backStar[ROW_NUM][COL_NUM];

	deque<Star*> selectedList;
	deque<Star*> m_starsNext;
	int currentSelectedNum; //��ǰ��ʾɾ������������
	ChallengeGameLayer* m_layer;
	float clearSumTime;
	
	bool isStarSeclected;

	SpriteBatchNode *m_starBatchNode;
	Vector<ParticleBatchNode *> m_particleBatchNode;
};
#endif
