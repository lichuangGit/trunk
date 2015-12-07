#include "ComboEffect.h"
void showComboEffect(int size,Node* node)
{
	if(size<5)
		return;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* comboSprite,* unbliveable;
	if(size>=10)
	{
		comboSprite = Sprite::createWithSpriteFrameName("combo_3.png");
		unbliveable = Sprite::createWithSpriteFrameName("unbelivable.png");
	}
	else if(size>=7)
	{
		comboSprite = Sprite::createWithSpriteFrameName("combo_2.png");
	}
	else
	{
		comboSprite = Sprite::createWithSpriteFrameName("combo_1.png");
	}

	if(size>=10)
	{
		unbliveable->setPosition(Point(visibleSize.width/2,visibleSize.height/2+70));
		node->addChild(unbliveable);
		ActionInterval * rotateto = RotateTo::create(0.7f, 90);
		CallFunc* remove2 = CallFunc::create([=](){unbliveable->removeFromParentAndCleanup(true);});
		Sequence* action2 = Sequence::create(rotateto,remove2,nullptr);
		unbliveable->runAction(action2);
	}

	comboSprite->setPosition(Point(visibleSize.width/2,visibleSize.height/2+70));
	node->addChild(comboSprite);

	Blink* blink = Blink::create(0.7f,2);
	CallFunc* remove = CallFunc::create([=](){comboSprite->removeFromParentAndCleanup(true);});
	Sequence* action = Sequence::create(blink,remove,nullptr);
	comboSprite->runAction(action);
}
