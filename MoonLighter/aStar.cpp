#include "stdafx.h"
#include "aStar.h"

aStar::aStar()
{
}

aStar::~aStar()
{
}

HRESULT aStar::init()
{
	return S_OK;
}

void aStar::release()
{
}

void aStar::update(int diffrentX, int differntY, RECT player, RECT enemyRc)
{
	RECT temp;
	//에이스타 카운트에따라 실행
	if (!_isAstarGo)
	{
		_count++;
		if (_count % 20 == 0)
		{
			if (!_vCloseList.empty())
			{

				if (IntersectRect(&temp, &_saveTile->getRc(), &enemyRc))
				{
					_endTileX = _saveTile->getIdX();
					_endTileY = _saveTile->getIdY();
					_saveTile = _saveTile->getParentNode();
				}
			}

			_count = 0;
		}
		resetTiles(diffrentX, differntY);

	}

	rcCollision = player;


	_startTileX = (rcCollision.left - diffrentX) / 26 + 1;
	_startTileY = (rcCollision.top - differntY) / 26 + 1;

	//스타트타일과 엔드타일의 좌표가 같을 경우 a* 중지!
	if (_endTileX == _startTileX && _endTileY == _startTileY) _isAstarGo = true;
	if (_endTileX != _startTileX || _endTileY != _startTileY) _isAstarGo = false;

	//스타트 타일의 인덱스 최대값 설정
	if (_startTileX >= ASTARMAXX - 1) _startTileX = ASTARMAXX - 1;
	if (_startTileY >= ASTARMAXY - 1) _startTileY = ASTARMAXY - 1;


}

void aStar::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < _vOpenList.size(); ++i)
		{
			D2DMANAGER->FillRectangle(_vOpenList[i]->getRc(),D2DDEFAULTBRUSH::Gray);

		}
		for (int i = 0; i < _vCloseList.size(); ++i)
		{
			D2DMANAGER->FillRectangle(_vCloseList[i]->getRc(),D2DDEFAULTBRUSH::White);

		}
		D2DMANAGER->FillRectangle(_startTile->getRc(), D2DDEFAULTBRUSH::Green);
		D2DMANAGER->FillRectangle(_endTile->getRc(), D2DDEFAULTBRUSH::Blue);
	}
}

void aStar::setTiles(int enemyX, int enemyY, RECT player, int diffrentX, int differntY)
{

	//가상의 판정렉트에 현재 렉트를 대입해주자
	rcCollision = player;


	_traceIdx = 0;
	_count = _start = 0;

	//_startTileX = (rcCollision.left - diffrentX) / 26;
	//_startTileY = (rcCollision.top - differntY) / 26;

	_endTileX = (enemyX - diffrentX) / 26;
	_endTileY = (enemyY - differntY) / 26;

	_startTile = new aStarTile;
	_startTile->init(_startTileX, _startTileY, diffrentX, differntY);
	_startTile->setAttribute("start");
	_endTile = new aStarTile;
	_endTile->init(_endTileX, _endTileY, diffrentX, differntY);
	_endTile->setAttribute("end");

	//현재 타일은 시작타일로
	_currentTile = _startTile;

	for (int i = 0; i < ASTARMAXY; ++i)
	{
		for (int j = 0; j < ASTARMAXX; ++j)
		{
			if (j == _startTile->getIdX() && i == _startTile->getIdY())
			{
				_vTotalList.push_back(_startTile);
				continue;
			}
			if (j == _endTile->getIdX() && i == _endTile->getIdY())
			{
				_vTotalList.push_back(_endTile);
				continue;
			}

			aStarTile* node;
			node = new aStarTile;
			node->init(j, i, diffrentX - 26, differntY);

			if (j % ASTARSIZE == 0) node->setAttribute("wall");
			if (j % ASTARSIZE == ASTARSIZE - 1) node->setAttribute("wall");

			_vTotalList.push_back(node);
		}
	}
}

vector<aStarTile*> aStar::addOpenList(aStarTile * currentTile)
{
	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			//인덱스가 최소값 및 최대값을 넘어가면 실행 X
			if ((startY * ASTARMAXX) + startX + j + (i * ASTARMAXX) < 0) continue;
			if ((startY * ASTARMAXX) + startX + j + (i * ASTARMAXX) > 230) continue;


			aStarTile* node = _vTotalList[(startY * ASTARMAXX) + startX + j + (i * ASTARMAXX)];

			//예외처리
			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "wall") continue;

			//현재 Tile 계속 갱신해준다
			node->setParentNode(_currentTile);

			//주변 타일을 검출하면서 체크했는지 유무를 알수있게 임의의 불값 선언
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				//이미 있는 애다
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}


			if (node->getAttribute() != "end")
			{
			}

			//이미 체크된 애는 건너뛴다
			if (!addObj) continue;

			//갈수 있는 타일은 오픈리스트 벡터에 담아준다
			_vOpenList.push_back(node);
		}
	}

	return _vOpenList;
}

void aStar::pathFinder(aStarTile * currentTile)
{
	//비교하기 쉽게 임의의 경로비용을 설정해둔다
	float tempTotalCost = 5000;
	aStarTile* tempTile = nullptr;

	//오픈리스트 벡터 안에서, 가장 빠른 경로를 뽑아낸다
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{
		//H 값 연산
		_vOpenList[i]->setCostToGoal(
			(abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) +
				abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();

		//Tile 중점 사이에 길이가 (타일사이즈 32)보다 크냐? 크면 대각선, 아니면 상하좌우
		_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > ASTARSIZE) ? 14 : 10);

		//총 경로비용 == 갈 수 있는 Tile 들 중에서 총 경로 비용들
		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() + _vOpenList[i]->getCostFromStart());

		//그렇게 뽑아낸 총 경로비용들을 임의의 경로비용과 연산해서,
		//가장 작은 값을 계속 뽑아낸다
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}

		bool addObj = true;
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{
				addObj = false;
				break;
			}
		}

		_vOpenList[i]->setIsOpen(false);
		if (!addObj) continue;

		_vOpenList.push_back(tempTile);
	}
	if (tempTile->getAttribute() == "end")
	{
		_saveTile = _currentTile;
		//최단 경로는 색칠해줘라
		while (_currentTile->getParentNode() != NULL)
		{
			_currentTile = _currentTile->getParentNode();
		}
		return;
	}

	//최단 경로를 뽑아주자
	_vCloseList.push_back(tempTile);

	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		//뽑아낸 최단 경로는 오픈리스트에서 삭제시킨다
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile;



	pathFinder(_currentTile);
}

void aStar::resetTiles(int diffrentX, int differntY)
{
	_start = true;

	_vOpenList.clear();
	_vCloseList.clear();


	for (int i = 0; i < _vTotalList.size(); i++)
	{
		if (_vTotalList[i]->getAttribute() == "wall") continue;
		_vTotalList[i]->setIsOpen(true);
		//_vTotalList[i]->setAttribute("");
		/*_vTotalList[i]->init(i % ASTARMAXX, i / ASTARMAXX, diffrentX - 26, differntY);
		if (i % ASTARMAXX == 0)	_vTotalList[i]->setAttribute("wall");
		if (i % ASTARMAXX == ASTARMAXX - 1)	_vTotalList[i]->setAttribute("wall");*/
	}
	_startTile = _vTotalList[_startTileX + _startTileY * ASTARMAXX];
	_startTile->setAttribute("start");
	_startTile->setParentNode(nullptr);

	_currentTile = _startTile;

	_endTile = _vTotalList[_endTileX + _endTileY * ASTARMAXX];
	_endTile->setParentNode(nullptr);
	_endTile->setAttribute("end");


	pathFinder(_currentTile);


}

