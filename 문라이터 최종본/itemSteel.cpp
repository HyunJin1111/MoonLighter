#include "stdafx.h"
#include "itemSteel.h"

itemSteel::itemSteel()
{
}

itemSteel::~itemSteel()
{
}

HRESULT itemSteel::init()
{
	IMAGEMANAGER->addDImage("steel", L"������/item_reinforced_steel_01.png", 32, 32);

	_item.name = "�ݼ�";
	_item.infomation = "�ݼ�";
	_item.itemMax = 0;
	_item.img = IMAGEMANAGER->findDImage("steel");

	return S_OK;
}

void itemSteel::release()
{
}

void itemSteel::update()
{
}

void itemSteel::render()
{
}
