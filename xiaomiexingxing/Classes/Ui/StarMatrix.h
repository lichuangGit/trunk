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
	*����:	�������Ǵ���
	*param:	true ��ʾ����������������� ��֮false 
	*����ֵ:
	*����: lichuang
	*����:2015-10-16-14:29                                                                   
	*/
	bool onTouch(const Vec2& p);

	void handlerRefurbish();

	/*
	*����:	�ָ��ϴε����ǲ���
	*param: 
	*����ֵ: true ��ʾ��������Ҫ�ָ��� false ��������Ҫ�ָ�
	*����: lichuang
	*����:2015-10-29-15:40                                                                   
	*/
	bool restorePreviousStars();

	/*
	*����:	��������ǰ���������ǵĲ���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-2-12:50                                                                   
	*/
	void saveStars(int rowIndex = 0, int colIndex = 0, bool isCheck = false);

	/*
	*����:	�뿪��Ϸҳ��ʱ�������ǲ��ֱ��浽json�ļ�
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-2-12:51                                                                   
	*/
	void saveStarAtExitGame();
	
	/*
		����������ɫ
	*/
	void updateStarColor(int color, bool isComplete=false, bool isChange=false);
	
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
	void getBombSelectedList(Star* s);
	void getSameColorSelectedList(Star* s);

	Star *createStar(int row, int col, int color, bool isMove=true);

	/*
	*����:	�ָ�ĳ��λ���ϴ���ɫ������
	*param: row �� col �� color �ϴ���ɫ
	*����ֵ:
	*����: lichuang
	*����:2015-10-29-14:58                                                                   
	*/
	void restoreNewStars(int row, int col, int color);

public:	
	std::vector<vector<vector<int>>> startsIndexVec;	

private:
	Star* stars[ROW_NUM][COL_NUM];
	Sprite* backStar[ROW_NUM][COL_NUM];

	deque<Star*> selectedList;
	deque<Star*> m_starsNext;
	int currentSelectedNum; //��ǰ��ʾɾ������������
	GameLayer* m_layer;
	float clearSumTime;
	
	bool isStarSeclected;
	Star *neadChangeColorStar;

	SpriteBatchNode *m_starBatchNode;
	Vector<ParticleBatchNode *> m_particleBatchNode;
	vector<map<int, vector<int>>> m_vecSaveStars;	//�������ǲ���
};
#endif
