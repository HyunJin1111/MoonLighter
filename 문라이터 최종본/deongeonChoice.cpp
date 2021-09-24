#include "stdafx.h"
#include "deongeonChoice.h"
#include <algorithm>

deongeonChoice::deongeonChoice()
{
}

deongeonChoice::~deongeonChoice()
{
}

HRESULT deongeonChoice::init()
{
	SOUNDMANAGER->play("던전선택배경음악");
	_deongeonTileMap = new deongeonChoiceTileMap;
	_deongeonTileMap->init();
	_player = new player;
	_player->init();
	_ui = new UI;
	_ui->init();
	//플레이어 좌표 저장
	_player->setPlayerX(atoi(INIDATA->loadDataString("플레이어좌표", "deongeonChoice", "playerX")));
	_player->setPlayerY(atoi(INIDATA->loadDataString("플레이어좌표", "deongeonChoice", "playerY")));
	if (_player->getPlayer().x == NULL) _player->setPlayerX(600);
	if (_player->getPlayer().y == NULL) _player->setPlayerY(1020);
	_alpha.rc = RectMake(0, 0, 1300, 1066);
	_alpha.alpha = 1.f;
	//던전 입장전 대화창 배경
	IMAGEMANAGER->addDImage("deongeonChoice베이스_short", L"UI/대화창 배경.png", 100, 25);
	//대화창 이미지
	_talkBaseShort.img = IMAGEMANAGER->findDImage("deongeonChoice베이스_short");
	_talkButton = IMAGEMANAGER->findDImage("J버튼");
	_talkBaseShort.isTalk = false;
	IMAGEMANAGER->addFrameDImage("포탈클로즈", L"던전/포탈클로즈.png", 280, 22, 7, 1);
	IMAGEMANAGER->addFrameDImage("포탈오픈", L"던전/포탈오픈.png", 280, 22, 7, 1);
	IMAGEMANAGER->addFrameDImage("포탈입장", L"던전/포탈입장.png", 880, 46, 22, 1);
	IMAGEMANAGER->addFrameDImage("포탈활성화", L"던전/포탈활성화.png", 240, 21, 6, 1);
	
	//던전입구 오브젝트
	_portalDoorOpen.img = IMAGEMANAGER->findDImage("포탈오픈");
	_portalDoorOpen.x = 458;
	_portalDoorOpen.y = 513;
	_portalDoorOpen.count = 0;
	_portalDoorOpen.currentFrameX = 0;
	_portalDoorOpen.currentFrameY = 0;
	_portalDoorOpen.rc = RectMakeCenter(_portalDoorOpen.x, _portalDoorOpen.y, _portalDoorOpen.img->getFrameWidth(), _portalDoorOpen.img->getFrameHeight());
	_portalDoorAtive.isBool = false;

	_portalDoorAtive.img = IMAGEMANAGER->findDImage("포탈활성화");
	_portalDoorAtive.x = 458;
	_portalDoorAtive.y = 512;
	_portalDoorAtive.count = 0;
	_portalDoorAtive.currentFrameX = 0;
	_portalDoorAtive.currentFrameY = 0;
	_portalDoorAtive.rc = RectMakeCenter(_portalDoorAtive.x, _portalDoorAtive.y, _portalDoorAtive.img->getFrameWidth(), _portalDoorAtive.img->getFrameHeight());
	
	_portalDoorGo.img = IMAGEMANAGER->findDImage("포탈입장");
	_portalDoorGo.x = 438;
	_portalDoorGo.y = 502;
	_portalDoorGo.count = 0;
	_portalDoorGo.currentFrameX = 0;
	_portalDoorGo.currentFrameY = 0;
	_portalDoorGo.rc = RectMakeCenter(_portalDoorGo.x, _portalDoorGo.y, _portalDoorGo.img->getFrameWidth(), _portalDoorGo.img->getFrameHeight());
	_portalDoorGo.isBool = false;




	//이동을 위한 렉트
	_loadVillage = RectMakeCenter(600, 1066, 100, 50);
	_dungeonIn = RectMakeCenter(458, 520, 50, 50);

	//z오더를 위한 벡터 푸쉬백
	_vPlayer.rc = _player->getPlayer().rc;
	_vPlayer.img = _player->getPlayer().img;
	_vPlayer.objFrameX = _player->getPlayer().currentFrameX;
	_vPlayer.objFrameY = _player->getPlayer().currentFrameY;
	_vPlayer.terrainFrameX = 100;

	_vZorder.push_back(&_vPlayer);


	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_deongeonTileMap->getTile(i).imgAt == DEFAULT_IMAGE)
		{
			if (_deongeonTileMap->getTile(i).obj == OBJ_NOTMOVE)
			{
				switch (_deongeonTileMap->getTile(i).pageObject)
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
				}

				_vTiles[i].rc = _deongeonTileMap->getTile(i).rc;
				_vTiles[i].objFrameX = _deongeonTileMap->getTile(i).objFrameX;
				_vTiles[i].objFrameY = _deongeonTileMap->getTile(i).objFrameY;
				_vTiles[i].obj = _deongeonTileMap->getTile(i).obj;

				_vZorder.push_back(&_vTiles[i]);

			}
		}
	}

	return S_OK;
}
bool compare(tagTile * a, tagTile * b)
{
	return a->rc.bottom < b->rc.bottom;
}

void deongeonChoice::release()
{
	_vZorder.clear();
	SOUNDMANAGER->stop("던전선택배경음악");
	SOUNDMANAGER->stop("윌발걸음");
}
void deongeonChoice::update()
{
	_ui->update(_player->getPlayer().currentHp);
	_alpha.alpha -= 0.01f;
	if (!_ui->getPauseCheck() && !_ui->getInvenCheck())
	{
		_deongeonTileMap->update();
		if(!_portalDoorGo.isBool)_player->update();
		_portalDoorOpen.count++;
	
		//던전으로 가는길의 렉트 충돌
		RECT p = _player->getPlayer().rc;
		RECT temp;
		if (IntersectRect(&temp, &_loadVillage, &p))
		{

			_itoa_s(_player->getPlayer().x, _playerXchar, sizeof(&_playerXchar), 10);
			_itoa_s(_player->getPlayer().y - 20, _playerYchar, sizeof(&_playerYchar), 10);
			INIDATA->addData("deongeonChoice", "playerX", _playerXchar);
			INIDATA->addData("deongeonChoice", "playerY", _playerYchar);
			INIDATA->iniSave("플레이어좌표");
			SCENEMANAGER->changeScene("village");

		}
		if (IntersectRect(&temp, &_dungeonIn, &p))
		{
			//진입 대화창 활성화
			_talkBaseShort.isTalk = true;
			_talkBaseShort.x = _dungeonIn.right;
			_talkBaseShort.y = _dungeonIn.top - 30;
			
			
			if (_portalDoorOpen.count % 7 == 0)
			{
				_portalDoorOpen.currentFrameX++;
				if (_portalDoorOpen.currentFrameX > _portalDoorOpen.img->getMaxFrameX())
				{
					_portalDoorOpen.currentFrameX = _portalDoorOpen.img->getMaxFrameX();
					_portalDoorAtive.isBool = true;
					_portalDoorOpen.count = 0;
				}
			}
			_portalDoorAtive.count++;
			if (_portalDoorAtive.count % 7 == 0) 
			{
				_portalDoorAtive.currentFrameX++;
				if (_portalDoorAtive.currentFrameX > _portalDoorAtive.img->getMaxFrameX())
				{
					_portalDoorAtive.currentFrameX = 0;
					_portalDoorAtive.count = 0;
				
				}
			}
			//버튼 상호작용
			if (KEYMANAGER->isOnceKeyDown('J') && !SCENEMANAGER->isCurrentScene("dungeon"))
			{
				_portalDoorGo.isBool = true;
				
				
			}
			if (_portalDoorGo.isBool) 
			{
				if (_portalDoorGo.currentFrameX == 0 && _portalDoorGo.count == 0) SOUNDMANAGER->play("포탈입장");
				_portalDoorGo.count++;
				if (_portalDoorGo.count % 7 == 0)
				{
					
					_portalDoorGo.currentFrameX++;
					_portalDoorGo.count = 0;
					
					if (_portalDoorGo.currentFrameX > _portalDoorGo.img->getMaxFrameX())
					{
						_portalDoorGo.currentFrameX = _portalDoorGo.img->getMaxFrameX();
						SCENEMANAGER->changeScene("dungeon");
					}
				}
			}
		}
		else
		{
			_portalDoorAtive.isBool = false;
			if (_portalDoorOpen.count % 7 == 0)
			{
				_portalDoorOpen.currentFrameX--;
				if (_portalDoorOpen.currentFrameX <= 0)
				{
					_portalDoorOpen.count = 0;
					_portalDoorOpen.currentFrameX = 0;
				}
			}
			_talkBaseShort.isTalk = false;
		}


		CAMERAMANAGER->updateScreen(_player->getPlayer().x, _player->getPlayer().y);

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
		sort(_vZorder.begin(), _vZorder.end(), &compare);

		tileCheck();
	}
}


void deongeonChoice::render()
{


	_deongeonTileMap->render();
	//_player->render();

	D2DMANAGER->DrawRectangle(_loadVillage, D2DDEFAULTBRUSH::White);
	if(_portalDoorAtive.isBool && !_portalDoorGo.isBool)_portalDoorAtive.img->frameRender(_portalDoorAtive.rc.left, _portalDoorAtive.rc.top, _portalDoorAtive.currentFrameX, _portalDoorAtive.currentFrameY);
	else if(!_portalDoorAtive.isBool && !_portalDoorGo.isBool) _portalDoorOpen.img->frameRender(_portalDoorOpen.rc.left, _portalDoorOpen.rc.top, _portalDoorOpen.currentFrameX, _portalDoorOpen.currentFrameY);
	if (_portalDoorGo.isBool) _portalDoorGo.img->frameRender(_portalDoorGo.x, _portalDoorGo.y, _portalDoorGo.currentFrameX, _portalDoorGo.currentFrameY);
	for (int i = 0; i < _vZorder.size(); ++i)
	{
		if (_vZorder[i]->terrainFrameX == 100 && _portalDoorGo.isBool) continue;
		_vZorder[i]->img->frameRender(_vZorder[i]->rc.left, _vZorder[i]->rc.top, _vZorder[i]->objFrameX, _vZorder[i]->objFrameY);


	}

	_deongeonTileMap->objectRender();

	

	if (_talkBaseShort.isTalk)
	{
		_talkBaseShort.img->render(_talkBaseShort.x, _talkBaseShort.y);
		_talkButton->render(_talkBaseShort.x + 10, _talkBaseShort.y + 2);
		D2DMANAGER->RenderText(_talkBaseShort.x + 38, _talkBaseShort.y + 6, L"입장하기", 12, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"제주고딕");
	}
	_ui->render();
	D2DMANAGER->FillRectangle(_alpha.rc, D2D1COLOR::Black, _alpha.alpha);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{


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

	D2DMANAGER->DrawRectangle(_dungeonIn, D2DDEFAULTBRUSH::White);



}


void deongeonChoice::tileCheck()
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

