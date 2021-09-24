#pragma once
#include "playerState.h"
#include "player.h"
class playerRoll : public playerState
{
private:

public:

	virtual playerState* inputHandle(player* player);
	virtual void enter(player* player);
	virtual void update(player* player);
	virtual void render(player* player);
	virtual void exit(player* player);
};

