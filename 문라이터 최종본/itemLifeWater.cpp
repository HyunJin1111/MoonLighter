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
	IMAGEMANAGER->addDImage("lifeWater", L"������/Item_LifeFluid.png", 32, 32);

	_item.name = "�����";
	_item.infomation = "�񷽴��������� ������ �����";
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
