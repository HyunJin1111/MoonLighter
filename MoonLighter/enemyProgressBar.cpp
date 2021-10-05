#include "stdafx.h"
#include "enemyProgressBar.h"
#include "stdafx.h"

enemyProgressBar::enemyProgressBar()
{
}

enemyProgressBar::~enemyProgressBar()
{
}

HRESULT enemyProgressBar::init(float x, float y, float width, float height, int index)
{


	_x = x;
	_y = y;
	_width = width;

	_rc = RectMake(x, y, width, height);

	if (index == 0) 
	{
		barTop[index] = IMAGEMANAGER->addDImage("enemyfrontBar", L"UI/playerHpFront.png", 40, 6);
		barBottom[index] = IMAGEMANAGER->addDImage("enemybottomBar", L"UI/enemyrHpFront.png", 40, 6);
	}
	if (index == 1) 
	{
		barTop[index] = IMAGEMANAGER->addDImage("minibossf", L"UI/playerHpFront.png", 100, 8);
		barBottom[index] = IMAGEMANAGER->addDImage("minibossb", L"UI/enemyrHpFront.png", 100, 8);
	}
	if (index == 2) 
	{
		barTop[index] = IMAGEMANAGER->addDImage("bossF", L"UI/playerHpFront.png", 400, 10);
		barBottom[index] = IMAGEMANAGER->addDImage("bossB", L"UI/enemyrHpFront.png", 400, 10);
	}
	


	return S_OK;
}

void enemyProgressBar::release()
{
}

void enemyProgressBar::update(int x , int y,int index)
{

	_rc = RectMakeCenter(x, y, barTop[index]->getWidth(), barTop[index]->getHeight());
}

void enemyProgressBar::render(int index, int maxWidth)
{
	barBottom[index]->render(_rc.left, _rc.top);
	barTop[index]->scaleRender(_rc.left, _rc.top , _width / maxWidth, 1);
}

void enemyProgressBar::setGauge(float currentGauge, float maxGauge, int index)
{
	_width = (currentGauge / maxGauge) *(barBottom[index]->getWidth());
}
