#pragma once
#include "gameNode.h"

class animation;

class Particle : public gameNode
{
protected:
	int _x;
	int _y;
	int _type;
	float _angle;

	dImage* _effectImage;
	animation* _effectAnimation;
	BOOL _isRunning;
	RECT _ParticleRect;
	Vector2 _RL, _RR, _RT, _RB;
	float _elapsedTime;

public:
	Particle();
	virtual ~Particle();

	HRESULT init(dImage* effectImage, int frameW, int frameH, int fps, float elapsedTime);
	void release();
	void update();
	void render();

	void startEffect(int x, int y, float angle);

	void killEffect();

	BOOL getIsRunning() { return _isRunning; }
};