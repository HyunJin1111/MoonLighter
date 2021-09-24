#pragma once

class player;

class playerState
{
private:

protected:
	int _playerCount;
public:

	virtual playerState* inputHandle(player* player) = 0;
	virtual	void update(player* player) = 0;
	virtual	void enter(player* player) = 0;
	virtual void render(player* player) = 0;
	virtual void exit(player* player) = 0;
};

