#include "stdafx.h"
#include "miniBoss.h"

miniBoss::miniBoss()
{
}

miniBoss::~miniBoss()
{

}

HRESULT miniBoss::init(float x, float y, RECT player, int diffrentX, int diffrentY)
{
	_miniBoss.x = x;
	_miniBoss.y = y;
	setMiniBoss();

	_aStar = new aStar;
	_aStar->setTiles(_miniBoss.x, _miniBoss.y, player, diffrentX, diffrentY);

	_hpBar = new enemyProgressBar;
	_hpBar->init(_miniBoss.x, _miniBoss.y - 50, 100, 8, 1);

	return S_OK;
}

void miniBoss::release()
{

}

void miniBoss::update(float distance, int diffrentX, int diffrentY, RECT player)
{
	_aStar->update(diffrentX, diffrentY, player, _miniBoss.rc);

	_hpBar->update(_miniBoss.x, _miniBoss.y - 50, 1);
	if (_miniBoss.currentHp <= 0)
	{
		_miniBoss.currentHp = 0;
	}
	_hpBar->setGauge(_miniBoss.currentHp, _miniBoss.maxHp, 1);


	_miniBoss.angle = getAngle(_miniBoss.x, _miniBoss.y, _aStar->getSaveTile()->getRc().left, _aStar->getSaveTile()->getRc().top);

	//준보스 이미지 프레임
	_miniBoss.count++;
	if (_miniBoss.count % 8 == 0)
	{
		_miniBoss.currentFrameX++;
		if (_miniBoss.currentFrameX > _miniBoss.img->getMaxFrameX())
		{
			if (_miniBoss.state == MINIBOSS_WALK || _miniBoss.state == MINIBOSS_IDLE)
			{
				_miniBoss.currentFrameX = 0;
				_miniBoss.count = 0;
				_miniBoss.changeState = false;
			}
			if (_miniBoss.state == MINIBOSS_SMASH || _miniBoss.state == MINIBOSS_SWORD)
			{
				_miniBoss.currentFrameX = 0;
				_miniBoss.count = 0;
				_miniBoss.state = MINIBOSS_IDLE;
				_miniBoss.changeState = false;
			}

		}
	}


	miniBossMove();


	if (distance < 120 && !_miniBoss.changeState)
	{
		_miniBoss.rand++;
		_miniBoss.state = MINIBOSS_IDLE;
		if (_miniBoss.rand % 70 == 0)
		{
			int randState = RND->getFromIntTo(0, 2);
			switch (randState)
			{
			case 0:
				_miniBoss.state = MINIBOSS_SMASH;
				break;
			case 1:
				_miniBoss.state = MINIBOSS_SWORD;
				break;
			}
			SOUNDMANAGER->play("MiniBossAttackSound");
			_miniBoss.currentFrameX = 0;
			_miniBoss.rand = 0;
			_miniBoss.changeState = true;
		}

	}
	else if (distance >= 120 && !_miniBoss.changeState)
	{
		_miniBoss.state = MINIBOSS_WALK;
		_miniBoss.currentFrameX = 0;
		_miniBoss.changeState = true;
	}

	miniBossState();
	_miniBoss.rc = RectMakeCenter(_miniBoss.x, _miniBoss.y, _miniBoss.img->getFrameWidth(), _miniBoss.img->getFrameHeight());
	_miniBoss.hitRc = RectMakeCenter(_miniBoss.x, _miniBoss.y, 100, 100);

}

void miniBoss::render()
{
	_miniBoss.img->frameRender(_miniBoss.rc.left, _miniBoss.rc.top, _miniBoss.currentFrameX, _miniBoss.currentFrameY);

	_aStar->render();

}

void miniBoss::hpRender()
{
	_hpBar->render(1, 100);
}

void miniBoss::setMiniBoss()
{
	IMAGEMANAGER->addFrameDImage("MiniBoss_idle_down", L"MiniBoss/MiniBoss_idle_down.png", 680, 108, 8, 1);
	IMAGEMANAGER->addFrameDImage("MiniBoss_idle_up", L"MiniBoss/MiniBoss_idle_up.png", 672, 109, 8, 1);
	IMAGEMANAGER->addFrameDImage("MiniBoss_idle_left", L"MiniBoss/MiniBoss_idle_left.png", 616, 111, 8, 1);
	IMAGEMANAGER->addFrameDImage("MiniBoss_idle_right", L"MiniBoss/MiniBoss_idle_right.png", 616, 111, 8, 1);

	IMAGEMANAGER->addFrameDImage("MiniBoss_smash_down", L"MiniBoss/MiniBoss_smash_down.png", 1455, 200, 15, 1);
	IMAGEMANAGER->addFrameDImage("MiniBoss_smash_up", L"MiniBoss/MiniBoss_smash_up.png", 1479, 200, 15, 1);
	IMAGEMANAGER->addFrameDImage("MiniBoss_smash_left", L"MiniBoss/MiniBoss_smash_left.png", 3600, 200, 15, 1);
	IMAGEMANAGER->addFrameDImage("MiniBoss_smash_right", L"MiniBoss/MiniBoss_smash_right.png", 3600, 200, 15, 1);

	IMAGEMANAGER->addFrameDImage("MiniBoss_sword_down", L"MiniBoss/MiniBoss_sword_down.png", 3600, 200, 15, 1);
	IMAGEMANAGER->addFrameDImage("MiniBoss_sword_up", L"MiniBoss/MiniBoss_sword_up.png", 3600, 200, 15, 1);
	IMAGEMANAGER->addFrameDImage("MiniBoss_sword_left", L"MiniBoss/MiniBoss_sword_left.png", 3600, 200, 15, 1);
	IMAGEMANAGER->addFrameDImage("MiniBoss_sword_right", L"MiniBoss/MiniBoss_sword_right.png", 3600, 200, 15, 1);

	_miniBoss.img = IMAGEMANAGER->findDImage("MiniBoss_idle_down");
	_miniBoss.rc = RectMakeCenter(_miniBoss.x, _miniBoss.y, _miniBoss.img->getFrameWidth(), _miniBoss.img->getFrameHeight());
	_miniBoss.hitRc = RectMakeCenter(_miniBoss.x, _miniBoss.y, 100, 100);
	_miniBoss.count = _miniBoss.rand = 0;
	_miniBoss.currentFrameX = _miniBoss.currentFrameY = 0;
	_miniBoss.currentHp = _miniBoss.maxHp = 100;
	_miniBoss.speed = 3;
	_miniBoss.power = 20;
	_miniBoss.angle = PI;
	_miniBoss.state = MINIBOSS_IDLE;
	_miniBoss.direction = MINIBOSS_DOWN;
	_miniBoss.changeState = false;
	_miniBoss.enemyHit = false;
	_miniBoss.enemyHitTime = false;
	_miniBoss.enemyHitCount = 0;


}

void miniBoss::miniBossState()
{
	//상태 및 방향에 따른 이미지 설정
	switch (_miniBoss.state)
	{
		//IDLE 상태
	case MINIBOSS_IDLE:
		switch (_miniBoss.direction)
		{
		case MINIBOSS_RIGHT:
			_miniBoss.img = IMAGEMANAGER->findDImage("MiniBoss_idle_right");
			break;
		case MINIBOSS_UP:
			_miniBoss.img = IMAGEMANAGER->findDImage("MiniBoss_idle_up");
			break;
		case MINIBOSS_LEFT:
			_miniBoss.img = IMAGEMANAGER->findDImage("MiniBoss_idle_left");
			break;
		case MINIBOSS_DOWN:
			_miniBoss.img = IMAGEMANAGER->findDImage("MiniBoss_idle_down");
			break;
		}
		break;
		//WALK 상태
	case MINIBOSS_WALK:
		_miniBoss.x += cosf(_miniBoss.angle) * 1;
		_miniBoss.y += -sinf(_miniBoss.angle) * 1;

		switch (_miniBoss.direction)
		{
		case MINIBOSS_RIGHT:
			_miniBoss.img = IMAGEMANAGER->findDImage("MiniBoss_idle_right");
			break;
		case MINIBOSS_UP:
			_miniBoss.img = IMAGEMANAGER->findDImage("MiniBoss_idle_up");
			break;
		case MINIBOSS_LEFT:
			_miniBoss.img = IMAGEMANAGER->findDImage("MiniBoss_idle_left");
			break;
		case MINIBOSS_DOWN:
			_miniBoss.img = IMAGEMANAGER->findDImage("MiniBoss_idle_down");
			break;
		}
		break;
		//SMASH 상태
	case MINIBOSS_SMASH:
		switch (_miniBoss.direction)
		{

		case MINIBOSS_RIGHT:
			_miniBoss.img = IMAGEMANAGER->findDImage("MiniBoss_smash_right");
			if (_miniBoss.currentFrameX == 4)
				_miniBoss.attackRc = RectMakeCenter(_miniBoss.x + 50, _miniBoss.y, 70, 70);
			break;
		case MINIBOSS_UP:
			_miniBoss.img = IMAGEMANAGER->findDImage("MiniBoss_smash_up");
			if (_miniBoss.currentFrameX == 4)
				_miniBoss.attackRc = RectMakeCenter(_miniBoss.x, _miniBoss.y - 50, 70, 70);
			break;
		case MINIBOSS_LEFT:
			_miniBoss.img = IMAGEMANAGER->findDImage("MiniBoss_smash_left");

			if (_miniBoss.currentFrameX == 4)
				_miniBoss.attackRc = RectMakeCenter(_miniBoss.x - 50, _miniBoss.y, 70, 70);
			break;
		case MINIBOSS_DOWN:
			_miniBoss.img = IMAGEMANAGER->findDImage("MiniBoss_smash_down");
			if (_miniBoss.currentFrameX == 4)
				_miniBoss.attackRc = RectMakeCenter(_miniBoss.x, _miniBoss.y + 50, 70, 70);
			break;
		}
		break;
		//SWORD 상태
	case MINIBOSS_SWORD:
		switch (_miniBoss.direction)
		{

		case MINIBOSS_RIGHT:
			_miniBoss.img = IMAGEMANAGER->findDImage("MiniBoss_sword_right");
			if (_miniBoss.currentFrameX == 4)
				_miniBoss.attack2Rc = RectMakeCenter(_miniBoss.x + 50, _miniBoss.y, 80, 100);
			break;
		case MINIBOSS_UP:
			_miniBoss.img = IMAGEMANAGER->findDImage("MiniBoss_sword_up");
			if (_miniBoss.currentFrameX == 4)
				_miniBoss.attack2Rc = RectMakeCenter(_miniBoss.x, _miniBoss.y - 50, 100, 80);
			break;
		case MINIBOSS_LEFT:
			_miniBoss.img = IMAGEMANAGER->findDImage("MiniBoss_sword_left");

			if (_miniBoss.currentFrameX == 4)
				_miniBoss.attack2Rc = RectMakeCenter(_miniBoss.x - 50, _miniBoss.y, 80, 100);
			break;
		case MINIBOSS_DOWN:
			_miniBoss.img = IMAGEMANAGER->findDImage("MiniBoss_sword_down");
			if (_miniBoss.currentFrameX == 4)
				_miniBoss.attack2Rc = RectMakeCenter(_miniBoss.x, _miniBoss.y + 50, 100, 80);
			break;
		}
		break;
	}
	if (_miniBoss.state == MINIBOSS_SMASH && _miniBoss.currentFrameX != 4) _miniBoss.attackRc = RectMakeCenter(0, 0, 0, 0);
	if (_miniBoss.state == MINIBOSS_SWORD && _miniBoss.currentFrameX != 4) _miniBoss.attack2Rc = RectMakeCenter(0, 0, 0, 0);
}

void miniBoss::miniBossMove()
{
	if (!_miniBoss.changeState)
	{


		//각도에 따른 방향 설정
		if (_miniBoss.angle >= PI2 - (PI / 4) && _miniBoss.angle <= PI2 || _miniBoss.angle >= 0 && _miniBoss.angle <= PI / 4) _miniBoss.direction = MINIBOSS_RIGHT;
		if (_miniBoss.angle > PI / 4 && _miniBoss.angle <= PI - (PI / 4)) _miniBoss.direction = MINIBOSS_UP;
		if (_miniBoss.angle > PI - (PI / 4) && _miniBoss.angle <= PI + (PI / 4)) _miniBoss.direction = MINIBOSS_LEFT;
		if (_miniBoss.angle > PI + (PI / 4) && _miniBoss.angle <= PI2 - (PI / 4)) _miniBoss.direction = MINIBOSS_DOWN;
	}
}
