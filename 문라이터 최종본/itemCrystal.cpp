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
	IMAGEMANAGER->addDImage("crystal", L"������/item_crystal_rock.png", 32, 32);

	_item.name = "ũ����Ż";
	_item.infomation = "ũ����Ż";
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
