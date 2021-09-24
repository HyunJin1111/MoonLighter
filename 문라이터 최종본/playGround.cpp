#include "stdafx.h"
#include "playGround.h"


#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요 제발
HRESULT playGround::init()
{

	gameNode::init(true);
	EFFECTMANAGER->addEffect("slimeEffect", "적/slime_die.png", 640, 44, 64, 44, 3, 0.1f, 10);
	EFFECTMANAGER->addEffect("이펙트1", "이펙트/이펙트1.png", 1150, 131, 115, 131, 3, 0.1f, 10);

	SOUNDMANAGER->addSound("intro", "사운드/intro.wav", true, true);

	SOUNDMANAGER->addSound("마을배경음악", "사운드/마을배경음악.wav", true, true);
	SOUNDMANAGER->addSound("상점배경음악", "사운드/상점배경음악.wav", true, true);
	SOUNDMANAGER->addSound("던전선택배경음악", "사운드/던전선택배경음악.wav", true, true);
	SOUNDMANAGER->addSound("던전배경음악", "사운드/던전배경음악.wav", true, true);
	SOUNDMANAGER->addSound("인트로배경음악", "사운드/인트로배경음악.wav", true, true);
	SOUNDMANAGER->addSound("보스배경음악", "사운드/보스배경음악.wav", true, true);
	SOUNDMANAGER->addSound("윌발걸음", "사운드/윌발걸음.wav", false, true);
	SOUNDMANAGER->addSound("윌수영", "사운드/윌수영.wav", false, true);
	SOUNDMANAGER->addSound("윌구르기", "사운드/윌구르기.wav", false, false);
	SOUNDMANAGER->addSound("윌공격", "사운드/윌공격.wav", false, false);
	SOUNDMANAGER->addSound("윌피격", "사운드/윌피격.wav", false, false);
	SOUNDMANAGER->addSound("보스죽음", "사운드/보스죽음.wav", false, false);
	SOUNDMANAGER->addSound("보스어택1", "사운드/보스어택1.wav", false, false);
	SOUNDMANAGER->addSound("보스어택2", "사운드/보스어택2.wav", false, false);
	SOUNDMANAGER->addSound("슬라임공격", "사운드/슬라임공격.wav", false, false);
	SOUNDMANAGER->addSound("슬라임죽음", "사운드/슬라임죽음.wav", false, false);
	SOUNDMANAGER->addSound("미니보스공격", "사운드/미니보스공격.wav", false, false);
	SOUNDMANAGER->addSound("미니보스죽음", "사운드/미니보스죽음.wav", false, false);
	SOUNDMANAGER->addSound("메뉴선택", "사운드/메뉴선택.wav", false, false);
	SOUNDMANAGER->addSound("포탈입장", "사운드/포탈입장.wav", false, false);

	_stageManager = new stageManager;
	_stageManager->init();



	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();



	SCENEMANAGER->update();

}


void playGround::render()
{

	D2DMANAGER->beginDraw();

	//================제발 이 사이에 좀 그립시다==========================



	SCENEMANAGER->render();

	//cout << TIMEMANAGER->getFrameRate() << endl;

	D2DMANAGER->endDraw();

	//==================================================s
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	//CAMERAMANAGER->render(getHDC(), 0, 0, getMemDC());
	D2DMANAGER->render();

}