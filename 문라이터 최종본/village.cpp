#include "stdafx.h"
#include "village.h"
#include <algorithm>

village::village()
{
}

village::~village()
{
}

HRESULT village::init()
{
	
	SOUNDMANAGER->play("마을배경음악");
	_villageTilemap = new villageTileMap;
	_villageTilemap->init();
	_player = new player;
	_player->init();
	_ui = new UI;
	_ui->init();
	//플레이어 좌표 저장
	_player->setPlayerX(atoi(INIDATA->loadDataString("플레이어좌표", "village", "playerX")));
	_player->setPlayerY(atoi(INIDATA->loadDataString("플레이어좌표", "village", "playerY")));
	if (_player->getPlayer().x == NULL) _player->setPlayerX(750);
	if (_player->getPlayer().y == NULL) _player->setPlayerY(280);
	_alpha.rc = RectMake(0, 0, 1300, 1066);
	_alpha.alpha = 1.f;

	IMAGEMANAGER->addDImage("village베이스_short", L"UI/대화창 배경.png", 100, 25);
	IMAGEMANAGER->addFrameDImage("blackSmith", L"NPC/blackSmith.png", 324, 41, 12, 1);
	IMAGEMANAGER->addFrameDImage("witch", L"NPC/witch.png", 600, 36, 24, 1);
	IMAGEMANAGER->addFrameDImage("extra1_left", L"NPC/extra1_left.png", 144, 37, 8, 1);
	IMAGEMANAGER->addFrameDImage("extra1_right", L"NPC/extra1_right.png", 144, 37, 8, 1);
	IMAGEMANAGER->addFrameDImage("extra2_down", L"NPC/extra2_down.png", 280, 36, 8, 1);
	IMAGEMANAGER->addFrameDImage("extra2_up", L"NPC/extra2_up.png", 280, 36, 8, 1);
	//대화창 이미지
	_talkBaseShort.img = IMAGEMANAGER->findDImage("village베이스_short");
	_talkButton = IMAGEMANAGER->findDImage("J버튼");
	_door = RectMakeCenter(750, 250, 25, 50);


	_roadDeongeon[0] = RectMakeCenter(360, 0, 100, 50);
	_roadDeongeon[1] = RectMakeCenter(1300, 310, 50, 100);

	//z오더를 위한 벡터 푸쉬백
	_vPlayer.rc = _player->getPlayer().rc;
	_vPlayer.img = _player->getPlayer().img;
	_vPlayer.objFrameX = _player->getPlayer().currentFrameX;
	_vPlayer.objFrameY = _player->getPlayer().currentFrameY;
	_vPlayer.terrainFrameX = 100;

	_vZorder.push_back(&_vPlayer);

	//타일 푸쉬백
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_villageTilemap->getTile(i).imgAt == DEFAULT_IMAGE || _villageTilemap->getTile(i).imgAt == FRAME_IMAGE)
		{
			if (_villageTilemap->getTile(i).obj == OBJ_NOTMOVE)
			{
				switch (_villageTilemap->getTile(i).pageObject)
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

				_vTiles[i].rc = _villageTilemap->getTile(i).rc;
				_vTiles[i].objFrameX = _villageTilemap->getTile(i).objFrameX;
				_vTiles[i].objFrameY = _villageTilemap->getTile(i).objFrameY;
				_vTiles[i].obj = _villageTilemap->getTile(i).obj;

				_vZorder.push_back(&_vTiles[i]);

			}
		}

	}
	//프레임 오브젝트 푸쉬백
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_villageTilemap->getTile(i).obj == OBJ_BLOCK1 && _villageTilemap->getTile(i).imgAt == FRAME_IMAGE)
		{
			if (_villageTilemap->getTile(i).pageObject == 1)
			{
				if (_villageTilemap->getTile(i).objFrameX == 0 && _villageTilemap->getTile(i).objFrameY == 7)
				{
					_vtree1[i].rc = _villageTilemap->getTile(i).rc;
					_vtree1[i].img = IMAGEMANAGER->findDImage("나무1");
					_vtree1[i].rc.bottom = _villageTilemap->getTile(i).rc.bottom + _vtree1[i].img->getHeight() - TILESIZE;
					_vtree1[i].objFrameX = 0;
					_vtree1[i].objFrameY = 0;
					_vtree1[i].terrainFrameX = 200;

					_vZorder.push_back(&_vtree1[i]);
				}
				if (_villageTilemap->getTile(i).objFrameX == 6 && _villageTilemap->getTile(i).objFrameY == 7)
				{
					_vtree2[i].rc = _villageTilemap->getTile(i).rc;
					_vtree2[i].img = IMAGEMANAGER->findDImage("나무2");
					_vtree2[i].rc.bottom = _villageTilemap->getTile(i).rc.bottom + _vtree2[i].img->getHeight() - TILESIZE;
					_vtree2[i].objFrameX = 0;
					_vtree2[i].objFrameY = 0;
					_vtree2[i].terrainFrameX = 200;

					_vZorder.push_back(&_vtree2[i]);
				}
				if (_villageTilemap->getTile(i).objFrameX == 12 && _villageTilemap->getTile(i).objFrameY == 4)
				{
					_vtree3[i].rc = _villageTilemap->getTile(i).rc;
					_vtree3[i].img = IMAGEMANAGER->findDImage("나무4");
					_vtree3[i].rc.bottom = _villageTilemap->getTile(i).rc.bottom + _vtree3[i].img->getHeight() - TILESIZE * 2;
					_vtree3[i].objFrameX = 0;
					_vtree3[i].objFrameY = 0;
					_vtree3[i].terrainFrameX = 200;

					_vZorder.push_back(&_vtree3[i]);
				}
				if (_villageTilemap->getTile(i).objFrameX == 2 && _villageTilemap->getTile(i).objFrameY == 5)
				{
					_fountain[i].rc = _villageTilemap->getTile(i).rc;
					_fountain[i].img = IMAGEMANAGER->findDImage("분수대");
					_fountain[i].rc.bottom = _villageTilemap->getTile(i).rc.bottom + _fountain[i].img->getHeight() - TILESIZE;
					_fountain[i].objFrameX = 0;
					_fountain[i].objFrameY = 0;
					_fountain[i].terrainFrameX = 200;

					_vZorder.push_back(&_fountain[i]);
				}
				if (_villageTilemap->getTile(i).objFrameX == 7 && _villageTilemap->getTile(i).objFrameY == 4)
				{
					_well[i].rc = _villageTilemap->getTile(i).rc;
					_well[i].img = IMAGEMANAGER->findDImage("우물");
					_well[i].rc.bottom = _villageTilemap->getTile(i).rc.bottom + _well[i].img->getHeight() - TILESIZE;
					_well[i].objFrameX = 0;
					_well[i].objFrameY = 0;
					_well[i].terrainFrameX = 200;

					_vZorder.push_back(&_well[i]);
				}

			}
			if (_villageTilemap->getTile(i).pageObject == 2)
			{
				if (_villageTilemap->getTile(i).objFrameX == 4 && _villageTilemap->getTile(i).objFrameY == 4)
				{
					_vHouse.rc = _villageTilemap->getTile(i).rc;
					_vHouse.img = IMAGEMANAGER->findDImage("집프레임");
					_vHouse.rc.bottom = _villageTilemap->getTile(i).rc.bottom + _vHouse.img->getHeight() - TILESIZE * 2;
					_vHouse.objFrameX = 0;
					_vHouse.objFrameY = 0;
					_vHouse.terrainFrameX = 200;

					_vZorder.push_back(&_vHouse);
				}

			}

		}
	}

	_blackSmith.img = IMAGEMANAGER->findDImage("blackSmith");
	_blackSmith.x = 1025;
	_blackSmith.y = 840;
	_blackSmith.rc = RectMakeCenter(_blackSmith.x, _blackSmith.y, _blackSmith.img->getFrameWidth(), _blackSmith.img->getFrameHeight());
	_blackSmith.currentFrameX = _blackSmith.currentFrameY = 0;
	_blackSmith.count = 0;
	_witch.img = IMAGEMANAGER->findDImage("witch");
	_witch.x = 200;
	_witch.y = 750;
	_witch.rc = RectMakeCenter(_witch.x, _witch.y, _witch.img->getFrameWidth(), _witch.img->getFrameHeight());
	_witch.currentFrameX = _witch.currentFrameY = 0;
	_witch.count = 0;
	_extra1.img = IMAGEMANAGER->findDImage("extra1_left");
	_extra1.x = 1100;
	_extra1.y = 300;
	_extra1.isTrue = false;
	_extra1.rc = RectMakeCenter(_extra1.x, _extra1.y, _extra1.img->getFrameWidth(), _extra1.img->getFrameHeight());
	_extra1.currentFrameX = _extra1.currentFrameY = 0;
	_extra1.count = 0;
	_extra2.img = IMAGEMANAGER->findDImage("extra2_down");
	_extra2.x = 365;
	_extra2.y = 300;
	_extra2.rc = RectMakeCenter(_extra2.x, _extra2.y, _extra2.img->getFrameWidth(), _extra2.img->getFrameHeight());
	_extra2.currentFrameX = _extra2.currentFrameY = 0;
	_extra2.count = 0;
	_extra2.isTrue = false;

	_vExtra1.rc = _extra1.rc;
	_vExtra1.img = _extra1.img;
	_vExtra1.objFrameX = _extra1.currentFrameX;
	_vExtra1.objFrameY = _extra1.currentFrameY;
	_vExtra1.terrainFrameX = 300;
	_vZorder.push_back(&_vExtra1);

	_vExtra2.rc = _extra2.rc;
	_vExtra2.img = _extra2.img;
	_vExtra2.objFrameX = _extra2.currentFrameX;
	_vExtra2.objFrameY = _extra2.currentFrameY;
	_vExtra2.terrainFrameX = 400;
	_vZorder.push_back(&_vExtra2);
	return S_OK;
}

void village::release()
{
	_vZorder.clear();
	SOUNDMANAGER->stop("마을배경음악");
	SOUNDMANAGER->stop("윌발걸음");
}
bool compare3(tagTile * a, tagTile * b)
{
	return a->rc.bottom < b->rc.bottom;
}
void village::update()
{


	_ui->update(_player->getPlayer().currentHp);
	_alpha.alpha -= 0.01f;
	if (_alpha.alpha <= 0) _alpha.alpha = 0;

	if (!_ui->getPauseCheck() && !_ui->getInvenCheck())
	{
		_villageTilemap->update();

		CAMERAMANAGER->updateScreen(_player->getPlayer().x, _player->getPlayer().y);

		//덙전으로 가는길, 상점 연결렉트
		RECT p = _player->getPlayer().rc;
		RECT temp;
		if (IntersectRect(&temp, &_door, &p))
		{
			_talkBaseShort.isTalk = true;
			_talkBaseShort.x = _door.right;
			_talkBaseShort.y = _door.top - 10;

			if (KEYMANAGER->isOnceKeyDown('J') && !SCENEMANAGER->isCurrentScene("dungeon"))
			{
				_itoa_s(_player->getPlayer().x, _playerXchar, sizeof(&_playerXchar), 10);
				_itoa_s(_player->getPlayer().y + 20, _playerYchar, sizeof(&_playerYchar), 10);
				INIDATA->addData("village", "playerX", _playerXchar);
				INIDATA->addData("village", "playerY", _playerYchar);
				INIDATA->iniSave("플레이어좌표");
				SCENEMANAGER->changeScene("shop");
			}
		}
		else _talkBaseShort.isTalk = false;
		if (IntersectRect(&temp, &_roadDeongeon[0], &p))
		{
			_itoa_s(_player->getPlayer().x, _playerXchar, sizeof(&_playerXchar), 10);
			_itoa_s(_player->getPlayer().y + 20, _playerYchar, sizeof(&_playerYchar), 10);
			INIDATA->addData("village", "playerX", _playerXchar);
			INIDATA->addData("village", "playerY", _playerYchar);
			INIDATA->iniSave("플레이어좌표");
			SCENEMANAGER->changeScene("deongeonChoice");
		}
		if (IntersectRect(&temp, &_roadDeongeon[1], &p))
		{
			_itoa_s(_player->getPlayer().x, _playerXchar, sizeof(&_playerXchar), 10);
			_itoa_s(_player->getPlayer().y + 20, _playerYchar, sizeof(&_playerYchar), 10);
			INIDATA->addData("village", "playerX", _playerXchar);
			INIDATA->addData("village", "playerY", _playerYchar);
			INIDATA->iniSave("플레이어좌표");
			SCENEMANAGER->changeScene("deongeonChoice");
		}
		_player->update();


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

			if (_vZorder[i]->terrainFrameX == 200)
			{
				_vZorder[i]->terrainFrameY++;
				if (_vZorder[i]->terrainFrameY % 10 == 0)
				{
					_vZorder[i]->objFrameX++;
					if (_vZorder[i]->objFrameX > _vZorder[i]->img->getMaxFrameX())
					{
						_vZorder[i]->objFrameX = 0;
						_vZorder[i]->terrainFrameY = 0;
					}
				}
			}
			if (_vZorder[i]->terrainFrameX == 300)
			{
				_vZorder[i]->img =_extra1.img;
				_vZorder[i]->objFrameX = _extra1.currentFrameX;
				_vZorder[i]->objFrameY = _extra1.currentFrameY;
				_vZorder[i]->rc = _extra1.rc;

				_vZorder[i]->terrainFrameY++;
				if (_vZorder[i]->terrainFrameY % 10 == 0)
				{
					_vZorder[i]->objFrameX++;
					if (_vZorder[i]->objFrameX > _vZorder[i]->img->getMaxFrameX())
					{
						_vZorder[i]->objFrameX = 0;
						_vZorder[i]->terrainFrameY = 0;
					}
				}
			}
			if (_vZorder[i]->terrainFrameX == 400)
			{
				_vZorder[i]->img =_extra2.img;
				_vZorder[i]->objFrameX = _extra2.currentFrameX;
				_vZorder[i]->objFrameY = _extra2.currentFrameY;
				_vZorder[i]->rc = _extra2.rc;

				_vZorder[i]->terrainFrameY++;
				if (_vZorder[i]->terrainFrameY % 10 == 0)
				{
					_vZorder[i]->objFrameX++;
					if (_vZorder[i]->objFrameX > _vZorder[i]->img->getMaxFrameX())
					{
						_vZorder[i]->objFrameX = 0;
						_vZorder[i]->terrainFrameY = 0;
					}
				}
			}

		}
		//퀵정렬 사용
		sort(_vZorder.begin(), _vZorder.end(), &compare3);

		tileCheck();
	}

	
	extraFrame();
}

void village::render()
{

	_villageTilemap->render();
	//_player->render();

	

	for (int i = 0; i < _vZorder.size(); ++i)
	{
		_vZorder[i]->img->frameRender(_vZorder[i]->rc.left, _vZorder[i]->rc.top, _vZorder[i]->objFrameX, _vZorder[i]->objFrameY);

	}
	_villageTilemap->objectRender();

	_blackSmith.img->frameRender(_blackSmith.rc.left, _blackSmith.rc.top, _blackSmith.currentFrameX, _blackSmith.currentFrameY);
	_witch.img->frameRender(_witch.rc.left, _witch.rc.top, _witch.currentFrameX, _witch.currentFrameY);

	if (_talkBaseShort.isTalk)
	{
		_talkBaseShort.img->render(_talkBaseShort.x, _talkBaseShort.y);
		_talkButton->render(_talkBaseShort.x + 10, _talkBaseShort.y + 2);
		D2DMANAGER->RenderText(_talkBaseShort.x + 38, _talkBaseShort.y + 6, L"들어가기", 12, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"제주고딕");
	}
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		D2DMANAGER->DrawRectangle(_door, D2DDEFAULTBRUSH::White);
		D2DMANAGER->DrawRectangle(_roadDeongeon[0], D2DDEFAULTBRUSH::White);
		D2DMANAGER->DrawRectangle(_roadDeongeon[1], D2DDEFAULTBRUSH::White);

		D2DMANAGER->DrawRectangle(_player->getPlayer().rc, D2DDEFAULTBRUSH::Black);

		D2DMANAGER->DrawRectangle(_player->getPlayer().upLeft, D2DDEFAULTBRUSH::Red);
		D2DMANAGER->DrawRectangle(_player->getPlayer().upRight, D2DDEFAULTBRUSH::Red);
		D2DMANAGER->DrawRectangle(_player->getPlayer().downLeft, D2DDEFAULTBRUSH::Red);
		D2DMANAGER->DrawRectangle(_player->getPlayer().downRight, D2DDEFAULTBRUSH::Red);
		D2DMANAGER->DrawRectangle(_player->getPlayer().leftUp, D2DDEFAULTBRUSH::Red);
		D2DMANAGER->DrawRectangle(_player->getPlayer().leftDown, D2DDEFAULTBRUSH::Red);
		D2DMANAGER->DrawRectangle(_player->getPlayer().rightUp, D2DDEFAULTBRUSH::Red);
		D2DMANAGER->DrawRectangle(_player->getPlayer().rightDown, D2DDEFAULTBRUSH::Red);
	}
	_ui->render();
	D2DMANAGER->FillRectangle(_alpha.rc, D2D1COLOR::Black, _alpha.alpha);

}

void village::tileCheck()
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

void village::extraFrame()
{
	_blackSmith.count++;
	_witch.count++;
	_extra1.count++;
	_extra2.count++;

	if (_blackSmith.count % 10 == 0)
	{
		_blackSmith.currentFrameX++;
		_blackSmith.count = 0;
		if (_blackSmith.currentFrameX > _blackSmith.img->getMaxFrameX())
		{
			_blackSmith.currentFrameX = 0;
		}
	}
	if (_witch.count % 10 == 0)
	{
		_witch.currentFrameX++;
		_witch.count = 0;
		if (_witch.currentFrameX > _witch.img->getMaxFrameX())
		{
			_witch.currentFrameX = 0;
		}
	}	
	if (_extra1.count % 10 == 0) 
	{
		_extra1.currentFrameX++;
		_extra1.count = 0;
		if (_extra1.currentFrameX > _extra1.img->getMaxFrameX()) 
		{
			_extra1.currentFrameX = 0;
		}
	}
	if (_extra2.count % 10 == 0)
	{
		_extra2.currentFrameX++;
		_extra2.count = 0;
		if (_extra2.currentFrameX > _extra2.img->getMaxFrameX())
		{
			_extra2.currentFrameX = 0;
		}
	}

	if (!_extra1.isTrue) 
	{
		_extra1.img = IMAGEMANAGER->findDImage("extra1_left");
		_extra1.x--;
		if (_extra1.x <= 350) _extra1.isTrue = true;
	}
	else
	{
		_extra1.img = IMAGEMANAGER->findDImage("extra1_right");
		_extra1.x++;
		if (_extra1.x >= 1100) _extra1.isTrue = false;
	}
	if (!_extra2.isTrue) 
	{
		_extra2.img = IMAGEMANAGER->findDImage("extra2_down");
		_extra2.y++;
		if (_extra2.y >= 650) _extra2.isTrue = true;
	}
	else
	{
		_extra2.img = IMAGEMANAGER->findDImage("extra2_up");
		_extra2.y--;
		if (_extra2.y <= 300) _extra2.isTrue = false;
	}
	_extra1.rc = RectMakeCenter(_extra1.x, _extra1.y, _extra1.img->getFrameWidth(), _extra1.img->getFrameHeight());
	_extra2.rc = RectMakeCenter(_extra2.x, _extra2.y, _extra2.img->getFrameWidth(), _extra2.img->getFrameHeight());
}



