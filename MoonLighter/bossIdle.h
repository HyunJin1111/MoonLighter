#pragma once
#include "bossState.h"
#include "boss.h"

class bossIdle : public bossState
{
private:

public:

	virtual bossState* inputHandle(boss* boss);
	virtual void enter(boss* boss);
	virtual void update(boss* boss);
	virtual void render(boss* boss);
	virtual void exit(boss* boss);
};

