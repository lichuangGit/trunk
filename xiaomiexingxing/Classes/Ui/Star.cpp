#include "Star.h"

Star* Star::create(int color)
{
	Star* ret = new Star();
	if(ret && ret->initWithSpriteFrameName(ret->getImage(color)))
	{
		ret->color = color;
		ret->selected = false;
		//ret->setScale(Director::getInstance()->getWinSize().width / O_SCREEN_WIDTH);
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

Star *Star::createWithTexture(int color, Texture2D *texture)
{
	Star *ret = new Star;
	if (ret && ret->initWithTexture(texture))
	{
		ret->color = color;
		ret->selected = false;
		ret->setScale(Director::getInstance()->getWinSize().width / O_SCREEN_WIDTH);
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

char* Star::getImage(int color)
{
	switch(color)
	{
	case Star::Color::BLUE:
		return "blue.png";
	case Star::Color::GREEN:
		return "green.png";
	case Star::Color::YELLOW:
		return "orange.png";
	case Star::Color::RED:
		return "red.png";
	case Star::Color::PURPLE:
		return "purple.png";
	}
	return nullptr;
}

bool Star::isSelected()
{
	return selected;
}

int Star::getColor()
{
	return color;
}

void Star::setDesPosition(const Point& p)
{
	desPosition = p;
}

bool Star::updatePosition()
{
	bool b = true;
	if(desPosition.y != getPositionY()){
		setPositionY(getPositionY() - MOVE_SPEED);
		if(getPositionY() < desPosition.y){
			setPositionY(desPosition.y);
		}
		b = false;
	}
	if(desPosition.x != getPositionX()){
		setPositionX(getPositionX() - MOVE_SPEED);
		if(getPositionX() < desPosition.x){
			setPositionX(desPosition.x);
		}
		b = false;
	}
	return b;
}
