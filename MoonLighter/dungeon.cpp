#include "stdafx.h"
#include "dungeon.h"
#include <algorithm>

dungeon::dungeon()
{
}

dungeon::~dungeon()
{
}

HRESULT dungeon::init()
{
	SOUNDMANAGER->play("DungeonBackgroundMusic");
	IMAGEMANAGER->addFrameDImage("GolemDunGeon", L"Tile/GolemDunGeon.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("Lake", L"DunGeon/Lake.png", 1488, 191, 8, 1);
	IMAGEMANAGER->addFrameDImage("Scroll_In", L"DunGeon/Scroll_In.png", 2145, 52, 11, 1);

	IMAGEMANAGER->addDImage("Dungeon_Background", L"DunGeon/Dungeon_Background.png", WINSIZEX / 2, WINSIZEY / 2);
	IMAGEMANAGER->addDImage("Dungeon_Background2", L"DunGeon/Dungeon_Background2.png", 650, 390);

	IMAGEMANAGER->addDImage("Bag_Pendant", L"UI/Bag_Pendant.png", 39, 28);
	IMAGEMANAGER->addDImage("Circle_How", L"UI/Circle_How.png", 50, 50);
	IMAGEMANAGER->addDImage("L_Button", L"UI/L_Button.png", 20, 20);


	IMAGEMANAGER->addDImage("Door_Up", L"DunGeon/Door_Up.png", 82, 52);
	IMAGEMANAGER->addDImage("Door_Down", L"DunGeon/Door_Down.png", 82, 52);
	IMAGEMANAGER->addDImage("Door_Left", L"DunGeon/Door_Left.png", 52, 82);
	IMAGEMANAGER->addDImage("Door_Right", L"DunGeon/Door_Right.png", 52, 82);

	IMAGEMANAGER->addDImage("Minimap_Room", L"MiniMap/Minimap_Room.png", 30, 21);
	IMAGEMANAGER->addDImage("Minimap_Will", L"MiniMap/Minimap_Will.png", 12, 12);
	IMAGEMANAGER->addDImage("Minimap_Onsen", L"MiniMap/Minimap_Onsen.png", 16, 16);

	IMAGEMANAGER->addDImage("Life_Water", L"ITEM/Item_LifeFluid.png", 32, 32);
	IMAGEMANAGER->addDImage("Golem_core", L"ITEM/item_golem_core.png", 32, 32);
	IMAGEMANAGER->addDImage("blueprint", L"ITEM/item_golem_blue_print.png", 32, 32);
	IMAGEMANAGER->addDImage("Break_Sword", L"ITEM/book_item_01_BrokenSword.png", 32, 32);
	IMAGEMANAGER->addDImage("Crystal", L"ITEM/item_crystal_rock.png", 32, 32);
	IMAGEMANAGER->addDImage("History_Book", L"ITEM/Item_GolemHistoryI.png", 32, 32);
	IMAGEMANAGER->addDImage("Note", L"ITEM/Item_NajaNotes.png", 32, 32);
	IMAGEMANAGER->addDImage("Steel", L"ITEM/item_reinforced_steel_01.png", 32, 32);
	IMAGEMANAGER->addDImage("Straw", L"ITEM/Item_Straw.png", 32, 32);
	IMAGEMANAGER->addDImage("Electronic_Line", L"ITEM/item_rune_tool.png", 32, 32);

	IMAGEMANAGER->addDImage("boss1_door", L"Boss/boss1_door_close_01.png", 100, 58);
	IMAGEMANAGER->addDImage("background_boss", L"Boss/background_boss room.png", 1156, 783);




	//ī�޶� ������ ����
	CAMERAMANAGER->setBackScreenSize(WINSIZEX * 10, WINSIZEY * 10);
	CAMERAMANAGER->setZoom(2);
	_tileMap = new tileMap;

	_differenceX = 78;
	_differenceY = 51;

	_huntSlime = 0;
	_huntMiniBoss = 0;

	_player = new player;
	_player->init();
	_playerHit = false;
	_miniBoss = new miniBoss;

	_slime = new slime;

	_ui = new UI;
	_ui->init();
	//����� ���İ�
	_alpha.rc = RectMake(0, 0, WINSIZEX * 10, WINSIZEY * 10);
	_alpha.alpha = 1.f;
	//���� ��ũ�� ����
	_scroll.img = IMAGEMANAGER->findDImage("Scroll_In");
	_scroll.x = 650 / 2 - 100;
	_scroll.y = 280;
	_scroll.rc = RectMakeCenter(_scroll.x, _scroll.y, _scroll.img->getFrameWidth(), _scroll.img->getFrameHeight());
	_scroll.count = 0;
	_scroll.currentFrameX = _scroll.currentFrameY = 0;
	_scroll.isInvisible = false;
	_scroll.alpha = 1.f;


	//Bag_Pendant ����
	_returnPotalBase.img = IMAGEMANAGER->findDImage("Circle_How");
	_returnPotalBase.x = 570;
	_returnPotalBase.y = 300;
	_returnPotalBase.rc = RectMakeCenter(_returnPotalBase.x, _returnPotalBase.y, _returnPotalBase.img->getFrameWidth(), _returnPotalBase.img->getFrameHeight());
	_returnPotal.img = IMAGEMANAGER->findDImage("Bag_Pendant");
	_returnPotal.x = 570;
	_returnPotal.y = 300;
	_returnPotal.rc = RectMakeCenter(_returnPotal.x, _returnPotal.y, _returnPotal.img->getFrameWidth(), _returnPotal.img->getFrameHeight());
	_returnLbutton.img = IMAGEMANAGER->findDImage("L_Button");
	_returnLbutton.x = 610;
	_returnLbutton.y = 320;
	_returnLbutton.rc = RectMakeCenter(_returnLbutton.x, _returnLbutton.y, _returnLbutton.img->getFrameWidth(), _returnLbutton.img->getFrameHeight());
	_returnPotalRect.x = 570;
	_returnPotalRect.y = 360;
	_returnPotalRect.width = 0;
	_returnPotalRect.rc = RectMake(_returnPotalRect.x, _returnPotalRect.y, _returnPotalRect.width, 10);
	_returnPotalRect.baseRc = RectMake(_returnPotalRect.x, _returnPotalRect.y, 60, 10);

	
	for (int y = 0; y < MAPSIZE; y++)
	{
		for (int x = 0; x < MAPSIZE; x++)
		{
			//��׶��� ���� ����
			_backGround[x + (y * MAPSIZE)].img = IMAGEMANAGER->findDImage("Dungeon_Background2");
			_backGround[x + (y * MAPSIZE)].x = _backGround[x + (y * MAPSIZE)].img->getWidth() / 2 + x * _backGround[x + (y * MAPSIZE)].img->getWidth();
			_backGround[x + (y * MAPSIZE)].y = _backGround[x + (y * MAPSIZE)].img->getHeight() / 2 + y * _backGround[x + (y * MAPSIZE)].img->getHeight();
			_backGround[x + (y * MAPSIZE)].rc = RectMakeCenter(_backGround[x + (y *MAPSIZE)].x, _backGround[x + (y * MAPSIZE)].y,
				_backGround[x + (y * MAPSIZE)].img->getWidth(), _backGround[x + (y * MAPSIZE)].img->getHeight());
			_backGround[x + (y * MAPSIZE)].indexX = x;
			_backGround[x + (y *MAPSIZE)].indexY = y;
			_backGround[x + (y *MAPSIZE)].isfix = false;
		
			//�� �ʱ� ����
			//2�� ���������� 0�̸� ���� ����, 1�̸� ���� ����
			if (x % 2 == 0 || y % 2 == 0)
				_backGround[x + (y * MAPSIZE)].isBool = false;
			else
				_backGround[x + (y * MAPSIZE)].isBool = true;
		}
	}	
	//Binary Tree �˰���
	for (int y = 0; y < MAPSIZE; y++)
	{
		for (int x = 0; x < MAPSIZE; x++)
		{	

			//�� ����
			//y���� ������ ���� ������ ����
			if (y % 6 == 0) _backGround[x + (y *MAPSIZE)].isBool = false;
			//x��� y���� 2�� ���������� 0�̸� ���� �ƴϸ� �������� ����
			if (x % 2 == 0 || y % 2 == 0) continue;
			//0�� 1�� ������ �������� �޾� 0�̸� �Ʒ� ���� ���ְ�, 1�̸� ������ ���� ����
			if (RND->getFromIntTo(0, 2) == 0)
			{
				_backGround[x + (y *MAPSIZE) + 1].isBool = true;
			}
			else
			{
				_backGround[x + (y *MAPSIZE) + 5].isBool = true;
			}
			
		}
	}
	//�÷��̾� ��ġ ������
	_player->setPlayerX(_backGround[45].x);
	_player->setPlayerY(_backGround[45].y + 120);
	_player->setPlayerRect(RectMakeCenter(_player->getPlayer().x, _player->getPlayer().y, _player->getPlayer().img->getFrameWidth(), _player->getPlayer().img->getFrameHeight()));
	//ī�޶� ����
	_isBossCamera = false;
	_dungeonCamera.x = _backGround[45].x;
	_dungeonCamera.y = _backGround[45].y;
	_dungeonCamera.rc = RectMakeCenter(_dungeonCamera.x, _dungeonCamera.y, 10, 10);
	_dungeonCamera.cameraDirection = CAMERASTOP;
	_dungeonCamera.speed = 0.3f;
	//��� ����
	for (int i = 0; i < MAPMAX; i++)
	{
		//���� �� ���ο� ���� ���(��) ���� 
		if (i % MAPSIZE != 0)
		{
			if (!_backGround[i - 1].isBool && !_backGround[i].isBool)
			{
				_backGround[i].roadLeft.rc = RectMakeCenter(_backGround[i].rc.left + 50, _backGround[i].y, 50, 30);
				_backGround[i].roadLeft.img = IMAGEMANAGER->findDImage("Door_Left");
			}
		}
		//������ �� ���ο� ���� ���(��) ���� 
		if (i % MAPSIZE != MAPSIZE - 1)
		{
			if (!_backGround[i + 1].isBool && !_backGround[i].isBool)
			{
				_backGround[i].roadRight.rc = RectMakeCenter(_backGround[i].rc.right - 50, _backGround[i].y, 50, 30);
				_backGround[i].roadRight.img = IMAGEMANAGER->findDImage("Door_Right");
			}
		}
		//���� �� ���ο� ���� ���(��) ����
		if (i / MAPSIZE != 0)
		{
			if (!_backGround[i - MAPSIZE].isBool && !_backGround[i].isBool)
			{
				_backGround[i].roadUp.rc = RectMakeCenter(_backGround[i].x, _backGround[i].rc.top + 20, 30, 50);
				_backGround[i].roadUp.img = IMAGEMANAGER->findDImage("Door_Up");
			}
		}
		//�Ʒ��� �� ���ο� ���� ���(��) ����
		if (i / MAPSIZE != MAPSIZE - 1)
		{
			if (!_backGround[i + MAPSIZE].isBool && !_backGround[i].isBool)
			{
				_backGround[i].roadDown.rc = RectMakeCenter(_backGround[i].x, _backGround[i].rc.bottom - 20, 30, 50);
				_backGround[i].roadDown.img = IMAGEMANAGER->findDImage("Door_Down");
			}
		}

	}

	//Lake ��ġ ����
	randPool = RND->getFromIntTo(2, 6);
	load(_backGround[randPool].tiles, "1");
	_backGround[randPool].isfix = true;
	//�غ��� ��ġ ���� 
	randBoss = RND->getFromIntTo(0, 2);
	if (randBoss == 0)
	{
		load(_backGround[randPool - 1].tiles, "0");
		_backGround[randPool - 1].isfix = true;

		_miniBoss->init(_backGround[randPool - 1].x, _backGround[randPool - 1].y, _player->getPlayer().rc, _backGround[randPool - 2].x + _backGround[randPool - 2].img->getWidth() / 2 + _differenceX, _differenceY);

	}
	else
	{
		load(_backGround[randPool + 1].tiles, "0");
		_backGround[randPool + 1].isfix = true;

		_miniBoss->init(_backGround[randPool + 1].x, _backGround[randPool + 1].y, _player->getPlayer().rc, _backGround[randPool].x + _backGround[randPool].img->getWidth() / 2 + _differenceX, _differenceY);
	}


	//�غ��� Ǫ����
	_vMiniBoss.img = _miniBoss->getMiniBoss().img;
	_vMiniBoss.rc = _miniBoss->getMiniBoss().rc;
	_vMiniBoss.objFrameX = _miniBoss->getMiniBoss().currentFrameX;
	_vMiniBoss.objFrameY = _miniBoss->getMiniBoss().currentFrameY;
	_vMiniBoss.terrainFrameX = 200;

	_vZorder.push_back(&_vMiniBoss);


	//������ġ ����
	load(_backGround[45].tiles, "0");
	_backGround[45].isfix = true;

	//Tile ������ ���� ����
	for (int k = 0; k < MAPMAX; ++k)
	{
		//���̸� ��׶��� ���� X
		if (_backGround[k].isBool) continue;

		// 1~10������ Ÿ�ϸ��� �������� �����Ѵ�.
		_changeChar[64] = _itoa_s(RND->getFromIntTo(2, 11), _changeChar, sizeof(_changeChar), 10);

		if (!_backGround[k].isfix)
		{
			load(_backGround[k].tiles, _changeChar);
			for (int i = 0; i < RND->getFromIntTo(1, 5); ++i)
			{
				_slime->init(_backGround[k].rc.left + _differenceX + RND->getFromIntTo(TILESIZE, (TILESIZE - 1) * DUNGEONTILEX), _backGround[k].rc.top + _differenceY + RND->getFromIntTo(TILESIZE, (TILESIZE - 1) * DUNGEONTILEY), _player->getPlayer().rc, _backGround[k].rc.left + _differenceX, _backGround[k].rc.top + _differenceY, k);

			}
		}
		//Tile ��ġ ����
		for (int i = 0; i < DUNGEONTILEY; ++i)
		{
			for (int j = 0; j < DUNGEONTILEX; ++j)
			{
				_backGround[k].tiles[i * DUNGEONTILEX + j].rc = RectMake(_backGround[k].rc.left + _differenceX + j * TILESIZE, _backGround[k].rc.top + _differenceY + i * TILESIZE, TILESIZE, TILESIZE);
			}
		}
	}
	//Lake ����	
	_pool.img = IMAGEMANAGER->findDImage("Lake");
	_pool.x = _backGround[randPool].x;
	_pool.y = _backGround[randPool].y;
	_pool.rc = RectMakeCenter(_pool.x, _pool.y, _pool.img->getFrameWidth(), _pool.img->getFrameHeight());
	_pool.count = 0;
	_pool.currentFrameX = _pool.currentFrameY = 0;
	//Lake �浹ü
	_poolCollision.x = _backGround[randPool].x;
	_poolCollision.y = _backGround[randPool].y;
	_poolCollision.radius = 90;
	_poolCollision.rc = RectMakeCenter(_poolCollision.x, _poolCollision.y, _poolCollision.radius, _poolCollision.radius);
	//z������ ���� ���� Ǫ����
	_vPlayer.rc = _player->getPlayer().rc;
	_vPlayer.img = _player->getPlayer().img;
	_vPlayer.objFrameX = _player->getPlayer().currentFrameX;
	_vPlayer.objFrameY = _player->getPlayer().currentFrameY;
	_vPlayer.terrainFrameX = 100;
	_vZorder.push_back(&_vPlayer);
	//Tile Ǫ����
	for (int j = 0; j < MAPMAX; ++j)
	{
		for (int i = 0; i < DUNGEONTILEX * DUNGEONTILEX; ++i)
		{
			if (_backGround[j].tiles[i].imgAt == DEFAULT_IMAGE)
			{
				if (_backGround[j].tiles[i].obj == OBJ_NOTMOVE)
				{
					_backGround[j].tiles[i].img = IMAGEMANAGER->findDImage("GolemDunGeon");


					_vZorder.push_back(&_backGround[j].tiles[i]);

				}
			}
		}
	}
	//�̴ϸʰ���
	_isMiniMapInvisible = false;
	_minimapBack.x = 1280 / 4;
	_minimapBack.y = 720 / 4;
	_minimapBack.rc = RectMakeCenter(_minimapBack.x + CAMERAMANAGER->getScreen().left, _minimapBack.y + CAMERAMANAGER->getScreen().top, 1280, 720);


	//�̴ϸ� ��
	for (int i = 0; i < MAPSIZE; ++i)
	{
		for (int j = 0; j < MAPSIZE; ++j)
		{
			_miniMap[i * MAPSIZE + j].img = IMAGEMANAGER->findDImage("Minimap_Room");
			_miniMap[i * MAPSIZE + j].x = 200 + j * 40;
			_miniMap[i * MAPSIZE + j].y = 100 + i * 28;
			_miniMap[i * MAPSIZE + j].rc = RectMakeCenter(_miniMap[i * MAPSIZE + j].x, _miniMap[i * MAPSIZE + j].y, _miniMap[i * MAPSIZE + j].img->getWidth(), _miniMap[i * MAPSIZE + j].img->getHeight());
			_miniMap[i * MAPSIZE + j].isInvisible = false;
		}
	}
	//�̴ϸ� ��
	_miniMapWill.img = IMAGEMANAGER->findDImage("Minimap_Will");
	_miniMapWill.x = _miniMap[45].x;
	_miniMapWill.y = _miniMap[45].y;
	_miniMapWill.rc = RectMakeCenter(_miniMapWill.x + CAMERAMANAGER->getScreen().left, _miniMapWill.y + CAMERAMANAGER->getScreen().top, _miniMapWill.img->getWidth(), _miniMapWill.img->getHeight());
	//�̴ϸ� Lake
	_miniMapPool.img = IMAGEMANAGER->findDImage("Minimap_Onsen");
	_miniMapPool.x = _miniMap[randPool].x + 10;
	_miniMapPool.y = _miniMap[randPool].y;
	_miniMapPool.rc = RectMakeCenter(_miniMapPool.x + CAMERAMANAGER->getScreen().left, _miniMapPool.y + CAMERAMANAGER->getScreen().top, _miniMapPool.img->getWidth(), _miniMapPool.img->getHeight());


	/*for (int i = 0; i < MAPMAX; ++i)
	{
		for (int j = 0; j < DUNGEONTILEX * DUNGEONTILEY; ++j)
		{
			if (_backGround[i].tiles[j].obj != OBJ_NOTMOVE) continue;

			for (int k = 0; k < _slime->getSlime().size(); ++k)
			{
				if (_slime->getSlime()[k].backGroundNum != i) continue;

				if		(j / 19 == 0) diff = j + 1;
				else if (j / 19 == 1) diff = j + 3;
				else if (j / 19 == 2) diff = j + 5;
				else if (j / 19 == 3) diff = j + 7;
				else if (j / 19 == 4) diff = j + 9;
				else if (j / 19 == 5) diff = j + 11;
				else if (j / 19 == 6) diff = j + 13;
				else if (j / 19 == 7) diff = j + 15;
				else if (j / 19 == 8) diff = j + 17;
				else if (j / 19 == 9) diff = j + 19;
				else if (j / 19 == 10) diff = j + 21;
				else diff = j;
				_slime->getAstar(k)->setVtotalAttribute(diff, "wall");


			}
		}


	}*/
	_bossDoor.img = IMAGEMANAGER->findDImage("boss1_door");
	if (randBoss == 0)
	{
		_bossDoor.x = _backGround[randPool - 1].x;
		_bossDoor.y = _backGround[randPool - 1].rc.top + _differenceY - 10;
	}

	if (randBoss == 1)
	{
		_bossDoor.x = _backGround[randPool + 1].x;
		_bossDoor.y = _backGround[randPool + 1].rc.top + _differenceY - 10;
	}
	_isBossDoor = false;

	_backGroundBoss.img = IMAGEMANAGER->findDImage("background_boss");
	_backGroundBoss.x = 5000;
	_backGroundBoss.y = 5000;
	_backGroundBoss.rc = RectMakeCenter(_backGroundBoss.x, _backGroundBoss.y, _backGroundBoss.img->getWidth(), _backGroundBoss.img->getHeight());
	_backGroundBoss.alpha = 1;


	_boss = new boss;
	_boss->init(_backGroundBoss.x, _backGroundBoss.y - 100);


	return S_OK;
}

void dungeon::release()
{
	_vZorder.clear();

	SOUNDMANAGER->stop("DungeonBackgroundMusic");
	SOUNDMANAGER->stop("BossBackgroundMusic");
	SOUNDMANAGER->stop("WillStep");
}
bool compareDun(tagTile * a, tagTile * b)
{
	return a->rc.bottom < b->rc.bottom;
}
void dungeon::update()
{

	_ui->update(_player->getPlayer().currentHp);
	//���۽� ���İ�
	_alpha.alpha -= 0.01f;
	if (_alpha.alpha <= 0) _alpha.alpha = 0;

	if (!_ui->getPauseCheck() && !_ui->getInvenCheck() && !_ui->getResultCheck())
	{

		_player->update();
		if (!_isBossCamera) CAMERAMANAGER->updateScreen(_dungeonCamera.x, _dungeonCamera.y);
		else 	CAMERAMANAGER->updateScreen(_player->getPlayer().x, _player->getPlayer().y);


		_dungeonCamera.rc = RectMakeCenter(_dungeonCamera.x, _dungeonCamera.y, 10, 10);

		RECT temp;
		RECT playerRc = _player->getPlayer().rc;
		//�뿡 ���� �÷��̾� ��ġ����
		for (int i = 0; i < MAPMAX; i++)
		{
			_backGround[i].rc = RectMakeCenter(_backGround[i].x, _backGround[i].y, _backGround[i].img->getWidth(), _backGround[i].img->getHeight());
			if (IntersectRect(&temp, &_backGround[i].rc, &playerRc))
			{
				//�̴ϸ� �ν�
				_miniMap[i].isInvisible = true;
				_miniMapWill.x = _miniMap[i].x;
				_miniMapWill.y = _miniMap[i].y;
				//�̴Ϻ��� ������Ʈ
				if (_miniBoss->getMiniBoss().currentHp > 0)
				{
					if (randBoss == 0 & i == randPool - 1)
					{
						_miniBoss->update(getDistance(_player->getPlayer().x, _player->getPlayer().y, _miniBoss->getMiniBoss().x, _miniBoss->getMiniBoss().y), _backGround[randPool - 2].x + _backGround[randPool - 2].img->getWidth() / 2 + _differenceX, _differenceY, _player->getPlayer().rc);
					}
					if (randBoss == 1 & i == randPool + 1)
					{
						_miniBoss->update(getDistance(_player->getPlayer().x, _player->getPlayer().y, _miniBoss->getMiniBoss().x, _miniBoss->getMiniBoss().y), _backGround[randPool].x + _backGround[randPool].img->getWidth() / 2 + _differenceX, _differenceY, _player->getPlayer().rc);
					}
				}

				//�÷��̾� ��ġ ����ó��
				if (_backGround[i].rc.left + _differenceX - 5 >= _player->getPlayer().rc.left) _player->setPlayerX(_backGround[i].rc.left + _differenceX + _player->getPlayer().img->getFrameWidth() / 2 - 5);
				if (_backGround[i].rc.right - _differenceX + 5 <= _player->getPlayer().rc.right) _player->setPlayerX(_backGround[i].rc.right - _differenceX - _player->getPlayer().img->getFrameWidth() / 2 + 5);
				if (_backGround[i].rc.top + _differenceY - 5 >= _player->getPlayer().rc.top) _player->setPlayerY(_backGround[i].rc.top + _differenceY + _player->getPlayer().img->getFrameHeight() / 2 - 5);
				if (_backGround[i].rc.bottom - _differenceY + 5 <= _player->getPlayer().rc.bottom) _player->setPlayerY(_backGround[i].rc.bottom - _differenceY - _player->getPlayer().img->getFrameHeight() / 2 + 5);
			}
		}
		//�� ��Ʈ�� �������� �÷��̾� ��ġ �̵�
		for (int i = 0; i < MAPMAX; i++)
		{
			RECT temp;
			RECT pl = _player->getPlayer().rc;
			if (IntersectRect(&temp, &_backGround[i].roadLeft.rc, &pl))
			{
				_player->setPlayerX(_backGround[i - 1].rc.right - 90);
				_player->setPlayerY(_backGround[i - 1].y);
				_dungeonCamera.cameraDirection = CAMERALEFT;
				_dungeonCamera.roomNumber = i - 1;
			}
			if (IntersectRect(&temp, &_backGround[i].roadRight.rc, &pl))
			{
				_player->setPlayerX(_backGround[i + 1].rc.left + 90);
				_player->setPlayerY(_backGround[i + 1].y);
				_dungeonCamera.cameraDirection = CAMERARIGHT;
				_dungeonCamera.roomNumber = i + 1;
			}
			if (IntersectRect(&temp, &_backGround[i].roadUp.rc, &pl))
			{
				_player->setPlayerX(_backGround[i - MAPSIZE].x);
				_player->setPlayerY(_backGround[i - MAPSIZE].rc.bottom - 80);
				_dungeonCamera.cameraDirection = CAMERAUP;
				_dungeonCamera.roomNumber = i - MAPSIZE;
			}
			if (IntersectRect(&temp, &_backGround[i].roadDown.rc, &pl))
			{
				_player->setPlayerX(_backGround[i + MAPSIZE].x);
				_player->setPlayerY(_backGround[i + MAPSIZE].rc.top + 80);
				_dungeonCamera.cameraDirection = CAMERADOWN;
				_dungeonCamera.roomNumber = i + MAPSIZE;
			}
			//�뿡 ���� ī�޶� ���� �ڿ������� �̵�
			switch (_dungeonCamera.cameraDirection)
			{
			case CAMERALEFT:
				_dungeonCamera.x -= _dungeonCamera.speed * 650 / 390;
				if (_dungeonCamera.x <= _backGround[_dungeonCamera.roomNumber].x) _dungeonCamera.cameraDirection = CAMERASTOP;
				break;
			case CAMERARIGHT:
				_dungeonCamera.x += _dungeonCamera.speed * 650 / 390;
				if (_dungeonCamera.x >= _backGround[_dungeonCamera.roomNumber].x) _dungeonCamera.cameraDirection = CAMERASTOP;
				break;
			case CAMERAUP:
				_dungeonCamera.y -= _dungeonCamera.speed;
				if (_dungeonCamera.y <= _backGround[_dungeonCamera.roomNumber].y) _dungeonCamera.cameraDirection = CAMERASTOP;
				break;
			case CAMERADOWN:
				_dungeonCamera.y += _dungeonCamera.speed;
				if (_dungeonCamera.y >= _backGround[_dungeonCamera.roomNumber].y) _dungeonCamera.cameraDirection = CAMERASTOP;
				break;
			case CAMERASTOP:

				break;
			}
		}
		//Lake ������
		_pool.count++;
		if (_pool.count % 10 == 0)
		{
			_pool.currentFrameX++;
			if (_pool.currentFrameX > _pool.img->getMaxFrameX())
			{
				_pool.currentFrameX = 0;
				_pool.count = 0;
			}
		}
		//��ũ�� ������
		_scroll.count++;
		if (_scroll.count % 8 == 0)
		{
			_scroll.currentFrameX++;
			if (_scroll.currentFrameX > _scroll.img->getMaxFrameX())
			{
				_scroll.currentFrameX = _scroll.img->getMaxFrameX();
				_scroll.alpha -= 0.1f;
				_scroll.count = 0;
			}
			if (_scroll.alpha <= 0) _scroll.isInvisible = true;
		}
		//z���� (���Ϳ� �־��� �÷��̾ ã�Ƴ��� �̹�����, ��ġ����, ������ ������ �������ش�.
		for (int i = 0; i < _vZorder.size(); ++i)
		{
			if (_vZorder[i]->terrainFrameX == 100)
			{
				_vZorder[i]->img = _player->getPlayer().img;
				_vZorder[i]->objFrameX = _player->getPlayer().currentFrameX;
				_vZorder[i]->objFrameY = _player->getPlayer().currentFrameY;
				_vZorder[i]->rc = _player->getPlayer().rc;
			}
			if (_miniBoss->getMiniBoss().currentHp > 0)
			{
				if (_vZorder[i]->terrainFrameX == 200)
				{
					_vZorder[i]->img = _miniBoss->getMiniBoss().img;
					_vZorder[i]->objFrameX = _miniBoss->getMiniBoss().currentFrameX;
					_vZorder[i]->objFrameY = _miniBoss->getMiniBoss().currentFrameY;
					_vZorder[i]->rc = _miniBoss->getMiniBoss().rc;
				}
			}
			else
			{
				//�̴Ϻ��� ���� 
				if (_vZorder[i]->terrainFrameX == 200)
				{
					_miniBoss->setMiniBossAttack1Rc(RectMakeCenter(0, 0, 0, 0));
					_miniBoss->setMiniBossAttack2Rc(RectMakeCenter(0, 0, 0, 0));
					_miniBoss->setMiniBossHitRc(RectMakeCenter(0, 0, 0, 0));
					_miniBoss->setMiniBossRc(RectMakeCenter(0, 0, 0, 0));
					_vZorder.erase(_vZorder.begin() + i);
				}
			}
		}

		//������ ���
		sort(_vZorder.begin(), _vZorder.end(), &compareDun);



		//������ ������Ʈ
		for (int i = 0; i < MAPMAX; ++i)
		{
			RECT temp;
			RECT player = _player->getPlayer().rc;
			if (IntersectRect(&temp, &player, &_backGround[i].rc))
			{
				_slime->update(_backGround[i].rc.left + _differenceX, _backGround[i].rc.top + _differenceY, _player->getPlayer().rc, i);

			}

		}


		playerCollision();
		enemyCollision();
		miniMap();
		tileCheck();
		poolCollision();
		itemCollision();
		bossDoor();
		bossRoomCollision();
		//���� ������Ʈ �� �浹
		if (_isBossCamera) _boss->update(_player->getPlayer().x, _player->getPlayer().y);
		bossCollision();
		itemMove();


		//enemyTileCheck();

	}

	dungeonReturn();
	EFFECTMANAGER->update();



}

void dungeon::render()
{

	//����Ÿ�� �̹���
	for (int j = 0; j < MAPMAX; j++)
	{
		for (int i = 0; i < DUNGEONTILEX * DUNGEONTILEY; ++i)
		{
			if (_backGround[j].isBool) continue;
			if (KEYMANAGER->isToggleKey(VK_NUMPAD0))
			{
				D2DMANAGER->DrawRectangle(_backGround[j].tiles[i].rc, D2DDEFAULTBRUSH::Yellow);
			}
			if (CAMERAMANAGER->getScreen().left - TILESIZE <= _backGround[j].tiles[i].rc.left && CAMERAMANAGER->getScreen().right + TILESIZE >= _backGround[j].tiles[i].rc.right &&
				CAMERAMANAGER->getScreen().top - TILESIZE <= _backGround[j].tiles[i].rc.top && CAMERAMANAGER->getScreen().bottom + TILESIZE >= _backGround[j].tiles[i].rc.bottom)
			{

				IMAGEMANAGER->findDImage("GolemDunGeon")->frameRender(_backGround[j].tiles[i].rc.left, _backGround[j].tiles[i].rc.top, _backGround[j].tiles[i].terrainFrameX, _backGround[j].tiles[i].terrainFrameY);

			}
		}
	}
	//Lake �̹���
	_pool.img->frameRender(_pool.rc.left, _pool.rc.top, _pool.currentFrameX, _pool.currentFrameY);
	//�׵θ� �׸���
	for (int i = 0; i < MAPMAX; i++)
	{
		if (!_backGround[i].isBool)_backGround[i].img->render(_backGround[i].rc.left, _backGround[i].rc.top);
	}
	//�׽�Ʈ ���� �׸���
	for (int i = 0; i < MAPMAX; i++)
	{
		//����
		if (i % MAPSIZE != 0)
		{
			if (!_backGround[i - 1].isBool && !_backGround[i].isBool)
			{
				_backGround[i].roadLeft.img->render(_backGround[i].roadLeft.rc.left + 17, _backGround[i].roadLeft.rc.top - 27);
			}
		}
		//������
		if (i % MAPSIZE != MAPSIZE - 1)
		{
			if (!_backGround[i + 1].isBool && !_backGround[i].isBool)
			{
				_backGround[i].roadRight.img->render(_backGround[i].roadRight.rc.left - 17, _backGround[i].roadRight.rc.top - 27);
			}
		}
		//��
		if (i / MAPSIZE != 0)
		{
			if (!_backGround[i - MAPSIZE].isBool && !_backGround[i].isBool)
			{
				_backGround[i].roadUp.img->render(_backGround[i].roadUp.rc.left - 27, _backGround[i].roadUp.rc.top + 17);
			}
		}
		//�Ʒ�
		if (i / MAPSIZE != MAPSIZE - 1)
		{
			if (!_backGround[i + MAPSIZE].isBool && !_backGround[i].isBool)
			{
				_backGround[i].roadDown.img->render(_backGround[i].roadDown.rc.left - 27, _backGround[i].roadDown.rc.top - 17);
			}
		}
	}
	//������
	_backGroundBoss.img->render(_backGroundBoss.rc.left, _backGroundBoss.rc.top);
	if (_isBossCamera) _boss->render();
	//z���� �̹���(������ �� ���� ������Ʈ ����)
	for (int i = 0; i < _vZorder.size(); ++i)
	{
		if (CAMERAMANAGER->getScreen().left - TILESIZE <= _vZorder[i]->rc.left && CAMERAMANAGER->getScreen().right + TILESIZE >= _vZorder[i]->rc.right &&
			CAMERAMANAGER->getScreen().top - TILESIZE <= _vZorder[i]->rc.top && CAMERAMANAGER->getScreen().bottom + TILESIZE >= _vZorder[i]->rc.bottom)
		{
			if (_vZorder[i]->terrainFrameX == 100 && _playerHit)
			{
				_vZorder[i]->img->frameRender(_vZorder[i]->rc.left, _vZorder[i]->rc.top, _vZorder[i]->objFrameX, _vZorder[i]->objFrameY, 0);
			}
			else if (_vZorder[i]->terrainFrameX == 100 && !_playerHit)
			{
				_vZorder[i]->img->frameRender(_vZorder[i]->rc.left, _vZorder[i]->rc.top, _vZorder[i]->objFrameX, _vZorder[i]->objFrameY, 1);
			}
			if (_vZorder[i]->terrainFrameX == 200 && _miniBoss->getMiniBoss().enemyHit)
			{
				_vZorder[i]->img->frameRender(_vZorder[i]->rc.left, _vZorder[i]->rc.top, _vZorder[i]->objFrameX, _vZorder[i]->objFrameY, 0);
			}
			else if (_vZorder[i]->terrainFrameX == 200 && !_miniBoss->getMiniBoss().enemyHit)
			{
				_vZorder[i]->img->frameRender(_vZorder[i]->rc.left, _vZorder[i]->rc.top, _vZorder[i]->objFrameX, _vZorder[i]->objFrameY, 1);
			}
			if (_vZorder[i]->terrainFrameX != 100 && !_playerHit && _vZorder[i]->terrainFrameX != 200) _vZorder[i]->img->frameRender(_vZorder[i]->rc.left, _vZorder[i]->rc.top, _vZorder[i]->objFrameX, _vZorder[i]->objFrameY);
			if (_vZorder[i]->terrainFrameX != 100 && _playerHit && _vZorder[i]->terrainFrameX != 200) _vZorder[i]->img->frameRender(_vZorder[i]->rc.left, _vZorder[i]->rc.top, _vZorder[i]->objFrameX, _vZorder[i]->objFrameY);

		}

	}

	//������Ʈ(������ ���� ����) Tile �̹���
	for (int j = 0; j < MAPMAX; j++)
	{
		for (int i = 0; i < DUNGEONTILEX * DUNGEONTILEY; ++i)
		{
			if (_backGround[j].isBool) continue;
			if (_backGround[j].tiles[i].obj == OBJ_BLOCK1)
			{
				if (KEYMANAGER->isToggleKey(VK_NUMPAD0))
				{
					D2DMANAGER->DrawRectangle(_backGround[j].tiles[i].rc, D2DDEFAULTBRUSH::Purple);
				}
				if (CAMERAMANAGER->getScreen().left - TILESIZE <= _backGround[j].tiles[i].rc.left && CAMERAMANAGER->getScreen().right + TILESIZE >= _backGround[j].tiles[i].rc.right &&
					CAMERAMANAGER->getScreen().top - TILESIZE <= _backGround[j].tiles[i].rc.top && CAMERAMANAGER->getScreen().bottom + TILESIZE >= _backGround[j].tiles[i].rc.bottom)
				{
					IMAGEMANAGER->findDImage("GolemDunGeon")->frameRender(_backGround[j].tiles[i].rc.left, _backGround[j].tiles[i].rc.top, _backGround[j].tiles[i].objFrameX, _backGround[j].tiles[i].objFrameY);
				}
			}
		}
	}
	//��ȯ ���Ʈ ���� ����
	_returnPotalBase.img->render(_returnPotalBase.rc.left + CAMERAMANAGER->getScreen().left, _returnPotalBase.rc.top + CAMERAMANAGER->getScreen().top - 10);
	_returnPotal.img->render(_returnPotal.rc.left + CAMERAMANAGER->getScreen().left, _returnPotal.rc.top + CAMERAMANAGER->getScreen().top);
	_returnLbutton.img->render(_returnLbutton.rc.left, _returnLbutton.rc.top);
	D2DMANAGER->FillRectangle(_returnPotalRect.baseRc, D2DDEFAULTBRUSH::Gray);
	D2DMANAGER->FillRectangle(_returnPotalRect.rc, D2DDEFAULTBRUSH::Green);



	EFFECTMANAGER->render();
	//��Ʈ ǥ��
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < MAPMAX; i++)
		{
			//����
			D2DMANAGER->DrawRectangle(_backGround[i].roadLeft.rc, D2DDEFAULTBRUSH::Yellow);
			D2DMANAGER->DrawRectangle(_backGround[i].roadRight.rc, D2DDEFAULTBRUSH::Yellow);
			D2DMANAGER->DrawRectangle(_backGround[i].roadUp.rc, D2DDEFAULTBRUSH::Yellow);
			D2DMANAGER->DrawRectangle(_backGround[i].roadDown.rc, D2DDEFAULTBRUSH::Yellow);
			//ī�޶�
			D2DMANAGER->DrawRectangle(_dungeonCamera.rc, D2DDEFAULTBRUSH::Red);
			//�̴Ϻ���
			D2DMANAGER->DrawRectangle(_miniBoss->getMiniBoss().rc);
			D2DMANAGER->DrawRectangle(_miniBoss->getMiniBoss().hitRc);
			D2DMANAGER->DrawRectangle(_miniBoss->getMiniBoss().attackRc);
			D2DMANAGER->DrawRectangle(_miniBoss->getMiniBoss().attack2Rc);
			//�÷��̾�
			D2DMANAGER->DrawRectangle(_player->getPlayer().attackRect);
			D2DMANAGER->DrawRectangle(_player->getPlayer().rc);
		}
	}


	_slime->render();
	if (_miniBoss->getMiniBoss().currentHp > 0)	_miniBoss->hpRender();
	//���� ��
	if (_isBossDoor)	_bossDoor.img->render(_bossDoor.rc.left, _bossDoor.rc.top);


	//������ �̹���
	for (int i = 0; i < _vitemGet.size(); ++i)
	{
		_vitemGet[i].img->render(_vitemGet[i].rc.left, _vitemGet[i].rc.top);

	}

	_player->hpRender();
	//�̴ϸ� �̹���
	if (_isMiniMapInvisible)
	{
		D2DMANAGER->FillRectangle(_minimapBack.rc, D2D1COLOR::Black, 0.7f);

		for (int i = 0; i < MAPMAX; i++)
		{
			if (_miniMap[i].isInvisible) _miniMap[i].img->render(_miniMap[i].rc.left, _miniMap[i].rc.top);
		}
		_miniMapWill.img->render(_miniMapWill.rc.left, _miniMapWill.rc.top);
		if (_miniMap[randPool].isInvisible) _miniMapPool.img->render(_miniMapPool.rc.left, _miniMapPool.rc.top);
	}
	//Scroll_In �̹���
	if (!_scroll.isInvisible)_scroll.img->frameRender(_scroll.x + CAMERAMANAGER->getScreen().left, _scroll.y + CAMERAMANAGER->getScreen().top, _scroll.currentFrameX, _scroll.currentFrameY, _scroll.alpha);
	_ui->render();

	D2DMANAGER->FillRectangle(_backGroundBoss.rc, D2D1COLOR::Black, _backGroundBoss.alpha);
	//���۽� ���İ�
	D2DMANAGER->FillRectangle(_alpha.rc, D2D1COLOR::Black, _alpha.alpha);

}
//Tile �ҷ�����
void dungeon::load(tagTile* tile, const char*   strKey)
{
	HANDLE file;
	DWORD read;

	char str[256];
	char dir[256];
	ZeroMemory(dir, sizeof(dir));
	GetCurrentDirectory(256, str);

	sprintf_s(dir, "\\%s.map", strKey);
	strncat_s(str, 256, dir, 254);

	file = CreateFile(str, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, tile, sizeof(tagTile)*DUNGEONTILEX*DUNGEONTILEY, &read, NULL);
	CloseHandle(file);
}
//�÷��̾� Ÿ��üũ
void dungeon::tileCheck()
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

		//���� �̵�
		//��
		if (IntersectRect(&rc, &_vZorder[i]->rc, &upLeft) && _player->getPlayer().direction == PLAYER_UP ||
			IntersectRect(&rc, &_vZorder[i]->rc, &upRight) && _player->getPlayer().direction == PLAYER_UP)
		{
			_player->setPlayerY((_vZorder[i]->rc.top + _vZorder[i]->rc.bottom) / 2 + _player->getPlayer().img->getFrameHeight() - 26);
		}
		//�Ʒ�
		if (IntersectRect(&rc, &_vZorder[i]->rc, &downLeft) && _player->getPlayer().direction == PLAYER_DOWN ||
			IntersectRect(&rc, &_vZorder[i]->rc, &downRight) && _player->getPlayer().direction == PLAYER_DOWN)
		{
			_player->setPlayerY((_vZorder[i]->rc.top + _vZorder[i]->rc.bottom) / 2 - _player->getPlayer().img->getFrameHeight() + 7);
		}
		//����
		if (IntersectRect(&rc, &_vZorder[i]->rc, &leftUp) && _player->getPlayer().direction == PLAYER_LEFT ||
			IntersectRect(&rc, &_vZorder[i]->rc, &leftDown) && _player->getPlayer().direction == PLAYER_LEFT)
		{
			_player->setPlayerX((_vZorder[i]->rc.left + _vZorder[i]->rc.right) / 2 + _player->getPlayer().img->getFrameWidth() - 3);
		}
		//������
		if (IntersectRect(&rc, &_vZorder[i]->rc, &rightUp) && _player->getPlayer().direction == PLAYER_RIGHT ||
			IntersectRect(&rc, &_vZorder[i]->rc, &rightDown) && _player->getPlayer().direction == PLAYER_RIGHT)
		{
			_player->setPlayerX((_vZorder[i]->rc.left + _vZorder[i]->rc.right) / 2 - _player->getPlayer().img->getFrameWidth() + 3);
		}

		//�밢�� �̵�
		//���� ����
		//���� �� �밢��
		if (IntersectRect(&rc, &_vZorder[i]->rc, &leftDown) && _player->getPlayer().direction == PLAYER_LEFTUP)
		{
			_player->setPlayerX((_vZorder[i]->rc.left + _vZorder[i]->rc.right) / 2 + _player->getPlayer().img->getFrameWidth() + 2);
		}
		//������ �� �밢��
		if (IntersectRect(&rc, &_vZorder[i]->rc, &rightDown) && _player->getPlayer().direction == PLAYER_RIGHTUP)
		{
			_player->setPlayerX((_vZorder[i]->rc.left + _vZorder[i]->rc.right) / 2 - _player->getPlayer().img->getFrameWidth() - 2);
		}
		//���� �Ʒ� �밢��
		if (IntersectRect(&rc, &_vZorder[i]->rc, &leftDown) && _player->getPlayer().direction == PLAYER_LEFTDOWN)
		{
			_player->setPlayerX((_vZorder[i]->rc.left + _vZorder[i]->rc.right) / 2 + _player->getPlayer().img->getFrameWidth() + 4);
		}
		//������ �Ʒ� �밢��
		if (IntersectRect(&rc, &_vZorder[i]->rc, &rightDown) && _player->getPlayer().direction == PLAYER_RIGHTDOWN)
		{
			_player->setPlayerX((_vZorder[i]->rc.left + _vZorder[i]->rc.right) / 2 - _player->getPlayer().img->getFrameWidth() - 3);
		}

		//���α���
		//���� �� �밢��
		if (IntersectRect(&rc, &_vZorder[i]->rc, &upLeft) && _player->getPlayer().direction == PLAYER_LEFTUP)
		{
			_player->setPlayerY((_vZorder[i]->rc.top + _vZorder[i]->rc.bottom) / 2 + _player->getPlayer().img->getFrameHeight() / 2 - 4);
		}
		//������ �� �밢��
		if (IntersectRect(&rc, &_vZorder[i]->rc, &upLeft) && _player->getPlayer().direction == PLAYER_RIGHTUP)
		{
			_player->setPlayerY((_vZorder[i]->rc.top + _vZorder[i]->rc.bottom) / 2 + _player->getPlayer().img->getFrameHeight() / 2 - 4);
		}
		//���� �Ʒ� �밢��
		if (IntersectRect(&rc, &_vZorder[i]->rc, &downLeft) && _player->getPlayer().direction == PLAYER_LEFTDOWN)
		{
			_player->setPlayerY((_vZorder[i]->rc.top + _vZorder[i]->rc.bottom) / 2 - _player->getPlayer().img->getFrameHeight() + 7);
		}
		//������ �Ʒ� �밢��
		if (IntersectRect(&rc, &_vZorder[i]->rc, &downLeft) && _player->getPlayer().direction == PLAYER_RIGHTDOWN)
		{
			_player->setPlayerY((_vZorder[i]->rc.top + _vZorder[i]->rc.bottom) / 2 - _player->getPlayer().img->getFrameHeight() + 7);
		}
	}
}

void dungeon::enemyTileCheck()
{
	for (int j = 0; j < _slime->getSlime().size(); ++j)
	{
		if (CAMERAMANAGER->getScreen().left - TILESIZE <= _slime->getSlime()[j].rc.left && CAMERAMANAGER->getScreen().right + TILESIZE >= _slime->getSlime()[j].rc.right &&
			CAMERAMANAGER->getScreen().top - TILESIZE <= _slime->getSlime()[j].rc.top && CAMERAMANAGER->getScreen().bottom + TILESIZE >= _slime->getSlime()[j].rc.bottom)
		{

			RECT rc;
			RECT upLeft = _slime->getSlime()[j].upLeft;
			RECT upRight = _slime->getSlime()[j].upRight;
			RECT downLeft = _slime->getSlime()[j].downLeft;
			RECT downRight = _slime->getSlime()[j].downRight;
			RECT leftUp = _slime->getSlime()[j].leftUp;
			RECT leftDown = _slime->getSlime()[j].leftDown;
			RECT rightUp = _slime->getSlime()[j].rightUp;
			RECT rightDown = _slime->getSlime()[j].rightDown;

			for (int i = 0; i < _vZorder.size(); ++i)
			{
				if (_vZorder[i]->obj != OBJ_NOTMOVE) continue;

				//���� �̵�
				//��
				if (IntersectRect(&rc, &_vZorder[i]->rc, &upLeft) || IntersectRect(&rc, &_vZorder[i]->rc, &upRight))
				{
					_slime->setSlimeY(j, (_vZorder[i]->rc.top + _vZorder[i]->rc.bottom) / 2 + _slime->getSlime()[j].img->getFrameHeight() - 30);
				}
				//�Ʒ�
				if (IntersectRect(&rc, &_vZorder[i]->rc, &downLeft) ||
					IntersectRect(&rc, &_vZorder[i]->rc, &downRight))
				{
					_slime->setSlimeY(j, (_vZorder[i]->rc.top + _vZorder[i]->rc.bottom) / 2 - _slime->getSlime()[j].img->getFrameHeight());
				}
				//����
				if (IntersectRect(&rc, &_vZorder[i]->rc, &leftUp) ||
					IntersectRect(&rc, &_vZorder[i]->rc, &leftDown))
				{
					_slime->setSlimeX(j, (_vZorder[i]->rc.left + _vZorder[i]->rc.right) / 2 + _slime->getSlime()[j].img->getFrameWidth());
				}
				//������
				if (IntersectRect(&rc, &_vZorder[i]->rc, &rightUp) ||
					IntersectRect(&rc, &_vZorder[i]->rc, &rightDown))
				{
					_slime->setSlimeX(j, (_vZorder[i]->rc.left + _vZorder[i]->rc.right) / 2 - _slime->getSlime()[j].img->getFrameWidth());
				}

				//�밢�� �̵�
				//���� ����
				//���� �� �밢��
				if (IntersectRect(&rc, &_vZorder[i]->rc, &leftDown))
				{
					_slime->setSlimeX(j, (_vZorder[i]->rc.left + _vZorder[i]->rc.right) / 2 + _slime->getSlime()[j].img->getFrameWidth());
				}
				//������ �� �밢��
				if (IntersectRect(&rc, &_vZorder[i]->rc, &rightDown))
				{
					_slime->setSlimeX(j, (_vZorder[i]->rc.left + _vZorder[i]->rc.right) / 2 - _slime->getSlime()[j].img->getFrameWidth());
				}
				//���� �Ʒ� �밢��
				if (IntersectRect(&rc, &_vZorder[i]->rc, &leftDown))
				{
					_slime->setSlimeX(j, (_vZorder[i]->rc.left + _vZorder[i]->rc.right) / 2 + _slime->getSlime()[j].img->getFrameWidth());
				}
				//������ �Ʒ� �밢��
				if (IntersectRect(&rc, &_vZorder[i]->rc, &rightDown))
				{
					_slime->setSlimeX(j, (_vZorder[i]->rc.left + _vZorder[i]->rc.right) / 2 - _slime->getSlime()[j].img->getFrameWidth());
				}

				//���α���
				//���� �� �밢��
				if (IntersectRect(&rc, &_vZorder[i]->rc, &upLeft))
				{
					_slime->setSlimeY(j, (_vZorder[i]->rc.top + _vZorder[i]->rc.bottom) / 2 + _slime->getSlime()[j].img->getFrameHeight());
				}
				//������ �� �밢��
				if (IntersectRect(&rc, &_vZorder[i]->rc, &upLeft))
				{
					_slime->setSlimeY(j, (_vZorder[i]->rc.top + _vZorder[i]->rc.bottom) / 2 + _slime->getSlime()[j].img->getFrameHeight());
				}
				//���� �Ʒ� �밢��
				if (IntersectRect(&rc, &_vZorder[i]->rc, &downLeft))
				{
					_slime->setSlimeY(j, (_vZorder[i]->rc.top + _vZorder[i]->rc.bottom) / 2 - _slime->getSlime()[j].img->getFrameHeight());
				}
				//������ �Ʒ� �밢��
				if (IntersectRect(&rc, &_vZorder[i]->rc, &downLeft))
				{
					_slime->setSlimeY(j, (_vZorder[i]->rc.top + _vZorder[i]->rc.bottom) / 2 - _slime->getSlime()[j].img->getFrameHeight());
				}
			}
		}
	}
}

void dungeon::poolCollision()
{
	RECT temp;
	RECT playerRc = _player->getPlayer().rc;
	if (IntersectRect(&temp, &_poolCollision.rc, &playerRc))
	{
		if (_poolCollision.rc.left < _player->getPlayer().rc.left && _poolCollision.rc.right > _player->getPlayer().rc.right &&
			_poolCollision.rc.top < _player->getPlayer().rc.top && _poolCollision.rc.bottom > _player->getPlayer().rc.bottom)
		{

			_player->setPlayerState(PLAYER_SWIM);
			if (_player->getPlayer().currentHp <= _player->getPlayer().maxHp) _player->setPlayerCurrentHp(_player->getPlayer().currentHp + 0.1f);
		}
		else _player->setPlayerState(PLAYER_WALK);
	}
}
//�̴ϸ� ����
void dungeon::miniMap()
{
	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		if (!_isMiniMapInvisible)_isMiniMapInvisible = true;
		else if (_isMiniMapInvisible)_isMiniMapInvisible = false;
	}

	//�̴ϸ� ��Ʈ ������Ʈ
	for (int i = 0; i < MAPMAX; i++)
	{
		_miniMap[i].rc = RectMakeCenter(_miniMap[i].x + CAMERAMANAGER->getScreen().left, _miniMap[i].y + CAMERAMANAGER->getScreen().top, _miniMap[i].img->getWidth(), _miniMap[i].img->getHeight());
	}
	_miniMapWill.rc = RectMakeCenter(_miniMapWill.x + CAMERAMANAGER->getScreen().left, _miniMapWill.y + CAMERAMANAGER->getScreen().top, _miniMapWill.img->getWidth(), _miniMapWill.img->getHeight());
	_miniMapPool.rc = RectMakeCenter(_miniMapPool.x + CAMERAMANAGER->getScreen().left, _miniMapPool.y + CAMERAMANAGER->getScreen().top, _miniMapPool.img->getWidth(), _miniMapPool.img->getHeight());
	_minimapBack.rc = RectMakeCenter(_minimapBack.x + CAMERAMANAGER->getScreen().left, _minimapBack.y + CAMERAMANAGER->getScreen().top, 400, 250);

}

void dungeon::playerCollision()
{

	RECT temp;
	RECT playerRc = _player->getPlayer().rc;
	RECT miniBossRc = _miniBoss->getMiniBoss().attackRc;
	RECT miniBoss2Rc = _miniBoss->getMiniBoss().attack2Rc;
	RECT bossRC1 = _boss->getBossArm().rc;
	RECT bossRC2 = _boss->getBoss().attackRc2;

	for (int i = 0; i < _slime->getSlime().size(); ++i)
	{
		//�÷��̾� - ������ �ǰݽ�
		if (IntersectRect(&temp, &playerRc, &_slime->getSlime()[i].powerRect) && !_playerHitTime)
		{
			_player->setPlayerCurrentHp(_player->getPlayer().currentHp - _slime->getSlime()[i].power);
			_playerHitTime = true;
			_playerHit = true;
		}
	}
	//�÷��̾� - �̴Ϻ��� �ǰݽ�
	if (IntersectRect(&temp, &playerRc, &miniBossRc) && !_playerHitTime)
	{
		_player->setPlayerCurrentHp(_player->getPlayer().currentHp - _miniBoss->getMiniBoss().power);
		_playerHitTime = true;
		_playerHit = true;
	}
	//�÷��̾� - �̴Ϻ��� �ǰݽ�
	if (IntersectRect(&temp, &playerRc, &miniBoss2Rc) && !_playerHitTime)
	{
		_player->setPlayerCurrentHp(_player->getPlayer().currentHp - _miniBoss->getMiniBoss().power);
		_playerHitTime = true;
		_playerHit = true;
	}
	//�÷��̾� - ���� �ǰݽ�
	if (IntersectRect(&temp, &playerRc, &bossRC1) && !_playerHitTime)
	{
		_player->setPlayerCurrentHp(_player->getPlayer().currentHp - _boss->getBoss().power);
		_playerHitTime = true;
		_playerHit = true;
	}

	//�÷��̾� - ���� �ǰݽ�
	if (IntersectRect(&temp, &playerRc, &bossRC2) && !_playerHitTime)
	{
		_player->setPlayerCurrentHp(_player->getPlayer().currentHp - _boss->getBoss().power);
		_playerHitTime = true;
		_playerHit = true;
	}

	//�÷��̾� �ǰݽ� ������
	if (_playerHitTime)
	{

		_playerHitCount++;
		if (_playerHitCount == 1) SOUNDMANAGER->play("WillHitSound");
		if (_playerHitCount % 5 == 0)
		{

			_playerHit = false;
		}
		if (_playerHitCount % 10 == 0)
		{
			_playerHit = true;
		}
		if (_playerHitCount >= 60)
		{
			_playerHit = false;
			_playerHitTime = false;
			_playerHitCount = 0;
			SOUNDMANAGER->stop("WillHitSound");
		}
	}
}

void dungeon::enemyCollision()
{
	RECT temp;
	RECT playerRc = _player->getPlayer().attackRect;
	RECT miniBossRc = _miniBoss->getMiniBoss().hitRc;

	for (int i = 0; i < _slime->getSlime().size(); ++i)
	{
		//������ �ǰݽ�
		if (IntersectRect(&temp, &playerRc, &_slime->getSlime()[i].hitRc) && !_slime->getSlime()[i].enemyHitTime)
		{
			_slime->setSlimeCurrentHp(i, _slime->getSlime()[i].currentHp - _player->getPlayer().power);
			_slime->setEnemyHitTime(i, true);
			_slime->setEnemyHit(i, true);
			////������ ȹ��
			if (_slime->getSlime()[i].currentHp <= 0)
			{
				_huntSlime++;
				//������ Item_Count ����
				int itemNumRand = RND->getFromIntTo(0, 4);
				for (int j = 0; j < itemNumRand; ++j)
				{
					//������ ���� ����
					int itemKindRand = RND->getFromIntTo(0, 9);
					tagItemGet itemGet;
					switch (itemKindRand)
					{
					case 0:
						itemGet.img = IMAGEMANAGER->findDImage("Life_Water");
						itemGet.rand = RND->getFromIntTo(0, 4);
						itemGet.count = 0;
						itemGet.angle = RND->getFromFloatTo(0, PI);
						itemGet.x = _slime->getSlime()[i].x;
						itemGet.y = _slime->getSlime()[i].y;
						itemGet.name = "Life_Water";
						itemGet.rc = RectMakeCenter(itemGet.x, itemGet.y, itemGet.img->getWidth(), itemGet.img->getHeight());
						break;
					case 1:
						itemGet.img = IMAGEMANAGER->findDImage("Golem_core");
						itemGet.rand = RND->getFromIntTo(0, 4);
						itemGet.count = 0;
						itemGet.angle = RND->getFromFloatTo(0, PI);
						itemGet.x = _slime->getSlime()[i].x;
						itemGet.y = _slime->getSlime()[i].y;
						itemGet.name = "Golem_core";
						itemGet.rc = RectMakeCenter(itemGet.x, itemGet.y, itemGet.img->getWidth(), itemGet.img->getHeight());
						break;
					case 2:
						itemGet.img = IMAGEMANAGER->findDImage("blueprint");
						itemGet.rand = RND->getFromIntTo(0, 4);
						itemGet.count = 0;
						itemGet.angle = RND->getFromFloatTo(0, PI);
						itemGet.x = _slime->getSlime()[i].x;
						itemGet.y = _slime->getSlime()[i].y;
						itemGet.name = "blueprint";
						itemGet.rc = RectMakeCenter(itemGet.x, itemGet.y, itemGet.img->getWidth(), itemGet.img->getHeight());
						break;
					case 3:
						itemGet.img = IMAGEMANAGER->findDImage("Break_Sword");
						itemGet.rand = RND->getFromIntTo(0, 4);
						itemGet.count = 0;
						itemGet.angle = RND->getFromFloatTo(0, PI);
						itemGet.x = _slime->getSlime()[i].x;
						itemGet.y = _slime->getSlime()[i].y;
						itemGet.name = "Break_Sword";
						itemGet.rc = RectMakeCenter(itemGet.x, itemGet.y, itemGet.img->getWidth(), itemGet.img->getHeight());
						break;
					case 4:
						itemGet.img = IMAGEMANAGER->findDImage("Crystal");
						itemGet.rand = RND->getFromIntTo(0, 4);
						itemGet.count = 0;
						itemGet.angle = RND->getFromFloatTo(0, PI);
						itemGet.x = _slime->getSlime()[i].x;
						itemGet.y = _slime->getSlime()[i].y;
						itemGet.name = "Crystal";
						itemGet.rc = RectMakeCenter(itemGet.x, itemGet.y, itemGet.img->getWidth(), itemGet.img->getHeight());
						break;
					case 5:
						itemGet.img = IMAGEMANAGER->findDImage("History_Book");
						itemGet.rand = RND->getFromIntTo(0, 4);
						itemGet.count = 0;
						itemGet.angle = RND->getFromFloatTo(0, PI);
						itemGet.x = _slime->getSlime()[i].x;
						itemGet.y = _slime->getSlime()[i].y;
						itemGet.name = "History_Book";
						itemGet.rc = RectMakeCenter(itemGet.x, itemGet.y, itemGet.img->getWidth(), itemGet.img->getHeight());
						break;
					case 6:
						itemGet.img = IMAGEMANAGER->findDImage("Note");
						itemGet.rand = RND->getFromIntTo(0, 4);
						itemGet.count = 0;
						itemGet.angle = RND->getFromFloatTo(0, PI);
						itemGet.x = _slime->getSlime()[i].x;
						itemGet.y = _slime->getSlime()[i].y;
						itemGet.name = "Note";
						itemGet.rc = RectMakeCenter(itemGet.x, itemGet.y, itemGet.img->getWidth(), itemGet.img->getHeight());
						break;
					case 7:
						itemGet.img = IMAGEMANAGER->findDImage("Steel");
						itemGet.rand = RND->getFromIntTo(0, 4);
						itemGet.count = 0;
						itemGet.angle = RND->getFromFloatTo(0, PI);
						itemGet.x = _slime->getSlime()[i].x;
						itemGet.y = _slime->getSlime()[i].y;
						itemGet.name = "Steel";
						itemGet.rc = RectMakeCenter(itemGet.x, itemGet.y, itemGet.img->getWidth(), itemGet.img->getHeight());
						break;
					case 8:
						itemGet.img = IMAGEMANAGER->findDImage("Straw");
						itemGet.rand = RND->getFromIntTo(0, 4);
						itemGet.count = 0;
						itemGet.angle = RND->getFromFloatTo(0, PI);
						itemGet.x = _slime->getSlime()[i].x;
						itemGet.y = _slime->getSlime()[i].y;
						itemGet.name = "Straw";
						itemGet.rc = RectMakeCenter(itemGet.x, itemGet.y, itemGet.img->getWidth(), itemGet.img->getHeight());
						break;
					case 9:
						itemGet.img = IMAGEMANAGER->findDImage("Electronic_Line");
						itemGet.rand = RND->getFromIntTo(0, 4);
						itemGet.count = 0;
						itemGet.angle = RND->getFromFloatTo(0, PI);
						itemGet.x = _slime->getSlime()[i].x;
						itemGet.y = _slime->getSlime()[i].y;
						itemGet.name = "Electronic_Line";
						itemGet.rc = RectMakeCenter(itemGet.x, itemGet.y, itemGet.img->getWidth(), itemGet.img->getHeight());
						break;
					}

					_vitemGet.push_back(itemGet);

				}
			}
		}
	}
	for (int i = 0; i < _slime->getSlime().size(); ++i)
	{
		//������ �ǰݽ� ������
		if (_slime->getSlime()[i].enemyHitTime)
		{
			_slime->setEnemyHitCount(i, _slime->getSlime()[i].enemyHitCount + 1);
			if (_slime->getSlime()[i].enemyHitCount % 3 == 0)
			{
				_slime->setEnemyHit(i, false);
			}
			if (_slime->getSlime()[i].enemyHitCount % 6 == 0)
			{
				_slime->setEnemyHit(i, true);
			}
			if (_slime->getSlime()[i].enemyHitCount >= 20)
			{
				_slime->setEnemyHit(i, false);
				_slime->setEnemyHitTime(i, false);
				_slime->setEnemyHitCount(i, 0);
			}
		}
	}

	//�̴Ϻ��� �ǰݽ�
	if (IntersectRect(&temp, &playerRc, &miniBossRc) && !_miniBoss->getMiniBoss().enemyHitTime)
	{
		_miniBoss->setMiniBossCurrentHp(_miniBoss->getMiniBoss().currentHp - _player->getPlayer().power);
		_miniBoss->setMiniBossEnemyHit(true);
		_miniBoss->setMiniBossEnemyHitTime(true);
		if (_miniBoss->getMiniBoss().currentHp <= 0)
		{
			_huntMiniBoss++;
			EFFECTMANAGER->play("Effect1", _miniBoss->getMiniBoss().x, _miniBoss->getMiniBoss().y, 1);
			EFFECTMANAGER->play("Effect1", _bossDoor.x, _bossDoor.y, 1);
			SOUNDMANAGER->play("MiniBossDeathSound");
			_isBossDoor = true;

			_bossDoor.rc = RectMakeCenter(_bossDoor.x, _bossDoor.y, _bossDoor.img->getWidth(), _bossDoor.img->getHeight());
		}
	}


	//�̴Ϻ��� �ǰݽ� ������
	if (_miniBoss->getMiniBoss().enemyHitTime)
	{
		_miniBoss->setMiniBossEnemyHitCount(_miniBoss->getMiniBoss().enemyHitCount + 1);
		if (_miniBoss->getMiniBoss().enemyHitCount % 3 == 0)
		{
			_miniBoss->setMiniBossEnemyHit(false);
		}
		if (_miniBoss->getMiniBoss().enemyHitCount % 6 == 0)
		{
			_miniBoss->setMiniBossEnemyHit(true);
		}
		if (_miniBoss->getMiniBoss().enemyHitCount >= 20)
		{
			_miniBoss->setMiniBossEnemyHit(false);
			_miniBoss->setMiniBossEnemyHitTime(false);
			_miniBoss->setMiniBossEnemyHitCount(0);
		}
	}

}
//������ �浹
void dungeon::itemCollision()
{
	RECT temp;
	RECT playerRc = _player->getPlayer().itemRc;
	for (int i = 0; i < _vitemGet.size(); ++i)
	{
		if (IntersectRect(&temp, &playerRc, &_vitemGet[i].rc) && _vitemGet[i].count > 60)
		{
			_ui->itemGet(_vitemGet[i].name);
			_vitemGet.erase(_vitemGet.begin() + i);
		}
	}
}

void dungeon::bossDoor()
{
	//�غ����濡�� �����̵��Ҷ�
	RECT temp;
	RECT playerRc = _player->getPlayer().rc;
	if (IntersectRect(&temp, &playerRc, &_bossDoor.rc))
	{
		SOUNDMANAGER->stop("DungeonBackgroundMusic");
		SOUNDMANAGER->play("BossBackgroundMusic");
		_player->setPlayerX(_backGroundBoss.x);
		_player->setPlayerY(_backGroundBoss.y + 210);
		_isBossCamera = true;
	}


}

void dungeon::bossRoomCollision()
{
	RECT temp;
	RECT playerRc = _player->getPlayer().rc;
	RECT bossHitRc = _boss->getBoss().hitRc;
	//������ �浹ó��
	if (IntersectRect(&temp, &playerRc, &_backGroundBoss.rc))
	{

		_backGroundBoss.alpha -= 0.01f;
		if (_backGroundBoss.alpha <= 0) _backGroundBoss.alpha = 0;

		//�÷��̾� ��ġ ����ó��(��)
		if (_backGroundBoss.rc.left + _differenceX - 20 >= _player->getPlayer().rc.left)
			_player->setPlayerX(_backGroundBoss.rc.left + _differenceX + _player->getPlayer().img->getFrameWidth() / 2 - 20);

		if (_backGroundBoss.rc.right - _differenceX + 20 <= _player->getPlayer().rc.right)
			_player->setPlayerX(_backGroundBoss.rc.right - _differenceX - _player->getPlayer().img->getFrameWidth() / 2 + 20);

		if (_backGroundBoss.rc.top + _differenceY + 140 >= _player->getPlayer().rc.top)
			_player->setPlayerY(_backGroundBoss.rc.top + _differenceY + _player->getPlayer().img->getFrameHeight() / 2 + 140);

		if (_backGroundBoss.rc.bottom - _differenceY + 5 <= _player->getPlayer().rc.bottom)
			_player->setPlayerY(_backGroundBoss.rc.bottom - _differenceY - _player->getPlayer().img->getFrameHeight() / 2 + 5);
	}

}

void dungeon::bossCollision()
{
	RECT temp;
	RECT playerRc = _player->getPlayer().attackRect;
	RECT bossHitRc = _boss->getBoss().hitRc;
	if (IntersectRect(&temp, &playerRc, &bossHitRc) && !_boss->getBoss().enemyHitTime)
	{
		_boss->setBossCurrentHp(_boss->getBoss().currentHp - _player->getPlayer().power);
		_boss->setBossEnemyHit(true);
		_boss->setBossEnemyHitTime(true);
	}

	//���� �ǰݽ� ������
	if (_boss->getBoss().enemyHitTime)
	{
		_boss->setBossEnemyHitCount(_boss->getBoss().enemyHitCount + 1);
		if (_boss->getBoss().enemyHitCount % 3 == 0)
		{
			_boss->setBossEnemyHit(false);
		}
		if (_boss->getBoss().enemyHitCount % 6 == 0)
		{
			_boss->setBossEnemyHit(true);
		}
		if (_boss->getBoss().enemyHitCount >= 20)
		{
			_boss->setBossEnemyHit(false);
			_boss->setBossEnemyHitTime(false);
			_boss->setBossEnemyHitCount(0);
		}
	}
	//���� - �÷��̾� ������ �浹ó��
	RECT rc;
	RECT bossRc = _boss->getBoss().hitRc;
	RECT upLeft = _player->getPlayer().upLeft;
	RECT upRight = _player->getPlayer().upRight;
	RECT downLeft = _player->getPlayer().downLeft;
	RECT downRight = _player->getPlayer().downRight;
	RECT leftUp = _player->getPlayer().leftUp;
	RECT leftDown = _player->getPlayer().leftDown;
	RECT rightUp = _player->getPlayer().rightUp;
	RECT rightDown = _player->getPlayer().rightDown;

	//���� ��
	if (IntersectRect(&rc, &bossRc, &upLeft) && _player->getPlayer().direction == PLAYER_UP ||
		IntersectRect(&rc, &bossRc, &upRight) && _player->getPlayer().direction == PLAYER_UP)
	{
		_player->setPlayerY(bossRc.bottom + _player->getPlayer().img->getFrameHeight() / 2 - 20);
	}
	//���� �Ʒ�
	if (IntersectRect(&rc, &bossRc, &downLeft) && _player->getPlayer().direction == PLAYER_DOWN ||
		IntersectRect(&rc, &bossRc, &downRight) && _player->getPlayer().direction == PLAYER_DOWN)
	{
		_player->setPlayerY(bossRc.top - _player->getPlayer().img->getFrameHeight() / 2);
	}
	//����
	if (IntersectRect(&rc, &bossRc, &leftUp) && _player->getPlayer().direction == PLAYER_LEFT ||
		IntersectRect(&rc, &bossRc, &leftDown) && _player->getPlayer().direction == PLAYER_LEFT)
	{
		_player->setPlayerX(bossRc.right + _player->getPlayer().img->getFrameWidth() / 2);
	}
	//������
	if (IntersectRect(&rc, &bossRc, &rightUp) && _player->getPlayer().direction == PLAYER_RIGHT ||
		IntersectRect(&rc, &bossRc, &rightDown) && _player->getPlayer().direction == PLAYER_RIGHT)
	{
		_player->setPlayerX(bossRc.left - _player->getPlayer().img->getFrameWidth() / 2);
	}
	//�밢�� �̵�
		//���� ����
		//���� �� �밢��
	if (IntersectRect(&rc, &bossRc, &leftDown) && _player->getPlayer().direction == PLAYER_LEFTUP)
	{
		_player->setPlayerX(bossRc.right + _player->getPlayer().img->getFrameWidth() / 2);
	}
	//������ �� �밢��
	if (IntersectRect(&rc, &bossRc, &rightDown) && _player->getPlayer().direction == PLAYER_RIGHTUP)
	{
		_player->setPlayerX(bossRc.left - _player->getPlayer().img->getFrameWidth() / 2);
	}
	//���� �Ʒ� �밢��
	if (IntersectRect(&rc, &bossRc, &leftDown) && _player->getPlayer().direction == PLAYER_LEFTDOWN)
	{
		_player->setPlayerX(bossRc.right + _player->getPlayer().img->getFrameWidth() / 2);
	}
	//������ �Ʒ� �밢��
	if (IntersectRect(&rc, &bossRc, &rightDown) && _player->getPlayer().direction == PLAYER_RIGHTDOWN)
	{
		_player->setPlayerX(bossRc.left - _player->getPlayer().img->getFrameWidth() / 2);
	}

	//���α���
	//���� �� �밢��
	if (IntersectRect(&rc, &bossRc, &upLeft) && _player->getPlayer().direction == PLAYER_LEFTUP)
	{
		_player->setPlayerY(bossRc.bottom + _player->getPlayer().img->getFrameHeight() / 2 - 20);
	}
	//������ �� �밢��
	if (IntersectRect(&rc, &bossRc, &upLeft) && _player->getPlayer().direction == PLAYER_RIGHTUP)
	{
		_player->setPlayerY(bossRc.bottom + _player->getPlayer().img->getFrameHeight() / 2 - 20);
	}
	//���� �Ʒ� �밢��
	if (IntersectRect(&rc, &bossRc, &downLeft) && _player->getPlayer().direction == PLAYER_LEFTDOWN)
	{
		_player->setPlayerY(bossRc.top - _player->getPlayer().img->getFrameHeight() / 2);
	}
	//������ �Ʒ� �밢��
	if (IntersectRect(&rc, &bossRc, &downLeft) && _player->getPlayer().direction == PLAYER_RIGHTDOWN)
	{
		_player->setPlayerY(bossRc.top - _player->getPlayer().img->getFrameHeight() / 2);
	}
}

//Ž������
void dungeon::dungeonReturn()
{
	//��ȯ ���Ʈ����
	if (_returnPotalRect.width <= 0) _returnPotalRect.width = 0;
	if (_returnPotalRect.width >= 60) _returnPotalRect.width = 60;
	_returnPotalRect.width -= 0.5f;
	_returnPotalRect.baseRc = RectMake(_returnPotalRect.x - 5 + CAMERAMANAGER->getScreen().left, _returnPotalRect.y + CAMERAMANAGER->getScreen().top - 15, 60, 10);
	_returnPotalRect.rc = RectMake(_returnPotalRect.x - 5 + CAMERAMANAGER->getScreen().left, _returnPotalRect.y + CAMERAMANAGER->getScreen().top - 15, _returnPotalRect.width, 10);
	_returnLbutton.rc = RectMake(_returnLbutton.x + CAMERAMANAGER->getScreen().left, _returnLbutton.y + CAMERAMANAGER->getScreen().top, _returnLbutton.img->getWidth(), _returnLbutton.img->getHeight());
	//��ȯ ����(L_Button ������ ��ȯ)
	if (KEYMANAGER->isStayKeyDown('L'))
	{
		_returnPotalRect.width++;
		if (_returnPotalRect.width >= 60)_ui->setResultCheck(true);
	}
	//�÷��̾� or ������ ü���� 0�̰� ��� �̹��� �������� ������ ��ȯ
	if (_player->getPlayer().currentHp <= 0 && _player->getPlayer().currentFrameX == _player->getPlayer().img->getMaxFrameX())_ui->setResultCheck(true);
	if (_boss->getBoss().currentHp <= 0 && _boss->getBoss().currentFrameX == _boss->getBoss().img->getMaxFrameX() && _boss->getBoss().currentFrameY == _boss->getBoss().img->getMaxFrameY())
		_ui->setResultCheck(true);
	if (_ui->getResultCheck() && KEYMANAGER->isOnceKeyDown('K')) SCENEMANAGER->changeScene("village");
	_ui->huntEnemy(_huntSlime, _huntMiniBoss);
}

//������ �̵�
void dungeon::itemMove()
{
	//������ ���� �� ī��Ʈ�� ���� ������ �ٲپ� �������� ��ó�� ǥ��
	for (int i = 0; i < _vitemGet.size(); ++i)
	{
		if (_vitemGet[i].count < 100)_vitemGet[i].count++;

		if (_vitemGet[i].count <= 30)
		{
			_vitemGet[i].x += cosf(_vitemGet[i].angle) * 1.5f;
			_vitemGet[i].y += -sinf(_vitemGet[i].angle) * 1.5f;
		}
		if (_vitemGet[i].count <= 60 && _vitemGet[i].count > 30)
		{
			_vitemGet[i].x += cosf(PI2 - _vitemGet[i].angle) * 1;
			_vitemGet[i].y += -sinf(PI2 - _vitemGet[i].angle) * 1;
		}
		//�����۰� �÷��̾��� RECT�� �浹 �� �������� �÷��� ������ �����δ�.
		RECT temp;
		RECT playerRc = _player->getPlayer().rc;
		if (_vitemGet[i].count > 60 && IntersectRect(&temp, &playerRc, &_vitemGet[i].rc))
		{
			_vitemGet[i].angle = getAngle(_vitemGet[i].x, _vitemGet[i].y, _player->getPlayer().x, _player->getPlayer().y);
			_vitemGet[i].x += cosf(_vitemGet[i].angle) *0.7f;
			_vitemGet[i].y += -sinf(_vitemGet[i].angle) * 0.7f;
		}


		_vitemGet[i].rc = RectMakeCenter(_vitemGet[i].x, _vitemGet[i].y, _vitemGet[i].img->getWidth(), _vitemGet[i].img->getHeight());

	}
}
