#pragma once
#include "itemBase.h"
class itemHistoryBook :	public itemBase
{
public:
	itemHistoryBook();
	~itemHistoryBook();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

