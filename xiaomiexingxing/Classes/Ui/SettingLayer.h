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
	*功能:	音乐控制
	*param:	is true 播放 false 停止
	*返回值:
	*作者: lichuang
	*日期:2015-11-2-13:08                                                                   
	*/
	void musicOnOff(bool is);

	/*
	*功能:	返回首页
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-11-2-13:15                                                                   
	*/
	void goHome();

private:
	MenuItemSprite *itemOn;
	MenuItemSprite *itemOff;
	bool isGoHome;
};

#endif
