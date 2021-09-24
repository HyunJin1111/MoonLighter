#pragma once
#include "gameNode.h"
#include "itemBase.h"
#include "itemLifeWater.h"
#include "itemGolemCore.h"
#include "itemBluePrint.h"
#include "itemBrokenSword.h"
#include "itemCrystal.h"
#include "itemHistoryBook.h"
#include "itemNote.h"
#include "itemSteel.h"
#include "itemStraw.h"
#include "itemWire.h"

class itemManager : public gameNode
{
private:
	vector<itemBase*>			_vItem;
	vector<itemBase*>::iterator _vIiItem;


	
public:
	itemManager();
	~itemManager();

	HRESULT init();
	void release();
	void update();
	void render();

	itemBase* getItem(string name);

	vector<itemBase*> getItemVector() { return _vItem; }
};

