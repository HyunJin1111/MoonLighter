#include "stdafx.h"
#include "bossAttack1Reverse.h"

bossState * bossAttack1Reverse::inputHandle(boss * boss)
{
	if (boss->getBoss().currentHp <= 0) return new bossDie();

	if (boss->getBoss().currentFrameX >= boss->getBoss().img->getMaxFrameX())
	{
		return new bossIdle();
	}
	return nullptr;
}

void bossAttack1Reverse::enter(boss * boss)
{
	boss->setBossImg(IMAGEMANAGER->findDImage("boss_launch2"));
	boss->setBossCurrentFrameX(0);
	boss->setBossCurrentFrameY(0);
	_bossCount = 0;
}

void bossAttack1Reverse::update(boss * boss)
{
	_bossCount++;
	//플레이어 이미지 프레임
	if (_bossCount % 5 == 0)
	{
		boss->setBossCurrentFrameX(boss->getBoss().currentFrameX + 1);
		_bossCount = 0;
	}
}

void bossAttack1Reverse::render(boss * boss)
{
	if (!boss->getBoss().enemyHit) boss->getBoss().img->frameRender(boss->getBoss().rc.left, boss->getBoss().rc.top, boss->getBoss().currentFrameX, boss->getBoss().currentFrameY, 1);
	else  boss->getBoss().img->frameRender(boss->getBoss().rc.left, boss->getBoss().rc.top, boss->getBoss().currentFrameX, boss->getBoss().currentFrameY, 0);
}

void bossAttack1Reverse::exit(boss * boss)
{
}
