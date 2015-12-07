#include "Data/Audio.h"
#include "SimpleAudioEngine.h"
#include "Data/GameData.h"

using namespace CocosDenshion;

Audio* Audio::m_instance = nullptr;

Audio* Audio::getInstance()
{
	if(m_instance == nullptr)
	{
		m_instance = new Audio();
	}
	return m_instance;
}

void Audio::playBGM()
{
	if(GameData::getInstance()->getMusicIsPlay())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music.ogg",true);
	}
}

void Audio::stopBGM()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
}

void Audio::playReadyGo()
{
	if (GameData::getInstance()->getMusicIsPlay())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("readygo.ogg",false);
	}
}

void Audio::playWin()
{
	if (GameData::getInstance()->getMusicIsPlay())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("win.ogg",false);
	}
}

void Audio::playPop()
{
	if (GameData::getInstance()->getMusicIsPlay())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("select.ogg",false);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pop.ogg",false);
	}
}

void Audio::playCombo(int size)
{
	if (GameData::getInstance()->getMusicIsPlay())
	{
		if(size < 5)
			return;
		if(size >= 10)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("combo_3.ogg",false);
		}
		else if(size >= 7)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("combo_2.ogg",false);
		}
		else 
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("combo_1.ogg",false);
		}
	}
}

void Audio::prepare()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("readygo.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pop.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("combo_1.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("combo_2.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("combo_3.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("select.ogg");
}
