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
	IMAGEMANAGER->addDImage("golemCore", L"ITEM/item_golem_core.png", 32, 32);

	_item.name = "Golem_core";
	_item.infomation = "�񷽴��������� ������ �ھ�";
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
