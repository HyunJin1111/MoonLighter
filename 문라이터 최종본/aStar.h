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

	//��ü Tile ���� ����
	vector<aStarTile*>			_vTotalList;
	vector<aStarTile*>::iterator _viTotalList;

	//�� �� �ִ� Tile ���� ����
	vector<aStarTile*>			_vOpenList;
	vector<aStarTile*>::iterator _viOpenList;

	//���� ����� ��θ� ���� ����
	vector<aStarTile*>			_vCloseList;
	vector<aStarTile*>::iterator _viCloseList;

	RECT rcCollision;	//������ �浹���� ��Ʈ�� �ϳ� ����������
	RECT enemyrcCollision;	//������ �浹���� ��Ʈ�� �ϳ� ����������

	//���̽�Ÿ ī��Ʈ
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

	//Tile ���� �Լ�
	void setTiles(int enemyX, int enemyY, RECT player, int diffrentX, int differntY);
	//�� �� �ִ� ���� ã�� ����� �Լ�
	vector<aStarTile*> addOpenList(aStarTile* currentTile);
	//�� ã�� �Լ�
	void pathFinder(aStarTile* currentTile);
	//���� �Լ�
	void resetTiles(int diffrentX, int differntY);




	aStarTile* getSaveTile() { return _saveTile; }

	void setVtotalAttribute(int index, string str) { _vTotalList[index]->setAttribute(str) ; }

	vector<aStarTile*> getVtotal() { return _vTotalList; }

};

