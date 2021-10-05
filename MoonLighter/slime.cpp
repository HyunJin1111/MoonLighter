#include "stdafx.h"
#include "slime.h"

slime::slime()
{
}

slime::~slime()
{
}

HRESULT slime::init(int x, int y, RECT player, int diffrentX, int diffrentY, int backGroundNum)
{
	IMAGEMANAGER->addFrameDImage("slime_walk", L"Enemy/slime_walk.png", 168, 24, 8, 1);
	IMAGEMANAGER->addFrameDImage("slime_attack", L"Enemy/slime_attack.png", 1120, 48, 16, 1);
	IMAGEMANAGER->addFrameDImage("slime_die", L"Enemy/slime_die.png", 640, 44, 10, 1);

	tagSlime slime;
	ZeroMemory(&slime, sizeof(tagSlime));
	slime.x = x;
	slime.y = y;
	slime.img = IMAGEMANAGER->findDImage("slime_walk");
	slime.currentFrameX = slime.currentFrameY = 0;
	slime.count = 0;
	slime.rand = 0;
	slime.power = 10;
	slime.die = false;
	slime.currentHp = slime.maxHp = 100;
	slime.angleRand1 = slime.angleRand2 = RND->getFromFloatTo(0, PI2);
	slime.walkRand = slime.walkCount = 0;
	slime.rc = RectMakeCenter(x, y, slime.img->getFrameWidth(), slime.img->getFrameHeight());
	slime.hitRc = RectMakeCenter(x, y, 21, 24);
	slime.moveRect = RectMakeCenter(x, y, 200, 200);
	slime.attackRect = RectMakeCenter(x, y, 30, 30);
	slime.speed = 2;
	slime.enemyHit = false;
	slime.enemyHitCount = 0;
	slime.enemyHitTime = false;
	slime.angle = PI;
	slime.state = SLIME_WALK;
	slime.changeState = false;
	slime.backGroundNum = backGroundNum;

	slime.hpBar = new enemyProgressBar;
	slime.hpBar->init(slime.x, slime.y - 20, 40, 6, 0);
	slime._aStar = new aStar;
	slime._aStar->setTiles(slime.x, slime.y, player, diffrentX, diffrentY);

	_vSlime.push_back(slime);
	return S_OK;
}

void slime::release()
{
}

void slime::update(int diffrentX, int diffrentY, RECT player, int backNum)
{


	for (int i = 0; i < _vSlime.size(); ++i)
	{
		if (_vSlime[i].backGroundNum != backNum) continue;


		_vSlime[i].hpBar->update(_vSlime[i].x, _vSlime[i].y - 20, 0);
		if (_vSlime[i].currentHp <= 0)_vSlime[i].currentHp = 0;
		_vSlime[i].hpBar->setGauge(_vSlime[i].currentHp, _vSlime[i].maxHp, 0);
		//예외처리
		if (diffrentX >= _vSlime[i].rc.left)
		{
			_vSlime[i].x = diffrentX + _vSlime[i].img->getFrameWidth() / 2;
			_vSlime[i].x++;
		}
		if (diffrentX - 78 * 2 + 650 <= _vSlime[i].rc.right)
		{
			_vSlime[i].x = diffrentX - 78 * 2 + 650 - _vSlime[i].img->getFrameWidth() / 2;
			_vSlime[i].x--;
		}
		if (diffrentY >= _vSlime[i].rc.top)
		{
			_vSlime[i].y = diffrentY + _vSlime[i].img->getFrameHeight() / 2;
			_vSlime[i].y++;
		}

		if (diffrentY - 51 * 2 + 390 <= _vSlime[i].rc.bottom)
		{
			_vSlime[i].y = diffrentY - 51 * 2 + 390 - _vSlime[i].img->getFrameHeight() / 2;
			_vSlime[i].y--;
		}


		_vSlime[i].count++;
		if (_vSlime[i].count % 4 == 0)
		{
			_vSlime[i].currentFrameX++;
			if (_vSlime[i].currentFrameX > _vSlime[i].img->getMaxFrameX())
			{
				if (_vSlime[i].state == SLIME_IDLE || _vSlime[i].state == SLIME_WALK || _vSlime[i].state == SLIME_RANDOM)
				{
					_vSlime[i].currentFrameX = 0;
					_vSlime[i].count = 0;
					_vSlime[i].changeState = false;
				}
				if (_vSlime[i].state == SLIME_ATTACK)
				{
					_vSlime[i].currentFrameX = 0;
					_vSlime[i].count = 0;
					_vSlime[i].state = SLIME_IDLE;
					_vSlime[i].changeState = false;
				}
			}
		}
		RECT AttackTemp;
		RECT MoveTemp;
		//플레이어가 attackRect에 닿았을때 공격
		if (IntersectRect(&AttackTemp, &player, &_vSlime[i].attackRect) && !_vSlime[i].changeState)
		{
			_vSlime[i].rand++;
			_vSlime[i].state = SLIME_IDLE;
			if (_vSlime[i].rand % 70 == 0)
			{
				_vSlime[i].state = SLIME_ATTACK;
				SOUNDMANAGER->play("SlimeAttackSound");
				_vSlime[i].currentFrameX = 0;
				_vSlime[i].changeState = true;
				_vSlime[i].rand = 0;
			}
		}

		//플레이어가 moveRect에 닿았을때 에이스타 실행(쫒아 이동)
		else if (IntersectRect(&MoveTemp, &player, &_vSlime[i].moveRect) && !_vSlime[i].changeState)
		{
			_vSlime[i].state = SLIME_WALK;
			_vSlime[i]._aStar->update(diffrentX, diffrentY, player, _vSlime[i].rc);
			_vSlime[i].angle = getAngle(_vSlime[i].x, _vSlime[i].y, _vSlime[i]._aStar->getSaveTile()->getRc().left + 13, _vSlime[i]._aStar->getSaveTile()->getRc().top + 13);
			_vSlime[i].x += cosf(_vSlime[i].angle) * 1;
			_vSlime[i].y += -sinf(_vSlime[i].angle) * 1;

		}
		//위 2개의 렉트에 닿지 않았을때 가만히 혹은 랜덤이동
		else if (!IntersectRect(&MoveTemp, &player, &_vSlime[i].moveRect) && !IntersectRect(&AttackTemp, &player, &_vSlime[i].attackRect))
		{
			_vSlime[i].state = SLIME_WALK;
			_vSlime[i].walkCount++;
			if (_vSlime[i].walkCount % 70 == 0)
			{
				_vSlime[i].angleRand1 = RND->getFromFloatTo(0, PI2);
				_vSlime[i].angleRand2 = RND->getFromFloatTo(0, PI2);
				_vSlime[i].walkRand = RND->getFromIntTo(0, 2);

				_vSlime[i].walkCount = 0;
			}
			switch (_vSlime[i].walkRand)
			{
			case 0:
				_vSlime[i].x += cosf(_vSlime[i].angleRand1) * 1;
				_vSlime[i].y += -sinf(_vSlime[i].angleRand2) * 1;
				break;
			case 1:
				break;
			}
		}




		//상태 및 방향에 따른 이미지 설정
		switch (_vSlime[i].state)
		{
			//IDLE 상태
		case SLIME_IDLE:
			_vSlime[i].img = IMAGEMANAGER->findDImage("slime_walk");
			break;
			//WALK 상태
		case SLIME_WALK:
			_vSlime[i].img = IMAGEMANAGER->findDImage("slime_walk");
			break;
			//attack 상태
		case SLIME_ATTACK:
			_vSlime[i].img = IMAGEMANAGER->findDImage("slime_attack");
			if (_vSlime[i].currentFrameX == 8) 	_vSlime[i].powerRect = RectMakeCenter(_vSlime[i].x, _vSlime[i].y, 50, 50);
			else if (_vSlime[i].currentFrameX != 8)  _vSlime[i].powerRect = RectMakeCenter(0, 0, 0, 0);
			break;
			//die 상태
		case SLIME_DIE:
			_vSlime[i].img = IMAGEMANAGER->findDImage("slime_die");
			break;
			//RANDOM 상태
		case SLIME_RANDOM:
			_vSlime[i].img = IMAGEMANAGER->findDImage("slime_walk");
			break;
		}
		if (_vSlime[i].state != SLIME_ATTACK)_vSlime[i].powerRect = RectMakeCenter(0, 0, 0, 0);

		//렉트 설정
		_vSlime[i].rc = RectMakeCenter(_vSlime[i].x, _vSlime[i].y, _vSlime[i].img->getFrameWidth(), _vSlime[i].img->getFrameHeight());
		_vSlime[i].hitRc = RectMakeCenter(_vSlime[i].x, _vSlime[i].y, 21, 24);
		_vSlime[i].moveRect = RectMakeCenter(_vSlime[i].x, _vSlime[i].y, 200, 200);
		_vSlime[i].attackRect = RectMakeCenter(_vSlime[i].x, _vSlime[i].y, 30, 30);



		//체력 0 이하 될 시
		if (_vSlime[i].currentHp <= 0 && !_vSlime[i].die)
		{
			_vSlime[i].currentFrameX = 0;
			_vSlime[i].enemyHitTime = false;
			_vSlime[i].enemyHit = false;
			_vSlime[i].state = SLIME_DIE;
			SOUNDMANAGER->play("SlimeDeathSound");
			_vSlime[i].die = true;
			EFFECTMANAGER->play("slimeEffect", _vSlime[i].x, _vSlime[i].y, 1);
			erase(i);
		}


		_vSlime[i].upLeft = RectMakeCenter(_vSlime[i].x - 5, _vSlime[i].y, 5, 5);
		_vSlime[i].upRight = RectMakeCenter(_vSlime[i].x + 5, _vSlime[i].y, 5, 5);
		_vSlime[i].downLeft = RectMakeCenter(_vSlime[i].x - 5, _vSlime[i].y + 15, 5, 5);
		_vSlime[i].downRight = RectMakeCenter(_vSlime[i].x + 5, _vSlime[i].y + 15, 5, 5);

		_vSlime[i].leftUp = RectMakeCenter(_vSlime[i].x - 12, _vSlime[i].y + 5, 5, 5);
		_vSlime[i].leftDown = RectMakeCenter(_vSlime[i].x - 12, _vSlime[i].y + 10, 5, 5);
		_vSlime[i].rightUp = RectMakeCenter(_vSlime[i].x + 12, _vSlime[i].y + 5, 5, 5);
		_vSlime[i].rightDown = RectMakeCenter(_vSlime[i].x + 12, _vSlime[i].y + 10, 5, 5);


	}

	EFFECTMANAGER->update();

}

void slime::render()
{

	for (int i = 0; i < _vSlime.size(); ++i)
	{
		if (_vSlime[i].currentHp <= 0 && _vSlime[i].currentFrameX == _vSlime[i].img->getMaxFrameX()) continue;
		if (_vSlime[i].enemyHit)	_vSlime[i].img->frameRender(_vSlime[i].rc.left, _vSlime[i].rc.top, _vSlime[i].currentFrameX, _vSlime[i].currentFrameY, 0);
		if (!_vSlime[i].enemyHit)	_vSlime[i].img->frameRender(_vSlime[i].rc.left, _vSlime[i].rc.top, _vSlime[i].currentFrameX, _vSlime[i].currentFrameY, 1);
		_vSlime[i].hpBar->render(0, 40);
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			D2DMANAGER->DrawRectangle(_vSlime[i].moveRect);
			D2DMANAGER->DrawRectangle(_vSlime[i].attackRect);
			D2DMANAGER->DrawRectangle(_vSlime[i].rc);
			D2DMANAGER->DrawRectangle(_vSlime[i].hitRc);
			D2DMANAGER->DrawRectangle(_vSlime[i].upLeft);
			D2DMANAGER->DrawRectangle(_vSlime[i].upRight);
			D2DMANAGER->DrawRectangle(_vSlime[i].downLeft);
			D2DMANAGER->DrawRectangle(_vSlime[i].downRight);
			D2DMANAGER->DrawRectangle(_vSlime[i].leftUp);
			D2DMANAGER->DrawRectangle(_vSlime[i].leftDown);
			D2DMANAGER->DrawRectangle(_vSlime[i].rightUp);
			D2DMANAGER->DrawRectangle(_vSlime[i].rightDown);
		}

	}
	EFFECTMANAGER->render();
	
}

void slime::erase(int num)
{
	if (_vSlime[num].state == SLIME_DIE)
	{
		_vSlime.erase(_vSlime.begin() + num);
	}

}

void slime::slimeState()
{

}

void slime::slimeMove()
{
}
