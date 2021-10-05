#include "stdafx.h"
#include "bossDie.h"

bossState * bossDie::inputHandle(boss * boss)
{
	return nullptr;
}

void bossDie::enter(boss * boss)
{
	SOUNDMANAGER->play("BossDeathSound");
	boss->setBossImg(IMAGEMANAGER->findDImage("boss_die"));
	boss->setBossCurrentFrameX(0);
	boss->setBossCurrentFrameY(0);
	_bossCount = 0;
}

void bossDie::update(boss * boss)
{
	_bossCount++;
	//플레이어 이미지 프레임
	if (_bossCount % 5 == 0)
	{
		boss->setBossCurrentFrameX(boss->getBoss().currentFrameX + 1);
		if (boss->getBoss().currentFrameX > boss->getBoss().img->getMaxFrameX())
		{
			boss->setBossCurrentFrameX(0);
			boss->setBossCurrentFrameY(boss->getBoss().currentFrameY + 1);
			if (boss->getBoss().currentFrameY > boss->getBoss().img->getMaxFrameY()) 
			{
				boss->setBossCurrentFrameY(0);
			}
		}
		_bossCount = 0;
	}
}

void bossDie::render(boss * boss)
{
	boss->getBoss().img->frameRender(boss->getBoss().rc.left, boss->getBoss().rc.top, boss->getBoss().currentFrameX, boss->getBoss().currentFrameY);
}

void bossDie::exit(boss * boss)
{
}
