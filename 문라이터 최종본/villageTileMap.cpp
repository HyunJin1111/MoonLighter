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
	//ī�޶� ������ ����
	CAMERAMANAGER->setBackScreenSize(1300, 1066);
	CAMERAMANAGER->setZoom(2);

	//Ÿ���� �̹��� �߰�
	IMAGEMANAGER->addFrameDImage("����Ÿ��������", L"Ÿ��/����Ÿ��_20_10.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("����������Ʈ1_������", L"Ÿ��/����������Ʈ1.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("����_��_������", L"Ÿ��/����_��.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("����_��2_������", L"Ÿ��/����_��2.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("����_��3_������", L"Ÿ��/����_��3.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("��������", L"Ÿ��/��������.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("����1", L"Ÿ��/����1.png", 1960, 72, 28, 1);
	IMAGEMANAGER->addFrameDImage("����2", L"Ÿ��/����2.png", 2450, 84, 35, 1);
	IMAGEMANAGER->addFrameDImage("����4", L"Ÿ��/����4.png", 5495, 174, 35, 1);
	IMAGEMANAGER->addFrameDImage("�м���", L"Ÿ��/�м���.png", 378, 46, 9, 1);
	IMAGEMANAGER->addFrameDImage("�칰", L"Ÿ��/�칰.png", 512, 81, 8, 1);
	IMAGEMANAGER->addFrameDImage("��������", L"Ÿ��/��������.png", 11395, 154, 53, 1);

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
	//����Ÿ�� �̹���
	for (int i = 0; i < TILEX * TILEY; ++i)
	{

		if (CAMERAMANAGER->getScreen().left - TILESIZE <= _tiles[i].rc.left && CAMERAMANAGER->getScreen().right + TILESIZE >= _tiles[i].rc.right &&
			CAMERAMANAGER->getScreen().top - TILESIZE <= _tiles[i].rc.top && CAMERAMANAGER->getScreen().bottom + TILESIZE >= _tiles[i].rc.bottom)
		{
			switch (_tiles[i].pageTerrain)
			{
			case 0:
				IMAGEMANAGER->findDImage("����Ÿ��������")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			case 1:
				IMAGEMANAGER->findDImage("����������Ʈ1_������")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			case 2:
				IMAGEMANAGER->findDImage("����_��_������")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			case 3:
				IMAGEMANAGER->findDImage("����_��2_������")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			case 4:
				IMAGEMANAGER->findDImage("����_��3_������")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			case 5:
				IMAGEMANAGER->findDImage("��������")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
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
	//������ƮŸ�� �̹���
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
					IMAGEMANAGER->findDImage("����Ÿ��������")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
					break;
				case 1: 
					IMAGEMANAGER->findDImage("����������Ʈ1_������")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
					break;
				case 2:
					IMAGEMANAGER->findDImage("����_��_������")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
					break;
				case 3:
					IMAGEMANAGER->findDImage("����_��2_������")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
					break;
				case 4:
					IMAGEMANAGER->findDImage("����_��3_������")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
					break;
				case 5:
					IMAGEMANAGER->findDImage("��������")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
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


	file = CreateFile("����.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile)*TILEX*TILEY, &read, NULL);
	CloseHandle(file);
}
