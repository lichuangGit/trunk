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
	int m_previousColor;			  //记录星星之前的颜色
	Menu *m_swapStarsMenu;			  //交换星星的菜单

	Sprite *spBlack[COLOR_MAX_NUM - 1];
	MenuItemSprite *menuItems[COLOR_MAX_NUM - 1];
	int m_selectedColor;			  //当前选中的颜色
};

#endif // !SHADELAYER_H
