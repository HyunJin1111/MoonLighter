#pragma once
#include "itemBase.h"
class itemBluePrint : public itemBase
{
public:
	itemBluePrint();
	~itemBluePrint();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

