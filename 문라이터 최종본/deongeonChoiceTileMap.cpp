#include "stdafx.h"
#include "deongeonChoiceTileMap.h"

deongeonChoiceTileMap::deongeonChoiceTileMap()
{
}

deongeonChoiceTileMap::~deongeonChoiceTileMap()
{
}

HRESULT deongeonChoiceTileMap::init()
{
	//카메라 사이즈 설정
	CAMERAMANAGER->setBackScreenSize(1300, 1066);
	CAMERAMANAGER->setZoom(2);

	//타일의 이미지 추가
	IMAGEMANAGER->addFrameDImage("VilageTileFrame", L"Tile/HouseTile_20_10.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("VilageObject1_Frame", L"Tile/Vilage_Object1.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("Vilage_House_Frame", L"Tile/Vilage_House.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("Vilage_House2_Frame", L"Tile/Vilage_House2.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("Vilage_House3_Frame", L"Tile/Vilage_House3.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("DunGeonChoice", L"Tile/DunGeonChoice.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("HouseFrame", L"Tile/HouseFrame.png", 11395, 154, 53, 1);


	load();
	return S_OK;
}

void deongeonChoiceTileMap::release()
{
}

void deongeonChoiceTileMap::update()
{
}

void deongeonChoiceTileMap::render()
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
				IMAGEMANAGER->findDImage("VilageTileFrame")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			case 1:
				IMAGEMANAGER->findDImage("VilageObject1_Frame")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			case 2:
				IMAGEMANAGER->findDImage("Vilage_House_Frame")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			case 3:
				IMAGEMANAGER->findDImage("Vilage_House2_Frame")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			case 4:
				IMAGEMANAGER->findDImage("Vilage_House3_Frame")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			case 5:
				IMAGEMANAGER->findDImage("DunGeonChoice")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			}

			if (KEYMANAGER->isToggleKey(VK_NUMPAD0))
			{
				D2DMANAGER->DrawRectangle(_tiles[i].rc, D2DDEFAULTBRUSH::Yellow);

			}

		}
	}

}

void deongeonChoiceTileMap::objectRender()
{
	//오브젝트타일 이미지
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].obj == OBJ_BLOCK1)
		{
			if (CAMERAMANAGER->getScreen().left - (TILESIZE * 8) <= _tiles[i].rc.left && CAMERAMANAGER->getScreen().right + TILESIZE >= _tiles[i].rc.right &&
				CAMERAMANAGER->getScreen().top - (TILESIZE * 8) <= _tiles[i].rc.top && CAMERAMANAGER->getScreen().bottom + TILESIZE >= _tiles[i].rc.bottom)
			{

				switch (_tiles[i].pageObject)
				{
				case 0:
					IMAGEMANAGER->findDImage("VilageTileFrame")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
					break;
				case 1:
					IMAGEMANAGER->findDImage("VilageObject1_Frame")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
					break;
				case 2:
					IMAGEMANAGER->findDImage("Vilage_House_Frame")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
					break;
				case 3:
					IMAGEMANAGER->findDImage("Vilage_House2_Frame")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
					break;
				case 4:
					IMAGEMANAGER->findDImage("Vilage_House3_Frame")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
					break;
				case 5:
					IMAGEMANAGER->findDImage("DunGeonChoice")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
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

void deongeonChoiceTileMap::load()
{
	HANDLE file;
	DWORD read;


	file = CreateFile("DunGeonChoice.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile)*TILEX*TILEY, &read, NULL);
	CloseHandle(file);
}
