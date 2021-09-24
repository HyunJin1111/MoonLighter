
#include "stdafx.h"
#include "iceSpear.h"

HRESULT iceSpear::init(int skillMax, float range)
{

	_SkillMax = skillMax;
	_range = range;
	_x2 = 0;
	return S_OK;
}

void iceSpear::release()
{
}

void iceSpear::update()
{
	if (_go == true)
	{
		move();

	}
}

void iceSpear::render()
{

	for (_viSkill = _vSkill.begin(); _viSkill != _vSkill.end(); ++_viSkill)
	{




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


			_viSkill->count = 0;
		}
	}

}

void iceSpear::fire(float x, float y, float angle)
{
	if (_SkillMax < _vSkill.size()) return;
	if (_go == true) return;

	tagiceSpear Skill;
	ZeroMemory(&Skill, sizeof(tagiceSpear));
	_angle = angle;
	Skill.skillImage = new dImage;
	Skill.skillImage->init(L"skill/¾óÀ½Ã¢.png", (int)760, 14, 8, 1);
	Skill.speed = 10.0f;
	Skill.angle = angle * PI / 180;
	Skill.x = Skill.fireX = x;
	Skill.y = Skill.fireY = y;
	Skill.rc = RectMakeCenter(Skill.x, Skill.y,
		Skill.skillImage->getFrameWidth(),
		Skill.skillImage->getFrameHeight());

	_vSkill.push_back(Skill);
}


void iceSpear::move()
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

			float _rx = (_viSkill->rc.right + _viSkill->rc.left) / 2;
			float _ry = (_viSkill->rc.bottom + _viSkill->rc.top) / 2;

			_go = false;
			PARTICLEMANAGER->play("¾óÀ½Æã", _rx, _ry, _angle);
			SAFE_RELEASE(_viSkill->skillImage);
			SAFE_DELETE(_viSkill->skillImage);
			_viSkill = _vSkill.erase(_viSkill);
		}
		else ++_viSkill;

	}
}

void iceSpear::moveGo()
{
	_go = true;
}

void iceSpear::removeSkill(int arrNum)
{
	_vSkill[arrNum].skillImage->release();
	_vSkill.erase(_vSkill.begin() + arrNum);


}
