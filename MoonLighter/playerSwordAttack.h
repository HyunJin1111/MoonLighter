#pragma once
#include "playerState.h"
#include "player.h"

class playerSwordAttack :	public playerState
{
private:

	bool _combo1;
	bool _combo2;
	bool _combo3;


public:

	virtual playerState* inputHandle(player* player);
	virtual void enter(player* player);
	virtual void update(player* player);
	virtual void render(player* player);
	virtual void exit(player* player);
};

