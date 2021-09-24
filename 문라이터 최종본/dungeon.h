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


	//던전 룸에 대한 구조체
	tagDungeon _backGround[MAPMAX];
	//호수관련 구조체
	tagDungeon _pool;
	tagDungeon _poolCollision;
	//던전용 카메라 구조체
	tagDungeon _dungeonCamera;
	bool _isBossCamera;
	//던전 시작 시 스크롤
	tagDoor _scroll;
	//던전 시작 시 불투명 값
	tagDoor _alpha;



	//귀환 팬던트 관련 구조체
	tagDoor _returnPotal;
	tagDoor _returnPotalBase;
	tagDoor _returnPotalRect;
	tagDoor _returnLbutton;

	//미니맵관련
	bool _isMiniMapInvisible;
	tagDoor _minimapBack;
	tagDoor _miniMap[MAPMAX];
	tagDoor _miniMapWill;
	tagDoor _miniMapPool;

	//z오더 전용
	tagTile _vPlayer;
	tagTile _vMiniBoss;
	vector<tagTile*> _vZorder;

	//아이템 관련
	vector<tagItemGet> _vitemGet;




	//룸의 x, y길이의 차이
	int _differenceX;
	int _differenceY;
	//던전 생성 시 호수와 보스의 위치를 랜덤으로 잡아줌
	int randPool;
	int randBoss;
	//던전 생성시 맵이름 받음
	char _changeChar[64];

	//플레이어 피격
	bool _playerHit;
	bool _playerHitTime;
	int _playerHitCount;


	//사냥한 적 담을 변수
	int _huntSlime;
	int _huntMiniBoss;

	//보스로 가는 문
	tagDoor _bossDoor;
	bool _isBossDoor;
	//보스 룸
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
	//충돌관련
	void poolCollision();
	void itemCollision();
	void bossRoomCollision();
	void playerCollision();
	void enemyCollision();
	void bossCollision();
};

