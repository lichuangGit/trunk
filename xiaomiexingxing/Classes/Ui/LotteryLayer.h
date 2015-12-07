#ifndef PLAYERLOTTERYLAYER_H
#define PLAYERLOTTERYLAYER_H

#define LOTTERYDIS 25

#include "StudioLayer.h"
#include "Core/Helper.h"
#include "Data/GameData.h"
#include "GameDialogLayer.h"
#include <ui/UIButton.h>

class LotteryLayer : public StudioLayer
{
public:
	LotteryLayer();
	~LotteryLayer();
	CREATE_FUNC(LotteryLayer);
	virtual bool init();

	void onEnter();

private:
	void initUI();

	/*
	*����:	��Ʒ��ʼ����ÿ�ε���͸ı�
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-5-14:33
	*/
	void initLotteryUI();

	/*
	*����:	��ť���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-5-16:08
	*/
	void onBtnClick(Ref* sender, Widget::TouchEventType type);

	/*
	*����:	��ʼ�齱
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-6-9:29                                                                   
	*/
	void startLottery();

	/*
	*����:	�齱����
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-6-9:29                                                                   
	*/
	void startLotteryActioin();

	/*
	*����:	�齱�����ص�
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-9-10:14                                                                   
	*/
	void callBackLight(int pos);

	/*
	*����:	�齱�����󣬽�Ʒ����Ӧλ���ƶ�������λ��
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-9-10:12                                                                   
	*/
	void moveToCenter();

	/*
	*����:	�жϳ齱���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-9-10:15                                                                   
	*/
	bool judgeLotteryResult(int pos);

	string getLotteryPath(GoodsType type);

	/*
	*����:	֧���ص�
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-2-16:57
	*/
	void payDialogCallBack(int point, int result, std::map<int, int> _map);

	/*
	*����:	������Ʒ����������ˢ��ҳ����ʾ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-17-15:12
	*/
	void updateGoodsNumber(GoodsType type, int num);

	void popOutDialog(PayType type);

	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

private:
	bool m_lotteryStatu;				//�齱״̬ true ���ڽ��� false �ѽ�����δ��ʼ
	int m_callbackCount;				//�ص�����
	int m_lotteryResult;				//��¼���ͣ����λ��
	Size lottSize;

private:
	SpriteBatchNode *m_batchNode;
	NumSprite *m_numSp;
	Button *m_startBtn;
	Button *m_closeBtn;
	Sprite *m_lightSp;	//��Ʒ�ϵĹ⻷
	Sprite *m_centerLightSp;	//����λ���ϵ�
	Sprite *m_goodsLottery;
	NumSprite *m_numGoodsLottery;

	Vector<Node *> m_goodsBg;
	Vector<Node *> m_lottery;
	std::vector<Vec2> m_vecLotteryPos;	//��Ʒ��λ��
	std::vector<int> m_vecGoodsResult;	//��Ʒ������
	std::vector<int> m_vecNumberResult;	//��Ʒ������	
};

#endif

