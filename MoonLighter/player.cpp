#include "stdafx.h"
#include "player.h"



player::player()
{
}

player::~player()
{
}

HRESULT player::init()
{
	setPlayer();
	
	_playerState = new playerIdle();
	_playerState->enter(this);
	_player.x = NULL;
	_player.y = NULL;

	_player.speed = 2;
	_player.power = 30;
	_player.currentHp = _player.maxHp = 300;
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	_player.count = 0;
	_player.currentFrameX = _player.currentFrameY = 0;
	_player.img = IMAGEMANAGER->findDImage("will_idle_down");

	_hpBar = new progressBar;
	_hpBar->init(115, 25, 64, 12);


	_player.itemRc = RectMakeCenter(_player.x, _player.y, 5, 5);

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	InputHandle();
	_playerState->update(this);

	_hpBar->update();
	if (_player.currentHp <= 0)_player.currentHp = 0;
	_hpBar->setGauge(_player.currentHp, _player.maxHp);
	
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	_player.itemRc = RectMakeCenter(_player.x, _player.y, 5, 5);

	_player.upLeft = RectMakeCenter(_player.x - 5, _player.y , 5, 5);
	_player.upRight = RectMakeCenter(_player.x + 5, _player.y , 5, 5);
	_player.downLeft = RectMakeCenter(_player.x - 5, _player.y + 15, 5, 5);
	_player.downRight = RectMakeCenter(_player.x + 5, _player.y  + 15 , 5, 5);

	_player.leftUp = RectMakeCenter(_player.x - 12, _player.y +5, 5, 5);
	_player.leftDown = RectMakeCenter(_player.x - 12, _player.y + 10 , 5, 5);
	_player.rightUp = RectMakeCenter(_player.x + 12, _player.y +5, 5, 5);
	_player.rightDown = RectMakeCenter(_player.x +12, _player.y + 10 , 5, 5);

}

void player::render()
{
	_playerState->render(this);
	
}

void player::hpRender()
{
	_hpBar->render();
}


void player::setPlayer()
{
	IMAGEMANAGER->addFrameDImage("will_idle_down", L"Will/will_idle_down.png", 200, 38, 10, 1);
	IMAGEMANAGER->addFrameDImage("will_idle_up", L"Will/will_idle_up.png", 210, 38, 10, 1);
	IMAGEMANAGER->addFrameDImage("will_idle_left", L"Will/will_idle_left.png", 280, 38, 10, 1);
	IMAGEMANAGER->addFrameDImage("will_idle_right", L"Will/will_idle_right.png", 280, 38, 10, 1);

	IMAGEMANAGER->addFrameDImage("will_run_down", L"Will/will_run_down.png", 160, 35, 8, 1);
	IMAGEMANAGER->addFrameDImage("will_run_up", L"Will/will_run_up.png", 168, 39, 8, 1);
	IMAGEMANAGER->addFrameDImage("will_run_left", L"Will/will_run_left.png", 248, 36, 8, 1);
	IMAGEMANAGER->addFrameDImage("will_run_right", L"Will/will_run_right.png", 248, 36, 8, 1);

	IMAGEMANAGER->addFrameDImage("will_roll_down", L"Will/will_roll_down.png", 200, 38, 8, 1);
	IMAGEMANAGER->addFrameDImage("will_roll_up", L"Will/will_roll_up.png", 176, 37, 8, 1);
	IMAGEMANAGER->addFrameDImage("will_roll_left", L"Will/will_roll_left.png", 248, 36, 8, 1);
	IMAGEMANAGER->addFrameDImage("will_roll_right", L"Will/will_roll_right.png", 248, 36, 8, 1);

	IMAGEMANAGER->addFrameDImage("sword_down", L"Will/sword_down.png", 1080, 72, 18, 1);
	IMAGEMANAGER->addFrameDImage("sword_up", L"Will/sword_up.png", 1080, 57, 18, 1);
	IMAGEMANAGER->addFrameDImage("sword_left", L"Will/sword_left.png", 1080, 70, 18, 1);
	IMAGEMANAGER->addFrameDImage("sword_right", L"Will/sword_right.png", 1116, 70, 18, 1);

	IMAGEMANAGER->addFrameDImage("will_swim_down", L"Will/will_swim_down.png", 180, 21, 10, 1);
	IMAGEMANAGER->addFrameDImage("will_swim_up", L"Will/will_swim_up.png", 170, 21, 10, 1);
	IMAGEMANAGER->addFrameDImage("will_swim_left", L"Will/will_swim_left.png", 170, 22, 10, 1);
	IMAGEMANAGER->addFrameDImage("will_swim_right", L"Will/will_swim_right.png", 170, 22, 10, 1);

	IMAGEMANAGER->addFrameDImage("will_die", L"Will/will_die.png", 440, 42, 10, 1);


	_player.direction = PLAYER_DOWN;

}

void player::InputHandle()
{
	playerState* newState = _playerState->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_playerState);
		_playerState = newState;
		_playerState->enter(this);
	}
}
