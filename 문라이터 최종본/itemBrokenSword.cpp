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
	IMAGEMANAGER->addDImage("brokenSword", L"아이템/book_item_01_BrokenSword.png", 32, 32);

	_item.name = "부러진검";
	_item.infomation = "부러진검";
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
