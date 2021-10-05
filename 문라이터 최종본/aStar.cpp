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
	//���̽�Ÿ ī��Ʈ������ ����
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

	//��ŸƮŸ�ϰ� ����Ÿ���� ��ǥ�� ���� ��� a* ����!
	if (_endTileX == _startTileX && _endTileY == _startTileY) _isAstarGo = true;
	if (_endTileX != _startTileX || _endTileY != _startTileY) _isAstarGo = false;

	//��ŸƮ Ÿ���� �ε��� �ִ밪 ����
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

	//������ ������Ʈ�� ���� ��Ʈ�� ����������
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

	//���� Ÿ���� ����Ÿ�Ϸ�
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
			//�ε����� �ּҰ� �� �ִ밪�� �Ѿ�� ���� X
			if ((startY * ASTARMAXX) + startX + j + (i * ASTARMAXX) < 0) continue;
			if ((startY * ASTARMAXX) + startX + j + (i * ASTARMAXX) > 230) continue;


			aStarTile* node = _vTotalList[(startY * ASTARMAXX) + startX + j + (i * ASTARMAXX)];

			//����ó��
			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "wall") continue;

			//���� Tile ��� �������ش�
			node->setParentNode(_currentTile);

			//�ֺ� Ÿ���� �����ϸ鼭 üũ�ߴ��� ������ �˼��ְ� ������ �Ұ� ����
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				//�̹� �ִ� �ִ�
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}


			if (node->getAttribute() != "end")
			{
			}

			//�̹� üũ�� �ִ� �ǳʶڴ�
			if (!addObj) continue;

			//���� �ִ� Ÿ���� ���¸���Ʈ ���Ϳ� ����ش�
			_vOpenList.push_back(node);
		}
	}

	return _vOpenList;
}

void aStar::pathFinder(aStarTile * currentTile)
{
	//���ϱ� ���� ������ ��κ���� �����صд�
	float tempTotalCost = 5000;
	aStarTile* tempTile = nullptr;

	//���¸���Ʈ ���� �ȿ���, ���� ���� ��θ� �̾Ƴ���
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{
		//H �� ����
		_vOpenList[i]->setCostToGoal(
			(abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) +
				abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();

		//Tile ���� ���̿� ���̰� (Ÿ�ϻ����� 32)���� ũ��? ũ�� �밢��, �ƴϸ� �����¿�
		_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > ASTARSIZE) ? 14 : 10);

		//�� ��κ�� == �� �� �ִ� Tile �� �߿��� �� ��� ����
		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() + _vOpenList[i]->getCostFromStart());

		//�׷��� �̾Ƴ� �� ��κ����� ������ ��κ��� �����ؼ�,
		//���� ���� ���� ��� �̾Ƴ���
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
		//�ִ� ��δ� ��ĥ�����
		while (_currentTile->getParentNode() != NULL)
		{
			_currentTile = _currentTile->getParentNode();
		}
		return;
	}

	//�ִ� ��θ� �̾�����
	_vCloseList.push_back(tempTile);

	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		//�̾Ƴ� �ִ� ��δ� ���¸���Ʈ���� ������Ų��
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

