#include "stdafx.h"
#include "intro.h"

intro::intro()
{
}

intro::~intro()
{
}

HRESULT intro::init()
{
	SOUNDMANAGER->play("인트로배경음악");
	_cameraSizeX = 450;
	_cameraSizeY = 213;
	CAMERAMANAGER->setBackScreenSize(_cameraSizeX, _cameraSizeY);
	IMAGEMANAGER->addFrameDImage("intro", L"intro/intro_2700_1704_10_11.png", 4500, 2343, 10, 11);
	IMAGEMANAGER->addFrameDImage("시작화면1", L"intro/시작화면1.png", 5120, 720, 8, 2);
	IMAGEMANAGER->addFrameDImage("시작화면2", L"intro/시작화면2.png", 5120, 720, 8, 2);
	IMAGEMANAGER->addDImage("시작_왼쪽문", L"intro/시작_왼쪽문.png", 320, 360);
	IMAGEMANAGER->addDImage("시작_오른쪽문", L"intro/시작_오른쪽문.png", 320, 360);
	IMAGEMANAGER->addDImage("시작화면_로고", L"intro/시작화면_로고.png", 171, 142);
	IMAGEMANAGER->addDImage("메뉴선택아이콘", L"intro/메뉴선택아이콘.png", 23, 26);

	_intro.img = IMAGEMANAGER->findDImage("intro");
	_intro.currentX = 0;
	_intro.currentY = 0;
	_intro.count = 0;
	_intro.isRender = true;
	_intro.alpha = 1.f;

	_startScreen1.img = IMAGEMANAGER->findDImage("시작화면1");
	_startScreen1.currentX = 0;
	_startScreen1.currentY = 0;
	_startScreen1.count = 0;
	_startScreen1.isRender = false;

	_startScreen2.img = IMAGEMANAGER->findDImage("시작화면2");
	_startScreen2.currentX = 0;
	_startScreen2.currentY = 0;
	_startScreen2.count = 0;
	_startScreen2.isRender = false;

	_leftDoor.img = IMAGEMANAGER->findDImage("시작_왼쪽문");
	_leftDoor.x = 0;

	_rightDoor.img = IMAGEMANAGER->findDImage("시작_오른쪽문");
	_rightDoor.x = 320;

	_logo.img = IMAGEMANAGER->findDImage("시작화면_로고");
	_logo.x = _cameraSizeX / 2;
	_logo.y = _cameraSizeY / 2;
	_logo.opacity = 0;
	_logo.rc = RectMakeCenter(_logo.x, _logo.y, _logo.img->getWidth(), _logo.img->getHeight());

	_menuSelect = 0;

	for (int i = 0; i < 3; i++)
	{
		_menu[i].x = 640 / 2;
		_menu[i].y = 360 / 2 + (i * 50);
		_menu[i].rc = RectMakeCenter(_menu[i].x, _menu[i].y, 200, 50);
	}
	//메뉴아이콘
	_menuIcon[0].x = 640 / 2 - 130;
	_menuIcon[1].x = 640 / 2 + 130;
	_menuIcon[0].y = 360 / 2 - 30;
	_menuIcon[1].y = 360 / 2 - 30;
	_menuIcon[0].rc = RectMakeCenter(_menuIcon[0].x, _menuIcon[0].y, 20, 20);
	_menuIcon[1].rc = RectMakeCenter(_menuIcon[1].x, _menuIcon[1].y, 20, 20);
	_menuIcon[0].img = IMAGEMANAGER->findDImage("메뉴선택아이콘");
	_menuIcon[1].img = IMAGEMANAGER->findDImage("메뉴선택아이콘");

	_alpha.rc = RectMakeCenter(640 / 2, 360 / 2, 640, 360);
	_alpha.alpha = 1.f;

	return S_OK;
}

void intro::release()
{
	SOUNDMANAGER->stop("인트로배경음악");
}

void intro::update()
{
	//인트로 프레임 시작
	if (_intro.isRender)
	{
		_intro.count++;

		if (_intro.count % 2 == 0)
		{
			_intro.currentX++;
			if (_intro.currentX > _intro.img->getMaxFrameX())
			{
				_intro.currentY++;
				_intro.currentX = 0;
			}
			if (_intro.currentY > _intro.img->getMaxFrameY())
			{
				_intro.currentX = _intro.img->getMaxFrameX();
				_intro.currentY = _intro.img->getMaxFrameY();
				_intro.alpha -= 0.01f;
				if (_intro.alpha <= 0)
				{
					_intro.isRender = false;
					_cameraSizeX = 640;
					_cameraSizeY = 360;
					CAMERAMANAGER->setBackScreenSize(_cameraSizeX, _cameraSizeY);
					
				}


			}
		}
	}

	//인트로 프레임 끝나고 메뉴 및 배경 프레임 시작
	if (!_intro.isRender)
	{
		_alpha.alpha -= 0.01f;
		if (_alpha.alpha <= 0) 
		{
			_startScreen1.count++;

			if (_startScreen1.count % 5 == 0)
			{
				_startScreen1.currentX++;
				_startScreen2.currentX++;
				if (_startScreen1.currentX > _startScreen1.img->getMaxFrameX())
				{
					_startScreen1.currentY++;
					_startScreen1.currentX = 0;
					_startScreen2.currentY++;
					_startScreen2.currentX = 0;
				}
				if (_startScreen1.currentY > _startScreen1.img->getMaxFrameY())
				{
					_startScreen1.currentY = 0;
					_startScreen1.currentX = 0;
					_startScreen2.currentY = 0;
					_startScreen2.currentX = 0;
				}
			}

			_leftDoor.x -= 2;
			_rightDoor.x += 2;
			if (_leftDoor.x <= -200) _leftDoor.x = -200;
			if (_rightDoor.x >= 520) _rightDoor.x = 520;

			_logo.x = _cameraSizeX / 2;
			_logo.y = _cameraSizeY / 2 - 100;
			_logo.opacity += 0.01f;
			if (_logo.opacity >= 1) _logo.opacity = 1;
			_logo.rc = RectMakeCenter(_logo.x, _logo.y, _logo.img->getWidth(), _logo.img->getHeight());

			//메뉴아이콘 및 제어 관련 함수
			button_menu();
		}
		
	}
}

void intro::render()
{
	if (_intro.isRender) _intro.img->frameRender(0, 0, _intro.currentX, _intro.currentY, _intro.alpha);
	if (!_intro.isRender)
	{
		_startScreen1.img->frameRender(0, 0, _startScreen1.currentX, _startScreen1.currentY);
		_startScreen2.img->frameRender(0, 0, _startScreen2.currentX, _startScreen2.currentY);
		D2DMANAGER->RenderTextField(_menu[0].rc.left, _menu[0].rc.top, L"계속하기", 20, 200, 50, D2DDEFAULTBRUSH::White, DWRITE_TEXT_ALIGNMENT_CENTER, L"제주고딕");
		D2DMANAGER->RenderTextField(_menu[1].rc.left, _menu[1].rc.top, L"불러오기 / 새로만들기", 20, 200, 50, D2DDEFAULTBRUSH::White, DWRITE_TEXT_ALIGNMENT_CENTER, L"제주고딕");
		D2DMANAGER->RenderTextField(_menu[2].rc.left, _menu[2].rc.top, L"종료", 20, 200, 50, D2DDEFAULTBRUSH::White, DWRITE_TEXT_ALIGNMENT_CENTER, L"제주고딕");

		_menuIcon[0].img->render(_menuIcon[0].rc.left, _menuIcon[0].rc.top);
		_menuIcon[1].img->render(_menuIcon[1].rc.left, _menuIcon[1].rc.top);
		_leftDoor.img->render(_leftDoor.x, 0);
		_rightDoor.img->render(_rightDoor.x, 0);

		_logo.img->render(_logo.rc.left, _logo.rc.top, _logo.opacity);

		D2DMANAGER->FillRectangle(_alpha.rc,D2D1COLOR::Black, _alpha.alpha);

	}
}

void intro::button_menu()
{
	//메뉴아이콘 움직임
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		SOUNDMANAGER->play("메뉴선택");
		_menuSelect--;
		if (_menuSelect <= 0)_menuSelect = 0;
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		SOUNDMANAGER->play("메뉴선택");
		_menuSelect++;
		if (_menuSelect >= 2) _menuSelect = 2;
	}
	//메뉴 선택
	switch (_menuSelect)
	{
	case 0:
		_menuIcon[0].y = _menuIcon[1].y = _menu[0].y - 5;
		if (KEYMANAGER->isOnceKeyDown('J')) SCENEMANAGER->changeScene("shop");
		break;
	case 1:
		_menuIcon[0].y = _menuIcon[1].y = _menu[1].y - 5;
		INIDATA->addData("설계도", "개수", NULL);
		INIDATA->addData("부러진검", "개수", NULL);
		INIDATA->addData("크리스탈", "개수", NULL);
		INIDATA->addData("골렘코어", "개수", NULL);
		INIDATA->addData("역사서", "개수", NULL);
		INIDATA->addData("생명수", "개수", NULL);
		INIDATA->addData("노트", "개수", NULL);
		INIDATA->addData("금속", "개수", NULL);
		INIDATA->addData("빨대", "개수", NULL);
		INIDATA->addData("전선", "개수", NULL);
		INIDATA->addData("보유재화", "돈", NULL);
		INIDATA->iniSave("아이템정보");
		if (KEYMANAGER->isOnceKeyDown('J')) SCENEMANAGER->changeScene("shop");
		break;
	case 2:
		_menuIcon[0].y = _menuIcon[1].y = _menu[2].y - 5;
		if (KEYMANAGER->isOnceKeyDown('J')) exit(0);
		break;
	}
	//메뉴아이콘 렉트
	_menuIcon[0].rc = RectMakeCenter(_menuIcon[0].x, _menuIcon[0].y, 20, 20);
	_menuIcon[1].rc = RectMakeCenter(_menuIcon[1].x, _menuIcon[1].y, 20, 20);
}
