#include "ShadeLayer.h"


ShadeLayer::ShadeLayer()
{	
}

ShadeLayer::~ShadeLayer()
{
}

ShadeLayer *ShadeLayer::create(int color /* = -1 */)
{
	ShadeLayer *shade = new ShadeLayer;
	
	if (shade && shade->init(color))
	{
		shade->autorelease();
		return shade;
	}

	CC_SAFE_DELETE(shade);

	return nullptr;
}

bool ShadeLayer::init(int color /* = -1 */)
{
	if (!StudioLayer::init(100, false))
	{
		return false;
	}

	m_previousColor = color;
	m_selectedColor = -1;

	auto keyboardlistener = EventListenerKeyboard::create();
	keyboardlistener->onKeyReleased = CC_CALLBACK_2(ShadeLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardlistener, this);

	initUI();

	return true;
}

void ShadeLayer::initUI()
{	
	auto bg = Sprite::createWithSpriteFrameName("bgStar.png");
	bg->setAnchorPoint(Vec2(0.5f, 0.0f));
	bg->setPosition(Vec2(VISIBLE_SIZE.width / 2, 0));
	bg->setScaleY((VISIBLE_SIZE.height / O_SCREEN_HEIGHT) * (STAR_BOTTOM/bg->getContentSize().height));
	this->addChild(bg);

	Vector<MenuItem *> vec;
	int j = 0;

	for (int i = 0; i < COLOR_MAX_NUM; i++)
	{
		if (m_previousColor != i)
		{				
			vec.pushBack(createMenuStar(i, j, (VISIBLE_SIZE.height / O_SCREEN_HEIGHT) * (STAR_BOTTOM / bg->getContentSize().height) * bg->getContentSize().height / 2));
			spBlack[j] = Sprite::createWithSpriteFrameName("black.png");
			spBlack[j]->setPosition(menuItems[j]->getPosition());
			spBlack[j]->setColor(Color3B::GREEN);
			spBlack[j]->setVisible(false);
			this->addChild(spBlack[j]);
			j++;
		}		
	}

	auto spClose = Sprite::createWithSpriteFrameName("exit.png");
	auto menuClose = MenuItemSprite::create(spClose, spClose, [&](Ref *pSender){ShadeLayer::closeLayer(); });
	menuClose->setPosition(Vec2(VISIBLE_SIZE.width - menuClose->getContentSize().width / 2, (VISIBLE_SIZE.height / O_SCREEN_HEIGHT) * (STAR_BOTTOM / bg->getContentSize().height) * bg->getContentSize().height - menuClose->getContentSize().height / 2));

	vec.pushBack(menuClose);

	Menu *menu = Menu::createWithArray(vec);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}

MenuItemSprite *ShadeLayer::createMenuStar(int color, int pos, int y)
{
	string path = getImage(color);

	if (path.empty())
	{
		return nullptr;
	}
	auto star = Sprite::createWithSpriteFrameName(path);
	menuItems[pos] = MenuItemSprite::create(star, star, CC_CALLBACK_0(ShadeLayer::callBackSwap, this, color, pos));
	Size size = menuItems[pos]->getContentSize();
	int middle = (START_MIDDLE - size.width * (COLOR_MAX_NUM - 1)) / (COLOR_MAX_NUM - 1 - 1);
	int x = START_LEFTRIGHT + (pos + 0.5) * size.width + middle * pos;

	menuItems[pos]->setPosition(Vec2(x, y));

	return menuItems[pos];
}

char* ShadeLayer::getImage(int color)
{
	switch (color)
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

void ShadeLayer::callBackSwap(int color, int pos)
{
	int scale = menuItems[pos]->getScale();

	setOtherStar(pos);
	m_selectedColor = scale < 1.0f ? -1 : color;

	menuItems[pos]->setScale(scale < 1.0f ? 1.0f : 0.8f);
	spBlack[pos]->setVisible(scale < 1.0f ? false : true);

	((StarMatrix*)this->getParent())->updateStarColor(m_selectedColor == -1 ? m_previousColor : m_selectedColor);
}

void ShadeLayer::setOtherStar(int pos)
{
	for (int i = 0; i < COLOR_MAX_NUM - 1; i++)
	{
		if (i != pos && menuItems[i]->getScale() < 1.0f)
		{
			menuItems[i]->setScale(1.0);
			spBlack[i]->setVisible(false);
		}
	}
}

void ShadeLayer::closeLayer()
{
	((StarMatrix*)this->getParent())->updateStarColor(-1, true, (m_selectedColor != -1) ? true : false);
	StudioLayer::removeSelf();
}

void ShadeLayer::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	if (event->getType() == Event::Type::KEYBOARD)
	{
		event->stopPropagation();
	}
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_BACK:
		closeLayer();
		break;
	}
}

