#pragma once
#include "gameNode.h"

//타일 사이즈
#define TILESIZE 26
//타일 개수
#define TILEX 50
#define TILEY 41
//던전타일 개수
#define DUNGEONTILEX 19
#define DUNGEONTILEY 11
//타일 총 사이즈
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY
//샘플타일 개수
#define SAMPLETILEX 20
#define SAMPLETILEY 10
//버튼
enum CTRL
{
	CTRL_TERRAINDRAW,	//지형		버튼
	CTRL_OBJDRAW,		//오브젝트	버튼
	CTRL_ERASER,		//지우개		버튼
};
//지형
enum TERRAIN
{
	TR_NOTMOVE, TR_DROP, TR_GRASS
};

//오브젝트
enum OBJECT
{
	OBJ_BLOCK1,
	OBJ_NOTMOVE,
	OBJ_NONE
};
//이미지, 프레임이미지 여부
enum IMAGEAT
{
	DEFAULT_IMAGE,
	FRAME_IMAGE
};

//타일 정보 담은 구조체
struct tagTile
{
	TERRAIN		terrain;
	OBJECT		obj;
	IMAGEAT		imgAt;
	RECT		rc;
	int			pageTerrain, pageObject;
	int			terrainFrameX;
	int			terrainFrameY;
	int			objFrameX;
	int			objFrameY;
	dImage*		img;

};

//샘플타일 정보 담을 구조체
struct tagSampleTile
{
	TERRAIN		terrain;
	OBJECT		obj;
	RECT		rcTile;
	int			terrainFrameX;
	int			terrainFrameY;
	int			pageTerrain, pageObject;
};

//현재 타일 받아올 구조체
struct tagCurrentTile
{
	TERRAIN		terrain;
	OBJECT		obj;
	IMAGEAT		imgAt;
	int			pageTerrain, pageObject;
	int			startX, startY;
	int			endX, endY;
	int			sizeX, sizeY;
};
//moveRect 전용
struct tagMoveRect
{
	int x, y;
	RECT rc;
};
//moveRect 전용
struct tagVillageObject
{
	int x, y;
	dImage* img;
	RECT rc;
	int currentFrameX, currentFrameY;
	int count;
};

class tileMap : public gameNode
{
private:
	tagCurrentTile _currentTile;
	tagSampleTile _sampleTile[SAMPLETILEX * SAMPLETILEY];
	dImage* _sampleImg;
	tagTile _tiles[TILEX * TILEY];

	//페이지
	int _page;
	//버튼 여부
	int _ctrSelect;

	//샘플타일 선택창
	bool _isTileSelect;
	RECT _backgroundSample;
	
	//타일맵 카메라
	tagMoveRect _moveRect;

	//카메라 사이즈, 카메라 마우스
	int _cameraSizeX, _cameraSizeY;
	POINT _cameraMouse;

	//버튼 다이렉트 렉트
	tagMoveRect _Rect_Button1;
	tagMoveRect _Rect_TerrainAttitude;
	tagMoveRect _Rect_ObjectAttitude;
	tagMoveRect _Rect_ImageAttitude;
	//버튼
	tagMoveRect _buttonTerrain;
	tagMoveRect _buttonObject;
	tagMoveRect _buttonEraser;
	tagMoveRect _buttonClear;
	tagMoveRect _buttonSave;
	tagMoveRect _buttonLoad;
	//페이지
	tagMoveRect _buttonPageDown;
	tagMoveRect _buttonPageUp;
	//지형 및 ,오브젝트 속성
	tagMoveRect _buttonTerrainDrop;
	tagMoveRect _buttonTerrainNotMove;
	tagMoveRect _buttonTerrainGrass;
	tagMoveRect _buttonObjectNone;
	tagMoveRect _buttonObjectBlock1;
	tagMoveRect _buttonObjectNotMove;
	//기본이미지, 프레임이미지 구분 버튼
	tagMoveRect _buttonDefaultImage;
	tagMoveRect _buttonFrameImage;

	//오브젝트 프레임
	tagVillageObject _tree1;
	tagVillageObject _tree2;
	tagVillageObject _tree3;
	tagVillageObject _house;
	tagVillageObject _fountain;
	tagVillageObject _well;
	//텍스트
	wstring _object;

public:
	tileMap();
	~tileMap();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setupTile();
	virtual void setupSampleTile();
	virtual void setMap();
	virtual void rectMove();
	virtual void button();
	virtual void save();
	virtual void load();
	

};

