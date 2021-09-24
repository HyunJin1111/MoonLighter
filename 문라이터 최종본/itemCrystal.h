#pragma once
#include "itemBase.h"
class itemCrystal : public itemBase
{
public:
	itemCrystal();
	~itemCrystal();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

