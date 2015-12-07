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

//������Ʒ
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
	Success = 0,//���ѳɹ�
	Failed,		//����ʧ��
	Cancel		//����ȡ��
};

//�Ʒѵ�
enum PayPoint
{
	payNone,				//�޼Ʒѵ�
	Chaozhilibao99,			//��ֵ��� 99��
	Chaozhilibao130,		//��ֵ��� 130��
	Twoyuanlibao,			//2Ԫ���
	Fouryuanlibao,			//4Ԫ���
	Sixyuanlibao,			//6Ԫ���
	Tenyuanlibao,			//10Ԫ���
	Zhijietongguan,			//ֱ��ͨ��
	Tongguanbomb3,			//ͨ�ؽ��� ը��3��
	Tongguanbomb6,			//ͨ�ؽ��� ը��6��
	Tongguanbomb9,			//ͨ�ؽ��� ը��9��
	Tongguantsx3,			//ͨ�ؽ��� ͬɫ��3��
	Tongguantsx6,			//ͨ�ؽ��� ͬɫ��6��
	Tongguantsx9,			//ͨ�ؽ��� ͬɫ��9��
	Logingift,				//��½�����
	Exitgift				//�˳������
};

#define O_SCREEN_WIDTH 			(480.0) //��Ļԭʼ���
#define O_SCREEN_HEIGHT  		(800.0) //��Ļԭʼ�߶�
#define VISIBLE_SIZE			(Director::getInstance()->getVisibleSize())		//��ȡ���ڿ��������С

#define SCALEFACTOR				(VISIBLE_SIZE.height/O_SCREEN_HEIGHT)	//�������� ȡ�������ֵ

#define MOVE_SPEED  			(9)
#define COLOR_MAX_NUM			(5)	 //���ǵ�������
#define ROW_NUM  				(10) //10������
#define COL_NUM  				(10) //10������
#define REAL_STAR_WIDTH			(VISIBLE_SIZE.width/ROW_NUM)	//������ʵ���
#define REAL_STAR_HEIGHT		(VISIBLE_SIZE.width/COL_NUM)	//������ʵ�߶�
#define STAR_BOTTOM				(130)	//���Ǿ���ײ��߶�

#define ONE_CLEAR_TIME			(0.05f)

#define DialogPathBg			"otherDialogBg.png"
#define menuBg					"menubg.png"

#define GameContinueZuanshi		(20)		//����������ʯ
#define LayerOpacity			(100)		//��͸����

#define Bomb_Range				(1)	//ը����ը�ķ�Χ 2���� 5X5

#define BLINK_DURATION			(3.0f) //������˸����ʱ��


#define Prop_LeftRight			(33)	//���߾������ұ߿�ľ���
#define Prop_Middle				(VISIBLE_SIZE.width-Prop_LeftRight*2)			//��ȡ������ռ���
#define Prop_Count				(5)	//���ߵĸ���

#define Prop_Bomb_Money			(20)	//ը��������ʯ
#define Prop_Tongsexiao_Money	(30)	//ͬɫ��������ʯ
#define Prop_Huanse_Money		(15)	//��ɫ������ʯ
#define Prop_Chexiao_Money		(10)	//����������ʯ
#define Prop_Shuaxin_Money		(10)	//ˢ��������ʯ

#define START_MIDDLE			(VISIBLE_SIZE.width-START_LEFTRIGHT*2)		//���Ǽ�ļ��
#define START_LEFTRIGHT			(60)										//���ǵı߾�

#define PropsWarningTime		(3.0) //���߾���ʱ��

#define DIAMOND					(100)			//��ʯ

#define LotteryZuanshi			(15)		//�齱�۸�

/***************������δ�õ�**********************************/
#define PROPS_BLINKS			5	//������˸�Ĵ���


#define PROPS_WARNINGBLINKTIME	1.5	//���߾�����˸ʱ��
#define PROPS_WARNINGBLINKHZ	8.0	//���߾�����˸Ƶ��
#define PROPS_WARNINGSCALEMULT	0.5	//���߾������ű���

#define FIRSTCOMEAWARD 10			//��һ��play��ʯ����

#define DIAMONDTWO	(2.0f)			//��ʯ�۸� 2Ԫ
#define DIAMONDFOUR	(4.0f)			//��ʯ�۸� 4Ԫ
#define DIAMONDSIX	(6.0f)			//��ʯ�۸� 6Ԫ
#define DIAMONDTEN	(10.0f)			//��ʯ�۸� 10Ԫ

#define ChallengeScore	(3100)		//��ս����

#define CHALLENGEBEISHU	(5)			//��ս��������



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
