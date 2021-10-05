#pragma once
#include "itemBase.h"
class itemNote : public itemBase
{
public:
	itemNote();
	~itemNote();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

