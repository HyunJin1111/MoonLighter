#include "stdafx.h"
#include "aStarTile.h"

aStarTile::aStarTile()
	: _totalCost(0), _costFromStart(0),
_costToGoal(0), _parentNode(NULL),
_idX(0), _idY(0), _isOpen(true)
{
}

aStarTile::~aStarTile()
{
}

HRESULT aStarTile::init(int idX, int idY , int diffrentX, int differntY)
{

	_center = PointMake(idX * 26 + (26 / 2),
		idY * 26 + (26 / 2));

	_idX = idX;
	_idY = idY;

	_rc = RectMakeCenter(diffrentX+_center.x, differntY+_center.y, 26, 26);
	_isOpen = true;
	_parentNode = nullptr;
	_attribute = "";

	return S_OK;
}

void aStarTile::release()
{
}

void aStarTile::update()
{
}

void aStarTile::render()
{
	D2DMANAGER->DrawRectangle(_rc, D2DDEFAULTBRUSH::Green);
}


