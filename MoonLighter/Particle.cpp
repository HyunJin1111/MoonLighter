#include "stdafx.h"
#include "Particle.h"
#include "animation.h"


Particle::Particle() :
	_effectImage(NULL), _effectAnimation(NULL),
	_isRunning(false), _x(0), _y(0), _angle(0), _type(0)
{
}


Particle::~Particle()
{
}

HRESULT Particle::init(dImage * effectImage, int frameW, int frameH, int fps, float elapsedTime)
{
	if (!effectImage) return E_FAIL;

	_isRunning = false;

	_effectImage = effectImage;
	_elapsedTime = elapsedTime;

	if (!_effectAnimation) _effectAnimation = new animation;
	_ParticleRect = RectMakeCenter(_x, _y, _effectImage->getFrameWidth(), _effectImage->getFrameHeight());
	_effectAnimation->init(_effectImage->getWidth(), _effectImage->getHeight(), frameW, frameH);
	_effectAnimation->setDefPlayFrame(false, false);
	_effectAnimation->setFPS(fps);
	_effectAnimation->stop();

	return S_OK;
}

void Particle::release()
{
	_effectImage = nullptr;
	SAFE_DELETE(_effectAnimation);
}

void Particle::update()
{
	if (!_isRunning) return;

	_effectAnimation->frameUpdate(_elapsedTime);
	_ParticleRect = RectMakeCenter(_x, _y, _effectImage->getFrameWidth(), _effectImage->getFrameHeight());
	if (!_effectAnimation->isPlay()) killEffect();

}

void Particle::render()
{
	if (!_isRunning) return;
	D2DMANAGER->setRotation(_angle, _x, _y);
	_effectImage->aniRender(_x, _y, _effectAnimation);
	D2DMANAGER->resetRotation();
	//DTDMANAGER->Rectangle(_ParticleRect);
}

void Particle::startEffect(int x, int y, float angle)
{
	if (!_effectImage || !_effectAnimation) return;

	_x = x - (_effectAnimation->getFrameWidth() / 2);
	_y = y - (_effectAnimation->getFrameHeight() / 2);
	_angle = angle;
	_isRunning = true;
	_effectAnimation->start();
}

void Particle::killEffect()
{
	_isRunning = false;
}
