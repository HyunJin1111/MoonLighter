#pragma once
#include "itemBase.h"
class itemGolemCore : public itemBase
{
public:
	itemGolemCore();
	~itemGolemCore();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

