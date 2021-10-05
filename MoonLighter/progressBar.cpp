#include "stdafx.h"
#include "progressBar.h"

progressBar::progressBar()
{
}

progressBar::~progressBar()
{
}

HRESULT progressBar::init(float x, float y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;

	_rc = RectMake(x, y, width, height);

	barTop = IMAGEMANAGER->addDImage("frontBar", L"UI/playerHpFront.png", 64, 12);
	barBottom = IMAGEMANAGER->addDImage("bottomBar", L"UI/HealthBar_Base.png", 73, 22);


	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	_rc = RectMakeCenter(_x, _y, barTop->getWidth(), barTop->getHeight());
}

void progressBar::render()
{
	barBottom->render(_rc.left + CAMERAMANAGER->getScreen().left - 5, _rc.top + CAMERAMANAGER->getScreen().top - 5);
	barTop->scaleRender(_rc.left + 2 + CAMERAMANAGER->getScreen().left, _rc.top + CAMERAMANAGER->getScreen().top, _width / 64, 1);
}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) *( barBottom->getWidth()-9);
}
