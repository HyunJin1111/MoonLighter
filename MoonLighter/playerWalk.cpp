#include "stdafx.h"
#include "playerWalk.h"

playerState * playerWalk::inputHandle(player * player)
{
	if (KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
	{
		SOUNDMANAGER->stop("WillStep");
		return new playerIdle();
	}
	if (SCENEMANAGER->isCurrentScene("dungeon") && KEYMANAGER->isOnceKeyDown('J'))
	{
		SOUNDMANAGER->stop("WillStep");
		return new playerSwordAttack();
	}
	if (player->getPlayer().state == PLAYER_SWIM) 
	{
		SOUNDMANAGER->stop("WillStep");
		return new playerSwim();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SOUNDMANAGER->stop("WillStep");
		return new playerRoll();
	}
	if (player->getPlayer().currentHp <= 0)
	{
		SOUNDMANAGER->stop("WillStep");
		return new playerDie();
	}


	return nullptr;
}

void playerWalk::enter(player * player)
{	
	SOUNDMANAGER->play("WillStep");
	player->setPlayerState(PLAYER_WALK);
	player->setPlayerCurrentFrameX(0);
	//플레이어 방향별 이미지
	switch (player->getPlayer().direction)
	{
	case PLAYER_DOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_run_down"));
		break;
	case PLAYER_UP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_run_up"));
		break;
	case PLAYER_LEFT:
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_run_left"));
		break;
	case PLAYER_RIGHT:
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_run_right"));
		break;
	case PLAYER_LEFTUP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_run_up"));
		break;
	case PLAYER_RIGHTUP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_run_up"));
		break;
	case PLAYER_LEFTDOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_run_down"));
		break;
	case PLAYER_RIGHTDOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_run_down"));
		break;
	}
	_playerCount = 0;
}

void playerWalk::update(player * player)
{
	
	//플레이어 이동
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->setPlayerDirection(PLAYER_DOWN);
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_run_down"));
		player->setPlayerY(player->getPlayer().y + player->getPlayer().speed);
	}
	if (KEYMANAGER->isStayKeyDown('W')) 
	{
		player->setPlayerDirection(PLAYER_UP);
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_run_up"));
		player->setPlayerY(player->getPlayer().y - player->getPlayer().speed);
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->setPlayerDirection(PLAYER_LEFT);
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_run_left"));
		player->setPlayerX(player->getPlayer().x - player->getPlayer().speed);
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{ 
		player->setPlayerDirection(PLAYER_RIGHT);
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_run_right"));
		player->setPlayerX(player->getPlayer().x + player->getPlayer().speed); 
	}
	if (KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isStayKeyDown('W'))
	{
		player->setPlayerDirection(PLAYER_LEFTUP);
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_run_up"));
	}
	if (KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown('W'))
	{
		player->setPlayerDirection(PLAYER_RIGHTUP);
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_run_up"));
	}
	if (KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isStayKeyDown('S'))
	{
		player->setPlayerDirection(PLAYER_LEFTDOWN);
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_run_down"));
	}
	if (KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown('S'))
	{ 
		player->setPlayerDirection(PLAYER_RIGHTDOWN);
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_run_down"));
	}

	//플레이어 이미지 프레임
	_playerCount++;
	if (_playerCount % 4 == 0)
	{
		player->setPlayerCurrentFrameX(player->getPlayer().currentFrameX + 1);
		if (player->getPlayer().currentFrameX > player->getPlayer().img->getMaxFrameX())
		{
			player->setPlayerCurrentFrameX(0);
		}
		_playerCount = 0;
	}
}

void playerWalk::render(player * player)
{
	player->getPlayer().img->frameRender(player->getPlayer().rc.left, player->getPlayer().rc.top, player->getPlayer().currentFrameX, player->getPlayer().currentFrameY);
}

void playerWalk::exit(player * player)
{
}
