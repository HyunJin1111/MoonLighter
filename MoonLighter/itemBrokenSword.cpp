#include "stdafx.h"
#include "itemBrokenSword.h"

itemBrokenSword::itemBrokenSword()
{
}

itemBrokenSword::~itemBrokenSword()
{
}

HRESULT itemBrokenSword::init()
{
	IMAGEMANAGER->addDImage("brokenSword", L"ITEM/book_item_01_BrokenSword.png", 32, 32);

	_item.name = "Break_Sword";
	_item.infomation = "Break_Sword";
	_item.itemMax = 0;
	_item.img = IMAGEMANAGER->findDImage("brokenSword");
	return S_OK;
}

void itemBrokenSword::release()
{
}

void itemBrokenSword::update()
{
}

void itemBrokenSword::render()
{
}
