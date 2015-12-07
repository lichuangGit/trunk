#ifndef STUDIOLAYER_H
#define STUDIOLAYER_H

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "../cocos2d/cocos/editor-support/cocostudio/CocoStudio.h"
#include <ui/UIButton.h>
#include "Data/Const.h"
#include "Data/Audio.h"
#include "Data/Const.h"
#include "Data/GameData.h"

using namespace cocos2d::ui;
using namespace cocostudio;
USING_NS_CC;

class StudioLayer :  public Layer
{
public:
	StudioLayer();
	~StudioLayer();

	virtual bool init(int opacity = 0, bool isMove = true);

	virtual void onEnter();

	/*
	*功能:	关闭layer
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-8-13-19:06
	*/
	//virtual void closeLayer(Ref *pSender, Widget::TouchEventType type);
	virtual void closeLayer();
	void removeSelf();

private:
	/*
	*功能:	创建背景层
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-8-13-17:59
	*/
	void initLayerColor(int opacity);

	/*
	*功能:	注册监听，屏蔽下层触摸
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-8-13-19:07                                                                   
	*/
	void registerListener();

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);

	void fadeInLayer();

	void setLayerOpacity(int value);

private:
	int m_opacity;		//背景层透明度
	LayerColor *m_layerColor;
};

#endif
