#pragma once
#include "gameNode.h"


class progressBar : public gameNode
{
private:
	RECT _rc;
	float _x, _y;
	float _width;

	dImage* barTop;
	dImage* barBottom;

public:
	progressBar();
	~progressBar();

	HRESULT init(float x, float y, float width, float height);
	void release();
	void update();
	void render();

	void setGauge(float currentGauge, float maxGauge);

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

};

