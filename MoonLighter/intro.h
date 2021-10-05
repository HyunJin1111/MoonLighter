#pragma once
#include "gameNode.h"

struct tagIntro
{
	int currentX, currentY;
	int count;
	int x, y;
	dImage* img;
	bool isRender;
	float opacity;
	RECT rc;
	float alpha;
};

class intro : public gameNode
{
private:
	//인트로 프레임
	tagIntro _intro;
	//시작시 화면
	tagIntro _startScreen1;
	tagIntro _startScreen2;
	//문
	tagIntro _leftDoor;
	tagIntro _rightDoor;
	//로고
	tagIntro _logo;
	//씬전환용 알파값
	tagIntro _alpha;
	//카메라 사이즈
	int _cameraSizeX;
	int _cameraSizeY;
	//메뉴관련
	int _menuSelect;
	tagIntro _menu[3];
	tagIntro _menuIcon[2];

public:
	intro();
	~intro();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void button_menu();
};

