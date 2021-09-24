#pragma once

class boss;


class bossState
{
private:

protected:
	int _bossCount;
	int _bossArmCount;
	int _bossStateRand;
	int _bossStateChange;
	int _bossStateCount;


public:

	virtual bossState* inputHandle(boss* boss) = 0;
	virtual	void update(boss* boss) = 0;
	virtual	void enter(boss* boss) = 0;
	virtual void render(boss* boss) = 0;
	virtual void exit(boss* boss) = 0;
};

