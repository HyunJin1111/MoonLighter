#include "stdafx.h"
#include "bossAttack1.h"

bossState * bossAttack1::inputHandle(boss * boss)
{
	if (boss->getBoss().currentHp <= 0) return new bossDie();

	if (boss->getBoss().currentFrameX >= boss->getBoss().img->getMaxFrameX())
	{
		return new bossAttack1Reverse();
	}
	return nullptr;
}

void bossAttack1::enter(boss * boss)
{
	boss->setBossImg(IMAGEMANAGER->findDImage("보스_attack1"));
	boss->setBossCurrentFrameX(0);
	boss->setBossCurrentFrameY(0);
	_bossCount = 0;
	_bossArmCount = 0;
}

void bossAttack1::update(boss * boss)
{
	_bossCount++;
	//플레이어 이미지 프레임
	if (_bossCount % 5 == 0)
	{
		boss->setBossCurrentFrameX(boss->getBoss().currentFrameX + 1);
		_bossCount = 0;
	}
	if (boss->getBoss().currentFrameX == 21) 
	{
		boss->setBossAttack1(true);
	}

	if (boss->getBoss().currentFrameX == 25 && _bossCount == 0) SOUNDMANAGER->play("보스어택1");

}

void bossAttack1::render(boss * boss)
{
	if (!boss->getBoss().enemyHit) boss->getBoss().img->frameRender(boss->getBoss().rc.left, boss->getBoss().rc.top, boss->getBoss().currentFrameX, boss->getBoss().currentFrameY, 1);
	else  boss->getBoss().img->frameRender(boss->getBoss().rc.left, boss->getBoss().rc.top, boss->getBoss().currentFrameX, boss->getBoss().currentFrameY, 0);
}

void bossAttack1::exit(boss * boss)
{
}
