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
	*����:	���µ�������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-15-9:43                                                                   
	*/
	void updatePropsNumber(int num);

	/*
	*����:	���߶���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-16-10:03                                                                   
	*/
	void goPropAction();

	/*
	*����:	ֹͣ���߶���
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-16-10:04                                                                   
	*/
	void stopPropAction();

	/*
	*����:	���õ���״̬��־
	*param: true ����ִ�� false δִ��
	*����ֵ:
	*����: lichuang
	*����:2015-10-16-10:05                                                                   
	*/
	CC_SYNTHESIZE(bool, m_actionStatus, ActionStatus);

private:
	/*
	*����:	���õ����Ƿ����ִ�ж��� ˲ʱ�Ե��߲���ִ�� ���������
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-16-10:15                                                                   
	*/
	CC_SYNTHESIZE(bool, m_isDoAction, DoAction);

	string getProps();

private:
	GameLayer *m_layer;
	GoodsType m_propType;	//��������
	string m_propName;		//����ͼƬ��
	NumSprite *m_propNumber;//��������
};

#endif
