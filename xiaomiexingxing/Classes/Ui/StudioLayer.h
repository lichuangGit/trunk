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
	*����:	�ر�layer
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-8-13-19:06
	*/
	//virtual void closeLayer(Ref *pSender, Widget::TouchEventType type);
	virtual void closeLayer();
	void removeSelf();

private:
	/*
	*����:	����������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-8-13-17:59
	*/
	void initLayerColor(int opacity);

	/*
	*����:	ע������������²㴥��
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-8-13-19:07                                                                   
	*/
	void registerListener();

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);

	void fadeInLayer();

	void setLayerOpacity(int value);

private:
	int m_opacity;		//������͸����
	LayerColor *m_layerColor;
};

#endif
