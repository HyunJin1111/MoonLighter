#include "stdafx.h"
#include "itemSteel.h"

itemSteel::itemSteel()
{
}

itemSteel::~itemSteel()
{
}

HRESULT itemSteel::init()
{
	IMAGEMANAGER->addDImage("steel", L"ITEM/item_reinforced_steel_01.png", 32, 32);

	_item.name = "Steel";
	_item.infomation = "Steel";
	_item.itemMax = 0;
	_item.img = IMAGEMANAGER->findDImage("steel");

	return S_OK;
}

void itemSteel::release()
{
}

void itemSteel::update()
{
}

void itemSteel::render()
{
}
