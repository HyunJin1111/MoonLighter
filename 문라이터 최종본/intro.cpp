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
	SOUNDMANAGER->play("��Ʈ�ι������");
	_cameraSizeX = 450;
	_cameraSizeY = 213;
	CAMERAMANAGER->setBackScreenSize(_cameraSizeX, _cameraSizeY);
	IMAGEMANAGER->addFrameDImage("intro", L"intro/intro_2700_1704_10_11.png", 4500, 2343, 10, 11);
	IMAGEMANAGER->addFrameDImage("����ȭ��1", L"intro/����ȭ��1.png", 5120, 720, 8, 2);
	IMAGEMANAGER->addFrameDImage("����ȭ��2", L"intro/����ȭ��2.png", 5120, 720, 8, 2);
	IMAGEMANAGER->addDImage("����_���ʹ�", L"intro/����_���ʹ�.png", 320, 360);
	IMAGEMANAGER->addDImage("����_�����ʹ�", L"intro/����_�����ʹ�.png", 320, 360);
	IMAGEMANAGER->addDImage("����ȭ��_�ΰ�", L"intro/����ȭ��_�ΰ�.png", 171, 142);
	IMAGEMANAGER->addDImage("�޴����þ�����", L"intro/�޴����þ�����.png", 23, 26);

	_intro.img = IMAGEMANAGER->findDImage("intro");
	_intro.currentX = 0;
	_intro.currentY = 0;
	_intro.count = 0;
	_intro.isRender = true;
	_intro.alpha = 1.f;

	_startScreen1.img = IMAGEMANAGER->findDImage("����ȭ��1");
	_startScreen1.currentX = 0;
	_startScreen1.currentY = 0;
	_startScreen1.count = 0;
	_startScreen1.isRender = false;

	_startScreen2.img = IMAGEMANAGER->findDImage("����ȭ��2");
	_startScreen2.currentX = 0;
	_startScreen2.currentY = 0;
	_startScreen2.count = 0;
	_startScreen2.isRender = false;

	_leftDoor.img = IMAGEMANAGER->findDImage("����_���ʹ�");
	_leftDoor.x = 0;

	_rightDoor.img = IMAGEMANAGER->findDImage("����_�����ʹ�");
	_rightDoor.x = 320;

	_logo.img = IMAGEMANAGER->findDImage("����ȭ��_�ΰ�");
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
	//�޴�������
	_menuIcon[0].x = 640 / 2 - 130;
	_menuIcon[1].x = 640 / 2 + 130;
	_menuIcon[0].y = 360 / 2 - 30;
	_menuIcon[1].y = 360 / 2 - 30;
	_menuIcon[0].rc = RectMakeCenter(_menuIcon[0].x, _menuIcon[0].y, 20, 20);
	_menuIcon[1].rc = RectMakeCenter(_menuIcon[1].x, _menuIcon[1].y, 20, 20);
	_menuIcon[0].img = IMAGEMANAGER->findDImage("�޴����þ�����");
	_menuIcon[1].img = IMAGEMANAGER->findDImage("�޴����þ�����");

	_alpha.rc = RectMakeCenter(640 / 2, 360 / 2, 640, 360);
	_alpha.alpha = 1.f;

	return S_OK;
}

void intro::release()
{
	SOUNDMANAGER->stop("��Ʈ�ι������");
}

void intro::update()
{
	//��Ʈ�� ������ ����
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

	//��Ʈ�� ������ ������ �޴� �� ��� ������ ����
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

			//�޴������� �� ���� ���� �Լ�
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
		D2DMANAGER->RenderTextField(_menu[0].rc.left, _menu[0].rc.top, L"����ϱ�", 20, 200, 50, D2DDEFAULTBRUSH::White, DWRITE_TEXT_ALIGNMENT_CENTER, L"���ְ��");
		D2DMANAGER->RenderTextField(_menu[1].rc.left, _menu[1].rc.top, L"�ҷ����� / ���θ����", 20, 200, 50, D2DDEFAULTBRUSH::White, DWRITE_TEXT_ALIGNMENT_CENTER, L"���ְ��");
		D2DMANAGER->RenderTextField(_menu[2].rc.left, _menu[2].rc.top, L"����", 20, 200, 50, D2DDEFAULTBRUSH::White, DWRITE_TEXT_ALIGNMENT_CENTER, L"���ְ��");

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
	//�޴������� ������
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		SOUNDMANAGER->play("�޴�����");
		_menuSelect--;
		if (_menuSelect <= 0)_menuSelect = 0;
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		SOUNDMANAGER->play("�޴�����");
		_menuSelect++;
		if (_menuSelect >= 2) _menuSelect = 2;
	}
	//�޴� ����
	switch (_menuSelect)
	{
	case 0:
		_menuIcon[0].y = _menuIcon[1].y = _menu[0].y - 5;
		if (KEYMANAGER->isOnceKeyDown('J')) SCENEMANAGER->changeScene("shop");
		break;
	case 1:
		_menuIcon[0].y = _menuIcon[1].y = _menu[1].y - 5;
		INIDATA->addData("���赵", "����", NULL);
		INIDATA->addData("�η�����", "����", NULL);
		INIDATA->addData("ũ����Ż", "����", NULL);
		INIDATA->addData("���ھ�", "����", NULL);
		INIDATA->addData("���缭", "����", NULL);
		INIDATA->addData("�����", "����", NULL);
		INIDATA->addData("��Ʈ", "����", NULL);
		INIDATA->addData("�ݼ�", "����", NULL);
		INIDATA->addData("����", "����", NULL);
		INIDATA->addData("����", "����", NULL);
		INIDATA->addData("������ȭ", "��", NULL);
		INIDATA->iniSave("����������");
		if (KEYMANAGER->isOnceKeyDown('J')) SCENEMANAGER->changeScene("shop");
		break;
	case 2:
		_menuIcon[0].y = _menuIcon[1].y = _menu[2].y - 5;
		if (KEYMANAGER->isOnceKeyDown('J')) exit(0);
		break;
	}
	//�޴������� ��Ʈ
	_menuIcon[0].rc = RectMakeCenter(_menuIcon[0].x, _menuIcon[0].y, 20, 20);
	_menuIcon[1].rc = RectMakeCenter(_menuIcon[1].x, _menuIcon[1].y, 20, 20);
}
