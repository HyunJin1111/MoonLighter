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

	//����ȯ�� ���
	RECT _door;
	tagUIobject _talkBaseShort;
	dImage* _talkButton;
	//�� ���� �̹��� ������
	tagAlpha2 _playerWakeUp;
	bool _isWakeUp;
	//���� ����
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

