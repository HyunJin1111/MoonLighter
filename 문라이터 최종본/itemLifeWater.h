#pragma once
#include "itemBase.h"


class itemLifeWater : public itemBase
{
public:
	itemLifeWater();
	~itemLifeWater();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

