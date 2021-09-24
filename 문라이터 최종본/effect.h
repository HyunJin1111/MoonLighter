#pragma once
#include "gameNode.h"

class animation;

class effect : public gameNode
{
protected:
	int _x;
	int _y;
	float _angle;

	dImage* _effectImage;
	animation* _effectAnimation;
	BOOL _isRunning;
	float _elapsedTime;

public:
	effect();
	virtual ~effect();

	HRESULT init(dImage* effectImage, int frameW, int frameH, int fps, float elapsedTime);
	void release();
	void update();
	void render();

	void startEffect(int x, int y, float angle);

	void killEffect();

	BOOL getIsRunning() { return _isRunning; }
};

