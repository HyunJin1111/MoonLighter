#include "stdafx.h"
#include "playerWalk.h"

playerState * playerWalk::inputHandle(player * player)
{
	if (KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
	{
		SOUNDMANAGER->stop("���߰���");
		return new playerIdle();
	}
	if (SCENEMANAGER->isCurrentScene("dungeon") && KEYMANAGER->isOnceKeyDown('J'))
	{
		SOUNDMANAGER->stop("���߰���");
		return new playerSwordAttack();
	}
	if (player->getPlayer().state == PLAYER_SWIM) 
	{
		SOUNDMANAGER->stop("���߰���");
		return new playerSwim();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SOUNDMANAGER->stop("���߰���");
		return new playerRoll();
	}
	if (player->getPlayer().currentHp <= 0)
	{
		SOUNDMANAGER->stop("���߰���");
		return new playerDie();
	}


	return nullptr;
}

void playerWalk::enter(player * player)
{	
	SOUNDMANAGER->play("���߰���");
	player->setPlayerState(PLAYER_WALK);
	player->setPlayerCurrentFrameX(0);
	//�÷��̾� ���⺰ �̹���
	switch (player->getPlayer().direction)
	{
	case PLAYER_DOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("���ȱ�Ʒ�"));
		break;
	case PLAYER_UP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("���ȱ���"));
		break;
	case PLAYER_LEFT:
		player->setPlayerImg(IMAGEMANAGER->findDImage("���ȱ����"));
		break;
	case PLAYER_RIGHT:
		player->setPlayerImg(IMAGEMANAGER->findDImage("���ȱ������"));
		break;
	case PLAYER_LEFTUP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("���ȱ���"));
		break;
	case PLAYER_RIGHTUP:
		player->setPlayerImg(IMAGEMANAGER->findDImage("���ȱ���"));
		break;
	case PLAYER_LEFTDOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("���ȱ�Ʒ�"));
		break;
	case PLAYER_RIGHTDOWN:
		player->setPlayerImg(IMAGEMANAGER->findDImage("���ȱ�Ʒ�"));
		break;
	}
	_playerCount = 0;
}

void playerWalk::update(player * player)
{
	
	//�÷��̾� �̵�
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->setPlayerDirection(PLAYER_DOWN);
		player->setPlayerImg(IMAGEMANAGER->findDImage("���ȱ�Ʒ�"));
		player->setPlayerY(player->getPlayer().y + player->getPlayer().speed);
	}
	if (KEYMANAGER->isStayKeyDown('W')) 
	{
		player->setPlayerDirection(PLAYER_UP);
		player->setPlayerImg(IMAGEMANAGER->findDImage("���ȱ���"));
		player->setPlayerY(player->getPlayer().y - player->getPlayer().speed);
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->setPlayerDirection(PLAYER_LEFT);
		player->setPlayerImg(IMAGEMANAGER->findDImage("���ȱ����"));
		player->setPlayerX(player->getPlayer().x - player->getPlayer().speed);
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{ 
		player->setPlayerDirection(PLAYER_RIGHT);
		player->setPlayerImg(IMAGEMANAGER->findDImage("���ȱ������"));
		player->setPlayerX(player->getPlayer().x + player->getPlayer().speed); 
	}
	if (KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isStayKeyDown('W'))
	{
		player->setPlayerDirection(PLAYER_LEFTUP);
		player->setPlayerImg(IMAGEMANAGER->findDImage("���ȱ���"));
	}
	if (KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown('W'))
	{
		player->setPlayerDirection(PLAYER_RIGHTUP);
		player->setPlayerImg(IMAGEMANAGER->findDImage("���ȱ���"));
	}
	if (KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isStayKeyDown('S'))
	{
		player->setPlayerDirection(PLAYER_LEFTDOWN);
		player->setPlayerImg(IMAGEMANAGER->findDImage("���ȱ�Ʒ�"));
	}
	if (KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown('S'))
	{ 
		player->setPlayerDirection(PLAYER_RIGHTDOWN);
		player->setPlayerImg(IMAGEMANAGER->findDImage("���ȱ�Ʒ�"));
	}

	//�÷��̾� �̹��� ������
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
