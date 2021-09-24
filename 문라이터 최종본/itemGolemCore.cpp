#include "stdafx.h"
#include "itemGolemCore.h"

itemGolemCore::itemGolemCore()
{
}

itemGolemCore::~itemGolemCore()
{
}

HRESULT itemGolemCore::init()
{
	IMAGEMANAGER->addDImage("golemCore", L"¾ÆÀÌÅÛ/item_golem_core.png", 32, 32);

	_item.name = "°ñ·½ÄÚ¾î";
	_item.infomation = "°ñ·½´øÀü¿¡¼­¸¸ ³ª¿À´Â ÄÚ¾î";
	_item.itemMax = 0;
	_item.img = IMAGEMANAGER->findDImage("golemCore");
	return S_OK;
}

void itemGolemCore::release()
{
}

void itemGolemCore::update()
{
}

void itemGolemCore::render()
{
}
