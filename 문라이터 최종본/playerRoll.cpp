#include "stdafx.h"
#include "playerRoll.h"

playerState * playerRoll::inputHandle(player * player)
{
	if (player->getPlayer().currentFrameX >= player->getPlayer().img->getMaxFrameX())
	{
		SOUNDMANAGER->stop("WillRoll");
		return new playerIdle();
	}
	if (player->getPlayer().currentHp <= 0)
	{
		SOUNDMANAGER->stop("WillRoll");
		return new playerDie();
	}

	return nullptr;
}

void playerRoll::enter(player * player)
{
	SOUNDMANAGER->play("WillRoll");
	player->setPlayerState(PLAYER_ROLL);
	player->setPlayerCurrentFrameX(0);
	//플레이어 방향별 이미지
	switch (player->getPlayer().direction)
	{
	case PLAYER_DOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_roll_down"));
		break;
	case PLAYER_UP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_roll_up"));
		break;
	case PLAYER_LEFT:
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_roll_left"));
		break;
	case PLAYER_RIGHT:
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_roll_right"));
		break;
	case PLAYER_LEFTUP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_roll_up"));
		break;
	case PLAYER_RIGHTUP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_roll_up"));
		break;
	case PLAYER_LEFTDOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_roll_down"));
		break;
	case PLAYER_RIGHTDOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("will_roll_down"));
		break;
	}
	_playerCount = 0;
}

void playerRoll::update(player * player)
{
	//플레이어 이미지 프레임
	_playerCount++;
	if (_playerCount % 5 == 0)
	{
		player->setPlayerCurrentFrameX(player->getPlayer().currentFrameX + 1);
		_playerCount = 0;
	}
	//플레이어 구르기
	switch (player->getPlayer().direction)
	{
	case PLAYER_DOWN:
		player->setPlayerY(player->getPlayer().y + player->getPlayer().speed * 1.5f);
		break;
	case PLAYER_UP:
		player->setPlayerY(player->getPlayer().y - player->getPlayer().speed * 1.5f);
		break;
	case PLAYER_LEFT:
		player->setPlayerX(player->getPlayer().x - player->getPlayer().speed * 1.5f);
		break;
	case PLAYER_RIGHT:
		player->setPlayerX(player->getPlayer().x + player->getPlayer().speed * 1.5f);
		break;
	case PLAYER_LEFTUP:
		player->setPlayerX(player->getPlayer().x - player->getPlayer().speed * 1.1f);
		player->setPlayerY(player->getPlayer().y - player->getPlayer().speed * 1.1f);
		break;
	case PLAYER_RIGHTUP:
		player->setPlayerX(player->getPlayer().x + player->getPlayer().speed * 1.1f);
		player->setPlayerY(player->getPlayer().y - player->getPlayer().speed * 1.1f);
		break;
	case PLAYER_LEFTDOWN:
		player->setPlayerX(player->getPlayer().x - player->getPlayer().speed * 1.1f);
		player->setPlayerY(player->getPlayer().y + player->getPlayer().speed * 1.1f);
		break;
	case PLAYER_RIGHTDOWN:
		player->setPlayerX(player->getPlayer().x + player->getPlayer().speed * 1.1f);
		player->setPlayerY(player->getPlayer().y + player->getPlayer().speed * 1.1f);
		break;
	}
}

void playerRoll::render(player * player)
{
	player->getPlayer().img->frameRender(player->getPlayer().rc.left, player->getPlayer().rc.top, player->getPlayer().currentFrameX, player->getPlayer().currentFrameY);

}

void playerRoll::exit(player * player)
{
}
