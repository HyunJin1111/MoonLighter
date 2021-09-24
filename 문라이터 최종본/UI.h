#pragma once
#include "gameNode.h"
#include "itemManager.h"

struct tagUIobject
{
	dImage* img;
	RECT rc;
	float x, y;
	int currentX, currentY;
	int count;
	float alpha;
	bool isTalk;
	bool isSell;
	float angle;
	string name;

};


class UI : public gameNode
{
private:
	vector<itemBase*> _vitemBase;
	vector<itemBase*>::iterator _viitemBase;
	tagUIobject _cursor;
	tagUIobject _sellSlime;
	tagUIobject _sellSlimeActive;
	tagUIobject _mirror;
	int _curIndex;
	bool _isSellActive;
	bool _isSellItem;

	tagUIobject _itemCoordinates[21];
	tagUIobject _itemSellImg[20];

	itemManager* _itemManager;

	//BASE �̹���
	tagUIobject _circleGold;
	tagUIobject _circleInven;
	tagUIobject _circleWeapon;
	tagUIobject _circleHeart;
	tagUIobject _prograssBarBack;

	//������ �̹���
	tagUIobject _iconBag;
	tagUIobject _iconHeart;
	tagUIobject _iconJump;
	tagUIobject _iconCoin;
	tagUIobject _iconMoenyBag;
	tagUIobject _swordImg;

	//��ư �̹���
	tagUIobject _iButton;
	tagUIobject _jButton;
	tagUIobject _zButton;
	tagUIobject _kButton;
	tagUIobject _spaceButton;

	//�κ��丮 �̹���
	tagUIobject _invenBase;
	tagUIobject _invenWill;

	//�Ͻ����� �̹���
	tagUIobject _pauseBase;
	tagUIobject _pauseSquareUp;
	tagUIobject _pauseSquareDown;
	tagUIobject _pauseTailUp;
	tagUIobject _pauseTailDown;
	tagUIobject _pauseHotdogLeft;
	tagUIobject _pauseHotdogRight;
	tagUIobject _pauseSelectLeft;
	tagUIobject _pauseSelectRight;
	tagUIobject _pauseEye;

	//��ȭâ �̹���
	tagUIobject _talkBaseLong;

	//������� �̹���
	tagUIobject _resultBack;
	tagUIobject _resultTitle;
	tagUIobject _resultFootHold;
	tagUIobject _portalDoorAtive;
	tagUIobject _portalDoorOpen;
	tagUIobject _resultEnemy;
	tagUIobject _resultEnemy2;
	tagUIobject _resultInvenBase;
	vector<tagUIobject> _vHuntEnemy;
	bool _vHuntEnemyCheck;

	bool _resultCheck;


	int _winsizeX, _winsizeY;
	int _pauseMenuSelect;
	//�κ��丮â�� �Ͻ����� â Ȱ��ȭ ����
	bool _invenCheck;
	bool _pauseCheck;
	//�Ͻ����� â ������ ������ �ִϸ��̼� �������� ����
	bool _pauseOpen;
	bool _pauseAnimation;

	//��ȭ
	int _money;
	int itemCount[10];

public:
	UI();
	~UI();
	
	virtual HRESULT init();
	virtual void release();
	virtual void update(float playerHp);
	virtual void render();

	void setting();
	void pause();
	void pauseOpen();
	void pauseClose();
	void resultUI();
	
	void cursorSet();
	void cursorUpdate();
	void sellItemFrame();

	bool getInvenCheck() { return _invenCheck; }
	bool getPauseCheck() { return _pauseCheck; }

	void setResultCheck(bool check) { _resultCheck = check; }
	bool getResultCheck() { return _resultCheck; }

	void huntEnemy(int huntNum, int miniboss);

	void itemGet(string name);
	void itemSet();


};

