#include "stdafx.h"
#include "itemBluePrint.h"

itemBluePrint::itemBluePrint()
{
}

itemBluePrint::~itemBluePrint()
{
}

HRESULT itemBluePrint::init()
{
	IMAGEMANAGER->addDImage("bluePrint", L"아이템/item_golem_blue_print.png", 32, 32);

	_item.name = "설계도";
	_item.infomation = "설계도";
	_item.itemMax = 0;
	_item.img = IMAGEMANAGER->findDImage("bluePrint");
	return S_OK;
}

void itemBluePrint::release()
{
}

void itemBluePrint::update()
{
}

void itemBluePrint::render()
{
}
