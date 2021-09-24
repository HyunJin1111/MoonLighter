#pragma once
#include "gameNode.h"
#include "player.h"
#include "tileMap.h"
#include "UI.h"
#include "miniBoss.h"
#include "slime.h"
#include "boss.h"
#include <vector>
#include <string>

#define MAPMAX 49
#define MAPSIZE 7

#define ASTARX 21

enum tagDungeonCamera
{
	CAMERALEFT, CAMERARIGHT, CAMERAUP, CAMERADOWN, CAMERASTOP
};

struct tagDoor
{
	float x, y;
	int currentFrameX, currentFrameY;
	int count;
	dImage* img;
	RECT rc;
	RECT baseRc;
	bool isInvisible;
	float alpha;
	float width;
};
struct tagDungeon
{
	float x, y;
	int currentFrameX, currentFrameY;
	int count;
	dImage* img;
	RECT rc;
	tagDoor roadLeft, roadRight, roadUp, roadDown;
	float alpha;
	bool isBool;
	int rand;
	int indexX, indexY;
	tagTile tiles[DUNGEONTILEX * DUNGEONTILEY];

	bool isfix;
	tagDungeonCamera cameraDirection;
	int roomNumber;
	float speed;
	float radius;
};

struct tagItemGet
{
	float x, y;
	dImage* img;
	RECT rc;
	int rand;
	int count;
	string name;
	float angle;
};



class dungeon : public gameNode
{
private:
	player* _player;
	tileMap* _tileMap;
	UI* _ui;
	miniBoss* _miniBoss;
	slime* _slime;


	//���� �뿡 ���� ����ü
	tagDungeon _backGround[MAPMAX];
	//ȣ������ ����ü
	tagDungeon _pool;
	tagDungeon _poolCollision;
	//������ ī�޶� ����ü
	tagDungeon _dungeonCamera;
	bool _isBossCamera;
	//���� ���� �� ��ũ��
	tagDoor _scroll;
	//���� ���� �� ������ ��
	tagDoor _alpha;



	//��ȯ �Ҵ�Ʈ ���� ����ü
	tagDoor _returnPotal;
	tagDoor _returnPotalBase;
	tagDoor _returnPotalRect;
	tagDoor _returnLbutton;

	//�̴ϸʰ���
	bool _isMiniMapInvisible;
	tagDoor _minimapBack;
	tagDoor _miniMap[MAPMAX];
	tagDoor _miniMapWill;
	tagDoor _miniMapPool;

	//z���� ����
	tagTile _vPlayer;
	tagTile _vMiniBoss;
	vector<tagTile*> _vZorder;

	//������ ����
	vector<tagItemGet> _vitemGet;




	//���� x, y������ ����
	int _differenceX;
	int _differenceY;
	//���� ���� �� ȣ���� ������ ��ġ�� �������� �����
	int randPool;
	int randBoss;
	//���� ������ ���̸� ����
	char _changeChar[64];

	//�÷��̾� �ǰ�
	bool _playerHit;
	bool _playerHitTime;
	int _playerHitCount;


	//����� �� ���� ����
	int _huntSlime;
	int _huntMiniBoss;

	//������ ���� ��
	tagDoor _bossDoor;
	bool _isBossDoor;
	//���� ��
	tagDungeon _backGroundBoss;
	boss* _boss;


	int enemyTileCount;

public:
	dungeon();
	~dungeon();

	HRESULT init();
	void release();
	void update();
	void render();

	void load(tagTile* tile, const char* strKey);

	void tileCheck();
	void enemyTileCheck();
	void miniMap();
	void bossDoor();
	void dungeonReturn();
	void itemMove();
	//�浹����
	void poolCollision();
	void itemCollision();
	void bossRoomCollision();
	void playerCollision();
	void enemyCollision();
	void bossCollision();
};

