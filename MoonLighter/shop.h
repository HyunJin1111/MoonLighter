#pragma once
#include "gameNode.h"
#include "UI.h"
#include "shopTileMap.h"

class player;

struct tagAlpha2
{
	float x, y;
	int currentFrameX, currentFrameY;
	int count;
	dImage* img;
	RECT rc;
	float alpha;
};

class shop : public gameNode
{
private:
	player* _player;
	UI* _ui;
	shopTileMap* _shopTileMap;

	tagAlpha2 _shopBack;
	tagAlpha2 _shopFront;

	tagAlpha2 _alpha;

	//씬전환시 사용
	RECT _door;
	tagUIobject _talkBaseShort;
	dImage* _talkButton;
	//윌 기상시 이미지 프레임
	tagAlpha2 _playerWakeUp;
	bool _isWakeUp;
	//담을 변수
	char _playerXchar[64];
	char _playerYchar[64];

	tagTile _vPlayer;
	tagTile _vTiles[TILEX * TILEY];
	vector<tagTile*> _vZorder;

public:
	shop();
	~shop();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void tileCheck();
	void linkPlayer(player* player) { _player = player; }

};

