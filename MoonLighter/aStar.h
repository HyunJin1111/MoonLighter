#pragma once
#include "gameNode.h"
#include "aStarTile.h"
#include <vector>
#include <string>

#define ASTARMAXX 21
#define ASTARMAXY 11
#define ASTARSIZE 26

class aStar : public gameNode
{
private:
	bool _isAstarGo;

	aStarTile* _startTile;
	aStarTile* _endTile;
	aStarTile* _currentTile;
	aStarTile* _saveTile;

	//전체 Tile 담을 벡터
	vector<aStarTile*>			_vTotalList;
	vector<aStarTile*>::iterator _viTotalList;

	//갈 수 있는 Tile 담을 벡터
	vector<aStarTile*>			_vOpenList;
	vector<aStarTile*>::iterator _viOpenList;

	//가장 가까운 경로를 담을 벡터
	vector<aStarTile*>			_vCloseList;
	vector<aStarTile*>::iterator _viCloseList;

	RECT rcCollision;	//가상의 충돌판정 렉트를 하나 생성해주자
	RECT enemyrcCollision;	//가상의 충돌판정 렉트를 하나 생성해주자

	//에이스타 카운트
	int _count;

	bool _start;

	int _endX, _endY;

	bool _isSet;

	int _startTileX, _startTileY;
	int _endTileX, _endTileY;
	int _traceIdx;
public:
	aStar();
	~aStar();

	HRESULT init();
	void release();
	void update(int diffrentX, int differntY, RECT player, RECT enemyRc);
	void render();

	//Tile 셋팅 함수
	void setTiles(int enemyX, int enemyY, RECT player, int diffrentX, int differntY);
	//갈 수 있는 길을 찾아 담아줄 함수
	vector<aStarTile*> addOpenList(aStarTile* currentTile);
	//길 찾는 함수
	void pathFinder(aStarTile* currentTile);
	//리셋 함수
	void resetTiles(int diffrentX, int differntY);




	aStarTile* getSaveTile() { return _saveTile; }

	void setVtotalAttribute(int index, string str) { _vTotalList[index]->setAttribute(str) ; }

	vector<aStarTile*> getVtotal() { return _vTotalList; }

};

