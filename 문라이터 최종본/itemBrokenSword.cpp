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
	IMAGEMANAGER->addDImage("brokenSword", L"������/book_item_01_BrokenSword.png", 32, 32);

	_item.name = "�η�����";
	_item.infomation = "�η�����";
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
