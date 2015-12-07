#include "GameDialogLayer.h"
#include "Data/GameData.h"
#include "Data/Const.h"
#include "Core/Helper.h"
#include "../Third/and_normal.h"

//数组索引
#define Index_ZUANSHI	0
#define Index_CHEXIAO 1
#define Index_HUANSE	2
#define Index_SHUAXIN	3

#define Index_LIBAO99		0
#define Index_LIBAO130		1
#define Index_TWO			2
#define Index_FOUR			3
#define Index_SIX			4
#define Index_TEN			5
#define Index_PASS			6
#define Index_ZHADAN3		7
#define Index_ZHADAN6		8
#define Index_ZHADAN9		9
#define Index_TONGSEXIAO3	10
#define Index_TONGSEXIAO6	11
#define Index_TONGSEXIAO9	12
#define Index_LOGIN			13
#define Index_EXIT			14

static string titleContinue = "previoustitle.png";
static string titleExit = "tuichu.png";
static string otherOkBtn = "menuOk.png";
static string otherCloseBtn = "menuClose.png";
static string otherDialogBg = "otherDialogBg.png";
static string dialogbg = "dialogBg.png";	//对话框背景
static string freeBg = "freegood.png";		//奇数关卡，免费奖励背景
static string closeBtn = "dialogClose.png";
static string okBtn = "dialogOk.png";
static string freeGoods[] = { "zuanshi.png", "chexiao.png", "huanse.png", "refurbish.png" };//奇数关卡奖励物品
static string payGoods[] = { "goods1.png", "goods2.png", "goods3.png", "goods4.png", "goods5.png", "goods6.png", "goods7.png", "goods8.png", "goods9.png",
							 "goods10.png", "goods11.png", "goods12.png", "goods13.png", "goods14.png", "goods15.png" };//偶数关卡奖励物品

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "Third/and_normal.h"
#include "Third/Game_native.h"
extern map<int, int> m_map;
#endif

GameDialogLayer::GameDialogLayer() :
m_dialogType(DialogType::NormalDialog),
m_childType(-1),
m_func(nullptr),
m_payFunc(nullptr),
m_noDataFunc(nullptr),
m_goodsNum(0),
m_goodsType(GoodsType::goodsNone),
m_freeGoodsNum(0),
m_payPoint(PayPoint::payNone)
{
	m_goodsMap.clear();
}


GameDialogLayer::~GameDialogLayer()
{
	//移除不用的缓存资源
	if (m_dialogType == DialogType::NormalDialog)
	{
		if (m_childType == NormalType::nGamePassed)
		{			
			TextureCache::getInstance()->removeTextureForKey(freeBg);
			TextureCache::getInstance()->removeTextureForKey("light.png");
			TextureCache::getInstance()->removeTextureForKey(dialogbg);
		}
		else if (m_childType == NormalType::nGameArchive)
		{
			TextureCache::getInstance()->removeTextureForKey(otherDialogBg);
		}
	}
	else
	{
		TextureCache::getInstance()->removeTextureForKey(dialogbg);
		TextureCache::getInstance()->removeTextureForKey(m_goodsName);
	}
}

GameDialogLayer *GameDialogLayer::createNoramlNoData(DialogType type, int childType, std::function<void(void)> func)
{
	GameDialogLayer *dialog = new GameDialogLayer;
	if (dialog && dialog->init(type, childType, func))
	{
		dialog->autorelease();
		return dialog;
	}

	CC_SAFE_DELETE(dialog);
	return nullptr;
}

GameDialogLayer *GameDialogLayer::createNoraml(DialogType type, int childType, std::function<void(map<int, int>, NormalType)> func)
{
	GameDialogLayer *dialog = new GameDialogLayer;
	if (dialog && dialog->init(type, childType, func))
	{
		dialog->autorelease();
		return dialog;
	}

	CC_SAFE_DELETE(dialog);
	return nullptr;
}

GameDialogLayer *GameDialogLayer::createPay(DialogType type, int childType, std::function<void(int, int, map<int, int>)> func)
{
	GameDialogLayer *dialog = new GameDialogLayer;
	if (dialog && dialog->init(type, childType, func))
	{
		dialog->autorelease();
		return dialog;
	}

	CC_SAFE_DELETE(dialog);
	return nullptr;
}

bool GameDialogLayer::init(DialogType type, int childType, std::function<void(map<int, int>, NormalType)> func)
{
	if (!StudioLayer::init(100/*, false*/))
	{
		return false;
	}

	m_dialogType = type;
	m_childType = childType;
	m_func = func;

	initFrame();

	return true;
}

bool GameDialogLayer::init(DialogType type, int childType, std::function<void(int, int, map<int, int>)> func)
{
	if (!StudioLayer::init(100, false))
	{
		return false;
	}

	m_dialogType = type;
	m_childType = childType;
	m_payFunc = func;

	initFrame();

	map<string, string> _map;
	_map["point"] = cocos2d::Value(m_payPoint).asString();
	UmengUpload::event(Umeng_Id_Payrequest, &_map);

	return true;
}

bool GameDialogLayer::init(DialogType type, int childType, std::function<void(void)> func)
{
	if (!StudioLayer::init(100/*, false*/))
	{
		return false;
	}

	m_dialogType = type;
	m_childType = childType;
	m_noDataFunc = func;

	initFrame();

	return true;
}

void GameDialogLayer::onEnter()
{
	StudioLayer::onEnter();

	auto keyboardlistener = EventListenerKeyboard::create();
	keyboardlistener->onKeyReleased = CC_CALLBACK_2(GameDialogLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardlistener, this);

	initUI();
}

void GameDialogLayer::initUI()
{
	string path = "";
	string colse = "";
	string ok = "";
	if (m_dialogType == DialogType::NormalDialog && (m_childType == NormalType::nGameArchive || m_childType == NormalType::nGameContinue || m_childType == NormalType::nGameExit))
	{
		path = otherDialogBg;
		colse = otherCloseBtn;
		ok = otherOkBtn;
	}
	else
	{
		path = dialogbg;
		colse = closeBtn;
		ok = okBtn;
	}
	m_dialogBg = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey(path));
	m_dialogBg->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	this->addChild(m_dialogBg);

	if (m_dialogType == DialogType::NormalDialog)
	{
		NormalType type = NormalType(m_childType);
		switch (type)
		{
		case NormalType::nGamePassed:
			initUiWithGamePassed();
			break;
		case NormalType::nGameExit:
			initUiWithGameHaveTitle();
			break;
		case NormalType::nGameArchive:
			initUiWithGameArchive();
			break;
		case NormalType::nGameContinue:
			initUiWithGameHaveTitle();
		default:
			break;
		}
	}
	else if (m_dialogType == DialogType::PayDialog)
	{
		PayType type = PayType(m_childType);
		switch (type)
		{
		case PayType::pGameFailed:
			//initPayDialog();
			//break;
		case PayType::pGamePassed:
			//initPayDialog();
			//break;
		case PayType::pGameLibao99:
			//initPayDialog();
			//break;
		case PayType::pGameLibao130:
			//initPayDialog();
			//break;
		case PayType::pGameExit:
			//initPayDialog();
			//break;
		case PayType::pGameLogin:
			//break;
		case PayType::pGameTwo:
		case PayType::pGameFour:
		case PayType::pGameSix:
		case PayType::pGameTen:
			initPayDialog();
			break;
		default:
			break;
		}
	}

	Size size = m_dialogBg->getContentSize();
	SpriteFrame * frame = nullptr;
	if (m_dialogType == DialogType::PayDialog)
	{
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(ok);
		if (frame == nullptr)
		{
			ok = otherOkBtn;
		}
	}	
	
	auto closeSp = Sprite::createWithSpriteFrameName(colse);
	auto closeItem = MenuItemSprite::create(closeSp, closeSp, closeSp, CC_CALLBACK_0(GameDialogLayer::onMenuItemCallBack, this, 1));
	closeItem->setPosition(Vec2(m_dialogBg->getPosition() + Vec2(size.width / 2 - closeItem->getContentSize().width, size.height / 2 - closeItem->getContentSize().height)));

	auto okSp = Sprite::createWithSpriteFrameName(ok);
	auto okItem = MenuItemSprite::create(okSp, okSp, okSp, CC_CALLBACK_0(GameDialogLayer::onMenuItemCallBack, this, 2));
	okItem->setPosition(Vec2(m_dialogBg->getPosition() + Vec2(0, -size.height / 2 + okItem->getContentSize().height * 0.8)));

	auto menu = Menu::create(closeItem, okItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}

void GameDialogLayer::initUiWithGamePassed()
{
	//奇数关免费 偶数关付费
	if (m_childType == NormalType::nGamePassed) //奇数
	{
		auto light = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("light.png"));
		light->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
		this->addChild(light);

		auto freebg = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey(freeBg));
		freebg->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
		this->addChild(freebg);
		
		auto goods = Sprite::createWithSpriteFrameName(m_goodsName);
		goods->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height * 0.475));
		goods->setScale(1.5f);
		this->addChild(goods);

		auto num = NumSprite::create(m_goodsNum,NumberType::GameNumberAward);
		num->setPosition(Vec2(VISIBLE_SIZE.width * 0.75, VISIBLE_SIZE.height * 0.475));
		num->setScale(2.0f);
		this->addChild(num);
	}
	else    //偶数
	{
		initPayDialog();
	}
}

void GameDialogLayer::initUiWithGameArchive()
{
	auto goods = Sprite::createWithSpriteFrameName(m_goodsName);
	goods->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	this->addChild(goods);
}

void GameDialogLayer::initUiWithGameHaveTitle()
{
	string title = "";
	if (m_childType == NormalType::nGameContinue)
	{
		title = titleContinue;
	}
	else if (m_childType == NormalType::nGameExit)
	{
		title = titleExit;
	}
	auto spTitle = Sprite::createWithSpriteFrameName(title);
	spTitle->setPosition(m_dialogBg->getPosition() + Vec2(0, m_dialogBg->getContentSize().height / 2 - spTitle->getContentSize().height));
	this->addChild(spTitle);

	auto goods = Sprite::createWithSpriteFrameName(m_goodsName);
	goods->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	this->addChild(goods);
}

void GameDialogLayer::initPayDialog()
{
	auto goods = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey(m_goodsName));
	goods->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	this->addChild(goods);
}

void GameDialogLayer::initFrame()
{
	if (m_dialogType == DialogType::NormalDialog && (m_childType == NormalType::nGameArchive || m_childType == NormalType::nGameContinue || m_childType == nGameExit))
	{
		TextureCache::getInstance()->addImage(otherDialogBg);
	}
	else
	{
		TextureCache::getInstance()->addImage(dialogbg);
	}
	if (m_dialogType == DialogType::NormalDialog)
	{
		if (m_childType == NormalType::nGamePassed)
		{
			int lv = GameData::getInstance()->getNextLevel();
			int rand = cocos2d::random() % 100;
			m_goodsNum = ceil(lv / 10.0);

			if (GameData::getInstance()->getGameMode() == GameData::GameChallenge)
			{
				rand = 60;
				m_goodsNum = GameData::getInstance()->getChallengeZuanshi() * (5 - 1);
			}
			if (rand >= 0 && rand < 10)
			{
				m_goodsType = GoodsType::Huanse;
				m_goodsName = freeGoods[Index_HUANSE];
			}
			else if (rand >= 10 && rand < 30)
			{
				m_goodsType = GoodsType::Shuaxin;
				m_goodsName = freeGoods[Index_SHUAXIN];
			}
			else if (rand >= 30 && rand < 50)
			{
				m_goodsType = GoodsType::Chexiao;
				m_goodsName = freeGoods[Index_CHEXIAO];
			}
			else
			{
				m_goodsType = GoodsType::Zuanshi;
				m_goodsName = freeGoods[Index_ZUANSHI];
			}
			m_goodsMap.insert(pair<int, int>(m_goodsType, m_goodsNum));
			TextureCache::getInstance()->addImage(freeBg);
			TextureCache::getInstance()->addImage("light.png");
		}
		else if (m_childType == NormalType::nGameArchive)
		{
			m_goodsName = "CovertTip.png";
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("text.plist");
		}
		else if (m_childType == NormalType::nGameContinue)
		{
			m_goodsName = "previoustext.png";
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("text.plist");
		}
		else if (m_childType == NormalType::nGameExit)
		{
			m_goodsName = "tuichutext.png";
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("text.plist");
		}
	}
	else
	{
		if (m_childType == PayType::pGamePassed)
		{
			int lv = GameData::getInstance()->getNextLevel();
			int rand = cocos2d::random() % 100;
			if (rand >= 0 && rand < 50)	//zhadan
			{
				m_goodsType = GoodsType::Bomb;
			}
			else //tongsexiao
			{
				m_goodsType = GoodsType::Tongsexiao;
			}

			if (lv > 0 && lv <= 10)
			{
				m_goodsNum = 3;
				m_goodsName = (m_goodsType == GoodsType::Bomb ? payGoods[Index_ZHADAN3] : payGoods[Index_TONGSEXIAO3]);
				m_payPoint = (m_goodsType == GoodsType::Bomb ? PayPoint::Tongguanbomb3 : PayPoint::Tongguantsx3);
			}
			else if (lv > 10 && lv <= 20)
			{
				m_goodsNum = 6;
				m_goodsName = (m_goodsType == GoodsType::Bomb ? payGoods[Index_ZHADAN6] : payGoods[Index_TONGSEXIAO6]);
				m_payPoint = (m_goodsType == GoodsType::Bomb ? PayPoint::Tongguanbomb6 : PayPoint::Tongguantsx6);
			}
			else
			{
				m_goodsNum = 9;
				m_goodsName = (m_goodsType == GoodsType::Bomb ? payGoods[Index_ZHADAN9] : payGoods[Index_TONGSEXIAO9]);
				m_payPoint = (m_goodsType == GoodsType::Bomb ? PayPoint::Tongguanbomb9 : PayPoint::Tongguantsx9);
			}
			m_freeGoodsNum = 145;
			m_goodsMap.insert(pair<int, int>(m_goodsType, m_goodsNum));
			m_goodsMap.insert(pair<int, int>(GoodsType::Zuanshi, m_freeGoodsNum));
			TextureCache::getInstance()->addImage(m_goodsName);
		}
		else if (m_childType == PayType::pGameFailed)
		{
			m_goodsType = GoodsType::Zuanshi;
			m_goodsNum = 99;
			m_goodsName = payGoods[Index_PASS];
			m_payPoint = PayPoint::Zhijietongguan;
			m_goodsMap.insert(pair<int, int>(m_goodsType, m_goodsNum));
		}
		else if (m_childType == PayType::pGameLibao99)
		{
			m_goodsName = payGoods[Index_LIBAO99];
			m_payPoint = PayPoint::Chaozhilibao99;
			m_goodsMap.insert(pair<int, int>(GoodsType::Bomb, 5));
			m_goodsMap.insert(pair<int, int>(GoodsType::Tongsexiao, 5));
			m_goodsMap.insert(pair<int, int>(GoodsType::Huanse, 1));
			m_goodsMap.insert(pair<int, int>(GoodsType::Chexiao, 1));
			m_goodsMap.insert(pair<int, int>(GoodsType::Shuaxin, 1));
			m_goodsMap.insert(pair<int, int>(GoodsType::Zuanshi, 99));
		}
		else if (m_childType == PayType::pGameLibao130)
		{
			m_goodsName = payGoods[Index_LIBAO130];
			m_payPoint = PayPoint::Chaozhilibao130;
			m_goodsMap.insert(pair<int, int>(GoodsType::Bomb, 1));
			m_goodsMap.insert(pair<int, int>(GoodsType::Tongsexiao, 1));
			m_goodsMap.insert(pair<int, int>(GoodsType::Huanse, 5));
			m_goodsMap.insert(pair<int, int>(GoodsType::Chexiao, 5));
			m_goodsMap.insert(pair<int, int>(GoodsType::Shuaxin, 5));
			m_goodsMap.insert(pair<int, int>(GoodsType::Zuanshi, 130));
		}
		else if (m_childType == PayType::pGameExit)
		{
			m_goodsName = payGoods[Index_EXIT];
			m_payPoint = PayPoint::Exitgift;
			m_goodsMap.insert(pair<int, int>(GoodsType::Zuanshi, 175));
		}
		else if (m_childType == PayType::pGameLogin)
		{
			m_goodsName = payGoods[Index_LOGIN];
			m_payPoint = PayPoint::Logingift;
			m_goodsMap.insert(pair<int, int>(GoodsType::Bomb, 3));
			m_goodsMap.insert(pair<int, int>(GoodsType::Tongsexiao, 3));
			m_goodsMap.insert(pair<int, int>(GoodsType::Huanse, 3));
			m_goodsMap.insert(pair<int, int>(GoodsType::Chexiao, 3));
			m_goodsMap.insert(pair<int, int>(GoodsType::Shuaxin, 3));
			m_goodsMap.insert(pair<int, int>(GoodsType::Zuanshi, 130));
		}
		else if (m_childType == PayType::pGameTwo)
		{
			m_goodsName = payGoods[Index_TWO];
			m_payPoint = PayPoint::Twoyuanlibao;
			m_goodsMap.insert(pair<int, int>(GoodsType::Zuanshi, 25 + (checkFirstShop() ? 2 * 10 : 0)));
		}
		else if (m_childType == PayType::pGameFour)
		{
			m_goodsName = payGoods[Index_FOUR];
			m_payPoint = PayPoint::Fouryuanlibao;
			m_goodsMap.insert(pair<int, int>(GoodsType::Zuanshi, 55 + (checkFirstShop() ? 4 * 10 : 0)));
		}
		else if (m_childType == PayType::pGameSix)
		{
			m_goodsName = payGoods[Index_SIX];
			m_payPoint = PayPoint::Sixyuanlibao;
			m_goodsMap.insert(pair<int, int>(GoodsType::Zuanshi, 85 + (checkFirstShop() ? 6 * 10 : 0)));
		}
		else if (m_childType == PayType::pGameTen)
		{
			m_goodsName = payGoods[Index_TEN];
			m_payPoint = PayPoint::Tenyuanlibao;
			m_goodsMap.insert(pair<int, int>(GoodsType::Zuanshi, 145 + (checkFirstShop() ? 10 * 10 : 0)));
		}

		TextureCache::getInstance()->addImage(m_goodsName);
	}
}

void GameDialogLayer::onMenuItemCallBack(int type)
{
	if (type == 1)	//close
	{
		dealClose();
	}
	else if (type == 2)	//ok
	{
		dealOk();
	}

	if (m_dialogType == DialogType::PayDialog)
	{
		StudioLayer::removeSelf();
	}
	else
	{
		StudioLayer::closeLayer();
	}
}

void GameDialogLayer::dealClose()
{
	if (m_dialogType == DialogType::NormalDialog)
	{
		normalDealClose();
	}
	else if (m_dialogType == DialogType::PayDialog)
	{
		payDealClose();
	}
}

void GameDialogLayer::dealOk()
{
	if (m_dialogType == DialogType::NormalDialog)
	{
		normalDealOk();
	}
	else if (m_dialogType == DialogType::PayDialog)
	{
		payDealOk();
	}
}

void GameDialogLayer::normalDealClose()
{
	NormalType type = NormalType(m_childType);
	if (m_childType == NormalType::nGamePassed)
	{
		if (m_func)
		{
			if (GameData::getInstance()->getGameMode() == GameData::GameNormal)
			{
				m_goodsMap.clear();
			}
			m_func(m_goodsMap, (NormalType)m_childType);
		}
	}
}

void GameDialogLayer::normalDealOk()
{
	NormalType type = NormalType(m_childType);
	if (m_childType == NormalType::nGamePassed)
	{
		if (m_func)
		{
			m_func(m_goodsMap, (NormalType)m_childType);
		}
	}
	else if (m_childType == NormalType::nGameArchive || m_childType == NormalType::nGameContinue || m_childType == NormalType::nGameExit)
	{
		if (m_noDataFunc)
		{
			m_noDataFunc();
		}
	}
}

void GameDialogLayer::payDealClose()
{
	PayType type = PayType(m_childType);

	if (type == PayType::pGamePassed || type == PayType::pGameFailed || type == PayType::pGameLibao99 || type == PayType::pGameLibao130 || type == PayType::pGameExit || type == PayType::pGameLogin ||
		type == PayType::pGameTwo || type == PayType::pGameFour || type == PayType::pGameSix || type == PayType::pGameTen)
	{
		if (m_payFunc)
		{
			map<string, string> _map;
			_map["point"] = cocos2d::Value(m_payPoint).asString();
			UmengUpload::event(Umeng_Id_Paycancel, &_map);
			m_goodsMap.clear();
			m_payFunc(m_payPoint, PayResult::Cancel, m_goodsMap);
		}
	}
}

void GameDialogLayer::payDealOk()
{
#if (CC_TARGET_PLATFORM ==  CC_PLATFORM_WIN32)
	if (m_payFunc && m_payPoint != PayPoint::payNone)
	{
		m_payFunc(m_payPoint, PayResult::Success, m_goodsMap);
	}
#else
	//调支付接口
	map<string,string> _map;
	_map["point"] = cocos2d::Value(m_payPoint).asString();
	UmengUpload::event(Umeng_Id_Payqueren,&_map);
	m_map = m_goodsMap;
	setCallBack(m_payFunc);
	and_normal::payment(m_payPoint);
#endif
}

void GameDialogLayer::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	if (event->getType() == Event::Type::KEYBOARD)
	{
		event->stopPropagation();
	}
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_BACK:
		if (m_dialogType == DialogType::PayDialog)
		{
			//StudioLayer::removeSelf();
		}
		else
		{
			dealClose();
			StudioLayer::closeLayer();
		}
		break;
	}
}

bool GameDialogLayer::checkFirstShop()
{
	int ret = getCurrentDays(0) - GameData::getInstance()->getFirstShopTime();
	if (ret)
	{
		GameData::getInstance()->setFirstShopTime(getCurrentDays(0));
	}
	return ret;
}
