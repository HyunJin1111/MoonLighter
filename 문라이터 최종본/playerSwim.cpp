#include "stdafx.h"
#include "playerSwim.h"

playerState * playerSwim::inputHandle(player * player)
{
	if (player->getPlayer().state == PLAYER_WALK)
	{
		SOUNDMANAGER->stop("윌수영");
		return new playerWalk();
	}
	return nullptr;
}

void playerSwim::enter(player * player)
{
	SOUNDMANAGER->play("윌수영");
	player->setPlayerState(PLAYER_SWIM);
	player->setPlayerCurrentFrameX(0);
	//플레이어 방향별 이미지
	switch (player->getPlayer().direction)
	{
	case PLAYER_DOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌수영아래"));
		break;
	case PLAYER_UP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌수영위"));
		break;
	case PLAYER_LEFT:
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌수영왼쪽"));
		break;
	case PLAYER_RIGHT:
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌수영오른쪽"));
		break;
	case PLAYER_LEFTUP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌수영위"));
		break;
	case PLAYER_RIGHTUP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌수영위"));
		break;
	case PLAYER_LEFTDOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌수영아래"));
		break;
	case PLAYER_RIGHTDOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌수영아래"));
		break;
	}
	_playerCount = 0;
}

void playerSwim::update(player * player)
{
	//플레이어 이동
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->setPlayerDirection(PLAYER_DOWN);
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌수영아래"));
		player->setPlayerY(player->getPlayer().y + player->getPlayer().speed);
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->setPlayerDirection(PLAYER_UP);
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌수영위"));
		player->setPlayerY(player->getPlayer().y - player->getPlayer().speed);
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->setPlayerDirection(PLAYER_LEFT);
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌수영왼쪽"));
		player->setPlayerX(player->getPlayer().x - player->getPlayer().speed);
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		player->setPlayerDirection(PLAYER_RIGHT);
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌수영오른쪽"));
		player->setPlayerX(player->getPlayer().x + player->getPlayer().speed);
	}
	if (KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isStayKeyDown('W'))
	{
		player->setPlayerDirection(PLAYER_LEFTUP);
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌수영위"));
	}
	if (KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown('W'))
	{
		player->setPlayerDirection(PLAYER_RIGHTUP);
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌수영위"));
	}
	if (KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isStayKeyDown('S'))
	{
		player->setPlayerDirection(PLAYER_LEFTDOWN);
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌수영아래"));
	}
	if (KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown('S'))
	{
		player->setPlayerDirection(PLAYER_RIGHTDOWN);
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌수영아래"));
	}

	//플레이어 이미지 프레임
	_playerCount++;
	if (_playerCount % 10 == 0)
	{
		player->setPlayerCurrentFrameX(player->getPlayer().currentFrameX + 1);
		if (player->getPlayer().currentFrameX > player->getPlayer().img->getMaxFrameX())
		{
			player->setPlayerCurrentFrameX(0);
		}
		_playerCount = 0;
	}
}

void playerSwim::render(player * player)
{
	player->getPlayer().img->frameRender(player->getPlayer().rc.left, player->getPlayer().rc.top, player->getPlayer().currentFrameX, player->getPlayer().currentFrameY);
}

void playerSwim::exit(player * player)
{
}
