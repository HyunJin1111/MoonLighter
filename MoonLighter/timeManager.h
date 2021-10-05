#pragma once
#include "singletonBase.h"
#include "timer.h"

class timeManager : public singletonBase<timeManager>
{
private:
	timeManager();
	~timeManager();

	friend singletonBase;

	timer* _timer;

public:
	

	HRESULT init();
	void release();
	void update(float lock = 0.0f);
	void render(HDC hdc);

	inline float getElapsedTime() const { return _timer->getElapsedTime(); }
	inline float getWorldTime() const { return _timer->getWorldTime(); }
	inline int getFrameRate(void) const { return _timer->getFrameRate(); }
};

