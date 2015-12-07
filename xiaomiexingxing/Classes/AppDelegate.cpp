#include "AppDelegate.h"
#include "Ui/MenuLayer.h"
#include "Data/Audio.h"
#include "Third/and_normal.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "libmobclickcpp/include/MobClickCpp.h"
#endif

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("xmxx");
        director->setOpenGLView(glview);
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	glview->setFrameSize(320, 600);
	glview->setDesignResolutionSize(480,800, ResolutionPolicy::FIXED_WIDTH);
	// turn on display FPS
	director->setDisplayStats(true);
#else
	glview->setDesignResolutionSize(480, 800, ResolutionPolicy::FIXED_WIDTH);
	MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL(and_normal::getUmengKey().c_str(), and_normal::getUmengChanel().c_str());
	// turn on display FPS
	director->setDisplayStats(false);
#endif
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	FileUtils::getInstance()->addSearchPath("image");
	FileUtils::getInstance()->addSearchPath("fonts");
	FileUtils::getInstance()->addSearchPath("music");

	Audio::getInstance()->prepare();

    auto scene = MenuLayer::scene();
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	umeng::MobClickCpp::applicationDidEnterBackground();
#endif
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	umeng::MobClickCpp::applicationWillEnterForeground();
#endif
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
