#include "stdafx.h"
#include "UI.h"

UI::UI()
{
}

UI::~UI()
{
}

HRESULT UI::init()
{
	//이미지 및 렉트 세팅
	setting();
	//bool값 및 인수 초기화
	_pauseCheck = false;
	_pauseAnimation = false;
	_pauseOpen = false;
	_pauseMenuSelect = 0;

	_money = 1000;

	_itemManager = new itemManager;

	itemSet();
	return S_OK;
}

void UI::release()
{
}

void UI::update(float playerHp)
{
	//일시정지 창 오픈 클로즈
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (!_pauseCheck)
		{
			_pauseCheck = true;
		}
		else if (_pauseCheck)
		{
			_pauseAnimation = true;
		}
		_pauseMenuSelect = 0;
	}
	//인벤토리 창 오픈 클로즈
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		if (!_invenCheck)
		{
			_invenCheck = true;
			cursorSet();
		}
		else if (_invenCheck) _invenCheck = false;
		_isSellActive = false;
	}
	//일시정지 제어 함수
	pause();

	//인벤토리 프레임 이미지
	_invenWill.count++;
	_sellSlime.count++;
	_sellSlimeActive.count++;
	_mirror.count++;
	if (_invenCheck)
	{
		if (_invenWill.count % 10 == 0)
		{
			_invenWill.currentX++;
			if (_invenWill.currentX > _invenWill.img->getMaxFrameX())
			{
				_invenWill.currentX = 0;
				_invenWill.count = 0;
			}
		}
		if (_sellSlime.count % 6 == 0)
		{
			_sellSlime.currentX++;
			if (_sellSlime.currentX > _sellSlime.img->getMaxFrameX())
			{
				_sellSlime.currentX = 0;
				_sellSlime.count = 0;
			}
		}
		if (_sellSlimeActive.count % 6 == 0)
		{
			_sellSlimeActive.currentX++;
			if (_sellSlimeActive.currentX > _sellSlimeActive.img->getMaxFrameX())
			{
				_sellSlimeActive.currentX = 0;
				_sellSlimeActive.count = 0;
			}
		}
		if (_isSellActive)
		{
			if (_mirror.count % 6 == 0)
			{
				_mirror.currentX++;
				if (_mirror.currentX > _mirror.img->getMaxFrameX())
				{
					_mirror.currentX = 0;
					_mirror.count = 0;
				}
			}
		}


		//커서관련 업데이트
		cursorUpdate();

		sellItemFrame();
		//J키를 눌렀을 경우
		if (KEYMANAGER->isOnceKeyDown('J'))
		{
			//판매상태가 활성화되지 않고 커서의 index가 20이면 판매상태를 활성화 시킨다.
			if (!_isSellActive && _curIndex == 20)
			{
				_isSellActive = true;

			}
			//판매활성화 상태에서 index가 20이면 판매상태를 비활성화 시킨다.
			else if (_isSellActive && _curIndex == 20)
			{
				_isSellActive = false;
			}
			//판매활성화가 되어있을때 index가 20이 아니면 해당 index의 아이템 정보를 NULL값으로 바꿔준다.
			else if (_isSellActive)
			{

				for (int i = 0; i < _vitemBase.size(); ++i)
				{
					if (i == _curIndex && _vitemBase[i] != NULL)
					{
						//커서의 index를 바탕으로 선택한 아이템의 정보를 불러와 판매애니메이션을 실행한다.
						_money += _vitemBase[i]->getItem().itemMax * 30;
						_itemSellImg[i].img = _vitemBase[i]->getItem().img;
						_itemSellImg[i].name = _vitemBase[i]->getItem().name;
						_itemSellImg[i].x = _vitemBase[i]->getItem().x;
						_itemSellImg[i].y = _vitemBase[i]->getItem().y;
						_itemSellImg[i].isSell = true;
						_itemSellImg[i].angle = getAngle(_itemSellImg[i].x, _itemSellImg[i].y, _itemCoordinates[20].x, _itemCoordinates[20].y);


						//제거한 아이템의 정보를 저장해주고 해당 vector를 NULL값으로 만든다.
						char cha[64];
						char cha_money[64];
						cha[63] = _itoa_s(0, cha, sizeof(cha), 10);
						cha_money[63] = _itoa_s(_money, cha_money, sizeof(cha_money), 10);
						INIDATA->addData(_itemSellImg[i].name.c_str(), "Item_Count", cha);
						INIDATA->addData("My_Money", "Money", cha_money);
						INIDATA->iniSave("Item_info");
						_vitemBase[i] = NULL;
					}
				}


			}
		}

		//인벤토리 정렬
		if (KEYMANAGER->isOnceKeyDown('K'))
		{
			//아이템이 NULL값인 경우 vector의 iter를 당겨준다.
			//for문을 ++로 하게되면 size가 줄어들어 iter도 당겨지기 때문에 NULL값을 체크하지 못하는 경우가 있다.(연속된 NULL 값일 경우)
			//그렇기 때문에 뒤에서부터 NULL값을 체크해준다.
			for (int i = _vitemBase.size() - 1; i >= 0; --i)
			{
				if (_vitemBase[i] == NULL) _vitemBase.erase(_vitemBase.begin() + i);
			}
			//NULL값을 제거해준 후 위치를 재설정 해준다.
			for (int i = 0; i < _vitemBase.size(); ++i)
			{
				_vitemBase[i]->setItemX(_itemCoordinates[i].x);
				_vitemBase[i]->setItemY(_itemCoordinates[i].y);
				_vitemBase[i]->setItemRC(_itemCoordinates[i].rc);
			}
		}


	}


	//모험결과 UI
	if (_resultCheck)
	{
		resultUI();
		sellItemFrame();
		if (_sellSlime.count % 6 == 0)
		{
			_sellSlime.currentX++;
			if (_sellSlime.currentX > _sellSlime.img->getMaxFrameX())
			{
				_sellSlime.currentX = 0;
				_sellSlime.count = 0;
			}
		}
		//인벤토리 아이템 좌표 셋팅
		for (int i = 0; i < 20; i++)
		{
			_itemCoordinates[i].x = 132 - 40 + (i % 5) * 36;
			_itemCoordinates[i].y = 118 + 1 + (i / 5) * 43;
			if (i / 5 >= 2) _itemCoordinates[i].y = 198 + (i / 5) / 3 * 36;
			_itemCoordinates[i].rc = RectMakeCenter(_itemCoordinates[i].x + CAMERAMANAGER->getScreen().left, _itemCoordinates[i].y + CAMERAMANAGER->getScreen().top, 32, 32);

		}
		_itemCoordinates[20].x = _resultInvenBase.x - 58;
		_itemCoordinates[20].y = _resultInvenBase.y + 92;
		_itemCoordinates[20].rc = RectMakeCenter(_itemCoordinates[20].x + CAMERAMANAGER->getScreen().left, _itemCoordinates[20].y + CAMERAMANAGER->getScreen().top, 32, 32);

		if (playerHp <= 0)
		{
			//index가 5부터인 아이템은 모두 삭제(플레이어 사망시)
			for (int i = 0; i < _vitemBase.size(); ++i)
			{
				if (i >= 5 && _vitemBase[i] != NULL)
				{


					//아이템의 정보를 불러와 버려지는 애니메이션을 실행한다.
					_itemSellImg[i].img = _vitemBase[i]->getItem().img;
					_itemSellImg[i].name = _vitemBase[i]->getItem().name;
					_itemSellImg[i].x = _vitemBase[i]->getItem().x;
					_itemSellImg[i].y = _vitemBase[i]->getItem().y;
					_itemSellImg[i].isSell = true;
					_itemSellImg[i].angle = getAngle(_itemSellImg[i].x, _itemSellImg[i].y, _itemCoordinates[20].x, _itemCoordinates[20].y);


					//제거한 아이템의 정보를 저장해주고 해당 vector를 NULL값으로 만든다.
					char cha[64];
					cha[63] = _itoa_s(0, cha, sizeof(cha), 10);
					INIDATA->addData(_itemSellImg[i].name.c_str(), "Item_Count", cha);
					INIDATA->iniSave("Item_info");
					_vitemBase[i] = NULL;
				}
			}
		}

	}

}

void UI::render()
{
	//배경 원 이미지 
	_circleGold.img->render(_circleGold.rc.left + CAMERAMANAGER->getScreen().left, _circleGold.rc.top + CAMERAMANAGER->getScreen().top);
	_circleInven.img->render(_circleInven.rc.left + CAMERAMANAGER->getScreen().left, _circleInven.rc.top + CAMERAMANAGER->getScreen().top);
	_circleWeapon.img->render(_circleWeapon.rc.left + CAMERAMANAGER->getScreen().left, _circleWeapon.rc.top + CAMERAMANAGER->getScreen().top);
	_swordImg.img->render(_swordImg.rc.left + CAMERAMANAGER->getScreen().left, _swordImg.rc.top + CAMERAMANAGER->getScreen().top);
	_circleHeart.img->render(_circleHeart.rc.left + CAMERAMANAGER->getScreen().left, _circleHeart.rc.top + CAMERAMANAGER->getScreen().top);
	//버튼 이미지
	_iButton.img->render(_iButton.rc.left + CAMERAMANAGER->getScreen().left, _iButton.rc.top + CAMERAMANAGER->getScreen().top);
	_spaceButton.img->render(_spaceButton.rc.left + CAMERAMANAGER->getScreen().left, _spaceButton.rc.top + CAMERAMANAGER->getScreen().top);
	//아이콘 이미지
	_iconBag.img->render(_iconBag.rc.left + CAMERAMANAGER->getScreen().left, _iconBag.rc.top + CAMERAMANAGER->getScreen().top);
	_iconHeart.img->render(_iconHeart.rc.left + CAMERAMANAGER->getScreen().left, _iconHeart.rc.top + CAMERAMANAGER->getScreen().top);
	_iconJump.img->render(_iconJump.rc.left + CAMERAMANAGER->getScreen().left, _iconJump.rc.top + CAMERAMANAGER->getScreen().top);
	_iconCoin.img->render(_iconCoin.rc.left + CAMERAMANAGER->getScreen().left, _iconCoin.rc.top + CAMERAMANAGER->getScreen().top);
	char size[64];
	size[32] = _itoa_s(_money, size, sizeof(&size[64]), 10);
	D2DMANAGER->RenderText(_iconCoin.rc.left + 20 + CAMERAMANAGER->getScreen().left, _iconCoin.rc.top + CAMERAMANAGER->getScreen().top, ConvertCtoWC(size), 10, D2DDEFAULTBRUSH::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"제주고딕");
	_iconMoenyBag.img->render(_iconMoenyBag.rc.left + CAMERAMANAGER->getScreen().left, _iconMoenyBag.rc.top + CAMERAMANAGER->getScreen().top);
	////프로그래스바 이미지
	//_prograssBarBack.img->render(_prograssBarBack.rc.left + CAMERAMANAGER->getScreen().left, _prograssBarBack.rc.top + CAMERAMANAGER->getScreen().top);
	//인벤토리 베이스 이미지
	if (_invenCheck)
	{

		_invenBase.img->render(_invenBase.rc.left + CAMERAMANAGER->getScreen().left, _invenBase.rc.top + CAMERAMANAGER->getScreen().top);
		_invenWill.img->frameRender(_invenWill.rc.left + CAMERAMANAGER->getScreen().left, _invenWill.rc.top + CAMERAMANAGER->getScreen().top, _invenWill.currentX, _invenWill.currentY);
		_sellSlime.img->frameRender(_sellSlime.rc.left + CAMERAMANAGER->getScreen().left, _sellSlime.rc.top + CAMERAMANAGER->getScreen().top, _sellSlime.currentX, _sellSlime.currentY);


		_cursor.img->render(_cursor.rc.left + CAMERAMANAGER->getScreen().left, _cursor.rc.top + CAMERAMANAGER->getScreen().top);
		_mirror.img->frameRender(_mirror.rc.left + CAMERAMANAGER->getScreen().left, _mirror.rc.top + CAMERAMANAGER->getScreen().top, _mirror.currentX, _mirror.currentY);

		//인벤토리 이미지
		for (int i = 0; i < _vitemBase.size(); ++i)
		{
			if (_vitemBase[i] == NULL) continue;
			char size[64];
			size[32] = _itoa_s((int)_vitemBase[i]->getItem().itemMax, size, sizeof(&size[64]), 10);
			_vitemBase[i]->getItem().img->render(_itemCoordinates[i].rc.left, _itemCoordinates[i].rc.top);
			D2DMANAGER->RenderText(_vitemBase[i]->getItem().x + 5 + CAMERAMANAGER->getScreen().left, _vitemBase[i]->getItem().y + 3 + CAMERAMANAGER->getScreen().top, ConvertCtoWC(size), 10);
		}
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			for (int i = 0; i < 21; i++)
			{
				D2DMANAGER->DrawRectangle(_itemCoordinates[i].rc);
			}
		}
		
		for (int i = 0; i < 20; i++)
		{
			if (!_itemSellImg[i].isSell) continue;
			_itemSellImg[i].img->render(_itemSellImg[i].rc.left, _itemSellImg[i].rc.top);
		}
		if (_isSellActive)
		{
			_sellSlimeActive.img->frameRender(_sellSlimeActive.rc.left + CAMERAMANAGER->getScreen().left, _sellSlimeActive.rc.top + CAMERAMANAGER->getScreen().top, _sellSlimeActive.currentX, _sellSlimeActive.currentY);
		}
		_swordImg.img->render(_swordImg.rc.left - 202 + CAMERAMANAGER->getScreen().left, _swordImg.rc.top + 67 + CAMERAMANAGER->getScreen().top);
		_kButton.img->render(_kButton.rc.left + CAMERAMANAGER->getScreen().left, _kButton.rc.top + 24 + CAMERAMANAGER->getScreen().top);
		D2DMANAGER->RenderTextField(_kButton.x + 25 + CAMERAMANAGER->getScreen().left, _kButton.rc.top + 18 + CAMERAMANAGER->getScreen().top, L"정렬", 12, 100, 30, D2DDEFAULTBRUSH::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"제주고딕");
	}


	if (_resultCheck)
	{
		//던전탐험관련
		D2DMANAGER->FillRectangle(_resultBack.rc, D2D1COLOR::Black, 0.8f);
		_resultInvenBase.img->render(_resultInvenBase.rc.left + CAMERAMANAGER->getScreen().left, _resultInvenBase.rc.top + CAMERAMANAGER->getScreen().top);
		_resultTitle.img->render(_resultTitle.rc.left + CAMERAMANAGER->getScreen().left, _resultTitle.rc.top + CAMERAMANAGER->getScreen().top);
		D2DMANAGER->RenderTextField(_resultTitle.x - 30 + CAMERAMANAGER->getScreen().left, _resultTitle.y - 8 + CAMERAMANAGER->getScreen().top, L"탐험 결과", 15, _resultTitle.img->getWidth(), _resultTitle.img->getHeight(), D2DDEFAULTBRUSH::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"제주고딕");
		_resultFootHold.img->render(_resultFootHold.rc.left + CAMERAMANAGER->getScreen().left, _resultFootHold.rc.top + CAMERAMANAGER->getScreen().top);
		_portalDoorOpen.img->render(_portalDoorOpen.rc.left + CAMERAMANAGER->getScreen().left, _portalDoorOpen.rc.top + CAMERAMANAGER->getScreen().top);
		_portalDoorAtive.img->frameRender(_portalDoorAtive.rc.left + CAMERAMANAGER->getScreen().left, _portalDoorAtive.rc.top + CAMERAMANAGER->getScreen().top, _portalDoorAtive.currentX, _portalDoorAtive.currentY);
		_resultEnemy.img->render(_resultEnemy.rc.left + CAMERAMANAGER->getScreen().left, _resultEnemy.rc.top + CAMERAMANAGER->getScreen().top);
		_resultEnemy2.img->render(_resultEnemy2.rc.left + CAMERAMANAGER->getScreen().left, _resultEnemy2.rc.top + CAMERAMANAGER->getScreen().top);
		_kButton.img->render(_kButton.rc.left + CAMERAMANAGER->getScreen().left, _kButton.rc.top + CAMERAMANAGER->getScreen().top);
		D2DMANAGER->RenderTextField(_kButton.x + 35 + CAMERAMANAGER->getScreen().left, _kButton.y - 5 + CAMERAMANAGER->getScreen().top, L"마을로 가기", 12, 100, 30, D2DDEFAULTBRUSH::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"제주고딕");
		for (int i = 0; i < _vHuntEnemy.size(); ++i)
		{
			_vHuntEnemy[i].img->frameRender(_vHuntEnemy[i].x + CAMERAMANAGER->getScreen().left, _vHuntEnemy[i].y + CAMERAMANAGER->getScreen().top, _vHuntEnemy[i].currentX, _vHuntEnemy[i].currentY);
		}
		//인벤토리 이미지
		for (int i = 0; i < _vitemBase.size(); ++i)
		{
			if (_vitemBase[i] == NULL) continue;
			char size[64];
			size[32] = _itoa_s((int)_vitemBase[i]->getItem().itemMax, size, sizeof(&size[64]), 10);
			_vitemBase[i]->getItem().img->render(_itemCoordinates[i].rc.left, _itemCoordinates[i].rc.top);
			D2DMANAGER->RenderText(_vitemBase[i]->getItem().x - 38 + CAMERAMANAGER->getScreen().left, _vitemBase[i]->getItem().y + 3 + CAMERAMANAGER->getScreen().top, ConvertCtoWC(size), 10);
		}
		_sellSlime.img->frameRender(_sellSlime.rc.left + CAMERAMANAGER->getScreen().left - 40, _sellSlime.rc.top + 2 + CAMERAMANAGER->getScreen().top, _sellSlime.currentX, _sellSlime.currentY);
		//판매할떄 이미지
		for (int i = 0; i < 20; i++)
		{
			if (!_itemSellImg[i].isSell) continue;
			_itemSellImg[i].img->render(_itemSellImg[i].rc.left, _itemSellImg[i].rc.top);
		}
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			for (int i = 0; i < 21; i++)
			{
				D2DMANAGER->DrawRectangle(_itemCoordinates[i].rc);
			}
		}
		
		//잡은 적 이미지
		char size[64];
		size[32] = _itoa_s((int)_vHuntEnemy.size(), size, sizeof(&size[64]), 10);
		D2DMANAGER->RenderTextField(_resultEnemy2.rc.right + 225 + CAMERAMANAGER->getScreen().left, _resultEnemy2.rc.top - 15 + CAMERAMANAGER->getScreen().top, L"X ", 12, 20, 30, D2DDEFAULTBRUSH::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"제주고딕");
		D2DMANAGER->RenderTextField(_resultEnemy2.rc.right + 235 + CAMERAMANAGER->getScreen().left, _resultEnemy2.rc.top - 15 + CAMERAMANAGER->getScreen().top, ConvertCtoWC(size), 12, 50, 30, D2DDEFAULTBRUSH::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"제주고딕");
	}

	//일시정지 이미지
	D2DMANAGER->FillRectangle(_pauseBase.rc, D2D1COLOR::Black, _pauseBase.alpha);
	if (_pauseCheck)
	{
		_pauseEye.img->render(_pauseEye.rc.left + CAMERAMANAGER->getScreen().left, _pauseEye.rc.top + CAMERAMANAGER->getScreen().top);
		_pauseSquareUp.img->render(_pauseSquareUp.rc.left + CAMERAMANAGER->getScreen().left, _pauseSquareUp.rc.top + CAMERAMANAGER->getScreen().top);
		_pauseSquareDown.img->render(_pauseSquareDown.rc.left + CAMERAMANAGER->getScreen().left, _pauseSquareDown.rc.top + CAMERAMANAGER->getScreen().top);
		_pauseTailDown.img->render(_pauseTailDown.rc.left + CAMERAMANAGER->getScreen().left, _pauseTailDown.rc.top + CAMERAMANAGER->getScreen().top);
		_pauseHotdogLeft.img->render(_pauseHotdogLeft.rc.left + CAMERAMANAGER->getScreen().left, _pauseHotdogLeft.rc.top + CAMERAMANAGER->getScreen().top);
		_pauseHotdogRight.img->render(_pauseHotdogRight.rc.left + CAMERAMANAGER->getScreen().left, _pauseHotdogRight.rc.top + CAMERAMANAGER->getScreen().top);

		//일시정지 창에서 닫힐 때 및 열릴 때 애니메이션 효과 끝난 후 보여줌
		if (_pauseOpen)
		{
			_pauseSelectLeft.img->render(_pauseSelectLeft.rc.left + CAMERAMANAGER->getScreen().left, _pauseSelectLeft.rc.top + CAMERAMANAGER->getScreen().top);
			_pauseSelectRight.img->render(_pauseSelectRight.rc.left + CAMERAMANAGER->getScreen().left, _pauseSelectRight.rc.top + CAMERAMANAGER->getScreen().top);

			D2DMANAGER->RenderTextField(_winsizeX + CAMERAMANAGER->getScreen().left - 75, _winsizeY + CAMERAMANAGER->getScreen().top - 120, L"게임으로 돌아가기", 20, 200, 50, D2DDEFAULTBRUSH::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"제주고딕");
			D2DMANAGER->RenderTextField(_winsizeX + CAMERAMANAGER->getScreen().left - 20, _winsizeY + CAMERAMANAGER->getScreen().top - 90, L"옵션", 20, 200, 50, D2DDEFAULTBRUSH::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"제주고딕");
			D2DMANAGER->RenderTextField(_winsizeX + CAMERAMANAGER->getScreen().left - 20, _winsizeY + CAMERAMANAGER->getScreen().top - 60, L"종료", 20, 200, 50, D2DDEFAULTBRUSH::White, DWRITE_TEXT_ALIGNMENT_LEADING, L"제주고딕");
		}
	}



}

void UI::setting()
{
	IMAGEMANAGER->addDImage("Circle_How", L"UI/Circle_How.png", 50, 50);
	IMAGEMANAGER->addDImage("Gold_circle", L"UI/Gold_circle.png", 35, 35);
	IMAGEMANAGER->addDImage("HealthBar_Circle", L"UI/HealthBar_Circle.png", 24, 24);
	IMAGEMANAGER->addDImage("I_Button", L"UI/I_Button.png", 20, 20);
	IMAGEMANAGER->addDImage("J_Button", L"UI/J_Button.png", 20, 20);
	IMAGEMANAGER->addDImage("L_Button", L"UI/L_Button.png", 20, 20);
	IMAGEMANAGER->addDImage("K_Button", L"UI/K_Button.png", 20, 20);
	IMAGEMANAGER->addDImage("SPACE_Button", L"UI/SPACE_Button.png", 20, 20);
	IMAGEMANAGER->addDImage("Bag", L"UI/Bag.png", 23, 26);
	IMAGEMANAGER->addDImage("Heart", L"UI/Heart.png", 10, 9);
	IMAGEMANAGER->addDImage("JumpMotion", L"UI/JumpMotion.png", 17, 19);
	IMAGEMANAGER->addDImage("Item_Coin", L"UI/Item_Coin.png", 9, 9);
	IMAGEMANAGER->addDImage("Gold4", L"UI/Gold4.png", 25, 28);
	IMAGEMANAGER->addDImage("HealthBar_Base", L"UI/HealthBar_Base.png", 73, 22);
	IMAGEMANAGER->addDImage("Inventory_base", L"UI/Inventory_base.png", 519, 274);
	IMAGEMANAGER->addDImage("Bag_paperbase", L"UI/Bag_paperbase.png", 241, 272);
	IMAGEMANAGER->addDImage("GUI_Pause_Triangles_Up", L"UI/GUI_Pause_Triangles_Up.png", 150, 15);
	IMAGEMANAGER->addDImage("GUI_Pause_Triangles_Down", L"UI/GUI_Pause_Triangles_Down.png", 150, 15);
	IMAGEMANAGER->addDImage("GUI_Pause_Tail_Up", L"UI/GUI_Pause_Tail_Up.png", 42, 23);
	IMAGEMANAGER->addDImage("GUI_Pause_Tail_Down", L"UI/GUI_Pause_Tail_Down.png", 42, 23);
	IMAGEMANAGER->addDImage("GUI_Pause_Arm_Left", L"UI/GUI_Pause_Arm_Left.png", 25, 42);
	IMAGEMANAGER->addDImage("GUI_Pause_Arm_Right", L"UI/GUI_Pause_Arm_Right.png", 25, 42);
	IMAGEMANAGER->addDImage("MenuChoiceIcon_Left", L"UI/MenuChoiceIcon_Left.png", 19, 19);
	IMAGEMANAGER->addDImage("MenuChoiceIcon_Right", L"UI/MenuChoiceIcon_Right.png", 19, 19);
	IMAGEMANAGER->addDImage("GUI_Pause_Eye", L"UI/GUI_Pause_Eye.png", 19, 19);
	IMAGEMANAGER->addDImage("GUI_Pause_Eye", L"UI/GUI_Pause_Eye.png", 19, 19);
	IMAGEMANAGER->addFrameDImage("Inventory_Will", L"UI/will_idle_down.png", 400, 76, 10, 1);
	IMAGEMANAGER->addDImage("Sword_Image", L"UI/soldier_short_sword.png", 32, 32);
	IMAGEMANAGER->addFrameDImage("Slime_Hunt", L"Enemy/slime_walk.png", 168, 24, 8, 1);
	IMAGEMANAGER->addFrameDImage("MiniBoss_HunT", L"MiniBoss/MiniBoss_idle_down.png", 680, 108, 8, 1);
	IMAGEMANAGER->addDImage("cursor", L"ITEM/selector.png", 32, 32);
	IMAGEMANAGER->addFrameDImage("sellSlime", L"UI/itemSellSlime.png", 280, 32, 10, 1);
	IMAGEMANAGER->addFrameDImage("sellSlimeActive", L"UI/itemSellSlimeActive.png", 288, 36, 8, 1);
	IMAGEMANAGER->addFrameDImage("mirror", L"UI/mirror.png", 816, 110, 8, 1);


	//사이즈
	_winsizeX = 1300 / 4;
	_winsizeY = 1066 / 4;

	//아이템 커서




	//인벤토리 아이템 좌표 셋팅
	for (int i = 0; i < 20; i++)
	{
		_itemCoordinates[i].x = 132 + (i % 5) * 36;
		_itemCoordinates[i].y = 118 + (i / 5) * 43;
		if (i / 5 >= 2) _itemCoordinates[i].y = 197 + (i / 5) / 3 * 36;
		_itemCoordinates[i].rc = RectMakeCenter(_itemCoordinates[i].x, _itemCoordinates[i].y, 32, 32);

	}
	_itemCoordinates[20].x = _invenBase.x + 132;
	_itemCoordinates[20].y = _invenBase.y + 292;
	_itemCoordinates[20].rc = RectMakeCenter(_itemCoordinates[20].x, _itemCoordinates[20].y, 32, 32);
	_cursor.img = IMAGEMANAGER->findDImage("cursor");
	_curIndex = 0;
	_cursor.x = _itemCoordinates[0].x;
	_cursor.y = _itemCoordinates[0].y;
	_cursor.rc = RectMakeCenter(_cursor.x, _cursor.y, _cursor.img->getWidth(), _cursor.img->getHeight());

	_sellSlime.img = IMAGEMANAGER->findDImage("sellSlime");
	_sellSlime.x = _itemCoordinates[20].x;
	_sellSlime.y = _itemCoordinates[20].y;
	_sellSlime.count = 0;
	_sellSlime.currentX = _sellSlime.currentY = 0;
	_sellSlime.rc = RectMakeCenter(_sellSlime.x, _sellSlime.y, _sellSlime.img->getFrameWidth(), _sellSlime.img->getFrameHeight());

	_isSellActive = false;

	_sellSlimeActive.img = IMAGEMANAGER->findDImage("sellSlimeActive");
	_sellSlimeActive.x = _cursor.x;
	_sellSlimeActive.y = _cursor.y - 32;
	_sellSlimeActive.count = 0;
	_sellSlimeActive.currentX = _sellSlimeActive.currentY = 0;
	_sellSlimeActive.rc = RectMakeCenter(_sellSlimeActive.x, _sellSlimeActive.y, _sellSlimeActive.img->getFrameWidth(), _sellSlimeActive.img->getFrameHeight());

	_mirror.img = IMAGEMANAGER->findDImage("mirror");
	_mirror.x = _itemCoordinates[20].x;
	_mirror.y = _itemCoordinates[20].y;
	_mirror.count = 0;
	_mirror.currentX = _mirror.currentY = 0;
	_mirror.rc = RectMakeCenter(_mirror.x, _mirror.y, _mirror.img->getFrameWidth(), _mirror.img->getFrameHeight());

	//던전결과 관련
	IMAGEMANAGER->addDImage("DunGeon_ResultTitle", L"UI/DunGeon_ResultTitle.png", 113, 17);
	IMAGEMANAGER->addDImage("DunGeon_ResultFootHold", L"UI/Base_GolemDungeon.png", 97, 135);
	IMAGEMANAGER->addFrameDImage("Portal_Active", L"DunGeon/Portal_Active.png", 240, 21, 6, 1);
	IMAGEMANAGER->addDImage("DunGeonUI_Door", L"UI/DunGeonUI_Door.png", 60, 57);
	IMAGEMANAGER->addDImage("Base_Enemies_Golem", L"UI/Base_Enemies_Golem.png", 221, 70);
	//던전결과 관련
	_resultTitle.img = IMAGEMANAGER->findDImage("DunGeon_ResultTitle");
	_resultTitle.x = 325;
	_resultTitle.y = 30;
	_resultTitle.rc = RectMakeCenter(_resultTitle.x, _resultTitle.y, _resultTitle.img->getWidth(), _resultTitle.img->getHeight());
	_resultBack.x = 325;
	_resultBack.y = 280;
	_resultBack.rc = RectMakeCenter(_resultBack.x, _resultBack.y, 1000, 1000);
	_resultFootHold.img = IMAGEMANAGER->findDImage("DunGeon_ResultFootHold");
	_resultFootHold.x = 325;
	_resultFootHold.y = 60;
	_resultFootHold.rc = RectMakeCenter(_resultFootHold.x, _resultFootHold.y, _resultFootHold.img->getWidth(), _resultFootHold.img->getHeight());
	_portalDoorAtive.img = IMAGEMANAGER->findDImage("Portal_Active");
	_portalDoorAtive.x = 325;
	_portalDoorAtive.y = 86;
	_portalDoorAtive.count = 0;
	_portalDoorAtive.currentX = 0;
	_portalDoorAtive.currentY = 0;
	_portalDoorAtive.rc = RectMakeCenter(_portalDoorAtive.x, _portalDoorAtive.y, _portalDoorAtive.img->getFrameWidth(), _portalDoorAtive.img->getFrameHeight());
	_portalDoorOpen.img = IMAGEMANAGER->findDImage("DunGeonUI_Door");
	_portalDoorOpen.x = 295;
	_portalDoorOpen.y = 50;
	_portalDoorOpen.rc = RectMakeCenter(_portalDoorOpen.x, _portalDoorOpen.y, _portalDoorOpen.img->getFrameWidth(), _portalDoorOpen.img->getFrameHeight());
	_resultEnemy.img = IMAGEMANAGER->findDImage("Base_Enemies_Golem");
	_resultEnemy.x = 360;
	_resultEnemy.y = 170;
	_resultEnemy.rc = RectMakeCenter(_resultEnemy.x, _resultEnemy.y, _resultEnemy.img->getWidth(), _resultEnemy.img->getHeight());
	_resultEnemy2.img = IMAGEMANAGER->findDImage("Base_Enemies_Golem");
	_resultEnemy2.x = 360;
	_resultEnemy2.y = 240;
	_resultEnemy2.rc = RectMakeCenter(_resultEnemy2.x, _resultEnemy2.y, _resultEnemy2.img->getWidth(), _resultEnemy2.img->getHeight());
	_kButton.img = IMAGEMANAGER->findDImage("K_Button");
	_kButton.x = 280;
	_kButton.y = 320;
	_kButton.rc = RectMakeCenter(_kButton.x, _kButton.y, _kButton.img->getWidth(), _kButton.img->getHeight());
	//인벤토리 이미지
	_resultInvenBase.img = IMAGEMANAGER->findDImage("Bag_paperbase");
	_resultInvenBase.x = 150;
	_resultInvenBase.y = 200;



	//배경 원 이미지 
	_circleGold.img = IMAGEMANAGER->findDImage("Gold_circle");
	_circleGold.x = 30;
	_circleGold.y = 30;
	_circleInven.img = IMAGEMANAGER->findDImage("Gold_circle");
	_circleInven.x = 600;
	_circleInven.y = 100;
	_circleWeapon.img = IMAGEMANAGER->findDImage("Gold_circle");
	_circleWeapon.x = 600;
	_circleWeapon.y = 50;
	_swordImg.img = IMAGEMANAGER->findDImage("Sword_Image");
	_swordImg.x = 600;
	_swordImg.y = 50;
	_circleHeart.img = IMAGEMANAGER->findDImage("HealthBar_Circle");
	_circleHeart.x = 70;
	_circleHeart.y = 25;

	//버튼 이미지
	_iButton.img = IMAGEMANAGER->findDImage("I_Button");
	_iButton.x = 585;
	_iButton.y = 117;
	_spaceButton.img = IMAGEMANAGER->findDImage("SPACE_Button");
	_spaceButton.x = 580;
	_spaceButton.y = 15;

	//아이콘 이미지
	_iconBag.img = IMAGEMANAGER->findDImage("Bag");
	_iconBag.x = 600;
	_iconBag.y = 100;
	_iconHeart.img = IMAGEMANAGER->findDImage("Heart");
	_iconHeart.x = 70;
	_iconHeart.y = 25;
	_iconJump.img = IMAGEMANAGER->findDImage("JumpMotion");
	_iconJump.x = 570;
	_iconJump.y = 27;
	_iconCoin.img = IMAGEMANAGER->findDImage("Item_Coin");
	_iconCoin.x = 15;
	_iconCoin.y = 60;
	_iconMoenyBag.img = IMAGEMANAGER->findDImage("Gold4");
	_iconMoenyBag.x = 30;
	_iconMoenyBag.y = 30;
	//인벤토리 이미지
	_invenBase.img = IMAGEMANAGER->findDImage("Inventory_base");
	_invenBase.x = 330;
	_invenBase.y = 200;
	_invenCheck = false;
	////프로그래스바 이미지
	//_prograssBarBack.img = IMAGEMANAGER->findDImage("HealthBar_Base");
	//_prograssBarBack.x = 115;
	//_prograssBarBack.y = 25;
	//일시정지 이미지
	_pauseBase.x = 1300 / 2;
	_pauseBase.y = 1066 / 2;
	_pauseBase.rc = RectMakeCenter(_pauseBase.x, _pauseBase.y, WINSIZEX * 7, WINSIZEY * 7);
	_pauseBase.alpha = 0;
	_pauseEye.img = IMAGEMANAGER->findDImage("GUI_Pause_Eye");
	_pauseEye.x = 1300 / 4;
	_pauseEye.y = 1066 / 4 - 90;
	_pauseEye.rc = RectMakeCenter(_pauseEye.x, _pauseEye.y, _pauseEye.img->getWidth(), _pauseEye.img->getHeight());
	_pauseSquareUp.img = IMAGEMANAGER->findDImage("GUI_Pause_Triangles_Down");
	_pauseSquareUp.x = 1300 / 4;
	_pauseSquareUp.y = 1066 / 4 - 70;
	_pauseSquareUp.rc = RectMakeCenter(_pauseSquareUp.x, _pauseSquareUp.y, _pauseSquareUp.img->getWidth(), _pauseSquareUp.img->getHeight());
	_pauseSquareDown.img = IMAGEMANAGER->findDImage("GUI_Pause_Triangles_Up");
	_pauseSquareDown.x = 1300 / 4;
	_pauseSquareDown.y = 1066 / 4 - 60;
	_pauseSquareDown.rc = RectMakeCenter(_pauseSquareDown.x, _pauseSquareDown.y, _pauseSquareDown.img->getWidth(), _pauseSquareDown.img->getHeight());
	_pauseTailDown.img = IMAGEMANAGER->findDImage("GUI_Pause_Tail_Down");
	_pauseTailDown.x = 1300 / 4;
	_pauseTailDown.y = 1066 / 4 - 30;
	_pauseTailDown.rc = RectMakeCenter(_pauseTailDown.x, _pauseTailDown.y, _pauseTailDown.img->getWidth(), _pauseTailDown.img->getHeight());
	_pauseHotdogLeft.img = IMAGEMANAGER->findDImage("GUI_Pause_Arm_Left");
	_pauseHotdogLeft.x = 1300 / 4 - 100;
	_pauseHotdogLeft.y = 1066 / 4 - 45;
	_pauseHotdogLeft.rc = RectMakeCenter(_pauseHotdogLeft.x, _pauseHotdogLeft.y, _pauseHotdogLeft.img->getWidth(), _pauseHotdogLeft.img->getHeight());
	_pauseHotdogRight.img = IMAGEMANAGER->findDImage("GUI_Pause_Arm_Right");
	_pauseHotdogRight.x = 1300 / 4 + 100;
	_pauseHotdogRight.y = 1066 / 4 - 45;
	_pauseHotdogRight.rc = RectMakeCenter(_pauseHotdogRight.x, _pauseHotdogRight.y, _pauseHotdogRight.img->getWidth(), _pauseHotdogRight.img->getHeight());
	_pauseSelectLeft.img = IMAGEMANAGER->findDImage("MenuChoiceIcon_Left");
	_pauseSelectLeft.x = 1300 / 4 - 100;
	_pauseSelectLeft.y = 1066 / 4 - 95;
	_pauseSelectLeft.rc = RectMakeCenter(_pauseSelectLeft.x, _pauseSelectLeft.y, _pauseSelectLeft.img->getWidth(), _pauseSelectLeft.img->getHeight());

	_pauseSelectRight.img = IMAGEMANAGER->findDImage("MenuChoiceIcon_Right");
	_pauseSelectRight.x = 1300 / 4 + 100;
	_pauseSelectRight.y = 1066 / 4 - 95;
	_pauseSelectRight.rc = RectMakeCenter(_pauseSelectRight.x, _pauseSelectRight.y, _pauseSelectRight.img->getWidth(), _pauseSelectRight.img->getHeight());

	_invenWill.img = IMAGEMANAGER->findDImage("Inventory_Will");
	_invenWill.x = _invenBase.x + 130;
	_invenWill.y = _invenBase.y;
	_invenWill.count = 0;
	_invenWill.currentX = _invenWill.currentY = 0;
	_invenWill.rc = RectMakeCenter(_invenWill.x, _invenWill.y, _invenWill.img->getFrameWidth(), _invenWill.img->getFrameHeight());


	//배경 원 렉트
	_circleGold.rc = RectMakeCenter(_circleGold.x, _circleGold.y, _circleGold.img->getWidth(), _circleGold.img->getHeight());
	_circleInven.rc = RectMakeCenter(_circleInven.x, _circleInven.y, _circleInven.img->getWidth(), _circleInven.img->getHeight());
	_circleWeapon.rc = RectMakeCenter(_circleWeapon.x, _circleWeapon.y, _circleWeapon.img->getWidth(), _circleWeapon.img->getHeight());
	_swordImg.rc = RectMakeCenter(_swordImg.x, _swordImg.y, _swordImg.img->getWidth(), _swordImg.img->getHeight());
	_circleHeart.rc = RectMakeCenter(_circleHeart.x, _circleHeart.y, _circleHeart.img->getWidth(), _circleHeart.img->getHeight());
	//버튼 렉트
	_iButton.rc = RectMakeCenter(_iButton.x, _iButton.y, _iButton.img->getWidth(), _iButton.img->getHeight());
	_spaceButton.rc = RectMakeCenter(_spaceButton.x, _spaceButton.y, _spaceButton.img->getWidth(), _spaceButton.img->getHeight());
	//아이콘 이미지
	_iconBag.rc = RectMakeCenter(_iconBag.x, _iconBag.y, _iconBag.img->getWidth(), _iconBag.img->getHeight());
	_iconHeart.rc = RectMakeCenter(_iconHeart.x, _iconHeart.y, _iconHeart.img->getWidth(), _iconHeart.img->getHeight());
	_iconJump.rc = RectMakeCenter(_iconJump.x, _iconJump.y, _iconJump.img->getWidth(), _iconJump.img->getHeight());
	_iconCoin.rc = RectMakeCenter(_iconCoin.x, _iconCoin.y, _iconCoin.img->getWidth(), _iconCoin.img->getHeight());
	_iconMoenyBag.rc = RectMakeCenter(_iconMoenyBag.x, _iconMoenyBag.y, _iconMoenyBag.img->getWidth(), _iconMoenyBag.img->getHeight());
	////프로그래스바 렉트
	//_prograssBarBack.rc = RectMakeCenter(_prograssBarBack.x, _prograssBarBack.y, _prograssBarBack.img->getWidth(), _prograssBarBack.img->getHeight());
	//인벤토리 베이스 렉트
	_invenBase.rc = RectMakeCenter(_invenBase.x, _invenBase.y, _invenBase.img->getWidth(), _invenBase.img->getHeight());
	_resultInvenBase.rc = RectMakeCenter(_resultInvenBase.x, _resultInvenBase.y, _resultInvenBase.img->getWidth(), _resultInvenBase.img->getHeight());
}

void UI::pause()
{
	//일시정지 창이 열리면
	if (_pauseCheck)
	{
		//일시정지 창 열기
		if (!_pauseOpen && !_pauseAnimation) pauseOpen();
		//일시정치 창 닫음
		if (_pauseAnimation) pauseClose();
		//알파값 설정
		_pauseBase.alpha += 0.1f;
		if (_pauseBase.alpha >= 0.7f) _pauseBase.alpha = 0.7f;
	}
	//일시정지 창이 열리면
	if (_pauseCheck)
	{
		//일시정지 창 메뉴 선택 관리
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			SOUNDMANAGER->play("MenuChoice");
			_pauseMenuSelect++;
			if (_pauseMenuSelect >= 2) _pauseMenuSelect = 2;
		}
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			SOUNDMANAGER->play("MenuChoice");
			_pauseMenuSelect--;
			if (_pauseMenuSelect <= 0) _pauseMenuSelect = 0;
		}
		//선택아이콘 위치 조정 및 버튼 조작
		switch (_pauseMenuSelect)
		{
			//게임으로 돌아가기
		case 0:
			if (KEYMANAGER->isOnceKeyDown('J')) _pauseAnimation = true;
			_pauseSelectLeft.x = 1300 / 4 - 100;
			_pauseSelectLeft.y = 1066 / 4 - 95;
			_pauseSelectRight.x = 1300 / 4 + 100;
			_pauseSelectRight.y = 1066 / 4 - 95;
			break;
			//옵션
		case 1:
			_pauseSelectLeft.x = 1300 / 4 - 50;
			_pauseSelectLeft.y = 1066 / 4 - 65;
			_pauseSelectRight.x = 1300 / 4 + 50;
			_pauseSelectRight.y = 1066 / 4 - 65;
			break;
			//게임 종료
		case 2:
			_pauseSelectLeft.x = 1300 / 4 - 50;
			_pauseSelectLeft.y = 1066 / 4 - 35;
			_pauseSelectRight.x = 1300 / 4 + 50;
			_pauseSelectRight.y = 1066 / 4 - 35;
			//게임을 종료할때 플레이어의 좌표를 초기화해준다.
			if (KEYMANAGER->isOnceKeyDown('J'))
			{
				INIDATA->addData("shop", "playerX", NULL);
				INIDATA->addData("shop", "playerY", NULL);
				INIDATA->addData("village", "playerX", NULL);
				INIDATA->addData("village", "playerY", NULL);
				INIDATA->addData("deongeonChoice", "playerX", NULL);
				INIDATA->addData("deongeonChoice", "playerY", NULL);
				INIDATA->iniSave("PlayerCoordinate");
				exit(0);
			}
			break;
		}
	}
	//일시정지 창이 비활성화 되어있을 때 위치 및 알파 값 조정
	if (!_pauseCheck)
	{
		_pauseEye.y = 1066 / 4 - 90;
		_pauseSquareUp.y = 1066 / 4 - 70;
		_pauseSquareDown.y = 1066 / 4 - 60;
		_pauseTailDown.y = 1066 / 4 - 30;
		_pauseHotdogLeft.y = 1066 / 4 - 45;
		_pauseHotdogRight.y = 1066 / 4 - 45;

		_pauseBase.alpha -= 0.1f;
		if (_pauseBase.alpha <= 0) _pauseBase.alpha = 0;
	}

	//렉트 위치 및 크기 재정의
	_pauseSelectLeft.rc = RectMakeCenter(_pauseSelectLeft.x, _pauseSelectLeft.y, _pauseSelectLeft.img->getWidth(), _pauseSelectLeft.img->getHeight());
	_pauseSelectRight.rc = RectMakeCenter(_pauseSelectRight.x, _pauseSelectRight.y, _pauseSelectRight.img->getWidth(), _pauseSelectRight.img->getHeight());

	_pauseEye.rc = RectMakeCenter(_pauseEye.x, _pauseEye.y, _pauseEye.img->getWidth(), _pauseEye.img->getHeight());
	_pauseSquareUp.rc = RectMakeCenter(_pauseSquareUp.x, _pauseSquareUp.y, _pauseSquareUp.img->getWidth(), _pauseSquareUp.img->getHeight());
	_pauseSquareDown.rc = RectMakeCenter(_pauseSquareDown.x, _pauseSquareDown.y, _pauseSquareDown.img->getWidth(), _pauseSquareDown.img->getHeight());
	_pauseTailDown.rc = RectMakeCenter(_pauseTailDown.x, _pauseTailDown.y, _pauseTailDown.img->getWidth(), _pauseTailDown.img->getHeight());
	_pauseHotdogLeft.rc = RectMakeCenter(_pauseHotdogLeft.x, _pauseHotdogLeft.y, _pauseHotdogLeft.img->getWidth(), _pauseHotdogLeft.img->getHeight());
	_pauseHotdogRight.rc = RectMakeCenter(_pauseHotdogRight.x, _pauseHotdogRight.y, _pauseHotdogRight.img->getWidth(), _pauseHotdogRight.img->getHeight());
	_pauseSelectLeft.rc = RectMakeCenter(_pauseSelectLeft.x, _pauseSelectLeft.y, _pauseSelectLeft.img->getWidth(), _pauseSelectLeft.img->getHeight());
}
//일시정지 창 오픈시 함수
void UI::pauseOpen()
{
	_pauseSquareDown.y -= 3;
	_pauseEye.y -= 3;

	_pauseSquareUp.y += 3;
	_pauseTailDown.y += 3;
	_pauseHotdogLeft.y += 3;
	_pauseHotdogRight.y += 3;

	if (_pauseSquareDown.y <= 1066 / 4 - 130 && _pauseSquareUp.y >= 1066 / 4)
	{
		_pauseAnimation = false;
		_pauseOpen = true;
	}
}
//일시정지 창 닫힐시 함수
void UI::pauseClose()
{
	_pauseOpen = false;
	_pauseSquareDown.y += 3;
	_pauseEye.y += 3;

	_pauseSquareUp.y -= 3;
	_pauseTailDown.y -= 3;
	_pauseHotdogLeft.y -= 3;
	_pauseHotdogRight.y -= 3;

	if (_pauseSquareDown.y >= 1066 / 4 - 60 && _pauseSquareUp.y <= 1066 / 4 - 70)
	{
		_pauseAnimation = false;
		_pauseCheck = false;
	}

}

void UI::resultUI()
{
	_portalDoorAtive.count++;
	if (_portalDoorAtive.count % 7 == 0)
	{
		_portalDoorAtive.currentX++;
		if (_portalDoorAtive.currentX > _portalDoorAtive.img->getMaxFrameX())
		{
			_portalDoorAtive.currentX = 0;
			_portalDoorAtive.count = 0;

		}
	}

	_resultBack.rc = RectMakeCenter(_resultBack.x + CAMERAMANAGER->getScreen().left, _resultBack.y + CAMERAMANAGER->getScreen().top, 1000, 1000);
	_portalDoorAtive.rc = RectMakeCenter(_portalDoorAtive.x, _portalDoorAtive.y, _portalDoorAtive.img->getFrameWidth(), _portalDoorAtive.img->getFrameHeight());
	_portalDoorOpen.rc = RectMakeCenter(_portalDoorOpen.x, _portalDoorOpen.y, _portalDoorOpen.img->getFrameWidth(), _portalDoorOpen.img->getFrameHeight());
	_resultEnemy.rc = RectMakeCenter(_resultEnemy.x, _resultEnemy.y, _resultEnemy.img->getFrameWidth(), _resultEnemy.img->getFrameHeight());
	_resultEnemy2.rc = RectMakeCenter(_resultEnemy2.x, _resultEnemy2.y, _resultEnemy2.img->getFrameWidth(), _resultEnemy2.img->getFrameHeight());
	_kButton.rc = RectMakeCenter(_kButton.x, _kButton.y, _kButton.img->getFrameWidth(), _kButton.img->getFrameHeight());
}

void UI::cursorSet()
{

	_curIndex = 0;
	_cursor.x = _itemCoordinates[0].x;
	_cursor.y = _itemCoordinates[0].y;
	_cursor.rc = RectMakeCenter(_cursor.x, _cursor.y, _cursor.img->getWidth(), _cursor.img->getHeight());


}

void UI::cursorUpdate()
{
	//아이템의 size가 NULL이라면

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		SOUNDMANAGER->play("MenuChoice");
		if (_curIndex % 5 == 0) _curIndex = _curIndex;
		else _curIndex--;

	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		SOUNDMANAGER->play("MenuChoice");
		if (_curIndex % 5 == 4) _curIndex = _curIndex;
		else _curIndex++;
		if (_curIndex >= 20) _curIndex = 20;

	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		SOUNDMANAGER->play("MenuChoice");
		if (_curIndex / 5 == 0) _curIndex = _curIndex;
		else _curIndex -= 5;

	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		SOUNDMANAGER->play("MenuChoice");
		if (_curIndex / 5 == 4) _curIndex = _curIndex;
		else _curIndex += 5;
		if (_curIndex >= 20) _curIndex = 20;

	}
	_cursor.x = _itemCoordinates[_curIndex].x;
	_cursor.y = _itemCoordinates[_curIndex].y;



	_sellSlimeActive.x = _cursor.x;
	_sellSlimeActive.y = _cursor.y - 32;
	_mirror.x = _itemCoordinates[20].x - 12;
	_mirror.y = _itemCoordinates[20].y + 12;
	_cursor.rc = RectMakeCenter(_cursor.x, _cursor.y, _cursor.img->getWidth(), _cursor.img->getHeight());
	_sellSlimeActive.rc = RectMakeCenter(_sellSlimeActive.x, _sellSlimeActive.y, _sellSlimeActive.img->getFrameWidth(), _sellSlimeActive.img->getFrameHeight());
	_mirror.rc = RectMakeCenter(_mirror.x, _mirror.y, _mirror.img->getFrameWidth(), _mirror.img->getFrameHeight());

	for (int i = 0; i < 21; i++)
	{
		_itemCoordinates[i].rc = RectMakeCenter(_itemCoordinates[i].x + CAMERAMANAGER->getScreen().left, _itemCoordinates[i].y + CAMERAMANAGER->getScreen().top, 32, 32);
	}

}

void UI::sellItemFrame()
{
	for (int i = 0; i < 20; i++)
	{
		if (_itemSellImg[i].isSell)
		{
			_itemSellImg[i].x += cosf(_itemSellImg[i].angle) * 2;
			_itemSellImg[i].y += -sinf(_itemSellImg[i].angle) * 2;
			_itemSellImg[i].rc = RectMakeCenter(_itemSellImg[i].x + CAMERAMANAGER->getScreen().left, _itemSellImg[i].y + CAMERAMANAGER->getScreen().top, 32, 32);

		}
		RECT temp;
		if (IntersectRect(&temp, &_itemSellImg[i].rc, &_itemCoordinates[20].rc))
		{
			_itemSellImg[i].isSell = false;
		}
	}
}

void UI::huntEnemy(int huntNum, int miniboss)
{
	//잡은 적 표시
	if (_resultCheck && !_vHuntEnemyCheck)
	{
		//잡은 적을 백터에 넣어줌
		for (int i = 0; i < huntNum; ++i)
		{
			tagUIobject huntEnemy;
			huntEnemy.img = IMAGEMANAGER->findDImage("Slime_Hunt");
			huntEnemy.x = 0;
			huntEnemy.y = 0;
			huntEnemy.count = 0;
			huntEnemy.currentX = 0;
			huntEnemy.currentY = 0;
			_vHuntEnemy.push_back(huntEnemy);
		}
		//잡은 적을 백터에 넣어줌
		for (int i = 0; i < miniboss; ++i)
		{
			tagUIobject huntEnemy;
			huntEnemy.img = IMAGEMANAGER->findDImage("MiniBoss_HunT");
			huntEnemy.x = 0;
			huntEnemy.y = 0;
			huntEnemy.count = 0;
			huntEnemy.currentX = 0;
			huntEnemy.currentY = 0;
			_vHuntEnemy.push_back(huntEnemy);
		}
		//잡은 적의 x,y 및 설정
		for (int i = 0; i < _vHuntEnemy.size(); ++i)
		{
			_vHuntEnemy[i].x = 370 + (i % 10 * 20);
			_vHuntEnemy[i].y = 170 + (i / 10 * 10);

			_vHuntEnemy[i].currentX = 0;
			_vHuntEnemy[i].currentY = 0;
		}
		_vHuntEnemyCheck = true;
	}
	if (_resultCheck)
	{
		//잡은 적의 프레임 이미지
		for (int i = 0; i < _vHuntEnemy.size(); ++i)
		{
			_vHuntEnemy[i].count++;
			if (_vHuntEnemy[i].count % 7 == 0)
			{
				_vHuntEnemy[i].currentX++;
				if (_vHuntEnemy[i].currentX > _vHuntEnemy[i].img->getMaxFrameX())_vHuntEnemy[i].currentX = 0;
			}
		}
	}

}

void UI::itemGet(string name)
{
	//아이템의 size가 NULL이라면 
	if (_vitemBase.size() == NULL)
	{
		//획득한 아이템을 벡터에 담아주고 해당 아이템 개수를 하나 늘린다.
		_vitemBase.push_back(_itemManager->getItem(name));
		for (int i = 0; i < _vitemBase.size(); ++i)
		{
			if (_vitemBase[i]->getItem().name == name)
			{
				_vitemBase[i]->setItemItemMax(_vitemBase[i]->getItem().itemMax + 1);
				_vitemBase[i]->setItemName(_vitemBase[i]->getItem().name);
				_vitemBase[i]->setItemX(_itemCoordinates[0].x);
				_vitemBase[i]->setItemY(_itemCoordinates[0].y);
				_vitemBase[i]->setItemRC(_itemCoordinates[0].rc);

				char cha[64];
				cha[63] = _itoa_s(_vitemBase[i]->getItem().itemMax, cha, sizeof(cha), 10);
				INIDATA->addData(name.c_str(), "Item_Count", cha);
				INIDATA->iniSave("Item_info");


			}
		}
	}

	//아이템의 size가 NULL이 아니라면
	else
	{
		bool itemCheck = false;
		//획득한 해당 아이템의 이름을 찾아 그 아이템의 개수를 하나 늘린다.
		for (int i = 0; i < _vitemBase.size(); ++i)
		{

			if (_vitemBase[i]->getItem().name == name)
			{
				itemCheck = true;
				_vitemBase[i]->setItemItemMax(_vitemBase[i]->getItem().itemMax + 1);
				char cha[64];
				cha[63] = _itoa_s(_vitemBase[i]->getItem().itemMax, cha, sizeof(cha), 10);
				INIDATA->addData(name.c_str(), "Item_Count", cha);
				INIDATA->iniSave("Item_info");
				break;
			}
			else if (_vitemBase[i]->getItem().name != name)
			{
				//일치하는 아이템 이름여부에 따라 itemCheck를 for문이 끝날때까지 반복하고,				
				itemCheck = false;
			}
		}
		//for문이 끝났을때 false를 반환하게 되면 아래와 같이 아이템을 새로 넣어주고 개수를 증가시켜준다.
		if (!itemCheck)
		{
			_vitemBase.push_back(_itemManager->getItem(name));
			for (int i = 0; i < _vitemBase.size(); ++i)
			{
				if (_vitemBase[i]->getItem().name == name)
				{
					_vitemBase[i]->setItemItemMax(_vitemBase[i]->getItem().itemMax + 1);
					_vitemBase[i]->setItemName(_vitemBase[i]->getItem().name);
					_vitemBase[i]->setItemX(_itemCoordinates[i].x);
					_vitemBase[i]->setItemY(_itemCoordinates[i].y);
					_vitemBase[i]->setItemRC(_itemCoordinates[i].rc);

					char cha[64];
					cha[63] = _itoa_s(_vitemBase[i]->getItem().itemMax, cha, sizeof(cha), 10);
					INIDATA->addData(name.c_str(), "Item_Count", cha);
					INIDATA->iniSave("Item_info");
				}
			}
		}
	}

}



void UI::itemSet()
{
	_money = INIDATA->loadDataInterger("Item_info", "My_Money", "Money");
	//아이템 별 개수를 불러온다.
	itemCount[0] = INIDATA->loadDataInterger("Item_info", "blueprint", "Item_Count");
	itemCount[1] = INIDATA->loadDataInterger("Item_info", "Break_Sword", "Item_Count");
	itemCount[2] = INIDATA->loadDataInterger("Item_info", "Crystal", "Item_Count");
	itemCount[3] = INIDATA->loadDataInterger("Item_info", "Golem_core", "Item_Count");
	itemCount[4] = INIDATA->loadDataInterger("Item_info", "History_Book", "Item_Count");
	itemCount[5] = INIDATA->loadDataInterger("Item_info", "Life_Water", "Item_Count");
	itemCount[6] = INIDATA->loadDataInterger("Item_info", "Note", "Item_Count");
	itemCount[7] = INIDATA->loadDataInterger("Item_info", "Steel", "Item_Count");
	itemCount[8] = INIDATA->loadDataInterger("Item_info", "Straw", "Item_Count");
	itemCount[9] = INIDATA->loadDataInterger("Item_info", "Electronic_Line", "Item_Count");


	for (int i = 0; i < 10; ++i)
	{
		//개수가  NULL값이 아니면
		if (itemCount[i] != NULL)
		{
			//개수가 있는 아이템을 찾아 vector에 넣어준다.
			int itemInfo = i;
			char changeInt[64];
			changeInt[63] = _itoa_s(itemInfo, changeInt, sizeof(changeInt), 10);
			_vitemBase.push_back(_itemManager->getItem(INIDATA->loadDataString2("Item_info", "Item_Name", changeInt)));

			//vector의 size를 확인하고 아이템별 개수를 넣어준다.
			for (int j = 0; j < _vitemBase.size(); ++j)
			{
				if (_vitemBase[j]->getItem().name != INIDATA->loadDataString2("Item_info", "Item_Name", changeInt)) continue;
				_vitemBase[j]->setItemItemMax(itemCount[i]);
				_vitemBase[j]->setItemName(INIDATA->loadDataString2("Item_info", "Item_Name", changeInt));
			}
		}
	}
	//남은 NULL값의 벡터를 제거해준다.
	for (int i = _vitemBase.size() - 1; i >= 0; --i)
	{
		if (_vitemBase[i] == NULL) _vitemBase.erase(_vitemBase.begin() + i);
	}
	//NULL값을 제거해준 후 위치를 재설정 해준다.
	for (int i = 0; i < _vitemBase.size(); ++i)
	{
		_vitemBase[i]->setItemX(_itemCoordinates[i].x);
		_vitemBase[i]->setItemY(_itemCoordinates[i].y);
		_vitemBase[i]->setItemRC(_itemCoordinates[i].rc);
	}

}
