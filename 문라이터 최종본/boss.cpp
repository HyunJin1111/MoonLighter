#include "stdafx.h"
#include "boss.h"

boss::boss()
{
}

boss::~boss()
{
}

HRESULT boss::init(float x, float y)
{
	IMAGEMANAGER->addFrameDImage("boss_idle", L"Boss/boss_idle.png", 4176, 295, 16, 1);
	IMAGEMANAGER->addFrameDImage("boss_launch", L"Boss/boss_launch.png", 12831, 295, 39, 1);
	IMAGEMANAGER->addFrameDImage("boss_launch2", L"Boss/boss_launch2.png", 7200, 400, 24, 1);
	IMAGEMANAGER->addFrameDImage("boss_punch", L"Boss/boss_punch.png", 810, 98, 9, 1);
	IMAGEMANAGER->addFrameDImage("boss_attack2", L"Boss/boss_attack2.png", 12900, 295, 43, 1);
	IMAGEMANAGER->addFrameDImage("boss_die", L"Boss/boss_die.png", 12423, 800, 41, 2);


	IMAGEMANAGER->addDImage("Heart_Ring", L"UI/Heart_Ring.png", 31 / 5, 54 / 5);
	IMAGEMANAGER->addDImage("Heart_Ring2", L"UI/Heart_Ring2.png", 31 / 5, 54 / 5);

	_bossState = new bossIdle();
	_bossState->enter(this);
	//보스
	_boss.x = x;
	_boss.y = y;
	_boss.rc = RectMakeCenter(_boss.x, _boss.y, _boss.img->getFrameWidth(), _boss.img->getFrameHeight());
	_boss.hitRc = RectMakeCenter(_boss.x, _boss.y - 40, 240, 200);
	_boss.currentFrameX = _boss.currentFrameY = 0;
	_boss.currentHp = _boss.maxHp = 400;
	_boss.power = 20;
	_boss.enemyHit = false;
	_boss.enemyHitTime = false;
	_boss.isAttack1 = false;
	_boss.enemyHitCount = 0;
	//보스 팔
	_bossArm.img = IMAGEMANAGER->findDImage("boss_punch");
	_bossArm.x = x;
	_bossArm.y = y - 400;
	_bossArm.rc = RectMakeCenter(_bossArm.x, _bossArm.y, _bossArm.img->getFrameWidth(), _bossArm.img->getFrameHeight());
	_bossArm.currentFrameX = _bossArm.currentFrameY = 0;
	_bossArm.count = 0;

	_isAttack1XY = false;

	_hpBar = new enemyProgressBar;
	_hpBar->init(5000, 5000, 400, 10, 2);
	_hpLeft = IMAGEMANAGER->findDImage("Heart_Ring");
	_hpRight = IMAGEMANAGER->findDImage("Heart_Ring2");
	return S_OK;
}

void boss::release()
{
}

void boss::update(float playerX, float playerY)
{
	InputHandle();
	_bossState->update(this);

	//hp 관련
	_hpBar->update(325 + CAMERAMANAGER->getScreen().left, 320 + CAMERAMANAGER->getScreen().top, 2);
	if (_boss.currentHp <= 0)_boss.currentHp = 0;
	_hpBar->setGauge(_boss.currentHp, _boss.maxHp, 2);

	//보스가 공격1을 실행하면
	if (_boss.isAttack1)
	{
		//플레이어의 좌표를 받아온다.
		if (!_isAttack1XY)
		{
			_bossArm.x = playerX;
			_attack1Y = playerY;
			_isAttack1XY = true;
		}
		//보스 팔 프레임
		_bossArm.count++;
		if (_bossArm.count % 10 == 0)
		{
			_bossArm.currentFrameX++;
			_bossArm.count = 0;
			//프레임이 다 돌면 공격1을 해제 후 팔의 위치를 변경해준다.
			if (_bossArm.currentFrameX > _bossArm.img->getMaxFrameX())
			{
				_bossArm.y = _boss.y - 400;
				_boss.isAttack1 = false;
				_isAttack1XY = false;
				_bossArm.currentFrameX = 0;
			}
		}
		//팔의 속도만큼 낙하시키고 처음 저장했던 플레이어의 y값을 더이상 넘어가지 않게 한다.
		_bossArm.y += 15;

		if (_bossArm.y >= _attack1Y)
		{
			_bossArm.y = _attack1Y;
		}

	}

	//렉트 갱신
	_boss.rc = RectMakeCenter(_boss.x, _boss.y, _boss.img->getFrameWidth(), _boss.img->getFrameHeight());
	_bossArm.rc = RectMakeCenter(_bossArm.x, _bossArm.y, _bossArm.img->getFrameWidth(), _bossArm.img->getFrameHeight());
}

void boss::render()
{
	_bossState->render(this);
	_bossArm.img->frameRender(_bossArm.rc.left, _bossArm.rc.top, _bossArm.currentFrameX, _bossArm.currentFrameY);
	_hpBar->render(2, 400);
	_hpLeft->render(120 + CAMERAMANAGER->getScreen().left, 315 + CAMERAMANAGER->getScreen().top);
	_hpRight->render(525 + CAMERAMANAGER->getScreen().left, 315 + CAMERAMANAGER->getScreen().top);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		D2DMANAGER->DrawRectangle(_boss.rc);
		D2DMANAGER->DrawRectangle(_boss.hitRc);
		D2DMANAGER->DrawRectangle(_bossArm.rc);
		D2DMANAGER->DrawRectangle(_boss.attackRc2);
	}
}

void boss::InputHandle()
{
	bossState* newState = _bossState->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_bossState);
		_bossState = newState;
		_bossState->enter(this);
	}
}

