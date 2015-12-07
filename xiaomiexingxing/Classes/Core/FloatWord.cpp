#include "FloatWord.h"
#include "Data/Const.h"

FloatWord* FloatWord::create(const std::string& word,const int fontSize,Point begin)
{
	FloatWord* ret = new FloatWord();
	if(ret && ret->init(word,fontSize,begin))
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);

	return nullptr;
}

bool FloatWord::init(const std::string& word,const int fontSize,Point begin)
{
	if(!Node::init())
	{
		return false;
	}
	_begin = begin;
	_label = Label::create();
	_label->setString(word);
	_label->setSystemFontSize(fontSize);
	_label->setPosition(begin);
	//_label->setColor(Color3B::BLUE);
	this->addChild(_label);
	
	return true;
}

void FloatWord::floatIn(const float delay,std::function<void()> callback)
{
	auto move = MoveTo::create(delay, Point(VISIBLE_SIZE.width / 2, _begin.y));
	auto call = CallFunc::create(callback);
	auto action = Sequence::create(move, DelayTime::create(0.5f), call, NULL);

	_label->runAction(action);
}

void FloatWord::floatOut(const float delay,std::function<void()> callback)
{
	auto move = MoveTo::create(delay, Point(0, _begin.y));
	auto call = CallFunc::create(callback);
	auto removeC = CallFuncN::create([&](Node *pSender){pSender->removeFromParentAndCleanup(true);});
	auto action = Sequence::create(move, call, removeC, NULL);

	_label->runAction(action);
}

void FloatWord::floatInOut(const float speed,const float delayTime,std::function<void()> callback)
{
	auto moveIn = MoveTo::create(speed, Point(VISIBLE_SIZE.width / 2, _begin.y));
	auto moveOut = MoveTo::create(speed, Point(0, _begin.y));
	auto removeC = CallFuncN::create([&](Node *pSender){pSender->removeFromParentAndCleanup(true);});
	auto action = Sequence::create(moveIn, DelayTime::create(delayTime), moveOut, removeC, CallFunc::create(callback), NULL);

	_label->runAction(action);
}
