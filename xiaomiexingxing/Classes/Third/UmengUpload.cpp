#include "UmengUpload.h"


UmengUpload::UmengUpload()
{
}


UmengUpload::~UmengUpload()
{
}

void UmengUpload::setLevel(string lv)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	umeng::MobClickCpp::setUserLevel(lv.c_str());
#endif
}

void UmengUpload::pay(double cash, int source, double coin)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	umeng::MobClickCpp::pay(cash,source,coin);
#endif
}

void UmengUpload::use(string item, int amount, double price)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	umeng::MobClickCpp::use(item.c_str(),amount,price);
#endif
}

void UmengUpload::bonus(double coin, int source)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	umeng::MobClickCpp::bonus(coin,source);
#endif
}

void UmengUpload::bonus(string item, int amount, double price, int source)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	umeng::MobClickCpp::bonus(item.c_str(),amount,price,source);
#endif
}

void UmengUpload::startLevel(string level)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	umeng::MobClickCpp::startLevel(level.c_str());
#endif
}

void UmengUpload::finishLevel(string level)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	umeng::MobClickCpp::finishLevel(level.c_str());
#endif
}

void UmengUpload::failLevel(string level)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	umeng::MobClickCpp::failLevel(level.c_str());
#endif
}

void UmengUpload::event(string eventId, const char * label /* = NULL */)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	umeng::MobClickCpp::event(eventId.c_str(),label);
#endif
}

void UmengUpload::event(string eventId, map<string, string> *attributes, int counter /* = 0 */)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	umeng::MobClickCpp::event(eventId.c_str(),attributes,counter);
#endif
}

void UmengUpload::end()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	map<string,string> _map;
	_map["playTime(m)"] = GameData::getInstance()->getGameDurationGPD();
	_map["money"] = cocos2d::Value(GameData::getInstance()->getGoodsNumber(GoodsType::Zuanshi)).asString();
	umeng::MobClickCpp::end();
#endif
}
