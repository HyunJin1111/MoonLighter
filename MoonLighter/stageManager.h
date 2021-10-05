#pragma once
#include "gameNode.h"
#include "intro.h"
#include "tileMap.h"
#include "village.h"
#include "shop.h"
#include "deongeonChoice.h"
#include "dungeon.h"

class stageManager : public gameNode
{
private:

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void sceneSet();
};

