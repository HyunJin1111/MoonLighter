#include "stdafx.h"
#include "villageTileMap.h"

villageTileMap::villageTileMap()
{
}

villageTileMap::~villageTileMap()
{
}

HRESULT villageTileMap::init()
{
	//카메라 사이즈 설정
	CAMERAMANAGER->setBackScreenSize(1300, 1066);
	CAMERAMANAGER->setZoom(2);

	//타일의 이미지 추가
	IMAGEMANAGER->addFrameDImage("마을타일프레임", L"타일/마을타일_20_10.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("마을오브젝트1_프레임", L"타일/마을오브젝트1.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("마을_집_프레임", L"타일/마을_집.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("마을_집2_프레임", L"타일/마을_집2.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("마을_집3_프레임", L"타일/마을_집3.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("던전선택", L"타일/던전선택.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("나무1", L"타일/나무1.png", 1960, 72, 28, 1);
	IMAGEMANAGER->addFrameDImage("나무2", L"타일/나무2.png", 2450, 84, 35, 1);
	IMAGEMANAGER->addFrameDImage("나무4", L"타일/나무4.png", 5495, 174, 35, 1);
	IMAGEMANAGER->addFrameDImage("분수대", L"타일/분수대.png", 378, 46, 9, 1);
	IMAGEMANAGER->addFrameDImage("우물", L"타일/우물.png", 512, 81, 8, 1);
	IMAGEMANAGER->addFrameDImage("집프레임", L"타일/집프레임.png", 11395, 154, 53, 1);

	load();


	return S_OK;
}

void villageTileMap::release()
{

}

void villageTileMap::update()
{

}

void villageTileMap::render()
{
	//지형타일 이미지
	for (int i = 0; i < TILEX * TILEY; ++i)
	{

		if (CAMERAMANAGER->getScreen().left - TILESIZE <= _tiles[i].rc.left && CAMERAMANAGER->getScreen().right + TILESIZE >= _tiles[i].rc.right &&
			CAMERAMANAGER->getScreen().top - TILESIZE <= _tiles[i].rc.top && CAMERAMANAGER->getScreen().bottom + TILESIZE >= _tiles[i].rc.bottom)
		{
			switch (_tiles[i].pageTerrain)
			{
			case 0:
				IMAGEMANAGER->findDImage("마을타일프레임")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			case 1:
				IMAGEMANAGER->findDImage("마을오브젝트1_프레임")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			case 2:
				IMAGEMANAGER->findDImage("마을_집_프레임")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			case 3:
				IMAGEMANAGER->findDImage("마을_집2_프레임")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			case 4:
				IMAGEMANAGER->findDImage("마을_집3_프레임")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			case 5:
				IMAGEMANAGER->findDImage("던전선택")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			}

			if (KEYMANAGER->isToggleKey(VK_NUMPAD0))
			{
				D2DMANAGER->DrawRectangle(_tiles[i].rc, D2DDEFAULTBRUSH::Yellow);

			}

		}
	}



}

void villageTileMap::objectRender()
{
	//오브젝트타일 이미지
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].obj == OBJ_BLOCK1 && _tiles[i].imgAt == DEFAULT_IMAGE)
		{
			if (CAMERAMANAGER->getScreen().left - (TILESIZE * 8) <= _tiles[i].rc.left && CAMERAMANAGER->getScreen().right + TILESIZE >= _tiles[i].rc.right &&
				CAMERAMANAGER->getScreen().top - (TILESIZE * 8) <= _tiles[i].rc.top && CAMERAMANAGER->getScreen().bottom + TILESIZE >= _tiles[i].rc.bottom)
			{

				switch (_tiles[i].pageObject)
				{
				case 0:
					IMAGEMANAGER->findDImage("마을타일프레임")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
					break;
				case 1: 
					IMAGEMANAGER->findDImage("마을오브젝트1_프레임")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
					break;
				case 2:
					IMAGEMANAGER->findDImage("마을_집_프레임")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
					break;
				case 3:
					IMAGEMANAGER->findDImage("마을_집2_프레임")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
					break;
				case 4:
					IMAGEMANAGER->findDImage("마을_집3_프레임")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
					break;
				case 5:
					IMAGEMANAGER->findDImage("던전선택")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
					break;
				}

			}
		}
		if (_tiles[i].obj == OBJ_NOTMOVE && KEYMANAGER->isToggleKey(VK_NUMPAD0))
		{
			D2DMANAGER->DrawRectangle(_tiles[i].rc, D2DDEFAULTBRUSH::Blue);

		}
	}

}

void villageTileMap::load()
{
	HANDLE file;
	DWORD read;


	file = CreateFile("마을.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile)*TILEX*TILEY, &read, NULL);
	CloseHandle(file);
}
