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
	IMAGEMANAGER->addDImage("bluePrint", L"������/item_golem_blue_print.png", 32, 32);

	_item.name = "���赵";
	_item.infomation = "���赵";
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
