#include "stdafx.h"
#include "bubble.h"

HRESULT bubble::init(int skillMax, float range)
{

	_SkillMax = skillMax;
	_range = range;
	_x2 = 0;

	return S_OK;
}

void bubble::release()
{
}

void bubble::update()
{

		move();

	
}

void bubble::render()
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
			if (_viSkill->skillImage->getFrameX() <= 1)
			{
				_viSkill->skillImage->setFrameX(_viSkill->skillImage->getFrameX() + 1);

			}
			//ÃÖ´ë ÇÁ·¹ÀÓº¸´Ù Ä¿Áö¸é
			//_viSkill->skillImage->setFrameX(0);

			_viSkill->count = 0;
		}
	}

}

void bubble::fire(float x, float y, float angle)
{
	if (_SkillMax < _vSkill.size()) return;

	tagbubble Skill;
	ZeroMemory(&Skill, sizeof(tagbubble));
	_angle = angle;

	Skill.skillImage = new dImage;
	Skill.skillImage->init(L"skill/BubblePop.png", (int)192, 32, 6, 1);
	Skill.speed = 1.0f;

	Skill.angle = angle * PI / 180;
	Skill.x = Skill.fireX = x;
	Skill.y = Skill.fireY = y;
	Skill.rc = RectMakeCenter(Skill.x, Skill.y,
	Skill.skillImage->getFrameWidth(),
	Skill.skillImage->getFrameHeight());
//	Skill._r = RND->getFromFloatTo(-3.14, 3.14);
	_vSkill.push_back(Skill);
}


void bubble::move()
{
	for (_viSkill = _vSkill.begin(); _viSkill != _vSkill.end();)
	{
		_viSkill->_count2++;
		_viSkill->_count3++;

		if (_viSkill->_count3 > 5)
		{
			_viSkill->_RNDOK = true;
			_viSkill->_count3 = 0;
		}
		if (_viSkill->_count2 == 50 && _viSkill->_RNDOK == true)
		{

			_viSkill->_r += RND->getFromFloatTo(-3.14, 3.14);
			_viSkill->_count2 = 0;
			_viSkill->_RNDOK = false;
		}

		_viSkill->_time++;
		//_viSkill->x += _viSkill->speed;
		if (_viSkill->_time > 50)
		{



			_viSkill->x += cosf(_viSkill->_r) * _viSkill->speed;
			_viSkill->y += -sinf(_viSkill->_r) * _viSkill->speed;
		}
		else
		{

			_viSkill->x -= cosf(_viSkill->angle) * _viSkill->speed;
			_viSkill->y -= -sinf(_viSkill->angle) * _viSkill->speed;
		}
		_viSkill->rc = RectMakeCenter(_viSkill->x, _viSkill->y,
			_viSkill->skillImage->getFrameWidth(),
			_viSkill->skillImage->getFrameHeight());
		if (_viSkill->_time > 200)
		{
				float _rx = (_viSkill->rc.right + _viSkill->rc.left) / 2;
				float _ry = (_viSkill->rc.bottom + _viSkill->rc.top) / 2;	
			_viSkill->_time = 0;
			_x2 = 0;
			PARTICLEMANAGER->play("¹öºíÆã", _rx, _ry, _angle);
			SAFE_RELEASE(_viSkill->skillImage);
			SAFE_DELETE(_viSkill->skillImage);
			_viSkill = _vSkill.erase(_viSkill);
		}
		else ++_viSkill;
		//»ç°Å¸®º¸´Ù ´õ ¸Ö¸® ³ª°¡¸é(?)
		//if (_range < getDistance(_viSkill->x, _viSkill->y, _viSkill->fireX, _viSkill->fireY))
		//{

		//	float _rx = (_viSkill->rc.right + _viSkill->rc.left) / 2;
		//	float _ry = (_viSkill->rc.bottom + _viSkill->rc.top) / 2;

		//	_go = false;
		//	PARTICLEMANAGER->play("¾óÀ½Æã", _rx, _ry, _angle);
		//	SAFE_RELEASE(_viSkill->skillImage);
		//	SAFE_DELETE(_viSkill->skillImage);
		//	_viSkill = _vSkill.erase(_viSkill);
		//}
		//else ++_viSkill;

	}
}

void bubble::moveGo()
{
	_go = true;
}

void bubble::removeSkill(int arrNum)
{
	_vSkill[arrNum].skillImage->release();
	_vSkill.erase(_vSkill.begin() + arrNum);


}
