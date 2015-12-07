#include "Game_native.h"
#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "jni/JniHelper.h"
#include "libMobClickCpp/include/MobClickJniHelper.h"

#if defined(__cplusplus)
extern "C" {
#endif
	map<int,int> m_map;
	std::function<void(int, int, map<int, int>)>  m_funPayCallBack = nullptr;

	void setCallBack(std::function<void(int, int, map<int, int>)> func)
	{
		m_funPayCallBack = func;
	}

	JNIEXPORT void JNICALL natvie_payCallBack(JNIEnv *env, jobject obj,jint payPoint,jint payResult,jint erroCode)
	{
		if (payResult == PayResult::Success)
		{
			map<string, string> _map;
			_map["point"] = cocos2d::Value(payPoint).asString();
			_map["playTime(m)"] = GameData::getInstance()->getGameDurationGPD();
			_map["money"] = cocos2d::Value(GameData::getInstance()->getGoodsNumber(GoodsType::Zuanshi)).asString();
			UmengUpload::event(Umeng_Id_Paysuccess, &_map);
			int price = 0;
			if (payPoint == PayPoint::Twoyuanlibao)
			{
				price = 2;
			}
			else if (payPoint == PayPoint::Fouryuanlibao)
			{
				price = 4;
			}
			else if (payPoint == PayPoint::Sixyuanlibao)
			{
				price = 6;
			}
			else
			{
				price = 10;
			}
			UmengUpload::pay(price,9,0);
		}
		else
		{
			map<string, string> _map;
			_map["point"] = cocos2d::Value(payPoint).asString();
			_map["errorcode"] = cocos2d::Value(erroCode).asString();
			UmengUpload::event(Umeng_Id_Payfailed, &_map);
		}
		if(m_funPayCallBack)
		{
			m_funPayCallBack(payPoint,payResult,m_map);
			m_funPayCallBack = nullptr;
			m_map.clear();
		}
	}
	static JNINativeMethod gMethods[] =
	{
		{"jniPayBack",	"(III)V", (void*)natvie_payCallBack}
	};
	jint JNI_RegisterNativeFunctions(JNIEnv* env)
		{
			jint res = 0;

			jclass clazz = env->FindClass("org/cocos2dx/cpp/AppActivity");

			res = env->RegisterNatives(clazz, gMethods, sizeof(gMethods) / sizeof(JNINativeMethod));

			if (0 > res)
			{
				return - 1;
			}
			return 0;
		}

	JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
		JNIEnv* env = 0;
		JniHelper::setJavaVM(vm);
		umeng::MobClickJniHelper::setJavaVM(vm);
		if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
			return -1;
		}
		JNI_RegisterNativeFunctions(env);

		return JNI_VERSION_1_4;
	}

#if defined(__cplusplus)
   }
#endif

#endif
