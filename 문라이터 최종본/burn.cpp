#include "stdafx.h"
#include "burn.h"

HRESULT burn::init(int skillMax, float range)
{
	_SkillMax = skillMax;
	_range = range;
	_x2 = 0;
	return S_OK;
}

void burn::release()
{
}

void burn::update()
{
	move();
}

void burn::render()
{

	for (_viSkill = _vSkill.begin(); _viSkill != _vSkill.end(); ++_viSkill)
	{

		DTDMANAGER->setRotation(-_angle, _viSkill->x, _viSkill->y);
		_viSkill->skillImage->frameRender(
			_viSkill->rc.left,
			_viSkill->rc.top,
			_viSkill->skillImage->getFrameX(), 0);
		DTDMANAGER->resetRotation();
		//DTDMANAGER->Rectangle(_viSkill->rc);
		//_viSkill->count++;
		_viSkill->skillImage->setFrameX(0);

		if (_viSkill->count % 5 == 0)
		{
		//	_viSkill->skillImage->setFrameX(_viSkill->skillImage->getFrameX() + 1);

			//최대 프레임보다 커지면
			if (_viSkill->skillImage->getFrameX() >= _viSkill->skillImage->getMaxFrameX())
			{
				_viSkill->skillImage->setFrameX(0);

			}

			_viSkill->count = 0;
		}
	}

}

void burn::fire(float x, float y,  int frame, float angle)
{
	if (_SkillMax < _vSkill.size()) return;

	tagburn Skill;
	ZeroMemory(&Skill, sizeof(tagburn));
	_angle = angle;
	_frame = frame;
	Skill.skillImage = new dImage;
	Skill.skillImage->init(L"skill/화상1.png", (int)192, 46, 4, 1);
	Skill.speed = 10.0f;
	Skill.angle = angle * PI / 180;
	Skill.x = Skill.fireX = x;
	Skill.y = Skill.fireY = y;
	Skill.rc = RectMakeCenter(Skill.x, Skill.y,
		Skill.skillImage->getFrameWidth(),
		Skill.skillImage->getFrameHeight());

	_vSkill.push_back(Skill);
}

void burn::move()
{
	for (_viSkill = _vSkill.begin(); _viSkill != _vSkill.end();)
	{
		_viSkill->_time++;
		//_viSkill->x += _viSkill->speed;
		//_viSkill->x += cosf(_viSkill->angle) * _viSkill->speed;
		//_viSkill->y += -sinf(_viSkill->angle) * _viSkill->speed;
		_viSkill->rc = RectMakeCenter(_viSkill->x, _viSkill->y,
			_viSkill->skillImage->getFrameWidth(),
			_viSkill->skillImage->getFrameHeight());
		if (_viSkill->_time > 100)
		{
			_viSkill->_time = 0;
			_x2 = 0;
			SAFE_RELEASE(_viSkill->skillImage);
			SAFE_DELETE(_viSkill->skillImage);
			_viSkill = _vSkill.erase(_viSkill);
		}
		else ++_viSkill;
		//사거리보다 더 멀리 나가면(?)
		//if (_range < getDistance(_viSkill->x, _viSkill->y, _viSkill->fireX, _viSkill->fireY))
		//{

		//	float _rx = (_viSkill->rc.right + _viSkill->rc.left) / 2;
		//	float _ry = (_viSkill->rc.bottom + _viSkill->rc.top) / 2;



		//	SAFE_RELEASE(_viSkill->skillImage);
		//	SAFE_DELETE(_viSkill->skillImage);
		//	_viSkill = _vSkill.erase(_viSkill);
		//}
		//else ++_viSkill;

	}
}

void burn::removeSkill(int arrNum)
{
	_vSkill[arrNum].skillImage->release();
	_vSkill.erase(_vSkill.begin() + arrNum);


}
