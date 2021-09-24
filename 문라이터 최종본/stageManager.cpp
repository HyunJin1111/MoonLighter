#include "stdafx.h"
#include "stageManager.h"

HRESULT stageManager::init()
{
	//글꼴 추가
	D2DMANAGER->AddTextFormat(L"Droid Sans Fallback");
	D2DMANAGER->AddTextFormat(L"제주고딕");
	D2DMANAGER->AddTextFormat(L"APPLE ][");
	D2DMANAGER->AddTextFormat(L"Fairfax");
	D2DMANAGER->AddTextFormat(L"JF Dot Shinonome Gothic 16");
	D2DMANAGER->AddTextFormat(L"m3x6");
	D2DMANAGER->AddTextFormat(L"m5x7");
	D2DMANAGER->AddTextFormat(L"PixelMplus10");
	D2DMANAGER->AddTextFormat(L"Zpix");
	sceneSet();





	return S_OK;
}

void stageManager::release()
{
}

void stageManager::update()
{
	SCENEMANAGER->update();
}

void stageManager::render()
{
	SCENEMANAGER->render();
}

void stageManager::sceneSet()
{
	SCENEMANAGER->addScene("intro", new intro);
	SCENEMANAGER->addScene("tileMap", new tileMap);
	SCENEMANAGER->addScene("village", new village);
	SCENEMANAGER->addScene("shop", new shop);
	SCENEMANAGER->addScene("deongeonChoice", new deongeonChoice);
	SCENEMANAGER->addScene("dungeon", new dungeon);

	SCENEMANAGER->changeScene("village");
}
