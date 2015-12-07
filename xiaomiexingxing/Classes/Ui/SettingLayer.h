#ifndef SETTINGLAYER_H
#define SETTINGLAYER_H

#include "StudioLayer.h"
#include "Data/GameData.h"
#include "Data/Audio.h"
#include "MenuLayer.h"

class SettingLayer : public StudioLayer
{
public:
	SettingLayer();
	~SettingLayer();

	CREATE_FUNC(SettingLayer);
	virtual bool init();
	void onEnter();

	void initUI();

	void onMenuCallBack(int type);

	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

	/*
	*����:	���ֿ���
	*param:	is true ���� false ֹͣ
	*����ֵ:
	*����: lichuang
	*����:2015-11-2-13:08                                                                   
	*/
	void musicOnOff(bool is);

	/*
	*����:	������ҳ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-2-13:15                                                                   
	*/
	void goHome();

private:
	MenuItemSprite *itemOn;
	MenuItemSprite *itemOff;
	bool isGoHome;
};

#endif
