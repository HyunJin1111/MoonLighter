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
	EFFECTMANAGER->addEffect("slimeEffect", "Enemy/slime_die.png", 640, 44, 64, 44, 3, 0.1f, 10);
	EFFECTMANAGER->addEffect("Effect1", "Effect/Effect1.png", 1150, 131, 115, 131, 3, 0.1f, 10);

	SOUNDMANAGER->addSound("intro", "Sound/intro.wav", true, true);

	SOUNDMANAGER->addSound("VilageBackgroundMusic", "Sound/VilageBackgroundMusic.wav", true, true);
	SOUNDMANAGER->addSound("ShopBackgroundMusic", "Sound/ShopBackgroundMusic.wav", true, true);
	SOUNDMANAGER->addSound("DungeonChoiceBackgroundMusic", "Sound/DungeonChoiceBackgroundMusic.wav", true, true);
	SOUNDMANAGER->addSound("DungeonBackgroundMusic", "Sound/DungeonBackgroundMusic.wav", true, true);
	SOUNDMANAGER->addSound("IntroBackgroundMusic", "Sound/IntroBackgroundMusic.wav", true, true);
	SOUNDMANAGER->addSound("BossBackgroundMusic", "Sound/BossBackgroundMusic.wav", true, true);
	SOUNDMANAGER->addSound("WillStep", "Sound/WillStep.wav", false, true);
	SOUNDMANAGER->addSound("WillSwim", "Sound/WillSwim.wav", false, true);
	SOUNDMANAGER->addSound("WillRoll", "Sound/WillRoll.wav", false, false);
	SOUNDMANAGER->addSound("WillAttack", "Sound/WillAttack.wav", false, false);
	SOUNDMANAGER->addSound("WillHitSound", "Sound/WillHitSound.wav", false, false);
	SOUNDMANAGER->addSound("BossDeathSound", "Sound/BossDeathSound.wav", false, false);
	SOUNDMANAGER->addSound("BossAttackSound1", "Sound/BossAttackSound1.wav", false, false);
	SOUNDMANAGER->addSound("BossAttackSound2", "Sound/BossAttackSound2.wav", false, false);
	SOUNDMANAGER->addSound("SlimeAttackSound", "Sound/SlimeAttackSound.wav", false, false);
	SOUNDMANAGER->addSound("SlimeDeathSound", "Sound/SlimeDeathSound.wav", false, false);
	SOUNDMANAGER->addSound("MiniBossAttackSound", "Sound/MiniBossAttackSound.wav", false, false);
	SOUNDMANAGER->addSound("MiniBossDeathSound", "Sound/MiniBossDeathSound.wav", false, false);
	SOUNDMANAGER->addSound("MenuChoice", "Sound/MenuChoice.wav", false, false);
	SOUNDMANAGER->addSound("portalIn", "Sound/portalIn.wav", false, false);

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