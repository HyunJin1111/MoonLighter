#include "stdafx.h"
#include "itemNote.h"

itemNote::itemNote()
{
}

itemNote::~itemNote()
{
}

HRESULT itemNote::init()
{
	IMAGEMANAGER->addDImage("note", L"아이템/Item_NajaNotes.png", 32, 32);

	_item.name = "노트";
	_item.infomation = "노트";
	_item.itemMax = 0;
	_item.img = IMAGEMANAGER->findDImage("note");
	
	return S_OK;
}

void itemNote::release()
{
}

void itemNote::update()
{
}

void itemNote::render()
{
}
