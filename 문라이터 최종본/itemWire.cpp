#include "stdafx.h"
#include "itemWire.h"

itemWire::itemWire()
{
}

itemWire::~itemWire()
{
}

HRESULT itemWire::init()
{
	IMAGEMANAGER->addDImage("wire", L"아이템/item_rune_tool.png", 32, 32);

	_item.name = "전선";
	_item.infomation = "전선";
	_item.itemMax = 0;
	_item.img = IMAGEMANAGER->findDImage("wire");

	return S_OK;
}

void itemWire::release()
{
}

void itemWire::update()
{
}

void itemWire::render()
{
}
