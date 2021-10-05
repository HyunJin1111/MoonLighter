#pragma once
#include "itemBase.h"
class itemBrokenSword :	public itemBase
{
public:
	itemBrokenSword();
	~itemBrokenSword();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

