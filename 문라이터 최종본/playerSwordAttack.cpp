#include "stdafx.h"
#include "playerSwordAttack.h"

playerState * playerSwordAttack::inputHandle(player * player)
{
	if (player->getPlayer().currentFrameX >= 4 && !_combo1) 
	{
		SOUNDMANAGER->stop("Àª°ø°Ý");
		return new playerIdle();
	}
	if (player->getPlayer().currentFrameX >= 8 && _combo1 && !_combo2) 
	{
		SOUNDMANAGER->stop("Àª°ø°Ý");
		return new playerIdle();
	}
	if (player->getPlayer().currentFrameX >= player->getPlayer().img->getMaxFrameX() && _combo2)
	{
		SOUNDMANAGER->stop("Àª°ø°Ý");
		return new playerIdle();
	}
	if (player->getPlayer().currentHp <= 0)
	{
		SOUNDMANAGER->stop("Àª°ø°Ý");
		return new playerDie();
	}
	return nullptr;
}

void playerSwordAttack::enter(player * player)
{
	SOUNDMANAGER->play("Àª°ø°Ý");
	player->setPlayerCurrentFrameX(0);
	//ÇÃ·¹ÀÌ¾î ¹æÇâº° ÀÌ¹ÌÁö
	switch (player->getPlayer().direction)
	{
	case PLAYER_DOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª´Ü°Ë¾Æ·¡"));
		break;
	case PLAYER_UP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª´Ü°ËÀ§"));
		break;
	case PLAYER_LEFT:
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª´Ü°Ë¿ÞÂÊ"));
		break;
	case PLAYER_RIGHT:
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª´Ü°Ë¿À¸¥ÂÊ"));
		break;
	case PLAYER_LEFTUP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª´Ü°ËÀ§"));
		break;
	case PLAYER_RIGHTUP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª´Ü°ËÀ§"));
		break;
	case PLAYER_LEFTDOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª´Ü°Ë¾Æ·¡"));
		break;
	case PLAYER_RIGHTDOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("Àª´Ü°Ë¾Æ·¡"));
		break;
	}
	_playerCount = 0;
	_combo1 = _combo2 = _combo3 = false;
}

void playerSwordAttack::update(player * player)
{
	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		if (player->getPlayer().currentFrameX <= 4 && !_combo1) _combo1 = true;
		else if (player->getPlayer().currentFrameX > 4 && player->getPlayer().currentFrameX <= 8 && _combo1)
		{
			
			_combo2 = true;
		}
		else if (player->getPlayer().currentFrameX > 8 && player->getPlayer().currentFrameX <= player->getPlayer().img->getMaxFrameX() && _combo1 && _combo2)
		{
		
			_combo3 = true;
		}
	}
	if (player->getPlayer().currentFrameX == 3)
	{
		SOUNDMANAGER->stop("Àª°ø°Ý");
		SOUNDMANAGER->play("Àª°ø°Ý");
	}
	if (player->getPlayer().currentFrameX == 6)
	{
		SOUNDMANAGER->stop("Àª°ø°Ý");
		SOUNDMANAGER->play("Àª°ø°Ý");
	}
	//ÇÃ·¹ÀÌ¾î ÀÌ¹ÌÁö ÇÁ·¹ÀÓ
	_playerCount++;
	if (_playerCount % 5 == 0)
	{
		player->setPlayerCurrentFrameX(player->getPlayer().currentFrameX + 1);
		

		_playerCount = 0;
	}
	switch (player->getPlayer().direction)
	{
	case PLAYER_DOWN:
		if(player->getPlayer().currentFrameX == 2 || player->getPlayer().currentFrameX == 6 || player->getPlayer().currentFrameX == 10)
			player->setPlayerAttackRect(RectMakeCenter(player->getPlayer().x, player->getPlayer().y + 20, 50, 30));
		if(player->getPlayer().currentFrameX != 2 && player->getPlayer().currentFrameX != 6 && player->getPlayer().currentFrameX != 10)
			player->setPlayerAttackRect(RectMakeCenter(0, 0, 0, 0));
		break;
	case PLAYER_UP:
		if (player->getPlayer().currentFrameX == 2 || player->getPlayer().currentFrameX == 6 || player->getPlayer().currentFrameX == 10)
		player->setPlayerAttackRect(RectMakeCenter(player->getPlayer().x, player->getPlayer().y - 10, 50, 30));
		if (player->getPlayer().currentFrameX != 2 && player->getPlayer().currentFrameX != 6 && player->getPlayer().currentFrameX != 10)
			player->setPlayerAttackRect(RectMakeCenter(0, 0, 0, 0));
		break;
	case PLAYER_LEFT:
		if (player->getPlayer().currentFrameX == 2 || player->getPlayer().currentFrameX == 6 || player->getPlayer().currentFrameX == 10)
		player->setPlayerAttackRect(RectMakeCenter(player->getPlayer().x - 20, player->getPlayer().y + 10 , 30, 50));
		if (player->getPlayer().currentFrameX != 2 && player->getPlayer().currentFrameX != 6 && player->getPlayer().currentFrameX != 10)
			player->setPlayerAttackRect(RectMakeCenter(0, 0, 0, 0));
		break;
	case PLAYER_RIGHT:
		if (player->getPlayer().currentFrameX == 2 || player->getPlayer().currentFrameX == 6 || player->getPlayer().currentFrameX == 10)
		player->setPlayerAttackRect(RectMakeCenter(player->getPlayer().x + 20, player->getPlayer().y + 10, 30, 50));
		if (player->getPlayer().currentFrameX != 2 && player->getPlayer().currentFrameX != 6 && player->getPlayer().currentFrameX != 10)
			player->setPlayerAttackRect(RectMakeCenter(0, 0, 0, 0));
		break;
	case PLAYER_LEFTUP:
		if (player->getPlayer().currentFrameX == 2 || player->getPlayer().currentFrameX == 6 || player->getPlayer().currentFrameX == 10)
		player->setPlayerAttackRect(RectMakeCenter(player->getPlayer().x, player->getPlayer().y - 10, 50, 30));
		if (player->getPlayer().currentFrameX != 2 && player->getPlayer().currentFrameX != 6 && player->getPlayer().currentFrameX != 10)
			player->setPlayerAttackRect(RectMakeCenter(0,0, 0, 0));
		break;
	case PLAYER_RIGHTUP:
		if (player->getPlayer().currentFrameX == 2 || player->getPlayer().currentFrameX == 6 || player->getPlayer().currentFrameX == 10)
		player->setPlayerAttackRect(RectMakeCenter(player->getPlayer().x, player->getPlayer().y - 10, 50, 30));
		if (player->getPlayer().currentFrameX != 2 && player->getPlayer().currentFrameX != 6 && player->getPlayer().currentFrameX != 10)
			player->setPlayerAttackRect(RectMakeCenter(0, 0, 0, 0));
		break;
	case PLAYER_LEFTDOWN:
		if (player->getPlayer().currentFrameX == 2 || player->getPlayer().currentFrameX == 6 || player->getPlayer().currentFrameX == 10)
		player->setPlayerAttackRect(RectMakeCenter(player->getPlayer().x, player->getPlayer().y + 20, 50, 30));
		if (player->getPlayer().currentFrameX != 2 && player->getPlayer().currentFrameX != 6 && player->getPlayer().currentFrameX != 10)
			player->setPlayerAttackRect(RectMakeCenter(0, 0, 0, 0));
		break;
	case PLAYER_RIGHTDOWN:
		if (player->getPlayer().currentFrameX == 2 || player->getPlayer().currentFrameX == 6 || player->getPlayer().currentFrameX == 10)
		player->setPlayerAttackRect(RectMakeCenter(player->getPlayer().x, player->getPlayer().y + 20, 50, 30));
		if (player->getPlayer().currentFrameX != 2 && player->getPlayer().currentFrameX != 6 && player->getPlayer().currentFrameX != 10)
			player->setPlayerAttackRect(RectMakeCenter(0, 0, 0, 0));
		break;
	}

}

void playerSwordAttack::render(player * player)
{
	player->getPlayer().img->frameRender(player->getPlayer().rc.left, player->getPlayer().rc.top, player->getPlayer().currentFrameX, player->getPlayer().currentFrameY);

}

void playerSwordAttack::exit(player * player)
{
}
