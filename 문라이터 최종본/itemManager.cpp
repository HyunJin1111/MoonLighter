#include "stdafx.h"
#include "itemManager.h"

itemManager::itemManager()
{
}

itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
	



	return S_OK;
}

void itemManager::release()
{
}

void itemManager::update()
{
}

void itemManager::render()
{

}

itemBase* itemManager::getItem(string name)
{
	if (name == "생명수") 
	{
		itemLifeWater* _itemLifeWater = new itemLifeWater;
		_itemLifeWater->init();

		return _itemLifeWater;
	}
	if (name == "골렘코어") 
	{
		 itemGolemCore* _itemGolemcore = new itemGolemCore;
		 _itemGolemcore->init();

		return _itemGolemcore;
	}
	if (name == "설계도") 
	{
		itemBluePrint* _itemBluePrint = new itemBluePrint;
		 _itemBluePrint->init();

		return _itemBluePrint;
	}
	if (name == "부러진검") 
	{
		 itemBrokenSword* _itemBrokenSword = new itemBrokenSword;
		 _itemBrokenSword->init();

		return _itemBrokenSword;
	}
	if (name == "크리스탈") 
	{
		 itemCrystal* _itemCrystal = new itemCrystal;
		 _itemCrystal->init();

		return _itemCrystal;
	}
	if (name == "역사서") 
	{
		 itemHistoryBook* _itemHistoryBook = new itemHistoryBook;
		 _itemHistoryBook->init();

		return _itemHistoryBook;
	}
	if (name == "노트") 
	{
		 itemNote* _itemNote = new itemNote;
		 _itemNote->init();

		return _itemNote;
	}
	if (name == "금속") 
	{
		 itemSteel* _itemSteel = new itemSteel;
		 _itemSteel->init();

		return _itemSteel;
	}
	if (name == "빨대") 
	{
		 itemStraw* _itemStraw = new itemStraw;
		 _itemStraw->init();

		return _itemStraw;
	}
	if (name == "전선") 
	{
		 itemWire* _itemWire = new itemWire;
		 _itemWire->init();

		return _itemWire;
	}


	return nullptr;
}
