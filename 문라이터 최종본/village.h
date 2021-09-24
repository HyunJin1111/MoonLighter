#pragma once
#include "gameNode.h"
#include "villageTileMap.h"
#include "player.h"
#include "UI.h"


struct tagAlpha
{
	float x, y;
	int currentFrameX, currentFrameY;
	int count;
	dImage* img;
	RECT rc;
	float alpha;
	bool isTrue;
};
class village :	public gameNode
{
private:
	villageTileMap* _villageTilemap;
	player* _player;
	UI* _ui;

	tagAlpha _alpha;
	//NPC
	tagAlpha _blackSmith;
	tagAlpha _witch;
	tagAlpha _extra1;
	tagAlpha _extra2;

	tagTile _vExtra1;
	tagTile _vExtra2;

	RECT _door;
	RECT _roadDeongeon[2];
	tagUIobject _talkBaseShort;
	dImage* _talkButton;

	//담을 변수
	char _playerXchar[64];
	char _playerYchar[64];

	tagTile _vHouse;
	tagTile _vtree1[TILEX * TILEY];
	tagTile _vtree2[TILEX * TILEY];
	tagTile _vtree3[TILEX * TILEY];
	tagTile _fountain[TILEX * TILEY];
	tagTile _well[TILEX * TILEY];

	tagTile _vPlayer;
	tagTile _vTiles[TILEX * TILEY];
	vector<tagTile*> _vZorder;


public:
	village();
	~village();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void tileCheck();
	void extraFrame();

};

