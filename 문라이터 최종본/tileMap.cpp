#include "stdafx.h"
#include "tileMap.h"


tileMap::tileMap()
{
}

tileMap::~tileMap()
{
}

HRESULT tileMap::init()
{
	SOUNDMANAGER->play("intro");

	//카메라 사이즈 조절
	_cameraSizeX = 1300;
	_cameraSizeY = 1066;
	//카메라 사이즈 설정
	CAMERAMANAGER->setBackScreenSize(_cameraSizeX, _cameraSizeY);
	//타일의 이미지 추가
	IMAGEMANAGER->addFrameDImage("VilageTileFrame", L"Tile/HouseTile_20_10.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("VilageObject1_Frame", L"Tile/Vilage_Object1.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("Vilage_House_Frame", L"Tile/Vilage_House.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("Vilage_House2_Frame", L"Tile/Vilage_House2.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("Vilage_House3_Frame", L"Tile/Vilage_House3.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("DunGeonChoice", L"Tile/DunGeonChoice.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("ShopTile1", L"Tile/ShopTile1.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("ShopTile2", L"Tile/ShopTile2.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("GolemDunGeon", L"Tile/GolemDunGeon.png", 520, 260, 20, 10);
	IMAGEMANAGER->addFrameDImage("Tree1", L"Tile/Tree1.png", 1960, 72, 28, 1);
	IMAGEMANAGER->addFrameDImage("Tree2", L"Tile/Tree2.png", 2450, 84, 35, 1);
	IMAGEMANAGER->addFrameDImage("Tree4", L"Tile/Tree4.png", 5495, 174, 35, 1);
	IMAGEMANAGER->addFrameDImage("Fountain", L"Tile/Fountain.png", 378, 46, 9, 1);
	IMAGEMANAGER->addFrameDImage("Well", L"Tile/Well.png", 512, 81, 8, 1);
	IMAGEMANAGER->addFrameDImage("HouseFrame", L"Tile/HouseFrame.png", 11395, 154, 53, 1);
	_tree1.img = IMAGEMANAGER->findDImage("Tree1");
	_tree2.img = IMAGEMANAGER->findDImage("Tree2");
	_tree3.img = IMAGEMANAGER->findDImage("Tree4");
	_fountain.img = IMAGEMANAGER->findDImage("Fountain");
	_well.img = IMAGEMANAGER->findDImage("Well");
	_house.img = IMAGEMANAGER->findDImage("HouseFrame");
	IMAGEMANAGER->addDImage("VilageTile", L"Tile/HouseTile_20_10.png", 520, 260);
	IMAGEMANAGER->addDImage("VilageObject1_Image", L"Tile/Vilage_Object1.png", 520, 260);
	IMAGEMANAGER->addDImage("Vilage_House_Image", L"Tile/Vilage_House.png", 520, 260);
	IMAGEMANAGER->addDImage("Vilage_House2_Image", L"Tile/Vilage_House2.png", 520, 260);
	IMAGEMANAGER->addDImage("Vilage_House3_Image", L"Tile/Vilage_House3.png", 520, 260);
	IMAGEMANAGER->addDImage("DunGeonChoice_Image", L"Tile/DunGeonChoice.png", 520, 260);
	IMAGEMANAGER->addDImage("ShopTile1_Image", L"Tile/ShopTile1.png", 520, 260);
	IMAGEMANAGER->addDImage("ShopTile2_Image", L"Tile/ShopTile2.png", 520, 260);
	IMAGEMANAGER->addDImage("GolemDunGeon_Image", L"Tile/GolemDunGeon.png", 520 , 260 );

	_sampleImg = IMAGEMANAGER->findDImage("VilageTile");
	_page = 0;

	_tree1.count = 0;
	_tree1.currentFrameX = 0;
	_tree1.currentFrameY = 0;
	_tree2.count = 0;
	_tree2.currentFrameX = 0;
	_tree2.currentFrameY = 0;
	_tree3.count = 0;
	_tree3.currentFrameX = 0;
	_tree3.currentFrameY = 0;
	_fountain.count = 0;
	_fountain.currentFrameX = 0;
	_fountain.currentFrameY = 0;
	_well.count = 0;
	_well.currentFrameX = 0;
	_well.currentFrameY = 0;
	_house.count = 0;
	_house.currentFrameX = 0;
	_house.currentFrameY = 0;


	//그릴타일도구 활성화
	_isTileSelect = true;
	//기본타일 셋팅
	setupTile();

	//맵툴에서 카메라 이동
	_moveRect.x = 1300 / 2;
	_moveRect.y = 1066 / 2;
	_moveRect.rc = RectMakeCenter(_moveRect.x, _moveRect.y, 50, 50);

	//버튼
	_buttonTerrain.x = WINSIZEX / 2 + 200;
	_buttonTerrain.y = WINSIZEY / 2 + 50;
	_buttonTerrainGrass.x = WINSIZEX / 2 + 200;
	_buttonTerrainGrass.y = WINSIZEY / 2 + 120;
	_buttonTerrainDrop.x = WINSIZEX / 2 + 200;
	_buttonTerrainDrop.y = WINSIZEY / 2 + 170;
	_buttonTerrainNotMove.x = WINSIZEX / 2 + 200;
	_buttonTerrainNotMove.y = WINSIZEY / 2 + 220;

	_buttonObject.x = WINSIZEX / 2 + 350;
	_buttonObject.y = WINSIZEY / 2 + 50;
	_buttonObjectNone.x = WINSIZEX / 2 + 350;
	_buttonObjectNone.y = WINSIZEY / 2 + 120;
	_buttonObjectBlock1.x = WINSIZEX / 2 + 350;
	_buttonObjectBlock1.y = WINSIZEY / 2 + 170;
	_buttonObjectNotMove.x = WINSIZEX / 2 + 350;
	_buttonObjectNotMove.y = WINSIZEY / 2 + 220;

	_buttonDefaultImage.x = WINSIZEX / 2 + 500;
	_buttonDefaultImage.y = WINSIZEY / 2 + 150;
	_buttonFrameImage.x = WINSIZEX / 2 + 500;
	_buttonFrameImage.y = WINSIZEY / 2 + 200;

	_buttonEraser.x = WINSIZEX / 2 + 500;
	_buttonEraser.y = WINSIZEY / 2 + 50;
	_buttonClear.x = WINSIZEX / 2 + 200;
	_buttonClear.y = WINSIZEY / 2 + 270;
	_buttonSave.x = WINSIZEX / 2 + 350;
	_buttonSave.y = WINSIZEY / 2 + 270;
	_buttonLoad.x = WINSIZEX / 2 + 500;
	_buttonLoad.y = WINSIZEY / 2 + 270;

	_buttonPageUp.x = WINSIZEX / 2 + 350;
	_buttonPageUp.y = 50;
	_buttonPageDown.x = WINSIZEX / 2 + 350;
	_buttonPageDown.y = WINSIZEY / 2 + 330;

	_Rect_Button1.x = WINSIZEX / 2 + 200;
	_Rect_Button1.y = WINSIZEY / 2 + 50;
	_Rect_TerrainAttitude.x = WINSIZEX / 2 + 200;
	_Rect_TerrainAttitude.y = WINSIZEY / 2 + 120;
	_Rect_ObjectAttitude.x = WINSIZEX / 2 + 350;
	_Rect_ObjectAttitude.y = WINSIZEY / 2 + 120;
	_Rect_ImageAttitude.x = WINSIZEX / 2 + 500;
	_Rect_ImageAttitude.y = WINSIZEY / 2 + 150;

	return S_OK;
}

void tileMap::release()
{
	SOUNDMANAGER->stop("intro");
}

void tileMap::update()
{
	cout << _tiles[3].obj << endl;
	setMap();
	rectMove();
	//일반 마우스포인트를 카메라 기준 마우스 포인트로 바꾸어준다.
	_cameraMouse.x = _ptMouse.x + CAMERAMANAGER->getScreen().left;
	_cameraMouse.y = _ptMouse.y + CAMERAMANAGER->getScreen().top;
	//카메라 활성화
	CAMERAMANAGER->updateScreen(_moveRect.x, _moveRect.y);
	//샘플타일 활성화
	setupSampleTile();
	//버튼 활성화
	button();
	//텍스트 관련
	if (_ctrSelect == CTRL_TERRAINDRAW) _object = L"현재 모드  지    형";
	if (_ctrSelect == CTRL_OBJDRAW) _object = L"현재 모드  오브젝트";
	if (_ctrSelect == CTRL_ERASER) _object = L"현재 모드  지 우 개";




	//Tree1 프레임 업데이트
	_tree1.count++;
	if (_tree1.count % 10 == 0)
	{
		_tree1.currentFrameX++;
		if (_tree1.currentFrameX > _tree1.img->getMaxFrameX()) _tree1.currentFrameX = 0;
		_tree1.count = 0;
	}
	//Tree1 프레임 업데이트
	_tree2.count++;
	if (_tree2.count % 10 == 0)
	{
		_tree2.currentFrameX++;
		if (_tree2.currentFrameX > _tree2.img->getMaxFrameX()) _tree2.currentFrameX = 0;
		_tree2.count = 0;
	}
	//Tree1 프레임 업데이트
	_tree3.count++;
	if (_tree1.count % 10 == 0)
	{
		_tree3.currentFrameX++;
		if (_tree3.currentFrameX > _tree3.img->getMaxFrameX()) _tree3.currentFrameX = 0;
		_tree3.count = 0;
	}
	//Tree1 프레임 업데이트
	_fountain.count++;
	if (_fountain.count % 10 == 0)
	{
		_fountain.currentFrameX++;
		if (_fountain.currentFrameX > _fountain.img->getMaxFrameX()) _fountain.currentFrameX = 0;
		_fountain.count = 0;
	}
	//Tree1 프레임 업데이트
	_well.count++;
	if (_well.count % 10 == 0)
	{
		_well.currentFrameX++;
		if (_well.currentFrameX > _well.img->getMaxFrameX()) _well.currentFrameX = 0;
		_well.count = 0;
	}
	//Tree1 프레임 업데이트
	_house.count++;
	if (_house.count % 10 == 0)
	{
		_house.currentFrameX++;
		if (_house.currentFrameX > _house.img->getMaxFrameX()) _house.currentFrameX = 0;
		_house.count = 0;
	}

}

void tileMap::render()
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
			case 6:
				IMAGEMANAGER->findDImage("ShopTile1")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			case 7:
				IMAGEMANAGER->findDImage("ShopTile2")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			case 8:
				IMAGEMANAGER->findDImage("GolemDunGeon")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;
			}

			if (KEYMANAGER->isToggleKey(VK_TAB))
			{
				D2DMANAGER->DrawRectangle(_tiles[i].rc, D2DDEFAULTBRUSH::Yellow);
			}

		}
	}
	//오브젝트타일 이미지
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].obj == OBJ_NONE) continue;

		if (CAMERAMANAGER->getScreen().left - TILESIZE <= _tiles[i].rc.left && CAMERAMANAGER->getScreen().right + TILESIZE >= _tiles[i].rc.right &&
			CAMERAMANAGER->getScreen().top - TILESIZE <= _tiles[i].rc.top && CAMERAMANAGER->getScreen().bottom + TILESIZE >= _tiles[i].rc.bottom)
		{

			switch (_tiles[i].pageObject)
			{
			case 0:
				IMAGEMANAGER->findDImage("VilageTileFrame")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
				break;
			case 1:
				if (_tiles[i].imgAt == FRAME_IMAGE)
				{
					if (_tiles[i].objFrameX == 0 && _tiles[i].objFrameY == 7) _tree1.img->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tree1.currentFrameX, _tree1.currentFrameY);
					if (_tiles[i].objFrameX == 6 && _tiles[i].objFrameY == 7) _tree2.img->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tree2.currentFrameX, _tree2.currentFrameY);
					if (_tiles[i].objFrameX == 12 && _tiles[i].objFrameY == 4) _tree3.img->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tree3.currentFrameX, _tree3.currentFrameY);
					if (_tiles[i].objFrameX == 2 && _tiles[i].objFrameY == 5) _fountain.img->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _fountain.currentFrameX, _fountain.currentFrameY);
					if (_tiles[i].objFrameX == 7 && _tiles[i].objFrameY == 4) _well.img->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _well.currentFrameX, _well.currentFrameY);
				}
				else IMAGEMANAGER->findDImage("VilageObject1_Frame")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
				break;
			case 2:
				if (_tiles[i].imgAt == FRAME_IMAGE)
				{
					if (_tiles[i].objFrameX == 4 && _tiles[i].objFrameY == 4) _house.img->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _house.currentFrameX, _house.currentFrameY);
				}
				else IMAGEMANAGER->findDImage("Vilage_House_Frame")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
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
			case 6:
				IMAGEMANAGER->findDImage("ShopTile1")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
				break;
			case 7:
				IMAGEMANAGER->findDImage("ShopTile2")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
				break;
			case 8:
				IMAGEMANAGER->findDImage("GolemDunGeon")->frameRender(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
				break;
			}
			if (KEYMANAGER->isToggleKey(VK_TAB))
			{
				if (_tiles[i].obj == OBJ_NOTMOVE) D2DMANAGER->DrawRectangle(_tiles[i].rc, D2DDEFAULTBRUSH::Blue);
			}

		}
	}

	//Tile 선택도구 등장
	if (_isTileSelect)
	{
		//샘플타일 이미지 및 렉트
		D2DMANAGER->FillRectangle(_backgroundSample, D2D1COLOR::White, 0.7f);
		_sampleImg->render(750 + CAMERAMANAGER->getScreen().left, 100 + CAMERAMANAGER->getScreen().top);
		for (int i = 0; i < SAMPLETILEY; ++i)
		{
			for (int j = 0; j < SAMPLETILEX; ++j)
			{
				D2DMANAGER->DrawRectangle(_sampleTile[i * SAMPLETILEX + j].rcTile, D2DDEFAULTBRUSH::White);
			}
		}
		//버튼
		D2DMANAGER->FillRectangle(_buttonTerrain.rc, D2DDEFAULTBRUSH::Gray);
		D2DMANAGER->RenderTextField(_buttonTerrain.rc.left, _buttonTerrain.rc.top, L"Terrain", 20, 100, 50, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_CENTER, L"PixelMplus10");
		D2DMANAGER->FillRectangle(_buttonTerrainGrass.rc, D2DDEFAULTBRUSH::Green);
		D2DMANAGER->RenderTextField(_buttonTerrainGrass.rc.left, _buttonTerrainGrass.rc.top, L"GRASS", 15, 70, 30, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_CENTER, L"PixelMplus10");
		D2DMANAGER->FillRectangle(_buttonTerrainDrop.rc, D2DDEFAULTBRUSH::Green);
		D2DMANAGER->RenderTextField(_buttonTerrainDrop.rc.left, _buttonTerrainDrop.rc.top, L"DROP", 15, 70, 30, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_CENTER, L"PixelMplus10");
		D2DMANAGER->FillRectangle(_buttonTerrainNotMove.rc, D2DDEFAULTBRUSH::Green);
		D2DMANAGER->RenderTextField(_buttonTerrainNotMove.rc.left, _buttonTerrainNotMove.rc.top, L"NOT MOVE", 15, 70, 30, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_CENTER, L"PixelMplus10");

		D2DMANAGER->FillRectangle(_buttonObject.rc, D2DDEFAULTBRUSH::Gray);
		D2DMANAGER->RenderTextField(_buttonObject.rc.left, _buttonObject.rc.top, L"Object", 20, 100, 50, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_CENTER, L"PixelMplus10");
		D2DMANAGER->FillRectangle(_buttonObjectNone.rc, D2DDEFAULTBRUSH::Green);
		D2DMANAGER->RenderTextField(_buttonObjectNone.rc.left, _buttonObjectNone.rc.top, L"NONE", 15, 70, 30, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_CENTER, L"PixelMplus10");
		D2DMANAGER->FillRectangle(_buttonObjectBlock1.rc, D2DDEFAULTBRUSH::Green);
		D2DMANAGER->RenderTextField(_buttonObjectBlock1.rc.left, _buttonObjectBlock1.rc.top, L"BLOCK1", 15, 70, 30, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_CENTER, L"PixelMplus10");
		D2DMANAGER->FillRectangle(_buttonObjectNotMove.rc, D2DDEFAULTBRUSH::Green);
		D2DMANAGER->RenderTextField(_buttonObjectNotMove.rc.left, _buttonObjectNotMove.rc.top, L"NOT MOVE", 15, 70, 30, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_CENTER, L"PixelMplus10");

		D2DMANAGER->FillRectangle(_buttonDefaultImage.rc, D2DDEFAULTBRUSH::Blue);
		D2DMANAGER->RenderTextField(_buttonDefaultImage.rc.left, _buttonDefaultImage.rc.top, L"DEFAULT IMG", 15, 100, 30, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_CENTER, L"PixelMplus10");
		D2DMANAGER->FillRectangle(_buttonFrameImage.rc, D2DDEFAULTBRUSH::Blue);
		D2DMANAGER->RenderTextField(_buttonFrameImage.rc.left, _buttonFrameImage.rc.top, L"FRAME IMG", 15, 100, 30, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_CENTER, L"PixelMplus10");

		D2DMANAGER->FillRectangle(_buttonEraser.rc, D2DDEFAULTBRUSH::Gray);
		D2DMANAGER->RenderTextField(_buttonEraser.rc.left, _buttonEraser.rc.top, L"Eraser", 20, 100, 50, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_CENTER, L"PixelMplus10");
		D2DMANAGER->FillRectangle(_buttonClear.rc, D2DDEFAULTBRUSH::Red);
		D2DMANAGER->RenderTextField(_buttonClear.rc.left, _buttonClear.rc.top, L"Clear", 20, 100, 50, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_CENTER, L"PixelMplus10");
		D2DMANAGER->FillRectangle(_buttonSave.rc, D2DDEFAULTBRUSH::Purple);
		D2DMANAGER->RenderTextField(_buttonSave.rc.left, _buttonSave.rc.top, L"Save", 20, 100, 50, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_CENTER, L"PixelMplus10");
		D2DMANAGER->FillRectangle(_buttonLoad.rc, D2DDEFAULTBRUSH::Purple);
		D2DMANAGER->RenderTextField(_buttonLoad.rc.left, _buttonLoad.rc.top, L"Load", 20, 100, 50, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_CENTER, L"PixelMplus10");
		D2DMANAGER->FillRectangle(_buttonPageUp.rc, D2DDEFAULTBRUSH::Yellow);
		D2DMANAGER->RenderTextField(_buttonPageUp.rc.left, _buttonPageUp.rc.top, L"Page Up", 15, 50, 50, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_CENTER, L"PixelMplus10");
		D2DMANAGER->FillRectangle(_buttonPageDown.rc, D2DDEFAULTBRUSH::Yellow);
		D2DMANAGER->RenderTextField(_buttonPageDown.rc.left, _buttonPageDown.rc.top, L"Page Down", 15, 50, 50, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_CENTER, L"PixelMplus10");
		D2DMANAGER->DrawRectangle(_Rect_Button1.rc, D2DDEFAULTBRUSH::Red);
		D2DMANAGER->DrawRectangle(_Rect_TerrainAttitude.rc, D2DDEFAULTBRUSH::Red);
		D2DMANAGER->DrawRectangle(_Rect_ObjectAttitude.rc, D2DDEFAULTBRUSH::Red);
		D2DMANAGER->DrawRectangle(_Rect_ImageAttitude.rc, D2DDEFAULTBRUSH::Red);

		////현재 상태
		//D2DMANAGER->RenderTextField(_buttonObject.rc.left, _buttonObject.rc.top + 100, _object, 20, 100, 100, D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_CENTER, L"PixelMplus10");
	}

	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; ++i)
	{
		switch (_page)
		{
		case 0:
			IMAGEMANAGER->findDImage("VilageTile")->render(_cameraMouse.x, _cameraMouse.y, _currentTile.startX * TILESIZE, _currentTile.startY * TILESIZE, _currentTile.sizeX * TILESIZE, _currentTile.sizeY * TILESIZE);
			break;
		case 1:
			IMAGEMANAGER->findDImage("VilageObject1_Image")->render(_cameraMouse.x, _cameraMouse.y, _currentTile.startX * TILESIZE, _currentTile.startY * TILESIZE, _currentTile.sizeX * TILESIZE, _currentTile.sizeY * TILESIZE);
			break;
		case 2:
			IMAGEMANAGER->findDImage("Vilage_House_Image")->render(_cameraMouse.x, _cameraMouse.y, _currentTile.startX * TILESIZE, _currentTile.startY * TILESIZE, _currentTile.sizeX * TILESIZE, _currentTile.sizeY * TILESIZE);
			break;
		case 3:
			IMAGEMANAGER->findDImage("Vilage_House2_Image")->render(_cameraMouse.x, _cameraMouse.y, _currentTile.startX * TILESIZE, _currentTile.startY * TILESIZE, _currentTile.sizeX * TILESIZE, _currentTile.sizeY * TILESIZE);
			break;
		case 4:
			IMAGEMANAGER->findDImage("Vilage_House3_Image")->render(_cameraMouse.x, _cameraMouse.y, _currentTile.startX * TILESIZE, _currentTile.startY * TILESIZE, _currentTile.sizeX * TILESIZE, _currentTile.sizeY * TILESIZE);
			break;
		case 5:
			IMAGEMANAGER->findDImage("DunGeonChoice_Image")->render(_cameraMouse.x, _cameraMouse.y, _currentTile.startX * TILESIZE, _currentTile.startY * TILESIZE, _currentTile.sizeX * TILESIZE, _currentTile.sizeY * TILESIZE);
			break;
		case 6:
			IMAGEMANAGER->findDImage("ShopTile1_Image")->render(_cameraMouse.x, _cameraMouse.y, _currentTile.startX * TILESIZE, _currentTile.startY * TILESIZE, _currentTile.sizeX * TILESIZE, _currentTile.sizeY * TILESIZE);
			break;
		case 7:
			IMAGEMANAGER->findDImage("ShopTile2_Image")->render(_cameraMouse.x, _cameraMouse.y, _currentTile.startX * TILESIZE, _currentTile.startY * TILESIZE, _currentTile.sizeX * TILESIZE, _currentTile.sizeY * TILESIZE);
			break;
		case 8:
			IMAGEMANAGER->findDImage("GolemDunGeon_Image")->render(_cameraMouse.x, _cameraMouse.y, _currentTile.startX * TILESIZE, _currentTile.startY * TILESIZE, _currentTile.sizeX * TILESIZE, _currentTile.sizeY * TILESIZE);
			break;
		}
	}

	//Tile 렉트보여주기
	//D2DMANAGER->DrawRectangle(_moveRect.rc);
}
//기본셋팅
void tileMap::setupTile()
{
	//처음상태는 지형
	_ctrSelect = CTRL_TERRAINDRAW;
	_currentTile.terrain = TR_GRASS;
	_currentTile.obj = OBJ_NONE;
	_currentTile.imgAt = DEFAULT_IMAGE;
	//Tile 프레임 정보 셋팅
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tiles[i].pageTerrain = 8;
		_tiles[i].pageObject = 0;
		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 0;
		_tiles[i].objFrameX = NULL;
		_tiles[i].objFrameY = NULL;
		_tiles[i].terrain = TR_GRASS;
		_tiles[i].obj = OBJ_NONE;
	}
	//Tile 위치 셋팅
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
		}
	}
}
//샘플타일 세팅
void tileMap::setupSampleTile()
{
	//스페이스 키로 그릴도구창 오픈 혹은 비오픈
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_isTileSelect)_isTileSelect = false;
		else if (!_isTileSelect)_isTileSelect = true;
	}
	if (_isTileSelect)
	{
		switch (_page)
		{
		case 0:
			_sampleImg = IMAGEMANAGER->findDImage("VilageTile");
			break;
		case 1:
			_sampleImg = IMAGEMANAGER->findDImage("VilageObject1_Image");
			break;
		case 2:
			_sampleImg = IMAGEMANAGER->findDImage("Vilage_House_Image");
			break;
		case 3:
			_sampleImg = IMAGEMANAGER->findDImage("Vilage_House2_Image");
			break;
		case 4:
			_sampleImg = IMAGEMANAGER->findDImage("Vilage_House3_Image");
			break;
		case 5:
			_sampleImg = IMAGEMANAGER->findDImage("DunGeonChoice_Image");
			break;
		case 6:
			_sampleImg = IMAGEMANAGER->findDImage("ShopTile1_Image");
			break;
		case 7:
			_sampleImg = IMAGEMANAGER->findDImage("ShopTile2_Image");
			break;
		case 8:
			_sampleImg = IMAGEMANAGER->findDImage("GolemDunGeon_Image");
			break;
		}
		//백그라운드 샘플타일
		_backgroundSample = RectMake(1280 - 600 + CAMERAMANAGER->getScreen().left, 0 + CAMERAMANAGER->getScreen().top, 600, WINSIZEY);
		//샘플타일 세팅
		for (int i = 0; i < SAMPLETILEY; ++i)
		{
			for (int j = 0; j < SAMPLETILEX; ++j)
			{
				if (_page == 0)
				{
					_sampleTile[i * SAMPLETILEX + j].pageTerrain = 0;
					_sampleTile[i * SAMPLETILEX + j].pageObject = 0;
				}
				else if (_page == 1)
				{
					_sampleTile[i * SAMPLETILEX + j].pageTerrain = 1;
					_sampleTile[i * SAMPLETILEX + j].pageObject = 1;
				}
				else if (_page == 2)
				{
					_sampleTile[i * SAMPLETILEX + j].pageTerrain = 2;
					_sampleTile[i * SAMPLETILEX + j].pageObject = 2;
				}
				else if (_page == 3)
				{
					_sampleTile[i * SAMPLETILEX + j].pageTerrain = 3;
					_sampleTile[i * SAMPLETILEX + j].pageObject = 3;
				}
				else if (_page == 4)
				{
					_sampleTile[i * SAMPLETILEX + j].pageTerrain = 4;
					_sampleTile[i * SAMPLETILEX + j].pageObject = 4;
				}
				else if (_page == 5)
				{
					_sampleTile[i * SAMPLETILEX + j].pageTerrain = 5;
					_sampleTile[i * SAMPLETILEX + j].pageObject = 5;
				}
				else if (_page == 6)
				{
					_sampleTile[i * SAMPLETILEX + j].pageTerrain = 6;
					_sampleTile[i * SAMPLETILEX + j].pageObject = 6;
				}
				else if (_page == 7)
				{
					_sampleTile[i * SAMPLETILEX + j].pageTerrain = 7;
					_sampleTile[i * SAMPLETILEX + j].pageObject = 7;
				}
				else if (_page == 8)
				{
					_sampleTile[i * SAMPLETILEX + j].pageTerrain = 8;
					_sampleTile[i * SAMPLETILEX + j].pageObject = 8;
				}
				//프레임 셋팅
				_sampleTile[i * SAMPLETILEX + j].terrainFrameY = i;
				_sampleTile[i * SAMPLETILEX + j].terrainFrameX = j;


				//렉트 셋팅
				_sampleTile[i * SAMPLETILEX + j].rcTile = RectMake(750 + (j * TILESIZE) + CAMERAMANAGER->getScreen().left, 100 + (i * TILESIZE) + CAMERAMANAGER->getScreen().top, TILESIZE, TILESIZE);
			}
		}

		//버튼의 렉트 활성화
		_buttonTerrain.rc = RectMakeCenter(_buttonTerrain.x + CAMERAMANAGER->getScreen().left, _buttonTerrain.y + CAMERAMANAGER->getScreen().top, 100, 50);
		_buttonTerrainGrass.rc = RectMakeCenter(_buttonTerrainGrass.x + CAMERAMANAGER->getScreen().left, _buttonTerrainGrass.y + CAMERAMANAGER->getScreen().top, 70, 30);
		_buttonTerrainDrop.rc = RectMakeCenter(_buttonTerrainDrop.x + CAMERAMANAGER->getScreen().left, _buttonTerrainDrop.y + CAMERAMANAGER->getScreen().top, 70, 30);
		_buttonTerrainNotMove.rc = RectMakeCenter(_buttonTerrainNotMove.x + CAMERAMANAGER->getScreen().left, _buttonTerrainNotMove.y + CAMERAMANAGER->getScreen().top, 70, 30);

		_buttonObject.rc = RectMakeCenter(_buttonObject.x + CAMERAMANAGER->getScreen().left, _buttonObject.y + CAMERAMANAGER->getScreen().top, 100, 50);
		_buttonObjectNone.rc = RectMakeCenter(_buttonObjectNone.x + CAMERAMANAGER->getScreen().left, _buttonObjectNone.y + CAMERAMANAGER->getScreen().top, 70, 30);
		_buttonObjectBlock1.rc = RectMakeCenter(_buttonObjectBlock1.x + CAMERAMANAGER->getScreen().left, _buttonObjectBlock1.y + CAMERAMANAGER->getScreen().top, 70, 30);
		_buttonObjectNotMove.rc = RectMakeCenter(_buttonObjectNotMove.x + CAMERAMANAGER->getScreen().left, _buttonObjectNotMove.y + CAMERAMANAGER->getScreen().top, 70, 30);

		_buttonDefaultImage.rc = RectMakeCenter(_buttonDefaultImage.x + CAMERAMANAGER->getScreen().left, _buttonDefaultImage.y + CAMERAMANAGER->getScreen().top, 100, 30);
		_buttonFrameImage.rc = RectMakeCenter(_buttonFrameImage.x + CAMERAMANAGER->getScreen().left, _buttonFrameImage.y + CAMERAMANAGER->getScreen().top, 100, 30);


		_buttonEraser.rc = RectMakeCenter(_buttonEraser.x + CAMERAMANAGER->getScreen().left, _buttonEraser.y + CAMERAMANAGER->getScreen().top, 100, 50);
		_buttonClear.rc = RectMakeCenter(_buttonClear.x + CAMERAMANAGER->getScreen().left, _buttonClear.y + CAMERAMANAGER->getScreen().top, 100, 50);
		_buttonSave.rc = RectMakeCenter(_buttonSave.x + CAMERAMANAGER->getScreen().left, _buttonSave.y + CAMERAMANAGER->getScreen().top, 100, 50);
		_buttonLoad.rc = RectMakeCenter(_buttonLoad.x + CAMERAMANAGER->getScreen().left, _buttonLoad.y + CAMERAMANAGER->getScreen().top, 100, 50);
		_buttonPageUp.rc = RectMakeCenter(_buttonPageUp.x + CAMERAMANAGER->getScreen().left, _buttonPageUp.y + CAMERAMANAGER->getScreen().top, 50, 50);
		_buttonPageDown.rc = RectMakeCenter(_buttonPageDown.x + CAMERAMANAGER->getScreen().left, _buttonPageDown.y + CAMERAMANAGER->getScreen().top, 50, 50);
		_Rect_Button1.rc = RectMakeCenter(_Rect_Button1.x + CAMERAMANAGER->getScreen().left, _Rect_Button1.y + CAMERAMANAGER->getScreen().top, 120, 70);
		_Rect_TerrainAttitude.rc = RectMakeCenter(_Rect_TerrainAttitude.x + CAMERAMANAGER->getScreen().left, _Rect_TerrainAttitude.y + CAMERAMANAGER->getScreen().top, 90, 45);
		_Rect_ObjectAttitude.rc = RectMakeCenter(_Rect_ObjectAttitude.x + CAMERAMANAGER->getScreen().left, _Rect_ObjectAttitude.y + CAMERAMANAGER->getScreen().top, 90,
			45);
		_Rect_ImageAttitude.rc = RectMakeCenter(_Rect_ImageAttitude.x + CAMERAMANAGER->getScreen().left, _Rect_ImageAttitude.y + CAMERAMANAGER->getScreen().top, 110,
			45);

	}
	else
	{
		for (int i = 0; i < SAMPLETILEY; ++i)
		{
			for (int j = 0; j < SAMPLETILEX; ++j)
			{
				//렉트 없앰
				_sampleTile[i * SAMPLETILEX + j].rcTile = RectMake(750 + (j * TILESIZE), 100 + (i * TILESIZE), 0, 0);
			}
		}

		//버튼의 렉트 비활성화         
		_buttonTerrain.rc = RectMakeCenter(_buttonTerrain.x, _buttonTerrain.y, 0, 0);
		_buttonTerrainGrass.rc = RectMakeCenter(_buttonTerrainGrass.x, _buttonTerrainGrass.y, 0, 0);
		_buttonTerrainDrop.rc = RectMakeCenter(_buttonTerrainDrop.x, _buttonTerrainDrop.y, 0, 0);
		_buttonTerrainNotMove.rc = RectMakeCenter(_buttonTerrainNotMove.x, _buttonTerrainNotMove.y, 0, 0);

		_buttonObject.rc = RectMakeCenter(_buttonObject.x, _buttonObject.y, 0, 0);
		_buttonObjectNone.rc = RectMakeCenter(_buttonObjectNone.x, _buttonObjectNone.y, 0, 0);
		_buttonObjectBlock1.rc = RectMakeCenter(_buttonObjectBlock1.x, _buttonObjectBlock1.y, 0, 0);
		_buttonObjectNotMove.rc = RectMakeCenter(_buttonObjectNotMove.x, _buttonObjectNotMove.y, 0, 0);

		_buttonDefaultImage.rc = RectMakeCenter(_buttonDefaultImage.x, _buttonDefaultImage.y, 0, 0);
		_buttonFrameImage.rc = RectMakeCenter(_buttonFrameImage.x, _buttonFrameImage.y, 0, 0);

		_buttonEraser.rc = RectMakeCenter(_buttonEraser.x, _buttonEraser.y, 0, 0);
		_buttonClear.rc = RectMakeCenter(_buttonClear.x, _buttonClear.y, 0, 0);
		_buttonSave.rc = RectMakeCenter(_buttonSave.x, _buttonSave.y, 0, 0);
		_buttonLoad.rc = RectMakeCenter(_buttonLoad.x, _buttonLoad.y, 0, 0);
		_buttonPageUp.rc = RectMakeCenter(_buttonPageUp.x, _buttonPageUp.y, 0, 0);
		_buttonPageDown.rc = RectMakeCenter(_buttonPageDown.x, _buttonPageDown.y, 0, 0);
		_Rect_Button1.rc = RectMakeCenter(0, 0, 0, 0);
		_Rect_TerrainAttitude.rc = RectMakeCenter(0, 0, 0, 0);
		_Rect_ObjectAttitude.rc = RectMakeCenter(0, 0, 0, 0);
		_Rect_ImageAttitude.rc = RectMakeCenter(0, 0, 0, 0);
	}
}
//Tile 그리기
void tileMap::setMap()
{
	//샘플타일에서 그리고 싶은 Tile 선택
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; ++i)
	{
		//클릭 Down시 처음 타일의 정보
		if (PtInRect(&_sampleTile[i].rcTile, _cameraMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_currentTile.pageTerrain = _sampleTile[i].pageTerrain;
			_currentTile.pageObject = _sampleTile[i].pageObject;
			_currentTile.startX = _sampleTile[i].terrainFrameX;
			_currentTile.startY = _sampleTile[i].terrainFrameY;
		}
		//클릭 up시 마지막 타일의 정보
		if (PtInRect(&_sampleTile[i].rcTile, _cameraMouse) && KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_currentTile.pageTerrain = _sampleTile[i].pageTerrain;
			_currentTile.pageObject = _sampleTile[i].pageObject;
			_currentTile.endX = _sampleTile[i].terrainFrameX;
			_currentTile.endY = _sampleTile[i].terrainFrameY;

			_currentTile.sizeX = _currentTile.endX + 1 - _currentTile.startX;
			_currentTile.sizeY = _currentTile.endY + 1 - _currentTile.startY;
		}

	}
	//선택한 타일을 화면에 그린다.
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (PtInRect(&_tiles[i].rc, _cameraMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON) && !_isTileSelect ||
			PtInRect(&_tiles[i].rc, _cameraMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _cameraMouse.x < 750 + CAMERAMANAGER->getScreen().left)
		{
			if (_ctrSelect == CTRL_TERRAINDRAW)
			{
				for (int k = 0; k < _currentTile.sizeY; ++k)
				{
					for (int j = 0; j < _currentTile.sizeX; ++j)
					{
						_tiles[i + k * TILEX + j].pageTerrain = _currentTile.pageTerrain;
						_tiles[i + k * TILEX + j].terrainFrameY = _currentTile.startY + k;
						_tiles[i + k * TILEX + j].terrainFrameX = _currentTile.startX + j;

						_tiles[i + k * TILEX + j].terrain = _currentTile.terrain;
					}
				}
				break;
			}
			else if (_ctrSelect == CTRL_OBJDRAW)
			{
				for (int k = 0; k < _currentTile.sizeY; ++k)
				{
					for (int j = 0; j < _currentTile.sizeX; ++j)
					{
						_tiles[i + k * TILEX + j].pageObject = _currentTile.pageObject;
						_tiles[i + k * TILEX + j].objFrameY = _currentTile.startY + k;
						_tiles[i + k * TILEX + j].objFrameX = _currentTile.startX + j;

						_tiles[i + k * TILEX + j].obj = _currentTile.obj;
						_tiles[i + k * TILEX + j].imgAt = _currentTile.imgAt;
					}
				}
				break;
			}
			else if (_ctrSelect == CTRL_ERASER)
			{
				if (_tiles[i].obj == OBJ_BLOCK1 || _tiles[i].obj == OBJ_NOTMOVE)
				{
					_tiles[i].pageTerrain = 0;
					_tiles[i].pageObject = 0;
					_tiles[i].objFrameX = NULL;
					_tiles[i].objFrameY = NULL;
					_tiles[i].obj = OBJ_NONE;
				}
			}
		}
	}
}
//맵툴에서 키보드로 카메라 조작
void tileMap::rectMove()
{
	if (KEYMANAGER->isStayKeyDown('W')) _moveRect.y -= 10;
	if (KEYMANAGER->isStayKeyDown('S')) _moveRect.y += 10;
	if (KEYMANAGER->isStayKeyDown('A')) _moveRect.x -= 10;
	if (KEYMANAGER->isStayKeyDown('D')) _moveRect.x += 10;
	if (_moveRect.y > _cameraSizeY * 0.7f)_moveRect.y = _cameraSizeY * 0.7f;
	if (_moveRect.y < _cameraSizeY * 0.3f)	 _moveRect.y = _cameraSizeY * 0.3f;
	if (_moveRect.x > _cameraSizeX * 0.51f)_moveRect.x = _cameraSizeX * 0.51f;
	if (_moveRect.x < _cameraSizeX * 0.49f)	 _moveRect.x = _cameraSizeX * 0.49f;

	_moveRect.rc = RectMakeCenter(_moveRect.x, _moveRect.y, 50, 50);
}

//버튼 상호작용
void tileMap::button()
{
	//지형모드 선택
	if (PtInRect(&_buttonTerrain.rc, _cameraMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_ctrSelect = CTRL_TERRAINDRAW;
		_Rect_Button1.x = _buttonTerrain.x;
	}
	//지형모드-GRASS 선택
	if (PtInRect(&_buttonTerrainGrass.rc, _cameraMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_currentTile.terrain = TR_GRASS;
		_Rect_TerrainAttitude.y = _buttonTerrainGrass.y;
	}
	//지형모드-DROP 선택
	if (PtInRect(&_buttonTerrainDrop.rc, _cameraMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_currentTile.terrain = TR_DROP;
		_Rect_TerrainAttitude.y = _buttonTerrainDrop.y;
	}
	//지형모드-MOTMOVE 선택
	if (PtInRect(&_buttonTerrainNotMove.rc, _cameraMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_currentTile.terrain = TR_NOTMOVE;
		_Rect_TerrainAttitude.y = _buttonTerrainNotMove.y;
	}
	//오브젝트모드 선택
	if (PtInRect(&_buttonObject.rc, _cameraMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_ctrSelect = CTRL_OBJDRAW;
		_Rect_Button1.x = _buttonObject.x;
	}
	//오브젝트모드-NONE 선택
	if (PtInRect(&_buttonObjectNone.rc, _cameraMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_currentTile.obj = OBJ_NONE;
		_Rect_ObjectAttitude.y = _buttonObjectNone.y;
	}
	//오브젝트모드-BLOCK 선택
	if (PtInRect(&_buttonObjectBlock1.rc, _cameraMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_currentTile.obj = OBJ_BLOCK1;
		_Rect_ObjectAttitude.y = _buttonObjectBlock1.y;

	}
	//오브젝트모드-NOTMOVE 선택
	if (PtInRect(&_buttonObjectNotMove.rc, _cameraMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_currentTile.obj = OBJ_NOTMOVE;
		_Rect_ObjectAttitude.y = _buttonObjectNotMove.y;

	}
	//default 이미지 선택
	if (PtInRect(&_buttonDefaultImage.rc, _cameraMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_currentTile.imgAt = DEFAULT_IMAGE;
		_Rect_ImageAttitude.y = _buttonDefaultImage.y;

	}
	//frame 이미지 선택
	if (PtInRect(&_buttonFrameImage.rc, _cameraMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_currentTile.imgAt = FRAME_IMAGE;
		_Rect_ImageAttitude.y = _buttonFrameImage.y;

	}
	//개별지우개모드 선택
	if (PtInRect(&_buttonEraser.rc, _cameraMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_ctrSelect = CTRL_ERASER;
		_Rect_Button1.x = _buttonEraser.x;
	}
	//전체삭제 선택
	if (PtInRect(&_buttonClear.rc, _cameraMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			_tiles[i].pageTerrain = NULL;
			_tiles[i].pageObject = NULL;
			_tiles[i].terrainFrameX = NULL;
			_tiles[i].terrainFrameY = NULL;
			_tiles[i].objFrameX = NULL;
			_tiles[i].objFrameY = NULL;
			_tiles[i].obj = OBJ_NONE;
			_tiles[i].imgAt = DEFAULT_IMAGE;
		}
	}
	//저장 선택
	if (PtInRect(&_buttonSave.rc, _cameraMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		save();
	}
	//불러오기 선택
	if (PtInRect(&_buttonLoad.rc, _cameraMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		load();
	}
	//페이지 up 선택
	if (PtInRect(&_buttonPageUp.rc, _cameraMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON) || KEYMANAGER->isOnceKeyDown(VK_NUMPAD8))
	{
		_page--;
		if (_page <= 0) _page = 0;
	}
	//페이지 down 선택
	if (PtInRect(&_buttonPageDown.rc, _cameraMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON) || KEYMANAGER->isOnceKeyDown(VK_NUMPAD2))
	{
		_page++;
		if (_page >= 8) _page = 8;
	}


}
//타일정보를 파일로 저장
void tileMap::save()
{
	HANDLE file;
	DWORD write;


	file = CreateFile("Test.map", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile)* TILEX * TILEY, &write, NULL);
	CloseHandle(file);
}
//타일정보를 파일에서 불러오기
void tileMap::load()
{
	HANDLE file;
	DWORD read;


	file = CreateFile("Test.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile)*TILEX*TILEY, &read, NULL);
	CloseHandle(file);
}

