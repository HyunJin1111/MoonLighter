#pragma once
#include "gameNode.h"


class enemyProgressBar : public gameNode
{
private:
	RECT _rc;
	float _x, _y;
	float _width;

	dImage* barTop[3];
	dImage* barBottom[3];

public:
	enemyProgressBar();
	~enemyProgressBar();

	HRESULT init(float x, float y, float width, float height, int index);
	void release();
	void update(int x, int y, int index);
	void render(int index, int maxWidth);

	void setGauge(float currentGauge, float maxGauge, int index);

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

};

