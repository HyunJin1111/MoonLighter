#include "stdafx.h"
#include "itemStraw.h"

itemStraw::itemStraw()
{
}

itemStraw::~itemStraw()
{
}

HRESULT itemStraw::init()
{
	IMAGEMANAGER->addDImage("straw", L"������/Item_Straw.png", 32, 32);

	_item.name = "����";
	_item.infomation = "����";
	_item.itemMax = 0;
	_item.img = IMAGEMANAGER->findDImage("straw");

	return S_OK;
}

void itemStraw::release()
{
}

void itemStraw::update()
{
}

void itemStraw::render()
{
}
