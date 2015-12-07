#ifndef CHALLENGEGAMELAYER_H
#define CHALLENGEGAMELAYER_H

#include "StudioLayer.h"
#include "Data/Const.h"
#include "Data/GameData.h"
#include "ChallengeTopMenu.h"
#include "ChallengeStarMatrix.h"
#include "Core/FloatWord.h"
#include "Data/Audio.h"
#include "Ui/GameDialogLayer.h"
#include "SettingLayer.h"

class ChallengeStarMatrix;

class ChallengeGameLayer : public Layer
{
public:
	ChallengeGameLayer();
	~ChallengeGameLayer();

	static Scene *createScene();
	CREATE_FUNC(ChallengeGameLayer);
	virtual bool init();

	//����״̬
	enum StarStatus
	{
		Status_Ready,		//��ʼ״̬
		Status_Activity,	//�״̬ ������������ƶ�
		Status_NoActivity,	//�ǻ״̬
		Status_Over			//�ؿ�����״̬
	};

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
	void setStarsStatus(ChallengeGameLayer::StarStatus status);
	ChallengeGameLayer::StarStatus getStarsStatus();

	/*
	*����:	��Ϸʧ��Ʈ�ִ���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-14-14:33
	*/
	void floatFailedMove();

	/*
	*����:	��ȡ��ǰ����
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-15-12:24                                                                   
	*/
	int getCurScore();

private:
	void registerListener();	//lichuang 2015/4/22 ��װע���������

	void initUI();

	void congratulations();

	/*
	*����:	�˵��ص�����
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-14-17:19
	*/
	void onMenuItemCallBack(int type);
	
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
	*����:	��ս������ת��ֵ���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-15-17:51                                                                   
	*/
	void goLibao(float f);

private:
	ChallengeTopMenu *m_topMenu;			//��Ϸ�����Ϣ
	ChallengeStarMatrix *m_starMatrix;

	FloatWord *m_levelMsg;
	FloatWord *m_targetScore;
	Label* m_linkNum;		//������ʾ
	SpriteBatchNode *m_spBatchNode;
	ChallengeGameLayer::StarStatus m_starStatus;	//���ǵĵ�ǰ״̬

public:
	Vec2 m_curScorePos;		//��ǰ����λ��
	Vec2 m_curZuanshiPos;
};

#endif


