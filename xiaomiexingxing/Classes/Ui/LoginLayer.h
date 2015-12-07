#ifndef LOGINLAYER_H
#define LOGINLAYER_H

#include "StudioLayer.h"

class LoginLayer : public StudioLayer
{
public:
	LoginLayer();
	~LoginLayer();
	CREATE_FUNC(LoginLayer);
	virtual bool init();

	void onEnter();

private:
	void initUI();

	/*
	*����:	��ť�������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-10-16:40                                                                   
	*/
	void onBtnClick(Ref* sender, Widget::TouchEventType type);

	/*
	*����:	��ȡǩ��������Ӧ�Ľ�����ʯ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-10-16:40                                                                   
	*/
	int getZuanshiByDays(int day);

	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

private:
	Vector<Sprite*> m_vecSp;
	bool m_isLogining;
	Button *m_closeBtn;
	Button *m_okBtn;
};

#endif




