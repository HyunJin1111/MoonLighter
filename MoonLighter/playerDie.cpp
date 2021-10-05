#include "stdafx.h"
#include "playerDie.h"

playerState * playerDie::inputHandle(player * player)
{
	return nullptr;
}

void playerDie::enter(player * player)
{
	player->setPlayerCurrentFrameX(0);

	player->setPlayerImg(IMAGEMANAGER->findDImage("will_die"));
	
	_playerCount = 0;
}

void playerDie::update(player * player)
{
	_playerCount++;
	//플레이어 이미지 프레임
	if (_playerCount % 7 == 0)
	{
		player->setPlayerCurrentFrameX(player->getPlayer().currentFrameX + 1);
		if (player->getPlayer().currentFrameX > player->getPlayer().img->getMaxFrameX())
		{
			player->setPlayerCurrentFrameX(0);
		}
		_playerCount = 0;
	}
}

void playerDie::render(player * player)
{
	player->getPlayer().img->frameRender(player->getPlayer().rc.left, player->getPlayer().rc.top, player->getPlayer().currentFrameX, player->getPlayer().currentFrameY);
}

void playerDie::exit(player * player)
{
}
