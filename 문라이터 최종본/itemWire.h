#pragma once
#include "itemBase.h"
class itemWire : public itemBase
{
public:
	itemWire();
	~itemWire();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

