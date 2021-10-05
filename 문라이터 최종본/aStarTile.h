#pragma once
#include "gameNode.h"

class aStarTile : public gameNode
{
private:
	int _idX;
	int _idY;

	POINT _center;
	RECT _rc;

	float _totalCost;
	float _costFromStart;
	float _costToGoal;

	bool _isOpen;//갈수있는 타일인지 유무

	aStarTile* _parentNode; //제일 상위 Tile (계속 갱신되는 Tile)

	string _attribute;

public:
	aStarTile();
	~aStarTile();

	HRESULT init(int idX, int idY, int diffrentX, int differntY);
	void release();
	void update();
	void render();

	



	int getIdX() { return _idX; }
	void setIdX(int idX) { _idX = idX; }
	int getIdY() { return _idY; }
	void setIdY(int idY) { _idY = idY; }

	//============ 편리를 위한 접근자 & 설정자 ===============
	void setCenter(POINT center) { _center = center; }
	POINT getCenter() { return _center; }

	RECT getRc() { return _rc ; }

	void setAttribute(string str) { _attribute = str; }
	string getAttribute() { return _attribute; }

	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }

	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }


	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }

	void setParentNode(aStarTile* t) { _parentNode = t; }
	aStarTile* getParentNode() { return _parentNode; }

	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen() { return _isOpen; }
};

