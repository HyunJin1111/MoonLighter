#pragma once
#include "itemBase.h"
class itemStraw : public itemBase
{
public:
	itemStraw();
	~itemStraw();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

