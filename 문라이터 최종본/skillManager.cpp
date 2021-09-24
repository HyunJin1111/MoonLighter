#include "stdafx.h"
#include "skillManager.h"

HRESULT skillManager::init()
{
	/*_skill = new skill;
	_skill->init(300, 300);

	_fireCross = new fireCross;
	_fireCross->init(300, 500);

	_fireDash = new fireDash;
	_fireDash->init(300, 500);

	_iceSpear = new iceSpear;
	_iceSpear->init(300, 900);
	
	_waterZone = new waterZone;
	_waterZone->init(300, 500);

	_bubble = new bubble;
	_bubble->init(300, 400);

	_LightningWave = new LightningWave;
	_LightningWave->init(300, 400);

	_LightningJump = new LightningJump;
	_LightningJump->init(300, 400);

	_LightBeam = new LightBeam;
	_LightBeam->init(300, 400);

	_iceWall = new iceWall;
	_iceWall->init(300, 400);

	_frostWall = new frostWall;
	_frostWall->init(300, 400);*/

	return S_OK;
}

void skillManager::release()
{
}

void skillManager::update()
{
	/*_skill->update();
	_fireCross->update();
	_fireDash->update();
	_iceSpear->update();
	_waterZone->update();
	_bubble->update();
	_LightningWave->update();
	_LightningJump->update();
	_LightBeam->update();
	_iceWall->update();
	_frostWall->update();*/
}

void skillManager::render()
{
	/*_skill->render();
	_fireCross->render();
	_fireDash->render();
	_iceSpear->render();
	_waterZone->render();
	_bubble->render();
	_LightningWave->render();
	_LightningJump->render();
	_LightBeam->render();
	_iceWall->render();
	_frostWall->render();*/
}

void skillManager::fire(int SkillNum, float x, float y, float angle)
{
	/*_skillType = SkillNum;

	if(_skillType == 0)
	{
		_skill->fire(x,y, angle);
	}
	if (_skillType == 1)
	{
		_fireCross->fire(x, y, angle);
	}
	if (_skillType == 2)
	{
		_fireDash->fire(x, y, angle);
	}
	if (_skillType == 3)
	{
		_iceSpear->fire(x, y, angle);
	}
	if (_skillType == 4)
	{
		_waterZone->fire(x, y, angle);
	}
	if (_skillType == 5)
	{
		_bubble->fire(x, y, angle);
	}
	if (_skillType == 6)
	{
		_LightningWave->fire(x, y, angle);
	}
	if (_skillType == 7)
	{
		_LightningJump->fire(x, y, angle);
	}
	if (_skillType == 8)
	{
		_LightBeam->fire(x, y, angle);
	}
	if (_skillType == 9)
	{
		_iceWall->fire(x, y, angle);
	}
	if (_skillType == 10)
	{
		_frostWall->fire(x, y, angle);
	}*/
}

void skillManager::keyUP()
{

	/*if (_skillType == 3)
	{
		_iceSpear->moveGo();
	}*/

}

