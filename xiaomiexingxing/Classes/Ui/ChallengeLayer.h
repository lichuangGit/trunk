#ifndef CHALLENGELAYER_H
#define CHALLENGELAYER_H

#include "StudioLayer.h"
#include "Data/GameData.h"
#include "Core/Helper.h"
#include "GameDialogLayer.h"
#include "ChallengeGameLayer.h"

class ChallengeLayer : public StudioLayer
{
public:
	ChallengeLayer();
	~ChallengeLayer();

	virtual bool init();
	CREATE_FUNC(ChallengeLayer);

	void onEnter();

private:
	void initUI();

	void onBtnClick(Ref *pSender, Widget::TouchEventType type);

	/*
	*����:	��Ϸ������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-10-14:27
	*/
	void popOutDialog(PayType type);

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

	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

private:
	Button *m_btnAdd;
	Button *m_btnSub;
	Button *m_btnStart;
	Button *m_btnClose;

	NumSprite *m_zuanshiCount;//����
	NumSprite *m_betSp;//Ͷע
	NumSprite *m_numSp;
};


#endif


