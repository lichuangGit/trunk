#ifndef STARBOOK_H
#define STARBOOK_H

#include "Ui/StudioLayer.h"

class StarBook : public StudioLayer
{
public:
	StarBook();
	~StarBook();

	virtual bool init();
	CREATE_FUNC(StarBook);

	void onEnter();

private:
	void initUI();

	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
};

#endif




