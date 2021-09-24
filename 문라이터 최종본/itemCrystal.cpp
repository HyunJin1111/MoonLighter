#include "stdafx.h"
#include "itemCrystal.h"

itemCrystal::itemCrystal()
{
}

itemCrystal::~itemCrystal()
{
}

HRESULT itemCrystal::init()
{
	IMAGEMANAGER->addDImage("crystal", L"아이템/item_crystal_rock.png", 32, 32);

	_item.name = "크리스탈";
	_item.infomation = "크리스탈";
	_item.itemMax = 0;
	_item.img = IMAGEMANAGER->findDImage("crystal");
	return S_OK;
}

void itemCrystal::release()
{
}

void itemCrystal::update()
{
}

void itemCrystal::render()
{
}
