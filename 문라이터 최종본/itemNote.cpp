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
	IMAGEMANAGER->addDImage("note", L"������/Item_NajaNotes.png", 32, 32);

	_item.name = "��Ʈ";
	_item.infomation = "��Ʈ";
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
