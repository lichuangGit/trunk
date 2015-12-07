#ifndef SHOPLAYER_H
#define SHOPLAYER_H

#include "StudioLayer.h"
#include "GameDialogLayer.h"
#include "Core/Helper.h"

class ShopLayer : public StudioLayer
{
public:
	ShopLayer();
	~ShopLayer();

	virtual bool init();
	CREATE_FUNC(ShopLayer);

	void onEnter();

private:
	void initUI();

	void onBtnClick(Ref *pSender, Widget::TouchEventType type);

	/*
	*����:	����
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-22-18:23                                                                   
	*/
	void popOutDialog(PayType type);

	/*
	*����:	֧���ص�
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-11-2-16:57
	*/
	void payDialogCallBack(int point, int result, std::map<int, int> _map);

	/*
	*����:	������Ʒ����������ˢ��ҳ����ʾ
	*param:
	*����ֵ:
	*����: lichuang
	*����:2015-10-17-15:12
	*/
	void updateGoodsNumber(GoodsType type, int num);

	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

private:
	Button *m_btnTwo;
	Button *m_btnFour;
	Button *m_btnSix;
	Button *m_btnTen;
	Button *m_btnClose;
	NumSprite *m_numSp;
};

#endif
