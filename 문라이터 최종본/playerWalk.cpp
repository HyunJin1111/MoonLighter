#include "stdafx.h"
#include "playerWalk.h"

playerState * playerWalk::inputHandle(player * player)
{
	if (KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
	{
		SOUNDMANAGER->stop("Àª¹ß°ÉÀ½");
		return new playerIdle();
	}
	if (SCENEMANAGER->isCurrentScene("dungeon") && KEYMANAGER->isOnceKeyDown('J'))
	{
		SOUNDMANAGER->stop("Àª¹ß°ÉÀ½");
		return new playerSwordAttack();
	}
	if (player->getPlayer().state == PLAYER_SWIM) 
	{
		SOUNDMANAGER->stop("Àª¹ß°ÉÀ½");
		return new playerSwim();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SOUNDMANAGER->stop("Àª¹ß°ÉÀ½");
		return new playerRoll();
	}
	if (player->getPlayer().currentHp <= 0)
	{
		SOUNDMANAGER->stop("Àª¹ß°ÉÀ½");
		return new playerDie();
	}


	return nullptr;
}

void playerWalk::enter(player * player)
{	
	SOUNDMANAGER->play("Àª¹ß°ÉÀ½");
	player->setPlayerState(PLAYER_WALK);
	player->setPlayerCurrentFrameX(0);
	//ÇÃ·¹ÀÌ¾î ¹æÇâº° ÀÌ¹ÌÁö
	switch (player->getPlayer().direction)
	{
	case PLAYER_DOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª°È±â¾Æ·¡"));
		break;
	case PLAYER_UP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª°È±âÀ§"));
		break;
	case PLAYER_LEFT:
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª°È±â¿ÞÂÊ"));
		break;
	case PLAYER_RIGHT:
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª°È±â¿À¸¥ÂÊ"));
		break;
	case PLAYER_LEFTUP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª°È±âÀ§"));
		break;
	case PLAYER_RIGHTUP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª°È±âÀ§"));
		break;
	case PLAYER_LEFTDOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª°È±â¾Æ·¡"));
		break;
	case PLAYER_RIGHTDOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª°È±â¾Æ·¡"));
		break;
	}
	_playerCount = 0;
}

void playerWalk::update(player * player)
{
	
	//ÇÃ·¹ÀÌ¾î ÀÌµ¿
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->setPlayerDirection(PLAYER_DOWN);
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª°È±â¾Æ·¡"));
		player->setPlayerY(player->getPlayer().y + player->getPlayer().speed);
	}
	if (KEYMANAGER->isStayKeyDown('W')) 
	{
		player->setPlayerDirection(PLAYER_UP);
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª°È±âÀ§"));
		player->setPlayerY(player->getPlayer().y - player->getPlayer().speed);
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->setPlayerDirection(PLAYER_LEFT);
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª°È±â¿ÞÂÊ"));
		player->setPlayerX(player->getPlayer().x - player->getPlayer().speed);
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{ 
		player->setPlayerDirection(PLAYER_RIGHT);
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª°È±â¿À¸¥ÂÊ"));
		player->setPlayerX(player->getPlayer().x + player->getPlayer().speed); 
	}
	if (KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isStayKeyDown('W'))
	{
		player->setPlayerDirection(PLAYER_LEFTUP);
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª°È±âÀ§"));
	}
	if (KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown('W'))
	{
		player->setPlayerDirection(PLAYER_RIGHTUP);
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª°È±âÀ§"));
	}
	if (KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isStayKeyDown('S'))
	{
		player->setPlayerDirection(PLAYER_LEFTDOWN);
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª°È±â¾Æ·¡"));
	}
	if (KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown('S'))
	{ 
		player->setPlayerDirection(PLAYER_RIGHTDOWN);
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª°È±â¾Æ·¡"));
	}

	//ÇÃ·¹ÀÌ¾î ÀÌ¹ÌÁö ÇÁ·¹ÀÓ
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
