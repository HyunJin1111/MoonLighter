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
	if (name == "Life_Water") 
	{
		itemLifeWater* _itemLifeWater = new itemLifeWater;
		_itemLifeWater->init();

		return _itemLifeWater;
	}
	if (name == "Golem_core") 
	{
		 itemGolemCore* _itemGolemcore = new itemGolemCore;
		 _itemGolemcore->init();

		return _itemGolemcore;
	}
	if (name == "blueprint") 
	{
		itemBluePrint* _itemBluePrint = new itemBluePrint;
		 _itemBluePrint->init();

		return _itemBluePrint;
	}
	if (name == "Break_Sword") 
	{
		 itemBrokenSword* _itemBrokenSword = new itemBrokenSword;
		 _itemBrokenSword->init();

		return _itemBrokenSword;
	}
	if (name == "Crystal") 
	{
		 itemCrystal* _itemCrystal = new itemCrystal;
		 _itemCrystal->init();

		return _itemCrystal;
	}
	if (name == "History_Book") 
	{
		 itemHistoryBook* _itemHistoryBook = new itemHistoryBook;
		 _itemHistoryBook->init();

		return _itemHistoryBook;
	}
	if (name == "Note") 
	{
		 itemNote* _itemNote = new itemNote;
		 _itemNote->init();

		return _itemNote;
	}
	if (name == "Steel") 
	{
		 itemSteel* _itemSteel = new itemSteel;
		 _itemSteel->init();

		return _itemSteel;
	}
	if (name == "Straw") 
	{
		 itemStraw* _itemStraw = new itemStraw;
		 _itemStraw->init();

		return _itemStraw;
	}
	if (name == "Electronic_Line") 
	{
		 itemWire* _itemWire = new itemWire;
		 _itemWire->init();

		return _itemWire;
	}


	return nullptr;
}
