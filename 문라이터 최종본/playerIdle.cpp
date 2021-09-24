#include "stdafx.h"
#include "playerIdle.h"

playerState * playerIdle::inputHandle(player * player)
{
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->setPlayerDirection(PLAYER_DOWN);
		return new playerWalk();
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->setPlayerDirection(PLAYER_UP);
		return new playerWalk();
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->setPlayerDirection(PLAYER_LEFT);
		return new playerWalk();
	}		
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		player->setPlayerDirection(PLAYER_RIGHT);
		return new playerWalk();
	}		
	if (SCENEMANAGER->isCurrentScene("dungeon") && KEYMANAGER->isOnceKeyDown('J'))
	{
		return new playerSwordAttack();
	}
	if (player->getPlayer().state == PLAYER_SWIM)
	{
		return new playerSwim();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) return new playerRoll();
	if (player->getPlayer().currentHp <= 0) return new playerDie();

	return nullptr;
}

void playerIdle::enter(player * player)
{
	player->setPlayerCurrentFrameX(0);
	//플레이어 방향별 이미지
	switch (player->getPlayer().direction)
	{
	case PLAYER_DOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌기본아래"));
		break;
	case PLAYER_UP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌기본위"));
		break;
	case PLAYER_LEFT:
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌기본왼쪽"));
		break;
	case PLAYER_RIGHT:
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌기본오른쪽"));
		break;
	case PLAYER_LEFTUP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌기본위"));
		break;
	case PLAYER_RIGHTUP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌기본위"));
		break;
	case PLAYER_LEFTDOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌기본아래"));
		break;
	case PLAYER_RIGHTDOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("윌기본아래"));
		break;
	}
	_playerCount = 0;
}

void playerIdle::update(player * player)
{
	player->setPlayerAttackRect(RectMakeCenter(0, 0, 0, 0));
	_playerCount++;
	//플레이어 이미지 프레임
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

void playerIdle::render(player * player)
{
	player->getPlayer().img->frameRender(player->getPlayer().rc.left, player->getPlayer().rc.top, player->getPlayer().currentFrameX, player->getPlayer().currentFrameY);
}

void playerIdle::exit(player * player)
{
}
