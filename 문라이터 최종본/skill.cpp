#include "stdafx.h"
#include "skill.h"

HRESULT skill::init(int skillMax, float range )
{
	_burn = new burn;
	_burn->init(50, 5);
	_SkillMax = skillMax;
	_range = range;
	_x2 = 0;
	return S_OK;
}

void skill::release()
{
}

void skill::update()
{
	move();
	_burn->update();
}

void skill::render()
{

	for (_viSkill = _vSkill.begin(); _viSkill != _vSkill.end(); ++_viSkill)
	{



		//PARTICLEMANAGER->play("ºÒ²É2", _viSkill->fireX - 10 , _viSkill->fireY,0);
		//PARTICLEMANAGER->play("ºÒ²É2", _viSkill->fireX - 20, _viSkill->fireY, 0);
		//PARTICLEMANAGER->play("ºÒ²É2", _viSkill->fireX - 30, _viSkill->fireY, 0);
		//PARTICLEMANAGER->play("ºÒ²É2", _viSkill->fireX - 40, _viSkill->fireY, 0);
		//PARTICLEMANAGER->play("ºÒ²É2", _viSkill->fireX - 50, _viSkill->fireY, 0);
		//PARTICLEMANAGER->play("ºÒ²É2", _viSkill->fireX - 60, _viSkill->fireY, 0);
		//PARTICLEMANAGER->play("ºÒ²É2", _viSkill->fireX - 70, _viSkill->fireY, 0);
		//PARTICLEMANAGER->play("ºÒ²É2", _viSkill->fireX - 80, _viSkill->fireY, 0);
		//PARTICLEMANAGER->play("ºÒ²É2", _viSkill->fireX - 90, _viSkill->fireY, 0);
		//PARTICLEMANAGER->play("ºÒ²É2", _viSkill->fireX - 100, _viSkill->fireY, 0);

		//DTDMANAGER->setRotation(_angle, (_viSkill->rc.right+ _viSkill->rc.left) /2, (_viSkill->rc.bottom + _viSkill->rc.top) / 2);
		DTDMANAGER->setRotation(-_angle, _viSkill->x, _viSkill->y);
		_viSkill->skillImage->frameRender(
			_viSkill->rc.left,
			_viSkill->rc.top,
			_viSkill->skillImage->getFrameX(), 0);
		DTDMANAGER->resetRotation();
		//DTDMANAGER->Rectangle(_viSkill->rc);
		_viSkill->count++;


		//PARTICLEMANAGER->play("ºÒ²É3", _viSkill->fireX, _viSkill->fireY, 180);
		//PARTICLEMANAGER->play("È²ºÒ²É4", _viSkill->fireX, _viSkill->fireY, 210);
		//PARTICLEMANAGER->play("ºÒ²É1", _viSkill->fireX, _viSkill->fireY, 240);
		//PARTICLEMANAGER->play("ºÒ²É2", _viSkill->fireX, _viSkill->fireY, 270);
		//PARTICLEMANAGER->play("ºÒ²É3", _viSkill->fireX, _viSkill->fireY, 300);
		//PARTICLEMANAGER->play("ºÒ²É1", _viSkill->fireX, _viSkill->fireY, 330);
		//PARTICLEMANAGER->play("ºÒ²É2", _viSkill->fireX, _viSkill->fireY, 360);
		if (_viSkill->count % 5 == 0)
		{
			_viSkill->skillImage->setFrameX(_viSkill->skillImage->getFrameX() + 1);

			//ÃÖ´ë ÇÁ·¹ÀÓº¸´Ù Ä¿Áö¸é
			if (_viSkill->skillImage->getFrameX() >= _viSkill->skillImage->getMaxFrameX())
			{
				_viSkill->skillImage->setFrameX(0);
				
			}

			_viSkill->count = 0;
		}
	}
	_burn->render();
}

void skill::fire(float x, float y, float angle)
{
	if (_SkillMax < _vSkill.size()) return;

	tagskill Skill;
	ZeroMemory(&Skill, sizeof(tagskill));
	_angle = angle;
	Skill.skillImage = new dImage;
	Skill.skillImage->init(L"skill/ÆÄÀÌ¾îº¼.png", (int)372, 38,6,1);
	Skill.speed = 10.0f;
	Skill.angle = angle * PI / 180;
	Skill.x = Skill.fireX = x;
	Skill.y = Skill.fireY = y;
	Skill.rc = RectMakeCenter(Skill.x, Skill.y,
		Skill.skillImage->getFrameWidth(),
		Skill.skillImage->getFrameHeight());

	_vSkill.push_back(Skill);
}


void skill::move()
{
	for (_viSkill = _vSkill.begin(); _viSkill != _vSkill.end();)
	{
		_time++;
		//_viSkill->x += _viSkill->speed;
		_viSkill->x += cosf(_viSkill->angle) * _viSkill->speed;
		_viSkill->y += -sinf(_viSkill->angle) * _viSkill->speed;
		_viSkill->rc = RectMakeCenter(_viSkill->x, _viSkill->y,
			_viSkill->skillImage->getFrameWidth(),
			_viSkill->skillImage->getFrameHeight());
		//if (_time > 100)
		//{
		//	_time = 0;
		//	_x2 = 0;
		//	SAFE_RELEASE(_viSkill->skillImage);
		//	SAFE_DELETE(_viSkill->skillImage);
		//	_viSkill = _vSkill.erase(_viSkill);
		//}
		//else ++_viSkill;
		//»ç°Å¸®º¸´Ù ´õ ¸Ö¸® ³ª°¡¸é(?)
		if (_range < getDistance(_viSkill->x, _viSkill->y, _viSkill->fireX, _viSkill->fireY))
		{

			float _rx = (_viSkill->rc.right + _viSkill->rc.left) / 2 ;
			float _ry = (_viSkill->rc.bottom + _viSkill->rc.top) / 2 ;
			int _scale = 10;
			
			PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(0) * _scale, _ry + -sinf(0) * _scale, 0);
			PARTICLEMANAGER->play("È²ºÒ²É3", _rx + cosf(20) * _scale, _ry + -sinf(20) * _scale, 20);
			PARTICLEMANAGER->play("ºÒ²É1", _rx + cosf(40) * _scale, _ry + -sinf(40) * _scale, 40);
			PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(60) * _scale, _ry + -sinf(60) * _scale, 60);
			PARTICLEMANAGER->play("È²ºÒ²É2", _rx + cosf(80) * _scale, _ry + -sinf(80) * _scale, 80);
			PARTICLEMANAGER->play("ºÒ²É3", _rx + cosf(100) * _scale, _ry + -sinf(100) * _scale, 100);
			PARTICLEMANAGER->play("ºÒ²É1", _rx + cosf(120) * _scale, _ry + -sinf(120) * _scale, 120);
			PARTICLEMANAGER->play("È²ºÒ²É4", _rx + cosf(140) * _scale, _ry + -sinf(140) * _scale, 140);
			PARTICLEMANAGER->play("È²ºÒ²É2", _rx + cosf(160) * _scale, _ry + -sinf(160) * _scale, 160);
			PARTICLEMANAGER->play("ºÒ²É3", _rx + cosf(180) * _scale, _ry + -sinf(180) * _scale, 180);
			PARTICLEMANAGER->play("ºÒ²É4", _rx + cosf(200) * _scale, _ry + -sinf(200) * _scale, 200);
			PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(220) * _scale, _ry + -sinf(220) * _scale, 220);
			PARTICLEMANAGER->play("È²ºÒ²É3", _rx + cosf(240) * _scale, _ry + -sinf(240) * _scale, 240);
			PARTICLEMANAGER->play("ºÒ²É1", _rx + cosf(260) * _scale, _ry + -sinf(260) * _scale, 260);
			PARTICLEMANAGER->play("ºÒ²É4", _rx + cosf(280) * _scale, _ry + -sinf(280) * _scale, 280);
			PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(300) * _scale, _ry + -sinf(300) * _scale, 300);
			PARTICLEMANAGER->play("È²ºÒ²É3", _rx + cosf(320) * _scale, _ry + -sinf(320) * _scale, 320);
			PARTICLEMANAGER->play("ºÒ²É4", _rx + cosf(340) * _scale, _ry + -sinf(340) * _scale, 340);
			PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(360) * _scale, _ry + -sinf(360) * _scale, 460);

			int _scale2 = 20;
			PARTICLEMANAGER->play("ºÒ²É1", _rx + cosf(0) * _scale2, _ry + -sinf(0) * _scale2, 0);
			PARTICLEMANAGER->play("È²ºÒ²É1", _rx + cosf(20) * _scale2, _ry + -sinf(20) * _scale2, 20);
			PARTICLEMANAGER->play("ºÒ²É1", _rx + cosf(40) * _scale2, _ry + -sinf(40) * _scale2, 40);
			PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(60) * _scale2, _ry + -sinf(60) * _scale2, 60);
			PARTICLEMANAGER->play("È²ºÒ²É2", _rx + cosf(80) * _scale2, _ry + -sinf(80) * _scale2, 80);
			PARTICLEMANAGER->play("ºÒ²É3", _rx + cosf(100) * _scale2, _ry + -sinf(100) * _scale2, 100);
			PARTICLEMANAGER->play("ºÒ²É1", _rx + cosf(120) * _scale2, _ry + -sinf(120) * _scale2, 120);
			PARTICLEMANAGER->play("È²ºÒ²É1", _rx + cosf(140) * _scale2, _ry + -sinf(140) * _scale2, 140);
			PARTICLEMANAGER->play("È²ºÒ²É2", _rx + cosf(160) * _scale2, _ry + -sinf(160) * _scale2, 160);
			PARTICLEMANAGER->play("ºÒ²É3", _rx + cosf(180) * _scale2, _ry + -sinf(180) * _scale2, 180);
			PARTICLEMANAGER->play("ºÒ²É3", _rx + cosf(200) * _scale2, _ry + -sinf(200) * _scale2, 200);
			PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(220) * _scale2, _ry + -sinf(220) * _scale2, 220);
			PARTICLEMANAGER->play("È²ºÒ²É3", _rx + cosf(240) * _scale2, _ry + -sinf(240) * _scale2, 240);
			PARTICLEMANAGER->play("ºÒ²É1", _rx + cosf(260) * _scale2, _ry + -sinf(260) * _scale2, 260);
			PARTICLEMANAGER->play("ºÒ²É1", _rx + cosf(280) * _scale2, _ry + -sinf(280) * _scale2, 280);
			PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(300) * _scale2, _ry + -sinf(300) * _scale2, 300);
			PARTICLEMANAGER->play("È²ºÒ²É3", _rx + cosf(320) * _scale2, _ry + -sinf(320) * _scale2, 320);
			PARTICLEMANAGER->play("ºÒ²É4", _rx + cosf(340) * _scale2, _ry + -sinf(340) * _scale2, 340);
			PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(360) * _scale2, _ry + -sinf(360) * _scale2, 460);
			_burn->fire(_rx, _ry,0,0);
			PARTICLEMANAGER->play("È­¿°Æã",_rx, _ry,0);
			SAFE_RELEASE(_viSkill->skillImage);
			SAFE_DELETE(_viSkill->skillImage);
			_viSkill = _vSkill.erase(_viSkill);
		}
		else ++_viSkill;

	}
}

void skill::removeSkill(int arrNum)
{
	_vSkill[arrNum].skillImage->release();
	_vSkill.erase(_vSkill.begin() + arrNum);


}
