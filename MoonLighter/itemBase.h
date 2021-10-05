#pragma once
#include "gameNode.h"

struct tagItem
{
	int x, y;
	int itemMax;
	dImage* img;
	RECT rc;
	string name;
	string infomation;
};



class itemBase : public gameNode
{
protected:

	tagItem _item;

public:
	itemBase();
	~itemBase();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual tagItem getItem() { return _item; }

	
	virtual void setItemMinus(int num) { _item.itemMax -= num; }
	virtual	void setItemName(string name) { _item.name = name; }
	virtual void setItemInfomation(string infomation) { _item.infomation = infomation; }
	virtual	void setItemItemMax(int itemMax) { _item.itemMax = itemMax; }
	virtual void setItemX(float x) { _item.x = x; }
	virtual void setItemY(float y) { _item.y = y; }
	virtual void setItemRC(RECT rc) { _item.rc = rc; }

};

