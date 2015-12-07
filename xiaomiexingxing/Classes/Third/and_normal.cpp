#include "and_normal.h"
#include "Data/GameData.h"

#define CLASS_NAME  "org/cocos2dx/cpp/AppActivity"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "jni/JniHelper.h"
//extern std::function<void(int, int, map<int, int>)>  m_funPayCallBack;
#endif

void and_normal::payment(int payPoint)
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;

	bool isHave =JniHelper::getStaticMethodInfo(minfo, CLASS_NAME,"jniPay","(I)V");
	if (!isHave) 
	{
		CCLOG( "buy not exist");
	} 
	else 
	{
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,payPoint);
	}
#endif
}

string and_normal::getUmengChanel()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo method;
	bool isHasActivity = JniHelper::getStaticMethodInfo(method,
		CLASS_NAME, "jniUmengChanel",
		"()Ljava/lang/String;");

	if (isHasActivity)
	{
		jstring channel = (jstring)method.env->CallStaticObjectMethod(method.classID,
			method.methodID);
		return JniHelper::jstring2string(channel);
	}
	else
	{
		return "yunlandefault";
	}
#endif
	return "";
}

string and_normal::getUmengKey()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo method;
	bool isHasActivity = JniHelper::getStaticMethodInfo(method,
		CLASS_NAME, "jniUmengKey",
		"()Ljava/lang/String;");

	if (isHasActivity)
	{
		jstring channel = (jstring)method.env->CallStaticObjectMethod(method.classID,
			method.methodID);
		return JniHelper::jstring2string(channel);
	}
	else
	{
		return "yunlandefault";
	}
#endif
	return "";
}
