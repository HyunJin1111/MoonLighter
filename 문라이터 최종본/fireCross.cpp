#include "stdafx.h"
#include "fireCross.h"

HRESULT fireCross::init(int skillMax, float range)
{
	_burn = new burn;
	_burn->init(50, 5);
	_SkillMax = skillMax;
	_range = range;
	_x2 = 0;
	return S_OK;
}

void fireCross::release()
{
}

void fireCross::update()
{
	move();
	_burn->update();
}

void fireCross::render()
{

	for (_viSkill = _vSkill.begin(); _viSkill != _vSkill.end(); ++_viSkill)
	{
		float _rx = (_viSkill->rc.right + _viSkill->rc.left) / 2;
		float _ry = (_viSkill->rc.bottom + _viSkill->rc.top) / 2 + 40;
		int _scale = 10;


		PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(_viSkill->angle + 220) * _scale, _ry + -sinf(_viSkill->angle + 220) * _scale, _angle + 220);
		PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(_viSkill->angle + 220) * _scale, _ry + -sinf(_viSkill->angle + 220) * _scale, _angle + 225);
		PARTICLEMANAGER->play("È²ºÒ²É3", _rx + cosf(_viSkill->angle + 240) * _scale, _ry + -sinf(_viSkill->angle + 240) * _scale, _angle + 230);
		PARTICLEMANAGER->play("È²ºÒ²É3", _rx + cosf(_viSkill->angle + 240) * _scale, _ry + -sinf(_viSkill->angle + 240) * _scale, _angle + 235);
		PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(_viSkill->angle + 220) * _scale, _ry + -sinf(_viSkill->angle + 220) * _scale, _angle + 240);
		PARTICLEMANAGER->play("È²ºÒ²É3", _rx + cosf(_viSkill->angle + 240) * _scale, _ry + -sinf(_viSkill->angle + 240) * _scale, _angle + 250);
		int _scale2 = 20;
		PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(_viSkill->angle + 220) * _scale2, _ry + -sinf(_viSkill->angle + 220) * _scale2, _angle + 220);
		PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(_viSkill->angle + 220) * _scale2, _ry + -sinf(_viSkill->angle + 220) * _scale2, _angle + 225);
		PARTICLEMANAGER->play("È²ºÒ²É3", _rx + cosf(_viSkill->angle + 240) * _scale2, _ry + -sinf(_viSkill->angle + 240) * _scale2, _angle + 230);
		PARTICLEMANAGER->play("È²ºÒ²É3", _rx + cosf(_viSkill->angle + 240) * _scale2, _ry + -sinf(_viSkill->angle + 240) * _scale2, _angle + 235);
		PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(_viSkill->angle + 220) * _scale2, _ry + -sinf(_viSkill->angle + 220) * _scale2, _angle + 240);
		PARTICLEMANAGER->play("È²ºÒ²É3", _rx + cosf(_viSkill->angle + 240) * _scale2, _ry + -sinf(_viSkill->angle + 240) * _scale2, _angle + 250);
		int _scale3 = 30;
		PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(_viSkill->angle + 220) * _scale3, _ry + -sinf(_viSkill->angle + 220) * _scale3, _angle + 220);
		PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(_viSkill->angle + 220) * _scale3, _ry + -sinf(_viSkill->angle + 220) * _scale3, _angle + 225);
		PARTICLEMANAGER->play("È²ºÒ²É3", _rx + cosf(_viSkill->angle + 240) * _scale3, _ry + -sinf(_viSkill->angle + 240) * _scale3, _angle + 230);
		PARTICLEMANAGER->play("È²ºÒ²É3", _rx + cosf(_viSkill->angle + 240) * _scale3, _ry + -sinf(_viSkill->angle + 240) * _scale3, _angle + 235);
		PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(_viSkill->angle + 220) * _scale3, _ry + -sinf(_viSkill->angle + 220) * _scale3, _angle + 240);
		PARTICLEMANAGER->play("È²ºÒ²É3", _rx + cosf(_viSkill->angle + 240) * _scale3, _ry + -sinf(_viSkill->angle + 240) * _scale3, _angle + 250);
		int _scale4 = 50;
		PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(_viSkill->angle + 220) * _scale4, _ry + -sinf(_viSkill->angle + 220) * _scale4, _angle + 220);
		PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(_viSkill->angle + 220) * _scale4, _ry + -sinf(_viSkill->angle + 220) * _scale4, _angle + 225);
		PARTICLEMANAGER->play("È²ºÒ²É3", _rx + cosf(_viSkill->angle + 240) * _scale4, _ry + -sinf(_viSkill->angle + 240) * _scale4, _angle + 230);
		PARTICLEMANAGER->play("È²ºÒ²É3", _rx + cosf(_viSkill->angle + 240) * _scale4, _ry + -sinf(_viSkill->angle + 240) * _scale4, _angle + 235);
		PARTICLEMANAGER->play("ºÒ²É2", _rx + cosf(_viSkill->angle + 220) * _scale4, _ry + -sinf(_viSkill->angle + 220) * _scale4, _angle + 240);
		PARTICLEMANAGER->play("È²ºÒ²É3", _rx + cosf(_viSkill->angle + 240) * _scale4, _ry + -sinf(_viSkill->angle + 240) * _scale4, _angle + 250);


		//DTDMANAGER->setRotation(_angle, (_viSkill->rc.right+ _viSkill->rc.left) /2, (_viSkill->rc.bottom + _viSkill->rc.top) / 2);
		DTDMANAGER->setRotation(-_angle, _viSkill->x, _viSkill->y);
		_viSkill->skillImage->frameRender(
			_viSkill->rc.left,
			_viSkill->rc.top,
			_viSkill->skillImage->getFrameX(), 0);
		DTDMANAGER->resetRotation();
		//DTDMANAGER->Rectangle(_viSkill->rc);
		_viSkill->count++;

		if (_viSkill->count % 5 == 0)
		{
			_viSkill->skillImage->setFrameX(_viSkill->skillImage->getFrameX() + 1);

			//ÃÖ´ë ÇÁ·¹ÀÓº¸´Ù Ä¿Áö¸é
			//if (_viSkill->skillImage->getFrameX() >= _viSkill->skillImage->getMaxFrameX())
			//{
			//	_viSkill->skillImage->setFrameX(0);


			//}

			_viSkill->count = 0;
		}
	}
	_burn->render();
}

void fireCross::fire(float x, float y, float angle)
{
	if (_SkillMax < _vSkill.size()) return;

	tagfireCross Skill;
	ZeroMemory(&Skill, sizeof(tagfireCross));
	_angle = angle;
	Skill.skillImage = new dImage;
	Skill.skillImage->init(L"skill/È­¿°ÅÍÁö±â.png", (int)342, 98, 3, 1);
	Skill.speed = 10.0f;
	Skill.angle = angle * PI / 180;
	Skill.x = Skill.fireX = x ;
	Skill.y = Skill.fireY = y;
	Skill.rc = RectMakeCenter(Skill.x , Skill.y,
		Skill.skillImage->getFrameWidth(),
		Skill.skillImage->getFrameHeight());

	_vSkill.push_back(Skill);
}


void fireCross::move()
{
	for (_viSkill = _vSkill.begin(); _viSkill != _vSkill.end();)
	{
		_time++;
		//_viSkill->x += _viSkill->speed;
		//_viSkill->x += cosf(_viSkill->angle) * _viSkill->speed;
		//_viSkill->y += -sinf(_viSkill->angle) * _viSkill->speed;
		_viSkill->rc = RectMakeCenter(_viSkill->x, _viSkill->y -40,
			_viSkill->skillImage->getFrameWidth(),
			_viSkill->skillImage->getFrameHeight());
		//if (_viSkill->_time > 100)
		//{
		//	_viSkill->_time = 0;
		//	_x2 = 0;
		//	SAFE_RELEASE(_viSkill->skillImage);
		//	SAFE_DELETE(_viSkill->skillImage);
		//	_viSkill = _vSkill.erase(_viSkill);
		//}
		//else ++_viSkill;
		if (_viSkill->skillImage->getFrameX() >= _viSkill->skillImage->getMaxFrameX())
		{
			//_viSkill->skillImage->setFrameX(0);
			SAFE_RELEASE(_viSkill->skillImage);
			SAFE_DELETE(_viSkill->skillImage);
			_viSkill = _vSkill.erase(_viSkill);

		}
		else ++_viSkill;
		//»ç°Å¸®º¸´Ù ´õ ¸Ö¸® ³ª°¡¸é(?)
		/*if (_range < getDistance(_viSkill->x, _viSkill->y, _viSkill->fireX, _viSkill->fireY))
		{

			float _rx = (_viSkill->rc.right + _viSkill->rc.left) / 2;
			float _ry = (_viSkill->rc.bottom + _viSkill->rc.top) / 2;
			_burn->fire(_rx, _ry, 0, 0);
			PARTICLEMANAGER->play("È­¿°Æã", _rx, _ry, 0);
			SAFE_RELEASE(_viSkill->skillImage);
			SAFE_DELETE(_viSkill->skillImage);
			_viSkill = _vSkill.erase(_viSkill);
		}*/
		//else ++_viSkill;

	}
}

void fireCross::removeSkill(int arrNum)
{
	_vSkill[arrNum].skillImage->release();
	_vSkill.erase(_vSkill.begin() + arrNum);


}
