#pragma once
#include "gameNode.h"

//Ÿ�� ������
#define TILESIZE 26
//Ÿ�� ����
#define TILEX 50
#define TILEY 41
//����Ÿ�� ����
#define DUNGEONTILEX 19
#define DUNGEONTILEY 11
//Ÿ�� �� ������
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY
//����Ÿ�� ����
#define SAMPLETILEX 20
#define SAMPLETILEY 10
//��ư
enum CTRL
{
	CTRL_TERRAINDRAW,	//����		��ư
	CTRL_OBJDRAW,		//������Ʈ	��ư
	CTRL_ERASER,		//���찳		��ư
};
//����
enum TERRAIN
{
	TR_NOTMOVE, TR_DROP, TR_GRASS
};

//������Ʈ
enum OBJECT
{
	OBJ_BLOCK1,
	OBJ_NOTMOVE,
	OBJ_NONE
};
//�̹���, �������̹��� ����
enum IMAGEAT
{
	DEFAULT_IMAGE,
	FRAME_IMAGE
};

//Ÿ�� ���� ���� ����ü
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

//����Ÿ�� ���� ���� ����ü
struct tagSampleTile
{
	TERRAIN		terrain;
	OBJECT		obj;
	RECT		rcTile;
	int			terrainFrameX;
	int			terrainFrameY;
	int			pageTerrain, pageObject;
};

//���� Ÿ�� �޾ƿ� ����ü
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
//moveRect ����
struct tagMoveRect
{
	int x, y;
	RECT rc;
};
//moveRect ����
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

	//������
	int _page;
	//��ư ����
	int _ctrSelect;

	//����Ÿ�� ����â
	bool _isTileSelect;
	RECT _backgroundSample;
	
	//Ÿ�ϸ� ī�޶�
	tagMoveRect _moveRect;

	//ī�޶� ������, ī�޶� ���콺
	int _cameraSizeX, _cameraSizeY;
	POINT _cameraMouse;

	//��ư ���̷�Ʈ ��Ʈ
	tagMoveRect _Rect_Button1;
	tagMoveRect _Rect_TerrainAttitude;
	tagMoveRect _Rect_ObjectAttitude;
	tagMoveRect _Rect_ImageAttitude;
	//��ư
	tagMoveRect _buttonTerrain;
	tagMoveRect _buttonObject;
	tagMoveRect _buttonEraser;
	tagMoveRect _buttonClear;
	tagMoveRect _buttonSave;
	tagMoveRect _buttonLoad;
	//������
	tagMoveRect _buttonPageDown;
	tagMoveRect _buttonPageUp;
	//���� �� ,������Ʈ �Ӽ�
	tagMoveRect _buttonTerrainDrop;
	tagMoveRect _buttonTerrainNotMove;
	tagMoveRect _buttonTerrainGrass;
	tagMoveRect _buttonObjectNone;
	tagMoveRect _buttonObjectBlock1;
	tagMoveRect _buttonObjectNotMove;
	//�⺻�̹���, �������̹��� ���� ��ư
	tagMoveRect _buttonDefaultImage;
	tagMoveRect _buttonFrameImage;

	//������Ʈ ������
	tagVillageObject _tree1;
	tagVillageObject _tree2;
	tagVillageObject _tree3;
	tagVillageObject _house;
	tagVillageObject _fountain;
	tagVillageObject _well;
	//�ؽ�Ʈ
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

