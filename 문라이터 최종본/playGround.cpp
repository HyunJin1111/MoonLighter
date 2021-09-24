#include "stdafx.h"
#include "playGround.h"


#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ��� ����
HRESULT playGround::init()
{

	gameNode::init(true);
	EFFECTMANAGER->addEffect("slimeEffect", "��/slime_die.png", 640, 44, 64, 44, 3, 0.1f, 10);
	EFFECTMANAGER->addEffect("����Ʈ1", "����Ʈ/����Ʈ1.png", 1150, 131, 115, 131, 3, 0.1f, 10);

	SOUNDMANAGER->addSound("intro", "����/intro.wav", true, true);

	SOUNDMANAGER->addSound("�����������", "����/�����������.wav", true, true);
	SOUNDMANAGER->addSound("�����������", "����/�����������.wav", true, true);
	SOUNDMANAGER->addSound("�������ù������", "����/�������ù������.wav", true, true);
	SOUNDMANAGER->addSound("�����������", "����/�����������.wav", true, true);
	SOUNDMANAGER->addSound("��Ʈ�ι������", "����/��Ʈ�ι������.wav", true, true);
	SOUNDMANAGER->addSound("�����������", "����/�����������.wav", true, true);
	SOUNDMANAGER->addSound("���߰���", "����/���߰���.wav", false, true);
	SOUNDMANAGER->addSound("������", "����/������.wav", false, true);
	SOUNDMANAGER->addSound("��������", "����/��������.wav", false, false);
	SOUNDMANAGER->addSound("������", "����/������.wav", false, false);
	SOUNDMANAGER->addSound("���ǰ�", "����/���ǰ�.wav", false, false);
	SOUNDMANAGER->addSound("��������", "����/��������.wav", false, false);
	SOUNDMANAGER->addSound("��������1", "����/��������1.wav", false, false);
	SOUNDMANAGER->addSound("��������2", "����/��������2.wav", false, false);
	SOUNDMANAGER->addSound("�����Ӱ���", "����/�����Ӱ���.wav", false, false);
	SOUNDMANAGER->addSound("����������", "����/����������.wav", false, false);
	SOUNDMANAGER->addSound("�̴Ϻ�������", "����/�̴Ϻ�������.wav", false, false);
	SOUNDMANAGER->addSound("�̴Ϻ�������", "����/�̴Ϻ�������.wav", false, false);
	SOUNDMANAGER->addSound("�޴�����", "����/�޴�����.wav", false, false);
	SOUNDMANAGER->addSound("��Ż����", "����/��Ż����.wav", false, false);

	_stageManager = new stageManager;
	_stageManager->init();



	return S_OK;
}

//�޸� ������ ����� �ϼ��� ����
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

	//================���� �� ���̿� �� �׸��ô�==========================



	SCENEMANAGER->render();

	//cout << TIMEMANAGER->getFrameRate() << endl;

	D2DMANAGER->endDraw();

	//==================================================s
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	//CAMERAMANAGER->render(getHDC(), 0, 0, getMemDC());
	D2DMANAGER->render();

}