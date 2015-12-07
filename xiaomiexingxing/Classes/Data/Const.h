/*
 * Const.h
 *
 *  Created on: 2015-08-04
 *      Author: lichuang
 */

#ifndef CONST_H_
#define CONST_H_

#include "cocos2d.h"
#include <math.h>
#include <algorithm>

using namespace std;
USING_NS_CC;

//奖励物品
enum GoodsType
{
	goodsNone,
	Bomb,
	Tongsexiao,
	Huanse,
	Chexiao,
	Shuaxin,
	Zuanshi
};

enum PayResult
{
	Success = 0,//付费成功
	Failed,		//付费失败
	Cancel		//付费取消
};

//计费点
enum PayPoint
{
	payNone,				//无计费点
	Chaozhilibao99,			//超值礼包 99钻
	Chaozhilibao130,		//超值礼包 130钻
	Twoyuanlibao,			//2元礼包
	Fouryuanlibao,			//4元礼包
	Sixyuanlibao,			//6元礼包
	Tenyuanlibao,			//10元礼包
	Zhijietongguan,			//直接通关
	Tongguanbomb3,			//通关奖励 炸弹3个
	Tongguanbomb6,			//通关奖励 炸弹6个
	Tongguanbomb9,			//通关奖励 炸弹9个
	Tongguantsx3,			//通关奖励 同色消3个
	Tongguantsx6,			//通关奖励 同色消6个
	Tongguantsx9,			//通关奖励 同色消9个
	Logingift,				//登陆大礼包
	Exitgift				//退出大礼包
};

#define O_SCREEN_WIDTH 			(480.0) //屏幕原始宽度
#define O_SCREEN_HEIGHT  		(800.0) //屏幕原始高度
#define VISIBLE_SIZE			(Director::getInstance()->getVisibleSize())		//获取窗口可视区域大小

#define SCALEFACTOR				(VISIBLE_SIZE.height/O_SCREEN_HEIGHT)	//缩放因子 取其最大者值

#define MOVE_SPEED  			(9)
#define COLOR_MAX_NUM			(5)	 //星星的总种类
#define ROW_NUM  				(10) //10行星星
#define COL_NUM  				(10) //10列星星
#define REAL_STAR_WIDTH			(VISIBLE_SIZE.width/ROW_NUM)	//星星真实宽度
#define REAL_STAR_HEIGHT		(VISIBLE_SIZE.width/COL_NUM)	//星星真实高度
#define STAR_BOTTOM				(130)	//星星距离底部高度

#define ONE_CLEAR_TIME			(0.05f)

#define DialogPathBg			"otherDialogBg.png"
#define menuBg					"menubg.png"

#define GameContinueZuanshi		(20)		//读档消耗钻石
#define LayerOpacity			(100)		//层透明度

#define Bomb_Range				(1)	//炸弹爆炸的范围 2代表 5X5

#define BLINK_DURATION			(3.0f) //道具闪烁持续时间


#define Prop_LeftRight			(33)	//道具距离左右边框的距离
#define Prop_Middle				(VISIBLE_SIZE.width-Prop_LeftRight*2)			//获取道具所占宽度
#define Prop_Count				(5)	//道具的个数

#define Prop_Bomb_Money			(20)	//炸弹消耗钻石
#define Prop_Tongsexiao_Money	(30)	//同色消消耗钻石
#define Prop_Huanse_Money		(15)	//换色消耗钻石
#define Prop_Chexiao_Money		(10)	//撤销消耗钻石
#define Prop_Shuaxin_Money		(10)	//刷新消耗钻石

#define START_MIDDLE			(VISIBLE_SIZE.width-START_LEFTRIGHT*2)		//星星间的间距
#define START_LEFTRIGHT			(60)										//星星的边距

#define PropsWarningTime		(3.0) //道具警告时间

#define DIAMOND					(100)			//钻石

#define LotteryZuanshi			(15)		//抽奖价格

/***************以下暂未用到**********************************/
#define PROPS_BLINKS			5	//道具闪烁的次数


#define PROPS_WARNINGBLINKTIME	1.5	//道具警告闪烁时间
#define PROPS_WARNINGBLINKHZ	8.0	//道具警告闪烁频率
#define PROPS_WARNINGSCALEMULT	0.5	//道具警告缩放倍数

#define FIRSTCOMEAWARD 10			//第一次play钻石奖励

#define DIAMONDTWO	(2.0f)			//钻石价格 2元
#define DIAMONDFOUR	(4.0f)			//钻石价格 4元
#define DIAMONDSIX	(6.0f)			//钻石价格 6元
#define DIAMONDTEN	(10.0f)			//钻石价格 10元

#define ChallengeScore	(3100)		//挑战分数

#define CHALLENGEBEISHU	(5)			//挑战奖励倍数



#define MENULAYER_CSB	"csb/menuLayer.csb"
#define SHOPLAYER_CSB	"csb/shopLayer.csb"
#define BOOKLAYER_CSB	"csb/textLayer.csb"
#define CHALLENGELAYER_CSB "csb/challengeLayer.csb"

#define CREATECHILD_FUNC(__TYPE__) \
__TYPE__ createChild() \
	{ \
		__TYPE__ *layer = __TYPE__::create(); \
		if (layer == nullptr) \
				{ \
		layer = __TYPE__::create(); \
				} \
		return layer; \
	} \

#define CREATECHILDCSB_FUNC(_path) \
Node * createCsbChild() \
{ \
		Node *node = CSLoader::createNode(_path); \
		if (node == nullptr) \
		{ \
			node = CSLoader::createNode(_path); \
		} \
		if (node) \
		{ \
			this->addChild(node); \
		} \
		return node; \
} \

#define ADDCHILD_FUNC(__TYPE__) \
	__TYPE__ *layer = __TYPE__::create(); \
	if (layer == nullptr) \
		{ \
		layer = __TYPE__::create(); \
		} \
	if (layer) \
		{ \
		this->addChild(layer); \
	} \


#endif /* CONST_H_ */
