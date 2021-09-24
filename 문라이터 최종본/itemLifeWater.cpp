#include "stdafx.h"
#include "itemLifeWater.h"

itemLifeWater::itemLifeWater()
{
}

itemLifeWater::~itemLifeWater()
{
}

HRESULT itemLifeWater::init()
{
	IMAGEMANAGER->addDImage("lifeWater", L"아이템/Item_LifeFluid.png", 32, 32);

	_item.name = "생명수";
	_item.infomation = "골렘던전에서만 나오는 생명수";
	_item.itemMax = 0;
	_item.img = IMAGEMANAGER->findDImage("lifeWater");
	return S_OK;
}

void itemLifeWater::release()
{
}

void itemLifeWater::update()
{
}

void itemLifeWater::render()
{
}
