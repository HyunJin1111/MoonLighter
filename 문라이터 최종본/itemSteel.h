#pragma once
#include "itemBase.h"
class itemSteel : public itemBase
{
public:
	itemSteel();
	~itemSteel();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

