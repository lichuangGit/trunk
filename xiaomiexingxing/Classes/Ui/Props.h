#ifndef PROPS_H
#define PROPS_H

#include "cocos2d.h"
#include "Data/Const.h"
#include "Data/GameData.h"
#include "Core/Helper.h"

USING_NS_CC;
class GameLayer;

class Props : public MenuItemSprite
{
public:
	Props();
	~Props();
	static Props *create(GoodsType type, GameLayer *layer, const ccMenuCallback& callback);
	bool init(GoodsType type, GameLayer *layer, const ccMenuCallback& callback);

	/*
	*功能:	更新道具数量
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-15-9:43                                                                   
	*/
	void updatePropsNumber(int num);

	/*
	*功能:	道具动作
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-16-10:03                                                                   
	*/
	void goPropAction();

	/*
	*功能:	停止道具动作
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-16-10:04                                                                   
	*/
	void stopPropAction();

	/*
	*功能:	设置道具状态标志
	*param: true 正在执行 false 未执行
	*返回值:
	*作者: lichuang
	*日期:2015-10-16-10:05                                                                   
	*/
	CC_SYNTHESIZE(bool, m_actionStatus, ActionStatus);

private:
	/*
	*功能:	设置道具是否可以执行动作 瞬时性道具不可执行 避免误操作
	*param:
	*返回值:
	*作者: lichuang
	*日期:2015-10-16-10:15                                                                   
	*/
	CC_SYNTHESIZE(bool, m_isDoAction, DoAction);

	string getProps();

private:
	GameLayer *m_layer;
	GoodsType m_propType;	//道具类型
	string m_propName;		//道具图片名
	NumSprite *m_propNumber;//道具数量
};

#endif
