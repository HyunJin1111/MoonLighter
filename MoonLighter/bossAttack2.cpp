#include "stdafx.h"
#include "bossAttack2.h"

bossState * bossAttack2::inputHandle(boss * boss)
{
	if (boss->getBoss().currentHp <= 0) return new bossDie();

	if (boss->getBoss().currentFrameX >= boss->getBoss().img->getMaxFrameX())
	{
		return new bossIdle();
	}
	return nullptr;
}

void bossAttack2::enter(boss * boss)
{
	boss->setBossImg(IMAGEMANAGER->findDImage("boss_attack2"));
	boss->setBossCurrentFrameX(0);
	boss->setBossCurrentFrameY(0);
	_bossCount = 0;
}

void bossAttack2::update(boss * boss)
{
	_bossCount++;
	//플레이어 이미지 프레임
	if (_bossCount % 5 == 0)
	{
		boss->setBossCurrentFrameX(boss->getBoss().currentFrameX + 1);	
		_bossCount = 0;
	}
	if (boss->getBoss().currentFrameX == 18) 
	{
		boss->setBossAttack2Rect(RectMakeCenter(boss->getBoss().x, boss->getBoss().y + 100, 200, 100));
	}
	else boss->setBossAttack2Rect(RectMakeCenter(0,0,0,0));
	if (boss->getBoss().currentFrameX == 12 && _bossCount == 0)SOUNDMANAGER->play("BossAttackSound2");
}

void bossAttack2::render(boss * boss)
{
	if (!boss->getBoss().enemyHit) boss->getBoss().img->frameRender(boss->getBoss().rc.left, boss->getBoss().rc.top, boss->getBoss().currentFrameX, boss->getBoss().currentFrameY, 1);
	else  boss->getBoss().img->frameRender(boss->getBoss().rc.left, boss->getBoss().rc.top, boss->getBoss().currentFrameX, boss->getBoss().currentFrameY, 0);
}

void bossAttack2::exit(boss * boss)
{
}
