#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_

#include "cocos2d.h"
#include "Data/Const.h"
#include "Data/GameData.h"
#include "TopMenu.h"
#include "StarMatrix.h"
#include "Core/FloatWord.h"
#include "Data/Audio.h"
#include "Ui/GameDialogLayer.h"
#include <map>
#include "Props.h"
#include "SettingLayer.h"

using namespace std;
USING_NS_CC;
class StarMatrix;

//gamelayer �˵�
#define SetMenu 6
#define AddMenu 7

class GameLayer: public Layer 
{
public:
	//��ǰ����״̬
	enum TouchStatus
	{
		Touch_Normal = 0,	//����״̬
		Touch_Bomb,			//ը������
		Touch_Tongsexiao,	//ͬɫ����
		Touch_Huanse,		//��ɫ����
		Touch_Chexiao,		//��������
		Touch_Shuanxin		//ˢ�µ���
	};
	//����״̬
	enum StarStatus
	{
		Status_Ready,		//��ʼ״̬
		Status_Activity,	//�״̬ ������������ƶ�
		Status_NoActivity,	//�ǻ״̬
		Status_Over			//�ؿ�����״̬
	};
public:
	static Scene *createScene();
	CREATE_FUNC(GameLayer);
	virtual bool init();

	CC_SYNTHESIZE(TouchStatus, m_curTouchStatus, CurTouchStatus);	//��ǰ����״̬
	CC_SYNTHESIZE(TouchStatus, m_previousTouchStatus, PreviousTouchStatus);//�ϴ�״̬

	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch *touch, Event *event);
	
	void floatLevelWord();
	void floatTargetScoreWord();
	void removeFloatWord();
	void showStarMatrix();
	
	void refreshMenu();
	void showLinkNum(int size);

	/*
	*����:	������һ��
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-13-10:07                                                                   
	*/
	void gotoNextLevel();

	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

	/*
	*����:	ÿ����������󣬷����ƶ���󣬸��·���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-9-9:20                                                                   
	*/
	void updateEveryScore(int score);

	/*
	*����:	�����������ӷ�����Ϻ�ͨ����ʾ,������Ч��ʾ��������ʾ�����ֲ���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-9-13:49                                                                   
	*/
	void startPassLevelDeal();

	/*
	*����:	ÿ�δ�����������������󣬷���ˢ�º�������ʾ
	*param: link ���������� Ĭ�� 0 ������ʾ��������ֻˢ��
	*����ֵ:
	*����: lichuang
	*����:2015-10-9-14:27                                                                   
	*/
	void refreshScoreAndLinkNum(int link = 0);

	/*
	*����:	���ؽ�������ʾ���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-9-18:07                                                                   
	*/
	void floatLeftStarMsg(int leftNum);

	/*
	*����:	��������Ʈ���Ĵ���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-9-18:08                                                                   
	*/
	void gameOverToDealStar(int score);

	/*
	*����:	��Ϸ������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-10-14:27                                                                   
	*/
	void popOutDialog(NormalType type);
	void popOutDialog(PayType type);

	/*
	*����:	��Ϸover�󣬵���ص�������
	*param: _map ��Ʒ���� key ��Ʒ���� value ��Ʒ����
	*����ֵ:
	*����: lichuang
	*����:2015-10-12-16:50                                                                   
	*/
	void normalDialogCallBack(std::map<int, int> _map, NormalType type = nGameNone);
	void payDialogCallBack(int point, int result, std::map<int, int> _map);

	/*
	*����:	����һ����Ʒ���ƶ����� 
	*param: type ��Ʒ���� num ���� isNextLevel �Ƿ������һ�� ����Ʒ�������ı䷢�������ġ�����(���ܷ�������Ϸ������ʱ�򣬹����һ����Ʒ�������֮�������һ��)
	*����ֵ:
	*����: lichuang
	*����:2015-10-12-16:56                                                                   
	*/
	void createGoodsAndMove(GoodsType type, int num, bool isNextLevel = false);

	/*
	*����:	������Ʒ����,���ڶԻ�������ѻ�����Ʒ��ˢ��gamelayer����
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-12-17:23                                                                   
	*/
	void updateGoodsNumberCallback(Node *pSender, GoodsType type, int num);
	
	/*
	*����:	������Ʒ����������ˢ��ҳ����ʾ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-17-15:12                                                                   
	*/
	void updateGoodsNumber(GoodsType type, int num);

	SpriteBatchNode *getBatchNode();

	/*
	*����:	�������ǵ�״̬ true �״̬ false ��ֹ״̬
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-9-16:26
	*/
	void setStarsStatus(StarStatus status);
	StarStatus getStarsStatus();

	/*
	*����:	�����Ƿ�����ʹ���У�true �� false ��  ��ͬɫ����������ˢ��ʹ���ڼ伴����û�����꣬������������������������������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-16-14:25                                                                   
	*/
	CC_SYNTHESIZE(bool, m_isPropUse, IsPropUse);

	/*
	*����:	����״̬��־����������������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-16-15:59                                                                   
	*/
	void updateTouchStatus(TouchStatus status);

	/*
	*����:	���ڵ������ģ�������Ʒ��ʾ,ͨ��״̬
	*param: status �ϴ�״̬
	*����ֵ:
	*����: lichuang
	*����:2015-10-16-17:34                                                                   
	*/
	void updateGoodsNumberByTouchStatus();

	/*
	*����:	����Ϸҳ���뿪ʱ������浵���Ա�����ҳ�ɵ����
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-2-10:27                                                                   
	*/
	void saveStarAtExitGame();

private:
	void registerListener();	//lichuang 2015/4/22 ��װע���������

	void initUI();

	void congratulations();

	GameLayer();
	~GameLayer();

	/*
	*����:	��Ϸʧ��Ʈ�ִ���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-14-14:33                                                                   
	*/
	void floatFailedMove();

	/*
	*����:	�˵��ص�����
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-14-17:19                                                                   
	*/
	void onMenuItemCallBack(int type);

	/*
	*����:	ը������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-15-16:24                                                                   
	*/
	void startDealWithBomb();

	/*
	*����:	ͬɫ������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-15-16:24                                                                   
	*/
	void startDealWithTongsexiao();

	/*
	*����:	����ɫ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-15-16:26                                                                   
	*/
	void startDealWithHuanse();

	/*
	*����:	ը����ͬɫ������ɫ����
	*param: type �������� status ���߶�Ӧ��״̬ money ���߶�Ӧ����ʯ�۸�
	*����ֵ:
	*����: lichuang
	*����:2015-11-5-9:14                                                                   
	*/
	void startDealWithProp(GoodsType type, TouchStatus status, int money);

	/*
	*����:	������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-15-16:27                                                                   
	*/
	void startDealWithChexiao();

	/*
	*����:	����ˢ��
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-15-16:28                                                                   
	*/
	void startDealWithShuaxin();

	/*
	*����:	������ˢ�µ���󣬴���״̬
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-29-18:26                                                                   
	*/
	void afterChexiaoAndShuaxinDeal(float f);

	/*
	*����:	����״̬���ض�Ӧ�ĵ��߶���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-16-11:27                                                                   
	*/
	Props *getPropByTouchStatus(TouchStatus status);

	/*
	*����:	��״̬��ȡ��Ʒ���ͻ�����Ʒ��ʯ�۸�
	*param: type ��������ֵ���� 1 ������Ʒ����GoodsType 2 ������Ʒ��ʯ�۸�
	*����ֵ:
	*����: lichuang
	*����:2015-10-17-15:34                                                                   
	*/
	int getGoodsByStatus(TouchStatus status, int type = 1);

	/*
	*����:	�жϵ�ǰ��Ϸ״̬���Ƿ���Ӧ�û��Ĳ���	�����û��ڲ���ʱ��Ĳ������������
	*param:
	*����ֵ:	true ��Ӧ false ����Ӧ
	*����: lichuang
	*����:2015-10-15-16:16                                                                   
	*/
	bool isReceiveTouchEvent();

	/*
	*����:	��ǰ�ؿ��Ƿ���ʾ�ɹ�
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-17-20:27                                                                   
	*/
	CC_SYNTHESIZE(bool, m_isCongratulation, IsCongratulation);

	/*
	*����: 5��û�в�������������ʾ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-4-16:23                                                                   
	*/
	void noTouchAndWarning(float f);

	/*
	*����:	ֹͣ��������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-12-13:59                                                                   
	*/
	void stopNoTouchAndWarning();

	/*
	*����:	����ֵ���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-24-14:31                                                                   
	*/
	void goLibao(string name);

	/*
	*����:	ˢ�µȼ�������ֵ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-12-6-16:32                                                                   
	*/
	void updateLvAndExpereience(int leftStar);

	/*
	*����:	������ʾ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-12-6-19:55                                                                   
	*/
	void congratulationsUpgrade();

	/*
	*����:	��ʱ�޸ľ�����
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-12-6-19:54                                                                   
	*/
	void afterUpate(float f);

	/*
	*����:	��ʾ�ȼ��ӷ���ʾ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-12-6-20:29                                                                   
	*/
	void showLvToAddScore(int leftStar);

	/*
	*����:	�ȼ��ӷ��ƶ������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-12-6-20:47                                                                   
	*/
	void dealLvAddScoreAfter(Node*pSender, int score);

private:
	TopMenu *m_topMenu;			//��Ϸ�����Ϣ
	StarMatrix *m_starMatrix;

	FloatWord *m_levelMsg;
	FloatWord *m_targetScore;
	Label* m_linkNum;		//������ʾ
	SpriteBatchNode *m_spBatchNode;
	StarStatus m_starStatus;	//���ǵĵ�ǰ״̬

	//����
	Props *m_bombProp;
	Props *m_tongsexiaoProp;
	Props *m_huanseProp;
	Props *m_chexiaoProp;
	Props *m_shuaxinProp;

	int m_enterTime;	//��¼��ҽ���ʱ��

	NumSprite *m_pSpLevel;	// ��ҵȼ�
	Sprite *m_pSpProg;		//������
	Sprite *m_pSpZengjia;
	Sprite *m_pSpChenghao;
	NumSprite *m_pSpLvAdd;
	NumSprite *m_pSpLvScore;
	int m_iLvCount;

public:
	Vec2 m_curScorePos;		//��ǰ����λ��
	Vec2 m_curZuanshiPos;
	Vec2 m_curBombPos;
	Vec2 m_curTongsexiaoPos;
	Vec2 m_curHuansePos;
	Vec2 m_curChexiaoPos;
	Vec2 m_curShuaxinPos;
};

#endif
