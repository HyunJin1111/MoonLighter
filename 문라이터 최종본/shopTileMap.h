#pragma once
#include "gameNode.h"
#include "tileMap.h"

class shopTileMap : public gameNode
{
	tagTile _tiles[TILEX*TILEY];

public:
	shopTileMap();
	~shopTileMap();

	HRESULT init();
	void release();
	void update();
	void render();
	void objectRender();
	void load();

	tagTile getTile(int index) { return _tiles[index]; }
};

