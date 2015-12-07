#ifndef SHADELAYER_H
#define SHADELAYER_H

#include "StudioLayer.h"
#include "StarMatrix.h"

class ShadeLayer:public StudioLayer
{
public:
	ShadeLayer();
	~ShadeLayer();
	static ShadeLayer *create(int color = -1);
	virtual bool init(int color = -1);
	
private:
	void initUI();

	MenuItemSprite *createMenuStar(int color, int pos, int y);

	char *getImage(int color);

	void callBackSwap(/*Ref *pSender, Sprite *sp, */int color, int pos);
	void setOtherStar(int pos);

	void closeLayer();

	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

private:
	int m_previousColor;			  //��¼����֮ǰ����ɫ
	Menu *m_swapStarsMenu;			  //�������ǵĲ˵�

	Sprite *spBlack[COLOR_MAX_NUM - 1];
	MenuItemSprite *menuItems[COLOR_MAX_NUM - 1];
	int m_selectedColor;			  //��ǰѡ�е���ɫ
};

#endif // !SHADELAYER_H
