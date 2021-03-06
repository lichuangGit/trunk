#ifndef _STAR_H_
#define _STAR_H_

#include "cocos2d.h"
#include "Data/Const.h"

USING_NS_CC;

class Star : public Sprite
{
public:
	enum Color
	{
		GREEN,
		RED,
		YELLOW,
		PURPLE,
		BLUE
	};
	static Star* create(int color);
	static Star *createWithTexture(int color, Texture2D *texture);
	bool isSelected();
	inline void setSelected(bool b){selected = b;}
	int getColor();
	void setDesPosition(const Point& p);
	inline Point getDesPosition(){return desPosition;}
	bool updatePosition();
	inline int getIndexI(){return index_i;}
	inline int getIndexJ(){return index_j;}
	inline void setIndex_ij(int i,int j){index_i = i;index_j = j;}

private:
	char* getImage(int color);

private:
	int color;
	Point desPosition;
	bool selected;
	int index_i;
	int index_j;
};
#endif
