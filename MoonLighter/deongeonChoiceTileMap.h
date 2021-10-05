#pragma once
#include "gameNode.h"
#include "tileMap.h"

class deongeonChoiceTileMap : public gameNode
{
private:
	tagTile _tiles[TILEX*TILEY];

public:
	deongeonChoiceTileMap();
	~deongeonChoiceTileMap();

	HRESULT init();
	void release();
	void update();
	void render();
	void objectRender();
	void load();

	tagTile getTile(int index) { return _tiles[index]; }
};

