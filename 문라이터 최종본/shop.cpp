#include "stdafx.h"
#include "shop.h"
#include "player.h"
#include <algorithm>

shop::shop()
{
}

shop::~shop()
{
}

HRESULT shop::init()
{
	SOUNDMANAGER->play("상점배경음악");
	_shopTileMap = new shopTileMap;
	_shopTileMap->init();
	_player = new player;
	_player->init();
	_ui = new UI;
	_ui->init();
	//플레이어 좌표 저장
	_player->setPlayerX(atoi(INIDATA->loadDataString("플레이어좌표", "shop", "playerX")));
	_player->setPlayerY(atoi(INIDATA->loadDataString("플레이어좌표", "shop", "playerY")));
	if (_player->getPlayer().x == NULL) _player->setPlayerX(620);
	if (_player->getPlayer().y != NULL) _isWakeUp = true;
	else if (_player->getPlayer().y == NULL)
	{
		_isWakeUp = false;
		_player->setPlayerY(395);
	}
	IMAGEMANAGER->addDImage("상점_front2", L"상점/상점_front2.png", 54, 48);
	IMAGEMANAGER->addFrameDImage("윌기상", L"윌/윌기상.png", 3538, 59, 58, 1);
	IMAGEMANAGER->addDImage("shop베이스_short", L"UI/대화창 배경.png", 80, 25);
	//상점이미지 앞
	_shopFront.img = IMAGEMANAGER->findDImage("상점_front2");
	//대화창 이미지
	_talkBaseShort.img = IMAGEMANAGER->findDImage("shop베이스_short");
	_talkButton = IMAGEMANAGER->findDImage("J버튼");
	_talkBaseShort.isTalk = false;



	_alpha.rc = RectMake(0, 0, 1300, 1066);
	_alpha.alpha = 1.f;

	_door = RectMakeCenter(580, 630, 50, 50);
	//z오더를 위한 벡터 푸쉬백
	_vPlayer.rc = _player->getPlayer().rc;
	_vPlayer.img = _player->getPlayer().img;
	_vPlayer.objFrameX = _player->getPlayer().currentFrameX;
	_vPlayer.objFrameY = _player->getPlayer().currentFrameY;
	_vPlayer.terrainFrameX = 100;

	_vZorder.push_back(&_vPlayer);


	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_shopTileMap->getTile(i).imgAt == DEFAULT_IMAGE)
		{
			if (_shopTileMap->getTile(i).obj == OBJ_NOTMOVE)
			{
				switch (_shopTileMap->getTile(i).pageObject)
				{
				case 0:
					_vTiles[i].img = IMAGEMANAGER->findDImage("마을타일프레임");
					break;
				case 1:
					_vTiles[i].img = IMAGEMANAGER->findDImage("마을오브젝트1_프레임");
					break;
				case 2:
					_vTiles[i].img = IMAGEMANAGER->findDImage("마을_집_프레임");
					break;
				case 3:
					_vTiles[i].img = IMAGEMANAGER->findDImage("마을_집2_프레임");
					break;
				case 4:
					_vTiles[i].img = IMAGEMANAGER->findDImage("마을_집3_프레임");
					break;
				case 5:
					_vTiles[i].img = IMAGEMANAGER->findDImage("던전선택");
					break;
				case 6:
					_vTiles[i].img = IMAGEMANAGER->findDImage("상점타일1");
					break;
				case 7:
					_vTiles[i].img = IMAGEMANAGER->findDImage("상점타일2");
					break;
				}

				_vTiles[i].rc = _shopTileMap->getTile(i).rc;
				_vTiles[i].objFrameX = _shopTileMap->getTile(i).objFrameX;
				_vTiles[i].objFrameY = _shopTileMap->getTile(i).objFrameY;
				_vTiles[i].obj = _shopTileMap->getTile(i).obj;

				_vZorder.push_back(&_vTiles[i]);

			}


		}
	}

	_playerWakeUp.img = IMAGEMANAGER->findDImage("윌기상");
	_playerWakeUp.x = 611;
	_playerWakeUp.y = 382;
	_playerWakeUp.count = 0;
	_playerWakeUp.currentFrameX = 0;
	_playerWakeUp.currentFrameY = 0;
	_playerWakeUp.rc = RectMakeCenter(_playerWakeUp.x, _playerWakeUp.y, _playerWakeUp.img->getFrameWidth(), _playerWakeUp.img->getFrameHeight());

	return S_OK;
}
bool compare2(tagTile * a, tagTile * b)
{
	return a->rc.bottom < b->rc.bottom;
}
void shop::release()
{
	_vZorder.clear();
	SOUNDMANAGER->stop("상점배경음악");
	SOUNDMANAGER->stop("윌발걸음");

}

void shop::update()
{
	_ui->update(_player->getPlayer().currentHp);
	_alpha.alpha -= 0.01f;

	if (!_ui->getPauseCheck() && !_ui->getInvenCheck())
	{
		_shopTileMap->update();

		CAMERAMANAGER->updateScreen(_player->getPlayer().x, _player->getPlayer().y);



		RECT p = _player->getPlayer().rc;
		RECT temp;
		if (IntersectRect(&temp, &_door, &p))
		{
			_talkBaseShort.isTalk = true;
			_talkBaseShort.x = _door.right;
			_talkBaseShort.y = _door.top - 30;

			if (KEYMANAGER->isOnceKeyDown('J') && !SCENEMANAGER->isCurrentScene("dungeon"))
			{
				_itoa_s(_player->getPlayer().x, _playerXchar, sizeof(&_playerXchar), 10);
				_itoa_s(_player->getPlayer().y - 20, _playerYchar, sizeof(&_playerYchar), 10);
				INIDATA->addData("shop", "playerX", _playerXchar);
				INIDATA->addData("shop", "playerY", _playerYchar);
				INIDATA->iniSave("플레이어좌표");
				SCENEMANAGER->changeScene("village");
			}

		}
		else _talkBaseShort.isTalk = false;

		//z오더 (벡터에 넣어줌 플레이어를 찾아내서 이미지와, 위치정보, 프레임 정보를 갱신해준다.
		for (int i = 0; i < _vZorder.size(); ++i)
		{
			if (_vZorder[i]->terrainFrameX == 100)
			{
				_vZorder[i]->img = _player->getPlayer().img;
				_vZorder[i]->objFrameX = _player->getPlayer().currentFrameX;
				_vZorder[i]->objFrameY = _player->getPlayer().currentFrameY;
				_vZorder[i]->rc = _player->getPlayer().rc;
			}

		}
		//퀵정렬 사용
		sort(_vZorder.begin(), _vZorder.end(), &compare2);

		tileCheck();

		//윌 기상 프레임
		_playerWakeUp.count++;
		if (_playerWakeUp.count % 4 == 0)
		{
			_playerWakeUp.currentFrameX++;
			if (_playerWakeUp.currentFrameX > _playerWakeUp.img->getMaxFrameX())
			{
				_isWakeUp = true;
				_playerWakeUp.currentFrameX = _playerWakeUp.img->getMaxFrameX();
			}
		}
	}
	if (_isWakeUp)	_player->update();
}

void shop::render()
{
	_shopTileMap->render();

	//_player->render();


	_shopTileMap->objectRender();


	for (int i = 0; i < _vZorder.size(); ++i)
	{
		_vZorder[i]->img->frameRender(_vZorder[i]->rc.left, _vZorder[i]->rc.top, _vZorder[i]->objFrameX, _vZorder[i]->objFrameY);

	}
	if (!_isWakeUp)	_playerWakeUp.img->frameRender(_playerWakeUp.rc.left, _playerWakeUp.rc.top, _playerWakeUp.currentFrameX, _playerWakeUp.currentFrameY);
	_shopFront.img->render(556, 438);


	if (_talkBaseShort.isTalk)
	{
		_talkBaseShort.img->render(_talkBaseShort.x, _talkBaseShort.y);
		_talkButton->render(_talkBaseShort.x + 10, _talkBaseShort.y + 2);
		D2DMANAGER->RenderText(_talkBaseShort.x + 38, _talkBaseShort.y + 6, L"나가기", 12, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"제주고딕");
	}

	_ui->render();
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		D2DMANAGER->DrawRectangle(_door, D2DDEFAULTBRUSH::White);
	}
	D2DMANAGER->FillRectangle(_alpha.rc, D2D1COLOR::Black, _alpha.alpha);
}

void shop::tileCheck()
{
	RECT rc;
	RECT upLeft = _player->getPlayer().upLeft;
	RECT upRight = _player->getPlayer().upRight;
	RECT downLeft = _player->getPlayer().downLeft;
	RECT downRight = _player->getPlayer().downRight;
	RECT leftUp = _player->getPlayer().leftUp;
	RECT leftDown = _player->getPlayer().leftDown;
	RECT rightUp = _player->getPlayer().rightUp;
	RECT rightDown = _player->getPlayer().rightDown;

	for (int i = 0; i < _vZorder.size(); ++i)
	{
		if (_vZorder[i]->obj != OBJ_NOTMOVE) continue;

		//십자 이동
		//위
		if (IntersectRect(&rc, &_vZorder[i]->rc, &upLeft) && _player->getPlayer().direction == PLAYER_UP ||
			IntersectRect(&rc, &_vZorder[i]->rc, &upRight) && _player->getPlayer().direction == PLAYER_UP)
		{
			_player->setPlayerY((_vZorder[i]->rc.top + _vZorder[i]->rc.bottom) / 2 + _player->getPlayer().img->getFrameHeight() - 26);
		}
		//아래
		if (IntersectRect(&rc, &_vZorder[i]->rc, &downLeft) && _player->getPlayer().direction == PLAYER_DOWN ||
			IntersectRect(&rc, &_vZorder[i]->rc, &downRight) && _player->getPlayer().direction == PLAYER_DOWN)
		{
			_player->setPlayerY((_vZorder[i]->rc.top + _vZorder[i]->rc.bottom) / 2 - _player->getPlayer().img->getFrameHeight() + 7);
		}
		//왼쪽
		if (IntersectRect(&rc, &_vZorder[i]->rc, &leftUp) && _player->getPlayer().direction == PLAYER_LEFT ||
			IntersectRect(&rc, &_vZorder[i]->rc, &leftDown) && _player->getPlayer().direction == PLAYER_LEFT)
		{
			_player->setPlayerX((_vZorder[i]->rc.left + _vZorder[i]->rc.right) / 2 + _player->getPlayer().img->getFrameWidth() - 3);
		}
		//오른쪽
		if (IntersectRect(&rc, &_vZorder[i]->rc, &rightUp) && _player->getPlayer().direction == PLAYER_RIGHT ||
			IntersectRect(&rc, &_vZorder[i]->rc, &rightDown) && _player->getPlayer().direction == PLAYER_RIGHT)
		{
			_player->setPlayerX((_vZorder[i]->rc.left + _vZorder[i]->rc.right) / 2 - _player->getPlayer().img->getFrameWidth() + 3);
		}

		//대각선 이동
		//세로 기준
		//왼쪽 위 대각선
		if (IntersectRect(&rc, &_vZorder[i]->rc, &leftDown) && _player->getPlayer().direction == PLAYER_LEFTUP)
		{
			_player->setPlayerX((_vZorder[i]->rc.left + _vZorder[i]->rc.right) / 2 + _player->getPlayer().img->getFrameWidth() + 2);
		}
		//오른쪽 위 대각선
		if (IntersectRect(&rc, &_vZorder[i]->rc, &rightDown) && _player->getPlayer().direction == PLAYER_RIGHTUP)
		{
			_player->setPlayerX((_vZorder[i]->rc.left + _vZorder[i]->rc.right) / 2 - _player->getPlayer().img->getFrameWidth() - 2);
		}
		//왼쪽 아래 대각선
		if (IntersectRect(&rc, &_vZorder[i]->rc, &leftDown) && _player->getPlayer().direction == PLAYER_LEFTDOWN)
		{
			_player->setPlayerX((_vZorder[i]->rc.left + _vZorder[i]->rc.right) / 2 + _player->getPlayer().img->getFrameWidth() + 4);
		}
		//오른쪽 아래 대각선
		if (IntersectRect(&rc, &_vZorder[i]->rc, &rightDown) && _player->getPlayer().direction == PLAYER_RIGHTDOWN)
		{
			_player->setPlayerX((_vZorder[i]->rc.left + _vZorder[i]->rc.right) / 2 - _player->getPlayer().img->getFrameWidth() - 3);
		}

		//가로기준
		//왼쪽 위 대각선
		if (IntersectRect(&rc, &_vZorder[i]->rc, &upLeft) && _player->getPlayer().direction == PLAYER_LEFTUP)
		{
			_player->setPlayerY((_vZorder[i]->rc.top + _vZorder[i]->rc.bottom) / 2 + _player->getPlayer().img->getFrameHeight() / 2 - 4);
		}
		//오른쪽 위 대각선
		if (IntersectRect(&rc, &_vZorder[i]->rc, &upLeft) && _player->getPlayer().direction == PLAYER_RIGHTUP)
		{
			_player->setPlayerY((_vZorder[i]->rc.top + _vZorder[i]->rc.bottom) / 2 + _player->getPlayer().img->getFrameHeight() / 2 - 4);
		}
		//왼쪽 아래 대각선
		if (IntersectRect(&rc, &_vZorder[i]->rc, &downLeft) && _player->getPlayer().direction == PLAYER_LEFTDOWN)
		{
			_player->setPlayerY((_vZorder[i]->rc.top + _vZorder[i]->rc.bottom) / 2 - _player->getPlayer().img->getFrameHeight() + 7);
		}
		//오른쪽 아래 대각선
		if (IntersectRect(&rc, &_vZorder[i]->rc, &downLeft) && _player->getPlayer().direction == PLAYER_RIGHTDOWN)
		{
			_player->setPlayerY((_vZorder[i]->rc.top + _vZorder[i]->rc.bottom) / 2 - _player->getPlayer().img->getFrameHeight() + 7);
		}
	}
}
