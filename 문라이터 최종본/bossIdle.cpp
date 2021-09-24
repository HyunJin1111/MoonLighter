#include "stdafx.h"
#include "bossIdle.h"

bossState * bossIdle::inputHandle(boss * boss)
{
	if (boss->getBoss().currentHp <= 0) return new bossDie();

	if (_bossStateCount %  _bossStateRand == 0)
	{
		switch (_bossStateChange)
		{
		case 0:
			return new bossAttack1();
			break;
		case 1:
			return new bossAttack2();
			break;
		}
	}
	return nullptr;
}

void bossIdle::enter(boss * boss)
{
	boss->setBossImg(IMAGEMANAGER->findDImage("보스_idle"));
	boss->setBossCurrentFrameX(0);
	boss->setBossCurrentFrameY(0);
	_bossCount = 0;
	_bossStateCount = 0;
	_bossStateRand = RND->getFromIntTo(100, 150);
	_bossStateChange = RND->getFromIntTo(0, 2);
}

void bossIdle::update(boss * boss)
{
	_bossCount++;
	//플레이어 이미지 프레임
	if (_bossCount % 5 == 0)
	{
		boss->setBossCurrentFrameX(boss->getBoss().currentFrameX + 1);
		if (boss->getBoss().currentFrameX > boss->getBoss().img->getMaxFrameX())
		{
			boss->setBossCurrentFrameX(0);
		}
		_bossCount = 0;
	}
	_bossStateCount++;


}

void bossIdle::render(boss * boss)
{
	if (!boss->getBoss().enemyHit) boss->getBoss().img->frameRender(boss->getBoss().rc.left, boss->getBoss().rc.top, boss->getBoss().currentFrameX, boss->getBoss().currentFrameY, 1);
	else  boss->getBoss().img->frameRender(boss->getBoss().rc.left, boss->getBoss().rc.top, boss->getBoss().currentFrameX, boss->getBoss().currentFrameY, 0);
}

void bossIdle::exit(boss * boss)
{
}
