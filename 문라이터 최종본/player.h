#pragma once
#include "gameNode.h"
#include "playerState.h"
#include "playerIdle.h"
#include "playerWalk.h"
#include "playerRoll.h"
#include "playerSwordAttack.h"
#include "playerSwim.h"
#include "progressBar.h"
#include "playerDie.h"



class village;
class shop;
class deongeonChoice;

enum PLAYER_STATE 
{
	PLAYER_ROLL,
	PLAYER_WALK,
	PLAYER_SWIM
};

enum PLAYRER_DIRECTION
{
	PLAYER_DOWN,
	PLAYER_UP,
	PLAYER_LEFT,
	PLAYER_RIGHT,
	PLAYER_LEFTUP,
	PLAYER_RIGHTUP,
	PLAYER_LEFTDOWN,
	PLAYER_RIGHTDOWN,
};
struct tagPlayer
{
	float x, y;
	int currentFrameX, currentFrameY;
	int count;
	int speed;
	dImage* img;
	RECT rc;
	RECT itemRc;
	RECT upLeft, upRight, downLeft, downRight, leftUp, leftDown, rightUp, rightDown;
	PLAYRER_DIRECTION direction;
	PLAYER_STATE state;
	float alpha;
	RECT attackRect;
	int power;
	float maxHp, currentHp;
};


class player : public gameNode
{
private:
	//Å¬·¡½º
	playerState* _playerState;
	shop* _shop;
	progressBar* _hpBar;
	


	tagPlayer _player;

public:
	player();
	~player();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void hpRender();

	void setPlayer();
	void InputHandle();

	tagPlayer getPlayer() { return _player; }
	
	void setPlayerImg(dImage* img) { _player.img = img; }
	void setPlayerCurrentFrameX(int x) { _player.currentFrameX = x; }
	void setPlayerCurrentFrameY(int y) { _player.currentFrameY = y; }
	void setPlayerX(float x) { _player.x = x; }
	void setPlayerY(float y) { _player.y = y; }
	void setPlayerRect(RECT rc) { _player.rc = rc; }
	void setPlayerAttackRect(RECT rc) { _player.attackRect = rc; }

	void setPlayerDirection(PLAYRER_DIRECTION direction) { _player.direction = direction; }
	void setPlayerState(PLAYER_STATE state) { _player.state = state; }

	void linkShop(shop* shop) { _shop = shop; }

	void setPlayerCurrentHp(float hp) { _player.currentHp = hp; }
	void setPlayerMaxHp(float hp) { _player.maxHp = hp; }
};

