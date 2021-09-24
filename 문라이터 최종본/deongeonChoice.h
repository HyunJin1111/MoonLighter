#pragma once
#include "gameNode.h"
#include "player.h"
#include "deongeonChoiceTileMap.h"
#include "UI.h"

struct tagZorder
{
	float x, y;
	int currentFrameX, currentFrameY;
	int count;
	dImage* img;
	RECT rc;
	float alpha;
};
struct tagAlpha3
{
	float x, y;
	int currentFrameX, currentFrameY;
	int count;
	dImage* img;
	RECT rc;
	float alpha;
	bool isBool;
};
class deongeonChoice : public gameNode
{
private:
	player* _player;
	deongeonChoiceTileMap* _deongeonTileMap;
	UI* _ui;

	tagAlpha3 _alpha;

	//포탈 문
	RECT _dungeonIn;
	tagAlpha3 _portalDoorOpen;
	tagAlpha3 _portalDoorAtive;
	tagAlpha3 _portalDoorGo;

	RECT _loadVillage;
	tagUIobject _talkBaseShort;
	dImage* _talkButton;

	//담을 변수
	char _playerXchar[64];
	char _playerYchar[64];

	tagTile _vPlayer;
	tagTile _vTiles[TILEX * TILEY];
	vector<tagTile*> _vZorder;

	
public:
	deongeonChoice();
	~deongeonChoice();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	
	void tileCheck();
};

