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
	IMAGEMANAGER->addDImage("wire", L"ITEM/item_rune_tool.png", 32, 32);

	_item.name = "Electronic_Line";
	_item.infomation = "Electronic_Line";
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
