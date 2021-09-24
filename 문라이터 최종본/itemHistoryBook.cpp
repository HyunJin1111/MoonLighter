#include "stdafx.h"
#include "itemHistoryBook.h"

itemHistoryBook::itemHistoryBook()
{
}

itemHistoryBook::~itemHistoryBook()
{
}

HRESULT itemHistoryBook::init()
{
	IMAGEMANAGER->addDImage("historyBook", L"아이템/Item_GolemHistoryI.png", 32, 32);

	_item.name = "역사서";
	_item.infomation = "역사서";
	_item.itemMax = 0;
	_item.img = IMAGEMANAGER->findDImage("historyBook");
	return S_OK;
}

void itemHistoryBook::release()
{
}

void itemHistoryBook::update()
{
}

void itemHistoryBook::render()
{
}
