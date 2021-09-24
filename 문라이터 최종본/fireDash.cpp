#include "stdafx.h"
#include "fireDash.h"

HRESULT fireDash::init(int skillMax, float range)
{
	_burn = new burn;
	_burn->init(50, 5);
	_SkillMax = skillMax;
	_range = range;
	_x2 = 0;
	return S_OK;
}

void fireDash::release()
{
}

void fireDash::update()
{
	move();
	_burn->update();
}

void fireDash::render()
{

	for (_viSkill = _vSkill.begin(); _viSkill != _vSkill.end(); ++_viSkill)
	{
		float _rx = (_viSkill->rc.right + _viSkill->rc.left) / 2;
		float _ry = (_viSkill->rc.bottom + _viSkill->rc.top) / 2 + 40;


		int _scale = 0;

		PARTICLEMANAGER->play("화염구펑", _rx , _ry + 10, 0);
		_burn->fire(_rx, _ry, 0, 0);




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

			//최대 프레임보다 커지면
			//if (_viSkill->skillImage->getFrameX() >= _viSkill->skillImage->getMaxFrameX())
			//{
			//	_viSkill->skillImage->setFrameX(0);


			//}

			_viSkill->count = 0;
		}
	}
	_burn->render();
}

void fireDash::fire(float x, float y, float angle)
{
	if (_SkillMax < _vSkill.size()) return;

	tagfireDash Skill;
	ZeroMemory(&Skill, sizeof(tagfireDash));
	_angle = angle;
	Skill.skillImage = new dImage;
	Skill.skillImage->init(L"skill/화염대쉬.png", (int)201, 85, 3, 1);
	Skill.speed = 10.0f;
	Skill.angle = angle * PI / 180;
	Skill.x = Skill.fireX = x;
	Skill.y = Skill.fireY = y;
	Skill.rc = RectMakeCenter(Skill.x, Skill.y,
		Skill.skillImage->getFrameWidth(),
		Skill.skillImage->getFrameHeight());

	_vSkill.push_back(Skill);
}


void fireDash::move()
{
	for (_viSkill = _vSkill.begin(); _viSkill != _vSkill.end();)
	{
		_time++;
		//_viSkill->x += _viSkill->speed;
		//_viSkill->x += cosf(_viSkill->angle) * _viSkill->speed;
		//_viSkill->y += -sinf(_viSkill->angle) * _viSkill->speed;
		_viSkill->rc = RectMakeCenter(_viSkill->x, _viSkill->y - 40,
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
		//사거리보다 더 멀리 나가면(?)
		/*if (_range < getDistance(_viSkill->x, _viSkill->y, _viSkill->fireX, _viSkill->fireY))
		{

			float _rx = (_viSkill->rc.right + _viSkill->rc.left) / 2;
			float _ry = (_viSkill->rc.bottom + _viSkill->rc.top) / 2;
			_burn->fire(_rx, _ry, 0, 0);
			PARTICLEMANAGER->play("화염펑", _rx, _ry, 0);
			SAFE_RELEASE(_viSkill->skillImage);
			SAFE_DELETE(_viSkill->skillImage);
			_viSkill = _vSkill.erase(_viSkill);
		}*/
		//else ++_viSkill;

	}
}

void fireDash::removeSkill(int arrNum)
{
	_vSkill[arrNum].skillImage->release();
	_vSkill.erase(_vSkill.begin() + arrNum);


}
