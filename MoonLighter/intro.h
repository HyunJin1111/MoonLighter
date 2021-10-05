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
	//��Ʈ�� ������
	tagIntro _intro;
	//���۽� ȭ��
	tagIntro _startScreen1;
	tagIntro _startScreen2;
	//��
	tagIntro _leftDoor;
	tagIntro _rightDoor;
	//�ΰ�
	tagIntro _logo;
	//����ȯ�� ���İ�
	tagIntro _alpha;
	//ī�޶� ������
	int _cameraSizeX;
	int _cameraSizeY;
	//�޴�����
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

